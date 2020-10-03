#pragma once
#include "gameNode.h"
#include "ObjectPool.h"
#include <set>

struct tagBullet
{
	image* bulletImage;		//총알에 쓸 이미지
	RECT rc;				//총알에 쓸 렉트
	float x, y;				//중점 x, y
	float angle;			//총알 각도
	float radius;			//총알 반지름
	float speed;			//스피드
	float fireX, fireY;		//총알 발사된 위치 XY
	bool isFire;			//발사했누?
	int count;				//프레임 이미지에 쓸 카운트
};

class bullet : public gameNode
{
private:
	objectPool<tagBullet>* _opBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;

public:
	bullet(int missileMax):_bulletMax(missileMax) { _opBullet = new objectPool<tagBullet> (missileMax); };
	~bullet() {};

	HRESULT init(const char* imageName, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed);

	void move();
	
	void removeBullet(int arrNum);

	objectPool<tagBullet>* getOpBullet() { return _opBullet; }
};


class knife : public gameNode
{
private:
	objectPool<tagBullet>* _opBullet;

	int _bulletMax;
	float _range;
public:
	knife(int missileMax) :_bulletMax(missileMax) { _opBullet = new objectPool<tagBullet> (missileMax); }
	~knife() {};

	virtual HRESULT init(float range);
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y);

	void move();

	void removeKnife(int arrNum);

	objectPool<tagBullet>* getOpBullet() { return _opBullet; }
};