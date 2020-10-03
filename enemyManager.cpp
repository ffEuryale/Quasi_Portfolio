#include "stdafx.h"
#include "enemyManager.h"
#include "sakuya.h"

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	_bullet = new bullet(3000);
	_bullet->init("bullet", 1200);

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}
	minionBulletFire();

	_bullet->update();
	collision();
}

void enemyManager::render()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
	_bullet->render();
}

void enemyManager::setMinion(int stage)
{
	switch (stage)
	{
		case 500:	//기본형 1
		{
			int dir[2] = { 2, 0 };
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					_Enemy1 = new minion;
					_Enemy1->init("enemy1", PointMake(-400 + j * 40, 50 + i * 70), 560, dir);

					_vMinion.push_back(_Enemy1);
				}
			}
		}
		break;
		case 550:	//기본형 2
		{
			{
				int dir[2] = { 3, 0 };
				for (int i = 0; i < 1; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						_Enemy2 = new minion;
						_Enemy2->init("enemy2", PointMake(-680 + j * 80, 80 + i * 30), 560, dir);

						_vMinion.push_back(_Enemy2);
					}
				}
			}
			{
				int dir[2] = { -3, 0 };
				for (int i = 0; i < 1; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						_Enemy2 = new minion;
						_Enemy2->init("enemy2", PointMake(680 + j * 80, 80 + i * 30), 560, dir);

						_vMinion.push_back(_Enemy2);
					}
				}
			}
		}
		break;
		case 600:	//기본형 2
		{
			{
				int dir[2] = { 3, 0 };
				for (int i = 0; i < 1; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						_Enemy2 = new minion;
						_Enemy2->init("enemy2", PointMake(-680 + j * 80, 80 + i * 30), 560, dir);

						_vMinion.push_back(_Enemy2);
					}
				}
			}
			{
				int dir[2] = { -3, 0 };
				for (int i = 0; i < 1; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						_Enemy2 = new minion;
						_Enemy2->init("enemy2", PointMake(680 + j * 80, 80 + i * 30), 560, dir);

						_vMinion.push_back(_Enemy2);
					}
				}
			}
		}
		break;
		case 620:	//기본형 1 + 좌우
		{
			{
				int dir[2] = { -2, 0 };
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						_Enemy1 = new minion;
						_Enemy1->init("enemy1", PointMake(560 + j * 40, 50 + i * 70), 400, dir);

						_vMinion.push_back(_Enemy1);
					}
				}
			}
		}
		break;
		case 750:	//기본형 3
		{
			{

				int dir[2] = { 0, 1 };
				for (int i = 0; i < 2; i++)
				{
					_EnemyE1 = new minion;
					_EnemyE2 = new minion;
					_EnemyE1->init("enemyE", PointMake(70 + i * 30, -80), 400, dir);
					_EnemyE2->init("enemyE", PointMake(460 + i * 30, -80), 400, dir);

					_vMinion.push_back(_EnemyE1);
					_vMinion.push_back(_EnemyE2);
				}
			}
		}
		break;
		case 1050:	//치르노 + 전면 책 도배 + 기본형 3
		{
			{
				int dir[2] = { 1, 0 };
				for (int i = 0; i < 1; i++)
				{
					for (int j = 0; j < 40; j++)
					{
						_Enemy3 = new enemy;
						_Enemy3->init("enemyB", PointMake(180 + j * 5, 200 + i * 0), 1, dir);

						_vMinion.push_back(_Enemy3);
					}
				}
			}
			{
				int dir[2] = { 0, 1 };
				for (int i = 0; i < 2; i++)
				{
					_EnemyE1 = new minion;
					_EnemyE2 = new minion;
					_EnemyE1->init("enemyE", PointMake(70 + i * 30, -80), 400, dir);
					_EnemyE2->init("enemyE", PointMake(460 + i * 30, -80), 400, dir);

					_vMinion.push_back(_EnemyE1);
					_vMinion.push_back(_EnemyE2);
				}
			}
			{
				int dir[2] = { 0, 1 };
				_cirno = new Ecirno;
				_cirno->init("cirno", PointMake(250, 150), 100, dir);

				_vMinion.push_back(_cirno);
			}
		}
		break;
		case 1500:	//기본형 1 + 좌우
		{
			{
				int dir[2] = { 2, 0 };
				for (int i = 0; i < 2; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						_Enemy1 = new minion;
						_Enemy1->init("enemy1", PointMake(-400 + j * 40, 50 + i * 70), 560, dir);

						_vMinion.push_back(_Enemy1);
					}
				}
			}
			{
				int dir[2] = { -2, 0 };
				for (int i = 0; i < 2; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						_Enemy1 = new minion;
						_Enemy1->init("enemy1", PointMake(560 + j * 40, 50 + i * 70), 400, dir);

						_vMinion.push_back(_Enemy1);
					}
				}
			}
		}
		break;
		case 2000:	//레티 + 기본형 2
		{
			{
				int dir[2] = { 2, 1 };
				_letty = new Ecirno;
				_letty->init("Letty", PointMake(250, 150), 150, dir);

				_vMinion.push_back(_letty);
			}
			{
				int dir[2] = { 1, 1 };
				_letty = new Ecirno;
				_letty->init("Letty", PointMake(250, 150), 150, dir);

				_vMinion.push_back(_letty);
			}
			{
				int dir[2] = { 3, 0 };
				for (int i = 0; i < 1; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						_Enemy2 = new minion;
						_Enemy2->init("enemy2", PointMake(-680 + j * 80, 80 + i * 30), 560, dir);

						_vMinion.push_back(_Enemy2);
					}
				}
			}
			{
				int dir[2] = { -3, 0 };
				for (int i = 0; i < 1; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						_Enemy2 = new minion;
						_Enemy2->init("enemy2", PointMake(680 + j * 80, 80 + i * 30), 560, dir);

						_vMinion.push_back(_Enemy2);
					}
				}
			}
		}
		break;
	}
}

void enemyManager::minionBulletFire()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{

		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();

			if (rc.bottom > 20 && rc.left < 580 && rc.right > 40 && rc.top && WINSIZEY - 19)
			{
				(*_viMinion)->attack(_sakuya, _bullet);
			}
		}
	}

}

void enemyManager::removeMinion(int arrNum)
{
	_vMinion.erase(_vMinion.begin() + arrNum);
}

void enemyManager::hitDamage(int damage)
{
	_HP -= damage;
}

void enemyManager::collision()
{
	objectPool<tagBullet>* opBullet = getBullet()->getOpBullet();
	vector<tagBullet> bullets = opBullet->_objects;
	list<int> usingIndex = opBullet->_usingIndex;
	vector<int> removeIndex;

	for (auto it = usingIndex.begin(); it != usingIndex.end(); it++)
	{
		RECT temp;

		int index = *it;

		RECT rc = RectMakeCenter(_sakuya->getSakuyaImage()->getCenterX(), _sakuya->getSakuyaImage()->getCenterY(), 6, 6);

		if (IntersectRect(&temp, &rc, &opBullet->_objects[index].rc))
		{
			_sakuya->hitDamage(34);
			removeIndex.push_back(index);
			SOUNDMANAGER->play("Damage",0.5f);
		}
	}

	for (int i = 0; i < removeIndex.size(); i++)
	{
		int index = removeIndex[i];
		_bullet->removeBullet(index);
	}
}

bool enemyManager::_getStageFinish()
{
	if (_vMinion.size() == 0) return true;
	return false;
}