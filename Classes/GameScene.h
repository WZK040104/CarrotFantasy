#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

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
	// implement the "static create()" method manually
	CREATE_FUNC(Game_two);
};

#endif
