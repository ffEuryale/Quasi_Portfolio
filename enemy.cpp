#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(const char * imageName, POINT position, int maxMoveCount, int moveDir[2])
{
	_currentFrameX = _currentFrameY = 0;
	_count = _fireCount = 0;

	//���ʹ� �̹����� Ű������ �־�����
	_enemyImage = IMAGEMANAGER->findImage(imageName);

	_rndFireCount = RND->getFromIntTo(1, 150);

	_rc = RectMakeCenter(position.x, position.y,
		_enemyImage->getFrameWidth(),
		_enemyImage->getFrameHeight());

	_maxMoveCount = maxMoveCount;
	_moveCount = 0;
	_moveDir[0] = moveDir[0];
	_moveDir[1] = moveDir[1];

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	_count++;

	if (_count % 5 == 0)
	{
		if (_currentFrameX >= _enemyImage->getMaxFrameX()) _currentFrameX = 0;
		_enemyImage->setFrameX(_currentFrameX);
		_currentFrameX++;
		_count = 0;
	}
	move();

}

void enemy::render()
{
	draw();
}

void enemy::move()
{
	_moveCount++;
	if (_moveCount == _maxMoveCount)
	{
		_moveCount = 0;
		_moveDir[0] = -_moveDir[0];
		_moveDir[1] = -_moveDir[1];
	}
	_rc.left += _moveDir[0];
	_rc.right += _moveDir[0];
	_rc.top += _moveDir[1];
	_rc.bottom += _moveDir[1];
}

void enemy::draw()
{
	//�̹����� 1���ε� ��Ʈ ��ġ�� ���� �ٸ��� ��ġ��������
	//��Ʈ�� ������� �׸��� ������ 1�尡���� ����� ��밡���ϴ�

	_enemyImage->frameRender(getMemDC(), _rc.left, _rc.top,
		_currentFrameX, _currentFrameY);
}

bool enemy::bulletCountFire()
{
	_fireCount++;

	if (_fireCount % _rndFireCount == 0)
	{
		_rndFireCount = RND->getFromIntTo(1, 150);
		_fireCount = 0;

		return true;
	}
	return false;
}

void enemy::attack(sakuya * name, bullet * bullet)
{
	bullet->fire((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
		getAngle((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
			name->getSakuyaImage()->getCenterX(),
			name->getSakuyaImage()->getCenterY()), 3.0f);
}
