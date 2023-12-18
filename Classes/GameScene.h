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

	// ��ͣ
	void Pause(Ref* pSender);
	// ��Ϸͨ��
	void Success(Ref* pSender);
	// ������¼��ص�����
	void onMouseDown(cocos2d::EventMouse* event);
	// ����Ļ����ʾ���λ������
	void drawMousePositionLabel(const cocos2d::Vec2& position);
	// ��߷���������ʾ
	void createTower0(const std::string& tower0Image, const std::string& tower0BackImage,
		const std::string& towerImage, const std::string& towerBackImage,
		int upgradeCoins, float positionY, int index);
	// �ж��Ƿ�������߷�����
	int checkTower0Clicked(const cocos2d::Vec2& touchLocation);
	// ��Ҳ���ı�
	cocos2d::Label* insufficientGoldLabel;
	// ��ʾ��Ҳ���
	void showInsufficientGoldLabel();
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
	// ��߷���������ʾ
	void createTower0(const std::string& tower0Image, const std::string& tower0BackImage,
		const std::string& towerImage, const std::string& towerBackImage,
		int upgradeCoins, float positionY, int index);
	// �ж��Ƿ�������߷�����
	int checkTower0Clicked(const cocos2d::Vec2& touchLocation);
	// implement the "static create()" method manually
	CREATE_FUNC(Game_two);
};

#endif
