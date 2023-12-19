#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "cocos/math/Vec2.h"
#include "AudioEngine.h"

USING_NS_CC;

extern int current_gold_coins;
extern Vec2 towerPosition;  // 用于存储防御塔的位置
extern int tower0Clicked;
extern int already;//是否选中防御塔
extern Vec2 mousePosition;

class Game_one : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// 暂停
	void Pause(Ref* pSender);
	// 游戏通关
	void Success(Ref* pSender);
	//点击侧边防御塔并放置
	void onMouseDown(cocos2d::EventMouse* event);
	void onMouseDown1(cocos2d::EventMouse* event);
	// 在屏幕上显示鼠标位置声明
	void drawMousePositionLabel(const cocos2d::Vec2& position);
	//侧边防御塔的显示
	void createTower0(const std::string& tower0Image, const std::string& tower0BackImage,
		const std::string& towerImage, const std::string& towerBackImage,
		int upgradeCoins, float positionY, int index);
	// 判断是否点击到侧边防御塔
	int checkTower0Clicked(const cocos2d::Vec2& touchLocation);
	//建造所需要的钱
	int getTowerUpgradeCoins(int towerType);
	// 金币不足的标
	cocos2d::Label* insufficientGoldLabel;
	// 放置位置错误的标
	cocos2d::Label* insufficientPlaceLabel;
	// 可放置位置边框
	cocos2d::Sprite* board[25];
	// 防御塔可放置位置
	const Vec2 pairxy[23] = {
		Vec2(155,211) ,Vec2(190,211) ,Vec2(190,177) ,Vec2(190,211) ,Vec2(225,211)
		,Vec2(225,177) ,Vec2(225,143) ,Vec2(225,109) ,Vec2(225,75)  ,Vec2(225,41)
		,Vec2(260,41)  ,Vec2(295,41)  ,Vec2(330,41)  ,Vec2(365,41)  ,Vec2(400,41)
		,Vec2(295,109) ,Vec2(330,109) ,Vec2(365,109) ,Vec2(400,109) ,Vec2(295,143)
		,Vec2(295,177) ,Vec2(295,211) ,Vec2(295,245) };
	// 显示金币不足
	void showInsufficientGoldLabel();
	// 显示放置位置错误
	void showInsufficientPlaceLabel();
	// 定时器倒数
	virtual void step(float Dt);
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
	//点击侧边防御塔并放置
	void onMouseDown(cocos2d::EventMouse* event);
	void onMouseDown1(cocos2d::EventMouse* event);
	// 在屏幕上显示鼠标位置声明
	void drawMousePositionLabel(const cocos2d::Vec2& position);
	//侧边防御塔的显示
	void createTower0(const std::string& tower0Image, const std::string& tower0BackImage,
		const std::string& towerImage, const std::string& towerBackImage,
		int upgradeCoins, float positionY, int index);
	// 判断是否点击到侧边防御塔
	int checkTower0Clicked(const cocos2d::Vec2& touchLocation);
	int getTowerUpgradeCoins(int towerType);
	cocos2d::Sprite* createTowerSprite(int towerType);
	// 金币不足的标
	cocos2d::Label* insufficientGoldLabel;
	// 放置位置错误的标
	cocos2d::Label* insufficientPlaceLabel;
	// 可放置位置边框
	cocos2d::Sprite* board[30];
	// 防御塔可放置位置
	const Vec2 pairxy[27] = {
		 Vec2(128,28) ,Vec2(162,28) ,Vec2(196,28),Vec2(230,28),Vec2(264,28),
		 Vec2(298,28) ,Vec2(332,28) ,Vec2(366,28),Vec2(128,72),Vec2(128,160) ,
		 Vec2(128,204),Vec2(128,116),Vec2(196,116) ,Vec2(230,116) ,Vec2(264,116),
		 Vec2(298,116),Vec2(332,116),Vec2(366,116) ,Vec2(162,204),Vec2(196,204),
		 Vec2(230,204),Vec2(264,204),Vec2(298,204) ,Vec2(332,204),Vec2(400,204),
		 Vec2(400,248),Vec2(400,160) };
	// 显示金币不足
	void showInsufficientGoldLabel();
	// 显示放置位置错误
	void showInsufficientPlaceLabel();
	// 定时器倒数
	virtual void step(float Dt);
	// implement the "static create()" method manually
	CREATE_FUNC(Game_two);
};
#endif