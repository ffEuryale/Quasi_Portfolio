#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "progressBar.h"
#include "timeManager.h"

#pragma warning(disable:4996)

class enemyManager;

class sakuya : public gameNode
{
private:
	image* _player;
	knife* _knife;

	image* _hitbox;
	image* _hitbox2;

	enemyManager* _em;

	progressBar* _hpBar;
	float _currentHP, _maxHP;

	float _currentTime;

	RECT _rc;
	RECT _rchit;

	int _EHP;
	int _currentFrameX;
	int _currentFrameY;
	int _count;
	int _fireCount;
	int _alphaVal;
	bool _isSlow;

public:
	sakuya();
	~sakuya();

	virtual HRESULT init(const char* imageName, POINT position);
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void collision();
	void draw();

	void hitDamage(float damage);

	void setEmMemoryAddressLink(enemyManager* em) { _em = em; }

	image* getSakuyaImage() { return _player; }
	knife* getKnife() { return _knife; }

};

