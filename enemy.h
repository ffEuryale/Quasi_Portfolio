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

	HRESULT init();											//�ʱ�ȭ��
	HRESULT init(const char* imageName, POINT position, int maxMoveCount, int moveDir[2]);	//�ʱ�ȭ too
	void release();
	void update();
	void render();

	void move();			//������
	void draw();			//�׷�����

	virtual bool bulletCountFire();	//�Ѿ� Ŭ�������� �߻�Ƕ�� �������ּ���~
	virtual void attack(sakuya* name, bullet* bullet);

	//��Ʈ ������
	inline RECT getRect() { return _rc; }
};

