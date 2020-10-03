#pragma once
#include "stdafx.h"
#include "gameNode.h"

class playGround;

class item
{
protected:
	playGround* _gameManager;
	image* _image;
	RECT _rc;
	int _count;
	bool _isUse;

public:
	item();
	~item();

	void init(playGround* gameManager);
	virtual void use() { if (!_isUse) { _isUse = true; } }
	virtual bool isOver();
	void move();
	virtual void update();
	virtual void reset();
	virtual void render();
	virtual void over();

	void setPos(float left, float top) {
		_rc = { static_cast<LONG>(left),static_cast<LONG>(top),static_cast<LONG> (left + 60),static_cast<LONG> (top + 60) }; }

	RECT getRect() { return _rc; }

};

