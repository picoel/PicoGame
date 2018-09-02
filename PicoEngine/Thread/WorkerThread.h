#pragma once

#include "PicoEngineCore/Util/Type.h"
#include "PicoEngineCore/Util/List.h"
#include "PicoEngineCore/Util/Mutex.h"
#include "PicoEngineCore/System/System.h"

#include <atomic>
#include <future>
#include <thread>

namespace PicoEngine
{
	class WorkerThread
	{
	public:
		WorkerThread( uint64 _uWorker )
			: m_pcWorkers()
			, m_pcTasks()
			, m_mutexTasks()
		{
			for( uint64 ii = 0; ii < _uWorker; ++ii )
			{
				m_pcWorkers.emplace_back( new Worker( this ) );
			}
		}

		virtual ~WorkerThread()
		{
			lock_guard<mutex> lock( m_mutexTasks );
			m_pcTasks.clear();
			for( auto& rpcWorker : m_pcWorkers )
			{
				if( rpcWorker )
				{
					rpcWorker->End();
				}
			}
		}

		template<typename T>
		std::future<T> Request( std::function<T()> _func )
		{
			lock_guard<mutex> lock( m_mutexTasks );
			std::promise<T> promise;
			std::future<T> future = promise.get_future();
			m_pcTasks.emplace_back( new Task<T>( _func, std::move( promise ) ) );
			return future;
		}

		bool IsWait() const
		{
			return std::all_of(m_pcWorkers.cbegin(), m_pcWorkers.cend(), 
				[]( const std::unique_ptr<Worker>& _rpcWorker )
				{
					return _rpcWorker ? _rpcWorker->IsWait() : true;
				}
			);
		}

	private:
		class ITask
		{
		public:
			ITask(){}
			virtual ~ITask(){}

			virtual void Run() = 0;
		};

		template<typename T>
		class Task : public ITask
		{
		public:
			Task( std::function<T()> _func, std::promise<T>&& _promise )
				: ITask()
				, m_func( _func )
				, m_promise( std::move( _promise ) )
			{
			}

			virtual ~Task()
			{
			}

			virtual void Run() override
			{
				m_promise.set_value( m_func() );
			}

		private:
			std::function<T()> m_func;
			std::promise<T> m_promise;
		};

		class Worker
		{
		public:
			Worker(WorkerThread* _pcWorkerThread)
				: m_pcWorkerThread( _pcWorkerThread )
				, m_bEndRequest( false )
				, m_bWait( true )
				, m_thread( [this](){ Run(); } )
			{
			}

			virtual ~Worker()
			{
			}

			void Run()
			{
				m_bEndRequest = false;
				while( !m_bEndRequest )
				{
					std::unique_ptr<ITask> pcTask( std::move( m_pcWorkerThread->GetTask() ) );
					if( !pcTask )
					{
						m_bWait = true;
						std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
						continue;
					}

					m_bWait = false;
					pcTask->Run();
				}
			}

			bool IsWait() const
			{
				return m_bWait;
			}

			void End()
			{
				m_bEndRequest = true;
				m_thread.join();
			}

		private:
			WorkerThread* m_pcWorkerThread;
			std::atomic_bool m_bEndRequest;
			std::atomic_bool m_bWait;
			std::thread m_thread;
		};

	private:
		std::unique_ptr<ITask> GetTask()
		{
			lock_guard<mutex> lock( m_mutexTasks );
			if( m_pcTasks.empty() )
			{
				std::unique_ptr<ITask> tmp(nullptr);
				return std::move( tmp );
			}

			std::unique_ptr<ITask> pcTask = std::move( m_pcTasks.front() );
			m_pcTasks.pop_front();
			return std::move( pcTask );
		}

	private:
		vector<std::unique_ptr<Worker> > m_pcWorkers;

		deque< std::unique_ptr<ITask> > m_pcTasks;
		mutex m_mutexTasks;
	};

	template<>
	void WorkerThread::Task<void>::Run()
	{
		m_func();
		m_promise.set_value();
	}

	class WorkerThreadSystem : public ISystem
	{
	public:
		WorkerThreadSystem( uint64 _uWorkers )
			: ISystem()
			, m_cWorkerThread( _uWorkers )
		{
		}
		virtual ~WorkerThreadSystem()
		{
		}

		template<typename T>
		std::future<T> Request( std::function<T()> _func )
		{
			return m_cWorkerThread.Request( _func );
		}

		virtual void LoopFirst() override{}
		virtual void LoopMiddle() override{}
		virtual void LoopLast() override{}

	protected:
		WorkerThread m_cWorkerThread;
	};

	class SyncWorkerThreadSystem : public WorkerThreadSystem
	{
	public:
		SyncWorkerThreadSystem( uint64 _uWorkers )
			: WorkerThreadSystem( _uWorkers )
		{
		}
		virtual ~SyncWorkerThreadSystem()
		{
		}

		virtual void LoopLast() override
		{
			while( !m_cWorkerThread.IsWait() )
			{
				std::this_thread::sleep_for( std::chrono::nanoseconds( 100 ) );
			}
		}
	};
}