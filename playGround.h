#pragma once
#include "gameNode.h"
#include "sakuya.h"
#include "enemyManager.h"
#include <commdlg.h>

//======================================================================
#include <iostream>
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
using namespace std;
//======================================================================

class playGround : public gameNode
{
private:
	sakuya* _sakuya;
	enemyManager* _em;
	int _loopX, _loopY;
	int _stage;
	bool _isFinishStage;
	bool _isBossStage;
	bool _isSoundPlay;
	bool _isBossPlay;

	int _count;


	int TEST;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

