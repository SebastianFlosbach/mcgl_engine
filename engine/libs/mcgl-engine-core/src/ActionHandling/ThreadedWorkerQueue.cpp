#include "ActionHandling/ThreadedWorkerQueue.h"

#include "ActionHandling/Action/Action.h"

template<>
void ThreadedWorkerQueue<action::Action_ptr>::enqueue(action::Action_ptr action) {
	std::lock_guard<std::mutex> lock(mQueue_);
	queue_.push_back(std::move(action));
	notify();
}

template<>
action::Action_ptr ThreadedWorkerQueue<action::Action_ptr>::dequeue() {
	std::lock_guard<std::mutex> lock(mQueue_);

	auto action = std::move(queue_.front());
	queue_.pop_front();
	return action;
}

template<>
const action::Action_ptr& ThreadedWorkerQueue<action::Action_ptr>::peek() {
	std::lock_guard<std::mutex> lock(mQueue_);
	return queue_.front();
}
