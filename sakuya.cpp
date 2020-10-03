#include "stdafx.h"
#include "sakuya.h"
#include "enemyManager.h"

sakuya::sakuya()
{
}


sakuya::~sakuya()
{
}

HRESULT sakuya::init()
{
	_player = IMAGEMANAGER->addFrameImage("player", "image/charactor-m.bmp", 216, 150, 8, 3, true, MAGENTA);
	
	_hitbox = IMAGEMANAGER->addImage("hitBox", "image/hitBox.bmp", 8, 8, true, MAGENTA);
	_hitbox2 = IMAGEMANAGER->addImage("hitBox2", "image/hitBox2.bmp", 64, 61, true, MAGENTA);
	
	_alphaVal = 0;

	_player->setX(260);
	_player->setY(WINSIZEY / 2 + 200);

	_player->setFrameX(0);

	_hpBar = new progressBar;
	_hpBar->init(_player->getX(), _player->getY() - 10, _player->getFrameWidth(), 10);
	_currentHP = _maxHP = 100;

	_hitbox->setX((_rc.right + _rc.left) / 2);
	_hitbox->setY((_rc.bottom + _rc.top) / 2);

	_hitbox2->setX((_rc.right + _rc.left) / 2);
	_hitbox2->setY((_rc.bottom + _rc.top) / 2);

	_knife = new knife(800);
	_knife->init(WINSIZEY);

	_isSlow = false;

	return S_OK;
}

HRESULT sakuya::init(const char * imageName, POINT position)
{
	_currentFrameX = _currentFrameY = 0;
	_count = 0;

	_player = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(position.x, position.y, _player->getFrameWidth(), _player->getFrameHeight());
	_rchit = RectMakeCenter((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2, _hitbox->getWidth(), _hitbox->getHeight());

	return S_OK;
}

void sakuya::release()
{
}

void sakuya::update()
{
	_count++;
	if (_count % 8 == 0)
	{
		if (_currentFrameX > _player->getMaxFrameX()) _currentFrameX = 0;
		_player->setFrameX(_currentFrameX);
		_currentFrameX++;
		_count = 0;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
	{
		_isSlow = true;
		_alphaVal += 10;
		if (_alphaVal >= 75) _alphaVal = 75;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LSHIFT))
	{
		_isSlow = false;
	}

	_alphaVal -= 5;
	if (_alphaVal <= 0) _alphaVal = 0;

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player->getX() > 40)
	{
		_player->setFrameY(1);
		if (_isSlow)
		{
			_player->setX(_player->getX() + 2.0f);
			_rc.left += 2.0f;
			_rc.right += 2.0f;
		}
		_player->setX(_player->getX() - 3.2f);
		_rc.left -= 3.2f;
		_rc.right -= 3.2f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) &&
		_player->getX() + _player->getFrameWidth() < WINSIZEX - 280)
	{
		_player->setFrameY(2);

		if (_isSlow)
		{
			_player->setX(_player->getX() - 2.0f);
			_rc.left -= 2.0f;
			_rc.right -= 2.0f;
		}
		_player->setX(_player->getX() + 3.2f);
		_rc.left += 3.2f;
		_rc.right += 3.2f;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_player->setX(_player->getX());
		_player->setY(_player->getY());
		_player->setFrameX(0);
		_player->setFrameY(0);
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _player->getY() > 21)
	{
		if (_isSlow)
		{
			_player->setY(_player->getY() + 2.0f);
			_rc.top += 2.0f;
			_rc.bottom += 2.0f;
		}
		_player->setY(_player->getY() - 3.2f);
		_rc.top -= 3.2f;
		_rc.bottom -= 3.2f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && 
		_player->getY() + _player->getFrameHeight() < WINSIZEY - 19)
	{
		if (_isSlow)
		{
			_player->setY(_player->getY() - 2.0f);
			_rc.top -= 2.0f;
			_rc.bottom -= 2.0f;
		}
		_player->setY(_player->getY() + 3.2f);
		_rc.top += 3.2f;
		_rc.bottom += 3.2f;
	}
	static int count = 0;
	if (KEYMANAGER->isStayKeyDown('Z'))
	{
		count++;
		if (count % 5== 0)
		{
			count = 0;
			_knife->fire(_player->getCenterX() - 6, _player->getY() - 10);
			_knife->fire(_player->getCenterX() + 6, _player->getY() - 10);
		}
		if (_currentHP < _maxHP) _currentHP += 0.2f;
	}
	_knife->update();

	_fireCount++;

	_hpBar->setX(_player->getX());
	_hpBar->setY(_player->getY() - 20);

	_hpBar->update();
	_hpBar->setGauge(_currentHP, _maxHP);

	collision();


	if (_currentHP <= 0 && KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		init();
	}
}

void sakuya::render()
{
	_player->alphaFrameRender(getMemDC(), _player->getX(), _player->getY(), _player->getFrameX(), _player->getFrameY(), 200);

	if (_isSlow)
	{
		_hitbox->render(getMemDC(), _player->getCenterX() - 4, _player->getCenterY() - 4);
	}
	
	_hitbox2->alphaRender(getMemDC(), _player->getCenterX() - (_hitbox2->getCenterX() - _hitbox2->getX()), _player->getCenterY() - (_hitbox2->getCenterY() - _hitbox2->getY()), _alphaVal);
	
	_knife->render();

	_hpBar->render();
}

void sakuya::draw()
{
	_player->frameRender(getMemDC(), _rc.left, _rc.top,_currentFrameX, _currentFrameY);
}

void sakuya::collision()
{
	objectPool<tagBullet>* opBullet = _knife->getOpBullet();
	vector<tagBullet> bullets = opBullet->_objects;
	list<int> usingIndex = opBullet->_usingIndex;
	for (int i = 0; i < _em->getVMinion().size(); ++i)
	{
		for (auto it = usingIndex.begin(); it != usingIndex.end(); it++)
		{
			int bulletIndex = *it;
			RECT temp;
			if (IntersectRect(&temp, &bullets[bulletIndex].rc, &_em->getVMinion()[i]->getRect()))
			{
				_knife->removeKnife(bulletIndex);
				
				_em->removeMinion(i);
				SOUNDMANAGER->play("e_Dead", 0.1f);
				break;
			}
		}
	}
}

void sakuya::hitDamage(float damage)
{
	_currentHP -= damage;
}