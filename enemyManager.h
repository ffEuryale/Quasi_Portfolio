#pragma once
#include "gameNode.h"
#include "minion.h"
#include "Ecirno.h"
#include "bullets.h"
#include "sakuya.h"
#include <vector>

//헤더파일 꼬임방지를 위한 클래스 전방선언
class sakuya;

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*>				vEnemy;
	typedef vector<enemy*>::iterator	viEnemy;

	vEnemy _vMinion;
	viEnemy _viMinion;

	bullet* _bullet;

	sakuya* _sakuya;
	effect* _effect;

	enemy* _cirno;
	enemy* _letty;
	enemy* _Enemy1;
	enemy* _Enemy2;
	enemy* _Enemy3;
	enemy* _EnemyE1;
	enemy* _EnemyE2;

	int _HP;

	float _x, _y;

	int _frameCount;

public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setMinion(int stage);

	void minionBulletFire();

	void removeMinion(int arrNum);

	void hitDamage(int damage);

	//충돌함수
	void collision();

	void setSakuyaMemoryAddressLink(sakuya* name) { _sakuya = name; }

	vector<enemy*> getVMinion() { return _vMinion; }
	vector<enemy*>::iterator getVIMinion() { return _viMinion; }

	bullet* getBullet() { return _bullet; }

	bool _getStageFinish();
};

