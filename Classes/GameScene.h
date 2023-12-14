#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class Game_one : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// ��ͣ
	void Pause(Ref* pSender);
	// ��Ϸͨ��
	void Success(Ref* pSender);
	// ������¼��ص�����
	void onMouseDown(cocos2d::EventMouse* event);
	// ����Ļ����ʾ���λ������
	void drawMousePositionLabel(const cocos2d::Vec2& position);
	// implement the "static create()" method manually
	CREATE_FUNC(Game_one);
};

class Game_two : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// ��ͣ
	void Pause(Ref* pSender);
	// ��Ϸͨ��
	void Success(Ref* pSender);
	// ������¼��ص�����
	void onMouseDown(cocos2d::EventMouse* event);
	// ����Ļ����ʾ���λ������
	void drawMousePositionLabel(const cocos2d::Vec2& position);
	// implement the "static create()" method manually
	CREATE_FUNC(Game_two);
};

#endif
