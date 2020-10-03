#include "stdafx.h"
#include "bullets.h"


HRESULT bullet::init(const char * imageName, float range)
{
	_imageName = imageName;
	_range = range;

	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	move();
}

void bullet::render()
{
	vector<tagBullet> bullets = _opBullet->_objects;
	list<int> usingIndex = _opBullet->_usingIndex;
	set<pair<int, int>> sets;
	
	for (auto it = usingIndex.begin(); it != usingIndex.end(); it++)
	{
		int index = *it;
		pair<int, int> currentLT = make_pair(static_cast<int> (bullets[index].rc.left),
			static_cast<int>(bullets[index].rc.top));
		
		if (sets.find(currentLT) != sets.end()) continue;
		else sets.insert(currentLT);
	}

	for (auto it = sets.begin(); it != sets.end(); it++)
	{
		pair<int, int> LT = *it;
		bullets[0].bulletImage->render(getMemDC(), LT.first, LT.second);
	}
}

void bullet::fire(float x, float y, float angle, float speed)
{
	if (_opBullet->_maxSize <= _opBullet->_usingIndex.size()) return;

	int newIndex = _opBullet->_waitingIndex.front();
	_opBullet->_waitingIndex.pop();

	_opBullet->_objects[newIndex].bulletImage = IMAGEMANAGER->findImage(_imageName);
	_opBullet->_objects[newIndex].speed = speed;
	_opBullet->_objects[newIndex].radius = _opBullet->_objects[newIndex].bulletImage->getWidth() / 2;
	_opBullet->_objects[newIndex].x = _opBullet->_objects[newIndex].fireX = x;
	_opBullet->_objects[newIndex].y = _opBullet->_objects[newIndex].fireY = y;
	_opBullet->_objects[newIndex].angle = angle;

	_opBullet->_objects[newIndex].rc = RectMakeCenter(_opBullet->_objects[newIndex].x, _opBullet->_objects[newIndex].y,
		_opBullet->_objects[newIndex].bulletImage->getWidth(), _opBullet->_objects[newIndex].bulletImage->getHeight());
	
	_opBullet->_usingIndex.push_back(newIndex);

	SOUNDMANAGER->play("e_Shot", 0.08f);

}

void bullet::move()
{
	list<int> usingIndex = _opBullet->_usingIndex;

	for (auto it = usingIndex.begin(); it != usingIndex.end(); it++)
	{
		int index = *it;
		_opBullet->_objects[index].x += cosf(_opBullet->_objects[index].angle)*_opBullet->_objects[index].speed;
		_opBullet->_objects[index].y -= sinf(_opBullet->_objects[index].angle)*_opBullet->_objects[index].speed;

		_opBullet->_objects[index].rc = RectMakeCenter(_opBullet->_objects[index].x, _opBullet->_objects[index].y, 
			_opBullet->_objects[index].bulletImage->getWidth(), _opBullet->_objects[index].bulletImage->getHeight());

		if (_range < getDistance(_opBullet->_objects[index].x, _opBullet->_objects[index].y,
			_opBullet->_objects[index].fireX, _opBullet->_objects[index].fireY))
		{
			removeBullet(index);
		}

	}
}

void bullet::removeBullet(int arrNum)
{
	_opBullet->_usingIndex.remove(arrNum);
	_opBullet->_waitingIndex.push(arrNum);
}

HRESULT knife::init(float range)
{
	_range = range;

	return S_OK;
}

void knife::release()
{

}

void knife::update()
{
	move();
}

void knife::render()
{
	vector<tagBullet> Knife = _opBullet->_objects;
	list<int> usingIndex = _opBullet->_usingIndex;

	for (auto it = usingIndex.begin(); it != usingIndex.end(); it++)
	{
		int index = *it;

		Knife[index].bulletImage->alphaFrameRender(getMemDC(),
			Knife[index].rc.left,
			Knife[index].rc.top,
			Knife[index].bulletImage->getFrameX(),
			0, 100);
		
		Knife[index].count++;

		if (Knife[index].count % 10 == 0)
		{
			Knife[index].bulletImage->setFrameX(Knife[index].bulletImage->getMaxFrameX() + 1);

			if (Knife[index].bulletImage->getFrameX() >= Knife[index].bulletImage->getMaxFrameX())
			{
				Knife[index].bulletImage->setFrameX(0);
			}
			Knife[index].count = 0;
		}
	}
}

void knife::fire(float x, float y)
{
	//총알의 최대갯수보다 더 생성되면 실행하지마라
	if (_opBullet->_maxSize <= _opBullet->_usingIndex.size()) return;

	vector<tagBullet> bullets = _opBullet->_objects;
	int newIndex = _opBullet->_waitingIndex.front();
	_opBullet->_waitingIndex.pop();

	_opBullet->_objects[newIndex].bulletImage = new image;
	_opBullet->_objects[newIndex].bulletImage->init("image/attack.bmp", 0, 0, 18, 29, 2, 1, true, MAGENTA);
	_opBullet->_objects[newIndex].speed = 8.0f;

	_opBullet->_objects[newIndex].x = _opBullet->_objects[newIndex].fireX = x;
	_opBullet->_objects[newIndex].y = _opBullet->_objects[newIndex].fireY = y;
	_opBullet->_objects[newIndex].rc = RectMakeCenter(_opBullet->_objects[newIndex].x, _opBullet->_objects[newIndex].y,
		_opBullet->_objects[newIndex].bulletImage->getFrameWidth(),
		_opBullet->_objects[newIndex].bulletImage->getFrameHeight());

	SOUNDMANAGER->play("p_Shot",0.05f);
	
	_opBullet->_usingIndex.push_back(newIndex);

}

void knife::move()
{
	list<int> usingIndex = _opBullet->_usingIndex;

	for (auto it = usingIndex.begin(); it != usingIndex.end(); it++)
	{
		int currentIndex = *it;

		_opBullet->_objects[currentIndex].y -= _opBullet->_objects[currentIndex].speed;
		_opBullet->_objects[currentIndex].rc = RectMakeCenter(_opBullet->_objects[currentIndex].x, _opBullet->_objects[currentIndex].y, 
			_opBullet->_objects[currentIndex].bulletImage->getFrameWidth(),
			_opBullet->_objects[currentIndex].bulletImage->getFrameHeight());

		if (_range < getDistance(_opBullet->_objects[currentIndex].x, _opBullet->_objects[currentIndex].y,
			_opBullet->_objects[currentIndex].fireX, _opBullet->_objects[currentIndex].fireY))
		{
			removeKnife(currentIndex);
		}
	}

}

void knife::removeKnife(int arrNum)
{
	_opBullet->_usingIndex.remove(arrNum);
	_opBullet->_waitingIndex.push(arrNum);
}
