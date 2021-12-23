#pragma once
#include"stdafx.h"
#include "Map.h"

using Point = sf::Vector2i;

class BigCave_Generator :
    public Map
{
private:
    int Inmap(int x, int y);
    void CA5();
    void CA3();
    void removeRegions();
    void removeBlocks(int size);

public:
    BigCave_Generator();
    virtual ~BigCave_Generator();
    //Cave_Generator(const Cave_Generator& _cave);

    void generate();
    void transform();

    void update();
    void render(sf::RenderTarget& target);
};

