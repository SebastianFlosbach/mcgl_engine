#pragma once

#include <queue>

template<typename T>
class ThreadedWorkerQueue {
public:
	ThreadedWorkerQueue() = default;

	void enqueue() {

	}

private:
	std::deque actionQueue_;

};
