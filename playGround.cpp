#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("배경", "image/backGround_Default.bmp", 480, 560, false, MAGENTA);
	IMAGEMANAGER->addImage("배경1", "image/backGround_Boss.bmp", 480, 960, false, MAGENTA);

	IMAGEMANAGER->addImage("foreGround", "image/foreGround.bmp", WINSIZEX, WINSIZEY, true, MAGENTA);

	IMAGEMANAGER->addImage("bullet", "image/bullet.bmp", 16, 16, true, MAGENTA);

	IMAGEMANAGER->addFrameImage("enemy1", "image/enemy.bmp", 0, 0, 288, 32, 9, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("enemy2", "image/enemy-r.bmp", 240, 30, 8, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("enemyE", "image/enemy-E.bmp", 155, 34, 5, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("enemyB", "image/Enemy-B.bmp", 54, 28, 2, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("cirno", "image/cirno.bmp", 376, 54, 8, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Letty", "image/letty_Whiterock_Default.bmp", 176, 64, 4, 1, true, MAGENTA);

	IMAGEMANAGER->addImage("enemyMark", "image/enemy-Mark.bmp", 42, 16, false, MAGENTA);

	IMAGEMANAGER->addImage("playerLife", "image/life.bmp", 16, 15, true, MAGENTA);
	IMAGEMANAGER->addImage("playerBomb", "image/bomb.bmp", 16, 15, true, MAGENTA);

	SOUNDMANAGER->addSound("BGM", "sound/st1_BGM.mp3", true, false);
	SOUNDMANAGER->addSound("BOSS_BGM", "sound/st1_BossBGM.mp3", true, false);
	SOUNDMANAGER->addSound("p_Shot", "sound/se_plst00.wav", true, false);
	SOUNDMANAGER->addSound("p_Dead", "sound/se_pldead00.wav", true, false);
	SOUNDMANAGER->addSound("Damage", "sound/se_damage00.wav", true, false);
	SOUNDMANAGER->addSound("e_Shot", "sound/se_tan01.wav", true, false);
	SOUNDMANAGER->addSound("e_Dead", "sound/se_enep00.wav", true, false);
	SOUNDMANAGER->addSound("item", "sound/se_item00.wav", true, false);

	/*
	IMAGEMANAGER->addImage("item_SP", "image/item_s_power.bmp", 12, 12, true, MAGENTA);
	IMAGEMANAGER->addImage("item_MP", "image/item_m_power.bmp", 16, 16, true, MAGENTA);
	IMAGEMANAGER->addImage("item_blos", "image/item_blossom.bmp", 12, 12, true, MAGENTA);
	IMAGEMANAGER->addImage("item_bomb", "image/item_bomb.bmp", 16, 16, true, MAGENTA);
	IMAGEMANAGER->addImage("item_Score", "image/item_score.bmp", 12, 12, true, MAGENTA);
	*/

	_loopX = 0;
	_loopY = WINSIZEX;

	_count = 0;

	_sakuya = new sakuya;
	_sakuya->init();

	_em = new enemyManager;
	_em->init();

	_em->setSakuyaMemoryAddressLink(_sakuya);
	_sakuya->setEmMemoryAddressLink(_em);

	_stage = 1;
	_isFinishStage = true;
	_isSoundPlay = _isBossPlay = false;

	return S_OK;
}

//메모리 해제
void playGround::release()
{

}

//연산
void playGround::update()
{
	gameNode::update();

	_loopX = 0;
	_loopY -= 3;

	if (!_isSoundPlay)
	{
		_count++;
		if (_count == 200)
		{
			_isSoundPlay = true;
			SOUNDMANAGER->play("BGM", 0.2f);
		}
	}

	if (_isFinishStage)
	{
		_em->setMinion(_stage++);
	}

	cout << _stage << endl;
	_sakuya->update();
	_em->update();

	if (_stage > 2000)
	{
		_isBossStage = true;
		SOUNDMANAGER->stop("BGM");
	}

	_isFinishStage = _em->_getStageFinish();
}

//그리기 전용
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================


	if (_isBossStage)
	{
		_loopX -= 1;
		IMAGEMANAGER->findImage("배경1")->loopRender(getMemDC(), &RectMake(40, 21, 480, 560), _loopX, _loopY);
		if (!_isBossPlay && _isSoundPlay)
		{
			SOUNDMANAGER->play("BOSS_BGM", 0.2f);
			_isBossPlay = true;
		}
	}
	else
	{
		IMAGEMANAGER->findImage("배경")->loopRender(getMemDC(), &RectMake(40, 21, 480, 560), _loopX, _loopY);
	}
	
	_sakuya->render();
	_em->render();

	IMAGEMANAGER->findImage("foreGround")->render(getMemDC());
	IMAGEMANAGER->findImage("playerLife")->render(getMemDC(), 622, 123);
	IMAGEMANAGER->findImage("playerLife")->render(getMemDC(), 642, 123);
	IMAGEMANAGER->findImage("playerBomb")->render(getMemDC(), 622, 143);
	IMAGEMANAGER->findImage("playerBomb")->render(getMemDC(), 642, 143);
	IMAGEMANAGER->findImage("playerBomb")->render(getMemDC(), 662, 143);

	//TIMEMANAGER->render(getMemDC());

	//================================================
	_backBuffer->render(getHDC(), 0, 0);
}
