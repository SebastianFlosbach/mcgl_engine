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
		queue_.empty();
	}

private:
	std::deque<T> queue_;

	std::mutex mQueue_ {};
};
