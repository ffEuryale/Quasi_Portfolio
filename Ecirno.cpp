#include "stdafx.h"
#include "Ecirno.h"

HRESULT Ecirno::init()
{
	return S_OK;
}

HRESULT Ecirno::init(const char* imageName, POINT position, int maxMoveCount, int moveDir[2])
{
	_currentFrameX = _currentFrameY = 0;
	_count = _fireCount = 0;

	_enemyImage = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(position.x, position.y,
		_enemyImage->getFrameWidth(),
		_enemyImage->getFrameHeight());

	_maxMoveCount = _moveCount = maxMoveCount;
	_moveDir[0] = moveDir[0];
	_moveDir[1] = moveDir[1];

	_isAttack = true;

	return S_OK;
}

void Ecirno::release()
{

}

void Ecirno::update()
{
	if (_isAttack)
	{
		switch (_type)
		{
			case CIRCLE:
			{
				if (_attackTime == 0)
				{
					if (_attackCount == 20)
					{
						_isAttack = false;
						break;
					}
					_attackTime = 60;
					_attackCount++;
	
					for (float angle = _attackCount * 0.07; angle < PI2 + _attackCount * 0.07; angle += 0.23)
					{
						_bullet->fire((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2, angle, 1.0f);
					}
	
				}
				_attackTime--;
			}
			break;
			case FLOWER:
			{
				if (_attackTime == 0)
				{
					for (int i = 0; i < 8; i++)
					{
						_bullet->fire((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2, _attackAngle[i], 0.7f);
						_attackAngle[i] += PI * 0.075;
					}
					_attackTime = 20;
					if (_attackAngle[0] > 3 * PI2)
					{
						_isAttack = false;
						break;
					}
				}
				_attackTime--;
			}
			break;
			case CIRCULARSECTOR:
			{
				if (_attackCount == 15)
				{
					_isAttack = false;
					break;
				}
				if (_attackTime == 0)
				{
					_bullet->fire((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
						getAngle((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
							_sakuya->getSakuyaImage()->getCenterX(),
							_sakuya->getSakuyaImage()->getCenterY()), 3.23f);

					_bullet->fire((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
						getAngle((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
							_sakuya->getSakuyaImage()->getCenterX() - 50, 
							_sakuya->getSakuyaImage()->getCenterY()), 3.21f);
	
					_bullet->fire((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
						getAngle((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
							_sakuya->getSakuyaImage()->getCenterX() + 50, 
							_sakuya->getSakuyaImage()->getCenterY()), 3.21f);
	
					_bullet->fire((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
						getAngle((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
							_sakuya->getSakuyaImage()->getCenterX() - 100,
							_sakuya->getSakuyaImage()->getCenterY()), 3.2f);
	
					_bullet->fire((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
						getAngle((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
							_sakuya->getSakuyaImage()->getCenterX() + 100, 
							_sakuya->getSakuyaImage()->getCenterY()), 3.2f);
	
					_bullet->fire((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
						getAngle((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
							_sakuya->getSakuyaImage()->getCenterX() - 150, 
							_sakuya->getSakuyaImage()->getCenterY()), 3.19f);
	
					_bullet->fire((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
						getAngle((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
							_sakuya->getSakuyaImage()->getCenterX() + 150, 
							_sakuya->getSakuyaImage()->getCenterY()), 3.19f);

					_bullet->fire((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
						getAngle((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
							_sakuya->getSakuyaImage()->getCenterX() - 200,
							_sakuya->getSakuyaImage()->getCenterY()), 3.17f);

					_bullet->fire((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
						getAngle((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
							_sakuya->getSakuyaImage()->getCenterX() + 200,
							_sakuya->getSakuyaImage()->getCenterY()), 3.17f);
	
					_attackTime = 40;
					_attackCount++;
				}
				_attackTime--;
			}
			break;
		}
	}
	else
	{
		_count++;

		if (_count % 2 == 0)
		{
			if (_currentFrameX >= _enemyImage->getMaxFrameX()) _currentFrameX = 0;
			_enemyImage->setFrameX(_currentFrameX);
			_currentFrameX++;
			_count = 0;
		}
		move();
	}

	//====================================================
	cout << "CirnoCount: " << _count << "	fireCount: " << _fireCount <<
		"	attackTime: " << _attackTime << endl;
	//====================================================
}

void Ecirno::render()
{
	draw();
}

void Ecirno::move()
{
	_moveCount--;
	if (_moveCount <= 0)
	{
		_moveCount = _maxMoveCount;
		_moveDir[0] = -_moveDir[0];
		_moveDir[1] = -_moveDir[1];
	}
	_rc.left += _moveDir[0];
	_rc.right += _moveDir[0];
	_rc.top += _moveDir[1];
	_rc.bottom += _moveDir[1];
}

void Ecirno::draw()
{
	_enemyImage->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

bool Ecirno::bulletCountFire()
{
	if (_isAttack) return false;
	_fireCount++;

	if (_fireCount % 100 == 0)
	{
		_fireCount = 0;

		return true;
	}

	return false;
}

void Ecirno::attack(sakuya* name, bullet* bullet)
{
	_bullet = bullet;
	_sakuya = name;
	_isAttack = true;
	_attackCount = 0;
	_attackTime = 0;
	int random = RND->getInt(100);
	if (random < 33)
	{
		_attackAngle[0] = 0;
		_attackAngle[1] = PI * 0.25;
		_attackAngle[2] = PI * 0.5;
		_attackAngle[3] = PI * 0.75;
		_attackAngle[4] = PI;
		_attackAngle[5] = PI * 1.25;
		_attackAngle[6] = PI * 1.5;
		_attackAngle[7] = PI * 1.75;
		_type = FLOWER;
	}
	else if (random < 66)
	{
		_type = CIRCLE;
	}
	else
	{
		_type = CIRCULARSECTOR;
	}
}