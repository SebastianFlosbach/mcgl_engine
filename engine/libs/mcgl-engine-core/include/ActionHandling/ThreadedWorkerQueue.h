#pragma once

#include <atomic>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

#include "ActionHandling/Action/Action.h"


typedef std::function<void(action::Action* action)> MCGL_WORKER_QUEUE_CALLBACK;

template<typename T>
class ThreadedWorkerQueue {
public:
	ThreadedWorkerQueue();

	ThreadedWorkerQueue(const ThreadedWorkerQueue& other) = delete;
	ThreadedWorkerQueue& operator=(const ThreadedWorkerQueue& other) = delete;

	ThreadedWorkerQueue(ThreadedWorkerQueue&& other) = delete;
	ThreadedWorkerQueue& operator=(ThreadedWorkerQueue&& other) = delete;

	~ThreadedWorkerQueue();

	void start();
	void stop();

	void enqueue(T&& action);

	void registerCallback( MCGL_WORKER_QUEUE_CALLBACK callback ) {
		callback_ = callback;
	}

	void deregisterCallback( MCGL_WORKER_QUEUE_CALLBACK callback ) {
		callback_ = NULL;
	}

private:
	std::thread workerThread_;

	MCGL_WORKER_QUEUE_CALLBACK callback_;

	std::atomic_bool isRunning_{ false };

	std::deque<T> workerQueue_;

	std::mutex mQueue_{};
	std::condition_variable cvQueue_{};
	
	T dequeue();
	inline void invokeCallback( action::Action* action );
};
