#include "ActionHandling/ThreadedWorkerQueue.h"

#include "ActionHandling/Action/Action.h"

template<>
void ThreadedWorkerQueue<action::Action_ptr>::enqueue(action::Action_ptr action) {
	std::unique_lock<std::mutex> lock(mQueue_);
	actionQueue_.push_back(std::move(action));
	actionAvailable_ = true;
	cvActionAvailable_.notify_one();
}

template<>
action::Action_ptr ThreadedWorkerQueue<action::Action_ptr>::dequeue() {
	std::unique_lock<std::mutex> lock(mQueue_);
	auto action = std::move(actionQueue_.front());
	actionQueue_.pop_front();
	if (actionQueue_.empty()) {
		actionAvailable_ = false;
	}
	return action;
}

template<>
action::Action_ptr& ThreadedWorkerQueue<action::Action_ptr>::peek() const {
	std::lock_guard<std::mutex> lock(mQueue_);
	return actionQueue_.front();
}

template<>
void ThreadedWorkerQueue<action::Action_ptr>::start(void(*actionCallback)(const action::Action_ptr& action)) {
	if (isRunning_.exchange(true)) {
		return;
	}

	actionCallback_ = actionCallback;

	workerThread_ = std::thread([this]() {
		while (isRunning_) {
			if (!actionAvailable_) {
				std::unique_lock<std::mutex> lock(mQueue_);
				cvActionAvailable_.wait(lock, [this]() { return actionAvailable_; });
			}

			actionCallback_(dequeue());
		}});
}
