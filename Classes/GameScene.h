#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "cocos/math/Vec2.h"

extern int current_gold_coins;

class Game_one : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// 暂停
	void Pause(Ref* pSender);
	// 游戏通关
	void Success(Ref* pSender);
	// 鼠标点击事件回调声明
	void onMouseDown(cocos2d::EventMouse* event);
	// 在屏幕上显示鼠标位置声明
	void drawMousePositionLabel(const cocos2d::Vec2& position);
	// 侧边防御塔的显示
	void createTower0(const std::string& tower0Image, const std::string& tower0BackImage,
		const std::string& towerImage, const std::string& towerBackImage,
		int upgradeCoins, float positionY, int index);
	// 判断是否点击到侧边防御塔
	int checkTower0Clicked(const cocos2d::Vec2& touchLocation);
	// 金币不足的标
	cocos2d::Label* insufficientGoldLabel;
	// 显示金币不足
	void showInsufficientGoldLabel();
	// implement the "static create()" method manually
	CREATE_FUNC(Game_one);
};

class Game_two : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// 暂停
	void Pause(Ref* pSender);
	// 游戏通关
	void Success(Ref* pSender);
	// 鼠标点击事件回调声明
	void onMouseDown(cocos2d::EventMouse* event);
	// 在屏幕上显示鼠标位置声明
	void drawMousePositionLabel(const cocos2d::Vec2& position);
	// 侧边防御塔的显示
	void createTower0(const std::string& tower0Image, const std::string& tower0BackImage,
		const std::string& towerImage, const std::string& towerBackImage,
		int upgradeCoins, float positionY, int index);
	// 判断是否点击到侧边防御塔
	int checkTower0Clicked(const cocos2d::Vec2& touchLocation);
	// implement the "static create()" method manually
	CREATE_FUNC(Game_two);
};

#endif
