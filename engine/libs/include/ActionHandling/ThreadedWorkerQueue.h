#pragma once

#include <atomic>
#include <mutex>
#include <queue>


template<typename T>
class ThreadedWorkerQueue {
public:
	ThreadedWorkerQueue() = default;

	ThreadedWorkerQueue(const ThreadedWorkerQueue& other) = delete;
	ThreadedWorkerQueue& operator=(const ThreadedWorkerQueue& other) = delete;

	ThreadedWorkerQueue(ThreadedWorkerQueue&& other) {
		*this = std::move(other);
	}

	ThreadedWorkerQueue& operator=(ThreadedWorkerQueue&& other) {
		this->workerThread_ = std::move(other.workerThread_);
		this->actionQueue_ = std::move(other.actionQueue_);
		this->actionCallback_ = std::move(other.actionCallback_)
		this->mQueue_ = std::move(other.mQueue_);
		this->cvActionAvailable_ = std::move(other.cvActionAvailable_);
		this->actionAvailable_ = other.actionAvailable_;
		this->isRunning_ = other.isRunning_;

		return *this;
	}

	~ThreadedWorkerQueue() {
		if ( workerThread_.joinable() ) {
			workerThread_.join();
		}
	}

	void enqueue( T action ) {
		std::unique_lock<std::mutex> lock( mQueue_ );
		actionQueue_.push_back( std::move( action ) );
		actionAvailable_ = true;
		cvActionAvailable_.notify_one();
	}

	T dequeue() {
		std::unique_lock<std::mutex> lock( mQueue_ );
		auto action = std::move( actionQueue_.front() );
		actionQueue_.pop_front();
		if ( actionQueue_.empty() ) {
			actionAvailable_ = false;
		}
		return action;
	}

	T peek() {
		std::lock_guard<std::mutex> lock( mQueue_ );
		return actionQueue_.front();
	} 

	bool isRunning() {
		return isRunning_;
	}

	void start( void(*actionCallback)( const T& action ) ) {
		if ( isRunning_.exchange( true ) ) {
			return;
		}

		actionCallback_ = actionCallback;

		workerThread_ = std::thread( [this]() {
			while ( isRunning_ ) {				
				if ( !actionAvailable_ ) {
					std::unique_lock<std::mutex> lock( mQueue_ );
					cvActionAvailable_.wait( lock, [this]() { return actionAvailable_; } );
				}
				
				actionCallback_( dequeue() );
			}
		} );
	}

	void stop() {
		std::lock_guard<std::mutex> lock( mQueue_ );
		
		if ( !isRunning_.exchange( false ) ) {
			return;
		}

		workerThread_.join();
	}

private:
	std::deque<T> actionQueue_;

	std::mutex mQueue_ {};
	std::condition_variable cvActionAvailable_ {};
	bool actionAvailable_;

	std::thread workerThread_;
	std::atomic_bool isRunning_;

	void( *actionCallback_ )(const T& action);
};
