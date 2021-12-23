#include<iostream>
#include<list>
#include<vector>
#include<queue>
#include <random>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<math.h>

const int R = 44;
const int C = 74;
const int WALLPROB = 20;
int map[R][C];


void CA3();
void CA5();
void CA5_old();
void CA5test();
void removeRegions(int removeProb = 100, int minSize = 0);
void removeWallChunks(int size);
void Big_Cave_Generator();
void Big_Cave_Generator11();
void Mine_Cave();
void Mainland();
void KarstCave();
void SKYPIEA();

int main()
{
	int x = 0, y = 0, i = 0, j = 0;
	srand((unsigned)time(NULL));
	for (int n = 0; n <1800; n++) rand();
	int N = 100000;
	while (N--)
	{
		//Big_Cave_Generator();
		//Big_Cave_Generator11();
		//Mine_Cave();
		//SKYPIEA();
		//Mainland();
		KarstCave();
	}

}

int Inmap(int x, int y)
{
	return x >= 0 && (x < R) && y >= 0 && (y < C);
}

void PRT()
{
	int i, j;
	for (i = 0; i < R; i++)
	{
		for (j = 0; j < C; j++)
		{
			if (map[i][j] == 1) std::cout << "□";
			else if (map[i][j] == 0) std::cout << "  ";
		}
		printf("\n");
	}
}
void CA3()
{
	int x = 0, y = 0;
	int temp[R][C] = { 0 };
	for (y = 1; y < C - 1; ++y)
	{
		for (x = 1; x < R - 1; ++x)
		{
			temp[x][y] = map[x][y];
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
					if (map[x + dx][y + dy] == 1)
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
			map[x][y] = temp[x][y];
		}
	}
}

void CA5test()
{
	int x = 0, y = 0;
	int temp[R][C] = { 0 };
	for (y = 1; y < C - 1; ++y)
	{
		for (x = 1; x < R - 1; ++x)
		{
			temp[x][y] = map[x][y];
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
					if (Inmap(x + dx, y + dy) && map[x + dx][y + dy] == 1)
					{
						if (ax <= 1 && ay <= 1)
							r1 += 1;
						r2 += 1;
					}
				}
			}
			if (r1 >= 5 || r2 <= 2)
				temp[x][y] = 0;
			else
				temp[x][y] = 1;
		}
	}
	for (y = 1; y < C - 1; ++y)
	{
		for (x = 1; x < R - 1; ++x)
		{
			map[x][y] = temp[x][y];
		}
	}
}

void CA5()
{
	int x = 0, y = 0;
	int temp[R][C] = { 0 };
	for (y = 1; y < C - 1; ++y)
	{
		for (x = 1; x < R - 1; ++x)
		{
			temp[x][y] = map[x][y];
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
					if (Inmap(x + dx, y + dy) && map[x + dx][y + dy] == 1)
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
			map[x][y] = temp[x][y];
		}
	}
}
void CA5_old()
{
	int x = 0, y = 0;
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
					if (Inmap(x + dx, y + dy) && map[x + dx][y + dy] == 1)
					{
						if (ax <= 1 && ay <= 1)
							r1 += 1;
						r2 += 1;
					}
				}
			}
			if (r1 >= 5 || r2 <= 2)
				map[x][y] = 1;
			else
				map[x][y] = 0;
		}
	}
}


using Point = sf::Vector2i;
void removeRegions(int removeProb, int minSize)
{
	int currentRegion = -1;
	int regions[R][C] = { 0 };
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)	regions[i][j] = currentRegion;
	std::vector<int> regionsSizes;

	for (int y = 1; y < C - 1; ++y)
		for (int x = 1; x < R - 1; ++x)
		{
			if (map[x][y] == 1 || regions[x][y] >= 0)
				continue;

			currentRegion += 1;
			regionsSizes.emplace_back(0);

			std::queue<Point> queue;
			queue.emplace(x, y);

			while (!queue.empty())
			{
				Point pos = queue.front();
				queue.pop();

				if (map[pos.x][pos.y] == 1 || regions[pos.x][pos.y] >= 0)
					continue;

				regions[pos.x][pos.y] = currentRegion;
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
	//int a1 = 0, a2 = 0, a3 = 0;
	//for (int i = 0; i < R; i++)
	//{
	//	for (int j = 0; j < C; j++)
	//	{
	//		if(regions[i][j]<0) std::cout << "□";
	//		else std::cout << " " <<regions[i][j]+1;
	//		if (regions[i][j] + 1 == 1) a1++;
	//		if (regions[i][j] + 1 == 2) a2++;
	//		if (regions[i][j] + 1 == 3) a3++;
	//		//std::cout <<regions[i][j]+1<< " ";
	//	}
	//		
	//	std::cout << "\n";
	//}
	//std::cout << "\n";
	//std::cout << a1 << " " << a2 << " " << a3 << "\n";
	// Find the biggest region
	int biggestRegion = 0;
	std::vector<bool> regionsForRemoval(currentRegion + 2, false);

	for (int i = 0; i <= currentRegion; ++i)
	{
		if (regionsSizes[i] > regionsSizes[biggestRegion])
			biggestRegion = i;

		if (rand() % 100 < removeProb || regionsSizes[i] < minSize)
			regionsForRemoval[i] = true;
	}
	// Always do not remove the biggest region
	regionsForRemoval[biggestRegion] = false;

	for (int y = 1; y < C - 1; ++y)
		for (int x = 1; x < R - 1; ++x)
		{
			if (map[x][y] == 1)
				continue;

			int i = regions[x][y];

			if (regionsForRemoval[i])
				map[x][y] = 1;
		}
}
void removeWallChunks(int minSize)
{
	int currentRegion = -1;
	int regions[R][C] = { 0 };
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)	regions[i][j] = currentRegion;
	std::vector<int> regionsSizes;

	for (int y = 1; y < C - 1; ++y)
		for (int x = 1; x < R - 1; ++x)
		{
			if (map[x][y] == 0 || regions[x][y] >= 0)
				continue;

			currentRegion += 1;
			regionsSizes.emplace_back(0);

			std::queue<Point> queue;
			queue.emplace(x, y);

			while (!queue.empty())
			{
				Point pos = queue.front();
				queue.pop();

				if (map[pos.x][pos.y] == 0 || regions[pos.x][pos.y] >= 0)
					continue;

				regions[pos.x][pos.y] = currentRegion;
				regionsSizes[currentRegion] += 1;

				//Point dpos[4] = { {0,1},{0,-1},{1,0},{-1,0} };
				//for (int i = 0; i < 4; i++)
				//{
				//	if (!Inmap(pos.x + dpos[i].x, pos.y + dpos[i].y))
				//		continue;

				//	queue.emplace(pos.x + dpos[i].x, pos.y + dpos[i].y);
				//}
				Point dpos[8] = { {0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1} };
				for (int i = 0; i < 8; i++)
				{
					if (!Inmap(pos.x + dpos[i].x, pos.y + dpos[i].y))
						continue;

					queue.emplace(pos.x + dpos[i].x, pos.y + dpos[i].y);
				}
			}
		}
	//int a1 = 0, a2 = 0, a3 = 0;
	//for (int i = 0; i < R; i++)
	//{
	//	for (int j = 0; j < C; j++)
	//	{
	//		//std::cout << " " << regions[i][j] + 1;
	//		if (regions[i][j] + 1 == 0) std::cout << "  ";
	//		else if (regions[i][j]+1 == 1) std::cout <<"□";
	//		else std::cout << " " << regions[i][j];
	//		if (regions[i][j] + 1 == 1) a1++;
	//		if (regions[i][j] + 1 == 2) a2++;
	//		if (regions[i][j] + 1 == 3) a3++;
	//		//std::cout <<regions[i][j]+1<< " ";
	//	}

	//	std::cout << "\n";
	//}
	//std::cout << "\n";
	//std::cout << a1 << " " << a2 << " " << a3 << "\n";

	// Find the biggest region
	int biggestRegion = 0;
	std::vector<bool> regionsForRemoval(currentRegion + 2, false);

	for (int i = 0; i <= currentRegion; ++i)
	{
		if (regionsSizes[i] > regionsSizes[biggestRegion])
			biggestRegion = i;

		if (rand() % 100 < 0 || regionsSizes[i] < minSize)
			regionsForRemoval[i] = true;
	}
	// Always do not remove the biggest region
	regionsForRemoval[biggestRegion] = false;

	for (int y = 1; y < C - 1; ++y)
		for (int x = 1; x < R - 1; ++x)
		{
			if (map[x][y] == 0)
				continue;

			int i = regions[x][y];

			if (regionsForRemoval[i])
				map[x][y] = 0;
		}
}
void remove_MaxWall(int minSize = 0);
void remove_MaxWall(int minSize) 
{
	int currentRegion = -1;
	int regions[R][C] = { 0 };
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)	regions[i][j] = currentRegion;
	std::vector<int> regionsSizes;

	for (int y = 1; y < C - 1; ++y)
		for (int x = 1; x < R - 1; ++x)
		{
			if (map[x][y] == 0 || regions[x][y] >= 0)
				continue;

			currentRegion += 1;
			regionsSizes.emplace_back(0);

			std::queue<Point> queue;
			queue.emplace(x, y);

			while (!queue.empty())
			{
				Point pos = queue.front();
				queue.pop();

				if (map[pos.x][pos.y] == 0 || regions[pos.x][pos.y] >= 0)
					continue;

				regions[pos.x][pos.y] = currentRegion;
				regionsSizes[currentRegion] += 1;

				//Point dpos[4] = { {0,1},{0,-1},{1,0},{-1,0} };
				//for (int i = 0; i < 4; i++)
				//{
				//	if (!Inmap(pos.x + dpos[i].x, pos.y + dpos[i].y))
				//		continue;

				//	queue.emplace(pos.x + dpos[i].x, pos.y + dpos[i].y);
				//}
				Point dpos[8] = { {0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1} };
				for (int i = 0; i < 8; i++)
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

		if (rand() % 100 < 100 || regionsSizes[i] < minSize)
			regionsForRemoval[i] = true;
	}
	// Always do not remove the biggest region
	regionsForRemoval[biggestRegion] = false;

	for (int y = 1; y < C - 1; ++y)
		for (int x = 1; x < R - 1; ++x)
		{
			if (map[x][y] == 0)
				continue;

			int i = regions[x][y];

			if (regionsForRemoval[i])
				map[x][y] = 0;
		}
}

void Big_Cave_Generator() {
	int x = 0, y = 0, i = 0, j = 0;
	//for (i = 0; i <100; i++) rand();
	//生成噪化图        -----------------------------------------------------------------------------------------------
	for (y = 0; y < C; ++y)
		for (x = 0; x < R; ++x)
		{
			if (x == 0 || x == R - 1 || y == 0 || y == C - 1)
				map[x][y] = 1;
			else if (rand() % 100 < WALLPROB)
				map[x][y] = 1;
			else
				map[x][y] = 0;
		}
	//PRT();
	//system("pause");
	//system("cls");
	//原孢 处理5*5-----------------------------------------------------------------------------------------------
	for (i = 0; i <4; i++) CA5();
	//PRT();
	//system("pause");
	//system("cls");
	////原孢 处理3*3-----------------------------------------------------------------------------------------------
	for (i = 0; i < 2; i++) CA3();
	//PRT();
	//system("pause");
	//system("cls");
	////洪水填充
	removeRegions();
	//PRT();
	//system("pause");
	//system("cls");
	removeWallChunks(7);
	PRT();
	system("pause");
	system("cls");

}
void Big_Cave_Generator11() {
	int x = 0, y = 0, i = 0, j = 0;
	//for (i = 0; i <100; i++) rand();
	//生成噪化图        -----------------------------------------------------------------------------------------------
	for (y = 0; y < C; ++y)
		for (x = 0; x < R; ++x)
		{
			if (x == 0 || x == R - 1 || y == 0 || y == C - 1)
				map[x][y] = 1;
			else if (rand() % 100 < WALLPROB)
				map[x][y] = 1;
			else
				map[x][y] = 0;
		}
	PRT();
	system("pause");
	system("cls");
	//原孢 处理5*5-----------------------------------------------------------------------------------------------
	for (i = 0; i < 4; i++) CA5();
	PRT();
	system("pause");
	system("cls");
	////原孢 处理3*3-----------------------------------------------------------------------------------------------
	for (i = 0; i < 2; i++) CA3();
	PRT();
	system("pause");
	system("cls");
	////洪水填充
	removeRegions();
	PRT();
	system("pause");
	system("cls");
	removeWallChunks(7);
	PRT();
	system("pause");
	system("cls");

}
void Mine_Cave() {
	int x = 0, y = 0, i = 0, j = 0;
	//for (i = 0; i <100; i++) rand();
	//生成噪化图        -----------------------------------------------------------------------------------------------
	for (y = 0; y < C; ++y)
		for (x = 0; x < R; ++x)
		{
			if (x == 0 || x == R - 1 || y == 0 || y == C - 1)
				map[x][y] = 1;
			else if (rand() % 100 < WALLPROB)
				map[x][y] = 1;
			else
				map[x][y] = 0;
		}
	//PRT();
	//system("pause");
	//system("cls");

	////原孢 处理3*3-----------------------------------------------------------------------------------------------
	for (i = 0; i < 3; i++) CA3();
	//PRT();
	//system("pause");
	//system("cls");

	//原孢 处理5*5-----------------------------------------------------------------------------------------------
	for (i = 0; i < 1; i++) CA5();
	//PRT();
	//system("pause");
	//system("cls");


	////洪水填充
	removeRegions();
	//PRT();
	//system("pause");
	//system("cls");
	removeWallChunks(10);
	PRT();
	system("pause");
	system("cls");

}

void SKYPIEA()
{
	int x = 0, y = 0, i = 0, j = 0;
	//for (i = 0; i <100; i++) rand();
	//生成噪化图        -----------------------------------------------------------------------------------------------
	for (y = 0; y < C; ++y)
		for (x = 0; x < R; ++x)
		{
			if (x == 0 || x == R - 1 || y == 0 || y == C - 1)
				map[x][y] = 1;
			else if (rand() % 100 < WALLPROB)
				map[x][y] = 1;
			else
				map[x][y] = 0;
		}
	PRT();
	system("pause");
	system("cls");
	//原孢 处理5*5-----------------------------------------------------------------------------------------------
	for (i = 0; i < 3; i++) CA5test();
	PRT();
	system("pause");
	system("cls");
	//原孢 处理5*5-----------------------------------------------------------------------------------------------
	//for (i = 0; i < 3; i++) CA3();
	//PRT();
	//system("pause");
	//system("cls");
	//移除区域
	removeRegions();
	PRT();
	system("pause");
	system("cls");
	//移除墙块儿
	removeWallChunks(6);
	PRT();
	system("pause");
	system("cls");

}
void KarstCave()
{
	int x = 0, y = 0, i = 0, j = 0;
	//for (i = 0; i <100; i++) rand();
	//生成噪化图        -----------------------------------------------------------------------------------------------
	for (y = 0; y < C; ++y)
		for (x = 0; x < R; ++x)
		{
			if (x == 0 || x == R - 1 || y == 0 || y == C - 1)
				map[x][y] = 1;
			else if (rand() % 100 < WALLPROB)
				map[x][y] = 1;
			else
				map[x][y] = 0;
		}
	//PRT();
	//system("pause");
	//system("cls");
	//原孢 处理5*5-----------------------------------------------------------------------------------------------
	for (i = 0; i < 2; i++) CA5();
	//PRT();
	//system("pause");
	//system("cls");
	//移除区域
	removeRegions();
	//PRT();
	//system("pause");
	//system("cls");
	//移除墙块儿
	removeWallChunks(6);
	PRT();
	system("pause");
	system("cls");


}
void Mainland()
{
	int x = 0, y = 0, i = 0, j = 0;
	//for (i = 0; i <100; i++) rand();
	//生成噪化图        -----------------------------------------------------------------------------------------------
	for (y = 0; y < C; ++y)
		for (x = 0; x < R; ++x)
		{
			if (x == 0 || x == R - 1 || y == 0 || y == C - 1)
				map[x][y] = 1;
			else if (rand() % 100 < WALLPROB)
				map[x][y] = 1;
			else
				map[x][y] = 0;
		}
	PRT();
	system("pause");
	system("cls");
	//原孢 处理5*5-----------------------------------------------------------------------------------------------
	for (i = 0; i < 4; i++) CA5_old();
	PRT();
	system("pause");
	system("cls");
	//移除区域
	removeRegions();
	PRT();
	system("pause");
	system("cls");
	//移除墙块儿
	removeWallChunks(25);
	PRT();
	system("pause");
	system("cls");

}