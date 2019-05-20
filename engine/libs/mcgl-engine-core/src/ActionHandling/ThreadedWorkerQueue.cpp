#include "ActionHandling/ThreadedWorkerQueue.h"

#include "ActionHandling/Action/Action.h"


template<>
ThreadedWorkerQueue<action::Action_ptr>::ThreadedWorkerQueue() {
}

template<>
ThreadedWorkerQueue<action::Action_ptr>::~ThreadedWorkerQueue() {
	if( isRunning_.exchange( false ) ) {
		workerThread_.join();
	}
}

template<>
void ThreadedWorkerQueue<action::Action_ptr>::start() {
	if( isRunning_.exchange( true ) ) {
		return;
	}

	workerThread_ = std::thread( [this]() {
		while( isRunning_ ) {

			if( workerQueue_.empty() ) {
				std::unique_lock<std::mutex> lock( mQueue_ );
				cvQueue_.wait( lock );
			}

			if( !isRunning_ ) {
				break;
			}

			invokeCallback( dequeue().get() );
		}
	} );
}

template<>
void ThreadedWorkerQueue<action::Action_ptr>::stop() {
	if( isRunning_.exchange( false ) ) {
		cvQueue_.notify_one();
		workerThread_.join();
	}
}

template<>
void ThreadedWorkerQueue<action::Action_ptr>::enqueue(action::Action_ptr&& action) {
	std::lock_guard<std::mutex> lock(mQueue_);

	workerQueue_.push_back( std::move(action) );
	cvQueue_.notify_one();
}

template<>
action::Action_ptr ThreadedWorkerQueue<action::Action_ptr>::dequeue() {
	std::lock_guard<std::mutex> lock(mQueue_);

	auto action = std::move( workerQueue_.front() );
	workerQueue_.pop_front();
	return action;
}

template<>
void ThreadedWorkerQueue<action::Action_ptr>::invokeCallback( action::Action* action ) {
	if( callback_ ) {
		callback_( action );
	}
}
