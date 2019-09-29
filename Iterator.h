#pragma once

#include "Queue.h"

template <typename T>
class Iterator
{
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() = 0;
	virtual T& CurrentItem() = 0;
};

template <typename T>
class QueueIterator : public Iterator<T> {
public:
	QueueIterator(Queue<T>& q);
	virtual void First() override;
	virtual void Next() override;
	virtual bool IsDone() override;
	virtual T& CurrentItem() override;
private:
	Queue<T>& queue;
	size_t pos = 0;
};

template <typename T>
QueueIterator<T>::QueueIterator(Queue<T>& q) :
	queue(q) {
	pos = 0;
}

template <typename T>
void QueueIterator<T>::First() {
	pos = 0;
}

template <typename T>
void QueueIterator<T>::Next() {
	++pos;
}

template <typename T>
bool QueueIterator<T>::IsDone() {
	return pos >= queue.Size();
}

template <typename T>
T& QueueIterator<T>::CurrentItem() {
	return queue.Get(pos);
}
