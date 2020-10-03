#pragma once
#include "effect.h"
#include "gameNode.h"
#include "bullets.h"
#include "sakuya.h"

class enemy : public gameNode
{
protected:
	image* _enemyImage;		

	RECT _rc;				

	int _currentFrameX;		
	int _currentFrameY;

	int _count;				
	int _fireCount;			
	int _rndFireCount;		

	int _maxMoveCount;
	int _moveCount;
	int _moveDir[2];
	int _countMax;

	bool _isRight;
	bool _isBottom;
	bool _phase;

public:
	enemy();
	~enemy();

	HRESULT init();											//초기화용
	HRESULT init(const char* imageName, POINT position, int maxMoveCount, int moveDir[2]);	//초기화 too
	void release();
	void update();
	void render();

	void move();			//움직임
	void draw();			//그려주자

	virtual bool bulletCountFire();	//총알 클래스에게 발사되라고 전달해주세요~
	virtual void attack(sakuya* name, bullet* bullet);

	//렉트 접근자
	inline RECT getRect() { return _rc; }
};

