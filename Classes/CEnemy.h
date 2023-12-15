#pragma once

class CEnemy	//怪物的属性 基类
{
private:
	int enemy_HP;				//该类怪物的生命值上限
	int HP;						//当前怪物生命值
	int velocity;				//移动速度
	int add_coins;				//怪物死之后增加的金币
	double enemy_position_x;	//怪物的横坐标
	double enemy_position_y;	//怪物的纵坐标

public:
	//构造函数
	CEnemy();
	
	// 析构函数
	virtual ~CEnemy();
	//初始化怪物的生命值,速度，金币
	void initial(int input_HP, int input_velocity, int input_coins, double x, double y); 
	//是否活着
	bool alive(); 

	double EnemyPositionX()const;
	double EnemyPositionY()const;
	void set_x(double input_x);
	void set_y(double input_y);
	void HP_calculate(int damage_per_time);
};
