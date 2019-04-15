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

	ThreadedWorkerQueue(ThreadedWorkerQueue&& other) = delete;
	ThreadedWorkerQueue& operator=(ThreadedWorkerQueue&& other) = delete;

	~ThreadedWorkerQueue() = default;

	void enqueue(T action);
	T dequeue();

	const T& peek();

	bool empty() {
		return queue_.empty();
	}

	void wait() {
		std::unique_lock<std::mutex> lock( mQueue_ );
		cvQueue_.wait( lock );
	}

	void notify() {
		cvQueue_.notify_one();
	}

private:
	std::deque<T> queue_;

	std::mutex mQueue_ {};
	std::condition_variable cvQueue_{};
};
