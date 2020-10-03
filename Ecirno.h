#pragma once
#include "effect.h"
#include "enemy.h"
#include "bullets.h"
#include "sakuya.h"

enum ATTACK_TYPE
{
	CIRCLE,
	FLOWER,
	CIRCULARSECTOR
};

class Ecirno : public enemy
{
private:
	bool _isAttack;
	ATTACK_TYPE _type;
	int _attackCount;
	int _attackTime;
	float _attackAngle[8];
	bullet* _bullet;
	sakuya* _sakuya;
	/*
	int _HP;*/

public:
	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position, int maxMoveCount, int moveDir[2]);

	virtual void release();
	virtual void update();
	virtual void render();
	virtual void move();
	virtual void draw();

	virtual bool bulletCountFire();
	virtual void attack(sakuya* name, bullet* bullet);
/*
	virtual void setHP(int hp) { _HP = hp; };
	virtual int getHP() { return _HP; };*/
};