#pragma once

#include <atomic>
#include <mutex>
#include <queue>


template<typename T>
class ThreadedWorkerQueue {
public:
	ThreadedWorkerQueue() = default;

	void enqueue( T action ) {
		std::lock_guard<std::mutex>( mQueue_ )
		actionQueue_.push_back( std::move( action ) );
		actionAvailable_ = true;
		cvActionAvailable_.notify_one();
	}

	T dequeue() {
		std::lock_guard<std::mutex>( mQueue_ );
		auto action = actionQueue_.front();
		actionQueue_.pop_front();
		if ( actionQueue_.empty() ) {
			actionAvailable_ = false;
		}
		return action;
	}

	T peek() {
		std::lock_guard<std::mutex>( mQueue_ );
		return actionQueue_.front();
	} 

	bool isRunning() {
		return isRunning_;
	}

	void start( void(*actionCallback)( T action ) ) {
		if ( isRunning_.exchange( true ) ) {
			return;
		}

		workerThread_ = std::thread( [this]() {
			while ( isRunning_ ) {
				std::unique_lock<std::mutex>( mQueue_ );
				
				if ( !actionAvailable_ ) {
					cvActionAvailable_.wait( mQueue_, []() { return actionAvailable_; } );
				}
				
				actionCallback( dequeue() );
			}
		})
	}

	void stop() {
		std::lock_guard<std::mutex>( mQueue_ );
		
		if ( !isRunning_.exchange( false ) ) {
			return;
		}

		workerThread_.join();
	}

private:
	std::deque<T> actionQueue_;

	std::mutex mQueue_;
	std::condition_variable cvActionAvailable_;
	bool actionAvailable_;

	std::thread workerThread_;
	std::atomic_bool isRunning_;

};
