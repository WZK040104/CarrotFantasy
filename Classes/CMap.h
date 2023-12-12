#pragma once
#define Map_x 12
#define Map_y 9

class CMap
{
private:
	char map[Map_x][Map_y];
	//char direction[Map_x][Map_y];
public:
	//构造函数
	CMap(char inputMap[][Map_x]);

	// 析构函数
	virtual ~CMap();

	int getMap(int x, int y);
	//void judgeDirection(int x, int y);

};


class Map1 : public CMap
{
public:
	Map1();
	virtual ~Map1();
};

class Map2 : public CMap
{
public:
	Map2();
	virtual ~Map2();
};

class Map3 : public CMap
{
public:
	Map3();
	virtual ~Map3();
};