#pragma once
#include <vector>
#include <queue>
#include <list>
#include "singletonBase.h"

template <typename T>

class objectPool : public singletonBase<T>
{
private:

public:
	int _maxSize;
	vector<T> _objects;
	list<int> _usingIndex;
	queue<int> _waitingIndex;

	objectPool(int maxSize) : _maxSize(maxSize)
	{
		_objects.resize(maxSize);
		for (int i = 0; i < maxSize; i++)
		{
			_waitingIndex.push(i);
		}
	}

	void clear()
	{
		queue<int> empty;
		swap(_waitingIndex, empty);

		for (int i = 0; i < _maxSize; i++)
		{
			_waitingIndex.push(i);
		}
		_usingIndex.clear();
	}
};
