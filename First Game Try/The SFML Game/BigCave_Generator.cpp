#include "stdafx.h"
#include "BigCave_Generator.h"

void BigCave_Generator::generate()
{
	//初始化数组，
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
		{
			if(i==0||i==R-1||j==0||j==C-1) p[i][j] = 1;
			else if (rand() % 100 <WALL_p) p[i][j] = 1;
			else p[i][j] = 0;
		}
	//原孢 处理5*5-----------------------------------------------------------------------------------------------
	for (int i = 0; i < 4; i++) CA5();
	for (int i = 0; i < 3; i++) CA3();
	//洪水填充
	removeRegions();
	removeBlocks(23);
}

void BigCave_Generator::transform()
{
	/*将地图数组的数据转化为 0-8 ，与素材相匹配
	* 0-3 代表虚空
	* 4-8 代表地面
	*/
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (p[i][j] == 1) p[i][j] = 0;
			else p[i][j] = 1;
		}
	}
	for (int i = 1; i < R - 1; i++)
	{
		for (int j = 1; j < C - 1; j++)
		{
			if (p[i][j] == 1 && (p[i - 1][j] == 0 || p[i][j - 1] == 0 || p[i][j + 1] == 0 || p[i + 1][j] == 0))
			{
				p[i][j] = 4;
			}
			else if (p[i][j] == 1) p[i][j] = rand() % 4 + 5;
		}
	}
	for (int i = 1; i < R; i++)
	{
		for (int j = 1; j < C - 1; j++)
		{
			if (p[i][j] == 0 && p[i - 1][j] >= 4)
			{
				p[i][j] = rand() % 3 + 1;
			}
		}
	}
}

void BigCave_Generator::update()
{
	map.load("TileSheet.png", sf::Vector2u(128, 104), (int*)p, C, R);
}

void BigCave_Generator::render(sf::RenderTarget& target)
{
	target.draw(this->map);
}

int BigCave_Generator::Inmap(int x, int y)
{
	return x >= 0 && (x < R) && y >= 0 && (y < C);
}

void BigCave_Generator::CA5()
{
	int x = 0, y = 0;
	int temp[R][C] = { 0 };
	for (y = 1; y < C - 1; ++y)
	{
		for (x = 1; x < R - 1; ++x)
		{
			temp[x][y] = p[x][y];
		}
	}
	for (y = 1; y < C - 1; ++y)
	{
		for (x = 1; x < R - 1; ++x)
		{
			int r1 = 0, r2 = 0;
			for (int dy = -2; dy <= 2; ++dy)
			{
				for (int dx = -2; dx <= 2; ++dx)
				{
					int ax = std::abs(dx);
					int ay = std::abs(dy);
					if (ax == 2 && ay == 2)
						continue;
					if (Inmap(x + dx, y + dy) && p[x + dx][y + dy] == 1)
					{
						if (ax <= 1 && ay <= 1)
							r1 += 1;
						r2 += 1;
					}
				}
			}
			if (r1 >= 5 || r2 <= 2)
				temp[x][y] = 1;
			else
				temp[x][y] = 0;
		}
	}
	for (y = 1; y < C - 1; ++y)
	{
		for (x = 1; x < R - 1; ++x)
		{
			p[x][y] = temp[x][y];
		}
	}
}

void BigCave_Generator::CA3()
{
	int x = 0, y = 0;
	int temp[R][C] = { 0 };
	for (y = 1; y < C - 1; ++y)
	{
		for (x = 1; x < R - 1; ++x)
		{
			temp[x][y] = p[x][y];
		}
	}
	for (y = 1; y < C - 1; ++y)
	{
		for (x = 1; x < R - 1; ++x)
		{
			int r1 = 0;
			for (int dy = -1; dy <= 1; ++dy)
			{
				for (int dx = -1; dx <= 1; ++dx)
				{
					if (p[x + dx][y + dy] == 1)
						r1++;
				}
			}
			if (r1 >= 5)
				temp[x][y] = 1;
			else
				temp[x][y] = 0;
		}
	}
	for (y = 1; y < C - 1; ++y)
	{
		for (x = 1; x < R - 1; ++x)
		{
			p[x][y] = temp[x][y];
		}
	}
}

void BigCave_Generator::removeRegions()
{
	int currentRegion = -1;
	std::vector<int> regions(R * C+2, currentRegion);
	std::vector<int> regionsSizes;

	// 统计空地数量与大小
	for (int y = 1; y < C - 1; ++y)
		for (int x = 1; x < R - 1; ++x)
		{
			if (p[x][y] == 1 || regions[x + y * R] >= 0)
				continue;

			currentRegion += 1;
			regionsSizes.emplace_back(0);

			//非递归洪水填充
			std::queue<Point> queue;
			queue.emplace(x, y);
			while (!queue.empty())  
			{
				Point pos = queue.front();
				queue.pop();

				if (p[pos.x][pos.y] == 1 || regions[pos.x+pos.y*R] >= 0)
					continue;

				regions[pos.x + pos.y * R] = currentRegion;
				regionsSizes[currentRegion] += 1;

				Point dpos[4] = { {0,1},{0,-1},{1,0},{-1,0} };
				for (int i = 0; i < 4; i++)
				{
					if (!Inmap(pos.x + dpos[i].x, pos.y + dpos[i].y))
						continue;

					queue.emplace(pos.x + dpos[i].x, pos.y + dpos[i].y);
				}
			}
		}
	// Find the biggest region
	int biggestRegion = 0;
	std::vector<bool> regionsForRemoval(currentRegion + 2, false);

	for (int i = 0; i <= currentRegion; ++i)
	{
		if (regionsSizes[i] > regionsSizes[biggestRegion])
			biggestRegion = i;
			regionsForRemoval[i] = true;
	}
	regionsForRemoval[biggestRegion] = false;

	for (int y = 1; y < C - 1; ++y)
	{
		for (int x = 1; x < R - 1; ++x)
		{
			if (p[x][y] == 0 && regionsForRemoval[regions[x + y * R]] == 1)
				p[x][y] = 1;
		}
	}
}

void BigCave_Generator::removeBlocks(int size)
{
	int currentRegion = -1;
	std::vector<int> regions(R * C + 2, currentRegion);
	std::vector<int> regionsSizes;

	for (int y = 1; y < C - 1; ++y)
		for (int x = 1; x < R - 1; ++x)
		{
			if (p[x][y] == 0 || regions[x + y * R] >= 0)
				continue;

			currentRegion += 1;
			regionsSizes.emplace_back(0);

			std::queue<Point> queue;
			queue.emplace(x, y);
			while (!queue.empty())
			{
				Point pos = queue.front();
				queue.pop();

				if (p[pos.x][pos.y] == 0 || regions[pos.x + pos.y * R] >= 0)
					continue;

				regions[pos.x + pos.y * R] = currentRegion;
				regionsSizes[currentRegion] += 1;

				Point dpos[8] = { {0,1},{0,-1},{1,0},{-1,0},
									{1,1},{1,-1},{-1,1},{-1,-1} };
				for (int i = 0; i < 8; i++)
				{
					if (!Inmap(pos.x + dpos[i].x, pos.y + dpos[i].y))
						continue;

					queue.emplace(pos.x + dpos[i].x, pos.y + dpos[i].y);
				}
			}
		}
	std::vector<bool> regionsForRemoval(currentRegion + 2, false);
	
	for (int i = 0; i <= currentRegion; ++i)
	{
		if (regionsSizes[i] < size)
		regionsForRemoval[i] = true;
	}
	for (int y = 1; y < C - 1; ++y)
		for (int x = 1; x < R - 1; ++x)
		{
			if (p[x][y] == 1&&regionsForRemoval[regions[x + y * R]])
				p[x][y] = 0;
		}
}



BigCave_Generator::BigCave_Generator()
{
	generate();
	transform();
}
BigCave_Generator::~BigCave_Generator()
{

}

