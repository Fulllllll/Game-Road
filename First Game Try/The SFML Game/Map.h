#pragma once
#include"stdafx.h"

class Map
{
	
public:
	int p[R][C] = { 0 };
	TileMap map;

	Map();
	virtual ~Map();

	void update();	
	void render();
};

