#include "stdafx.h"
#include "item.h"
#include "playGround.h"

item::item()
{
}

item::~item()
{
}

void item::init(playGround * gameManager)
{
	_isUse = false;
	_gameManager = gameManager;
}

bool item::isOver()
{
	return false;
}

void item::update()
{
	move();
}

void item::move()
{
}

void item::reset()
{
}

void item::render()
{
}

void item::over()
{
}
