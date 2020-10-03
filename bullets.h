#pragma once
#include "gameNode.h"
#include "ObjectPool.h"
#include <set>

struct tagBullet
{
	image* bulletImage;		//�Ѿ˿� �� �̹���
	RECT rc;				//�Ѿ˿� �� ��Ʈ
	float x, y;				//���� x, y
	float angle;			//�Ѿ� ����
	float radius;			//�Ѿ� ������
	float speed;			//���ǵ�
	float fireX, fireY;		//�Ѿ� �߻�� ��ġ XY
	bool isFire;			//�߻��ߴ�?
	int count;				//������ �̹����� �� ī��Ʈ
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