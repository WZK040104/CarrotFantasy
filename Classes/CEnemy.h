#pragma once
#include"cocos2d.h"

class CEnemy	//怪物的属性 基类
{
private:
	int enemy_HP;				//该类怪物的生命值上限
	int HP;						//当前怪物生命值
	float velocity;				//移动速度
	int add_coins;				//怪物死之后增加的金币
	double enemy_position_x;	//怪物的横坐标
	double enemy_position_y;	//怪物的纵坐标
	
public:
	//构造函数
	CEnemy();
	
	// 析构函数
	virtual ~CEnemy();
	//初始化怪物的生命值,速度，金币
	void initial(int input_type,int input_HP, float input_velocity, int input_coins, double x, double y); 
	//是否活着
	bool alive(); 

	double EnemyPositionX();
	double EnemyPositionY();
	void set_x(double input_x);
	void set_y(double input_y);
	void HP_calculate(int damage_per_time);
	void setHP();
	float get_velocity();
	float getHPpercentage();
	int enemytype;
	cocos2d::Sprite* enemySprite; //怪物的精灵
	cocos2d::Sprite* getSprite();
	cocos2d::ProgressTimer* enemyHealthbar;//怪物血条
	cocos2d::Sprite* enemyHealthbar_back;
	//cocos2d::Sprite* getHealthbar();
	//cocos2d::Sprite* getHealthbar_back();
};

