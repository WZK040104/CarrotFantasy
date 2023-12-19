#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "cocos/math/Vec2.h"
#include "AudioEngine.h"

USING_NS_CC;

extern int current_gold_coins;
extern Vec2 towerPosition;  // ���ڴ洢��������λ��
extern int tower0Clicked;
extern int already;//�Ƿ�ѡ�з�����
extern Vec2 mousePosition;

class Game_one : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// ��ͣ
	void Pause(Ref* pSender);
	// ��Ϸͨ��
	void Success(Ref* pSender);
	//�����߷�����������
	void onMouseDown(cocos2d::EventMouse* event);
	void onMouseDown1(cocos2d::EventMouse* event);
	// ����Ļ����ʾ���λ������
	void drawMousePositionLabel(const cocos2d::Vec2& position);
	//��߷���������ʾ
	void createTower0(const std::string& tower0Image, const std::string& tower0BackImage,
		const std::string& towerImage, const std::string& towerBackImage,
		int upgradeCoins, float positionY, int index);
	// �ж��Ƿ�������߷�����
	int checkTower0Clicked(const cocos2d::Vec2& touchLocation);
	//��������Ҫ��Ǯ
	int getTowerUpgradeCoins(int towerType);
	// ��Ҳ���ı�
	cocos2d::Label* insufficientGoldLabel;
	// ����λ�ô���ı�
	cocos2d::Label* insufficientPlaceLabel;
	// �ɷ���λ�ñ߿�
	cocos2d::Sprite* board[25];
	// �������ɷ���λ��
	const Vec2 pairxy[23] = {
		Vec2(155,211) ,Vec2(190,211) ,Vec2(190,177) ,Vec2(190,211) ,Vec2(225,211)
		,Vec2(225,177) ,Vec2(225,143) ,Vec2(225,109) ,Vec2(225,75)  ,Vec2(225,41)
		,Vec2(260,41)  ,Vec2(295,41)  ,Vec2(330,41)  ,Vec2(365,41)  ,Vec2(400,41)
		,Vec2(295,109) ,Vec2(330,109) ,Vec2(365,109) ,Vec2(400,109) ,Vec2(295,143)
		,Vec2(295,177) ,Vec2(295,211) ,Vec2(295,245) };
	// ��ʾ��Ҳ���
	void showInsufficientGoldLabel();
	// ��ʾ����λ�ô���
	void showInsufficientPlaceLabel();
	// ��ʱ������
	virtual void step(float Dt);
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
	//�����߷�����������
	void onMouseDown(cocos2d::EventMouse* event);
	void onMouseDown1(cocos2d::EventMouse* event);
	// ����Ļ����ʾ���λ������
	void drawMousePositionLabel(const cocos2d::Vec2& position);
	//��߷���������ʾ
	void createTower0(const std::string& tower0Image, const std::string& tower0BackImage,
		const std::string& towerImage, const std::string& towerBackImage,
		int upgradeCoins, float positionY, int index);
	// �ж��Ƿ�������߷�����
	int checkTower0Clicked(const cocos2d::Vec2& touchLocation);
	int getTowerUpgradeCoins(int towerType);
	cocos2d::Sprite* createTowerSprite(int towerType);
	// ��Ҳ���ı�
	cocos2d::Label* insufficientGoldLabel;
	// ����λ�ô���ı�
	cocos2d::Label* insufficientPlaceLabel;
	// �ɷ���λ�ñ߿�
	cocos2d::Sprite* board[30];
	// �������ɷ���λ��
	const Vec2 pairxy[27] = {
		 Vec2(128,28) ,Vec2(162,28) ,Vec2(196,28),Vec2(230,28),Vec2(264,28),
		 Vec2(298,28) ,Vec2(332,28) ,Vec2(366,28),Vec2(128,72),Vec2(128,160) ,
		 Vec2(128,204),Vec2(128,116),Vec2(196,116) ,Vec2(230,116) ,Vec2(264,116),
		 Vec2(298,116),Vec2(332,116),Vec2(366,116) ,Vec2(162,204),Vec2(196,204),
		 Vec2(230,204),Vec2(264,204),Vec2(298,204) ,Vec2(332,204),Vec2(400,204),
		 Vec2(400,248),Vec2(400,160) };
	// ��ʾ��Ҳ���
	void showInsufficientGoldLabel();
	// ��ʾ����λ�ô���
	void showInsufficientPlaceLabel();
	// ��ʱ������
	virtual void step(float Dt);
	// implement the "static create()" method manually
	CREATE_FUNC(Game_two);
};
#endif