#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "cocos/math/Vec2.h"
#include "AudioEngine.h"
#include "CEnemy.h"
#include <vector>
using namespace std;
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

	CEnemy _enemy;
	cocos2d::Label* mapnum;
	vector<int> flags;
	int current_flag;
	// �������ɷ���λ��
	const Vec2 pairxy[23] = {
		Vec2(155,211) ,Vec2(190,211) ,Vec2(190,177) ,Vec2(190,211) ,Vec2(225,211)
		,Vec2(225,177) ,Vec2(225,143) ,Vec2(225,109) ,Vec2(225,75)  ,Vec2(225,41)
		,Vec2(260,41)  ,Vec2(295,41)  ,Vec2(330,41)  ,Vec2(365,41)  ,Vec2(400,41)
		,Vec2(295,109) ,Vec2(330,109) ,Vec2(365,109) ,Vec2(400,109) ,Vec2(295,143)
		,Vec2(295,177) ,Vec2(295,211) ,Vec2(295,245) };
	// ��Ӳ�߷�������ͼ��
	cocos2d::Sprite* tower_zero0;
	cocos2d::Sprite* tower_one0;
	cocos2d::Sprite* tower_two0;
	cocos2d::Sprite* tower_three0;
	cocos2d::Sprite* tower_back0;
	cocos2d::Sprite* tower_back1;
	cocos2d::Sprite* tower_back2;
	cocos2d::Sprite* tower_back3;
	cocos2d::Label* buildcoins0;
	cocos2d::Label* buildcoins1;
	cocos2d::Label* buildcoins2;
	cocos2d::Label* buildcoins3;
	// ���������ͼ��
	cocos2d::Node* layout_delete;
	cocos2d::Node* layout_uplevel;
	cocos2d::Node* layout_return;
	cocos2d::Label* layout_coin;
	cocos2d::Label* layout_nowlevel;
	// ��ͣ
	void Pause(Ref* pSender);
	// ��Ϸʧ��
	void Default(Ref* pSender);
	// �����߷�����������
	void onMouseDown(cocos2d::EventMouse* event);
	void onMouseDown1(cocos2d::EventMouse* event);
	// ��߷���������ʾ
	void createTower0(const std::string& towerImage, const std::string& towerBackImage,
		int upgradeCoins, float positionY, int index);
	// �ж��Ƿ�������߷�����
	int checkTower0Clicked(const cocos2d::Vec2& touchLocation);
	//��������Ҫ��Ǯ
	int getTowerUpgradeCoins(int towerType);
	//���½�ҵ���ֵ
	void updateGoldCoinsDisplay();
	//��Ҳ���ı�
	cocos2d::Label* insufficientGoldLabel;
	//��ʾ��Ҳ���
	void showInsufficientGoldLabel();
	// ����λ�ô���ı�
	cocos2d::Label* insufficientPlaceLabel;
	// �ɷ���λ�ñ߿�
	cocos2d::Sprite* board[25];
	// �ȼ������ı�
	cocos2d::Label* insufficientLevelLabel;
	// ��ʾ����λ�ô���
	void showInsufficientPlaceLabel();
	// ��ʾ�ȼ�����
	void showInsufficientLevelLabel();
	// ��ʾ��ɫ������
	void showTowerGrey();
	// ��ʱ������
	virtual void step(float Dt);
	// ����һ������
	void generateOneEnemy(vector<CEnemy*>& EnemyExist, int enemyType, double x, double y);
	// ����һ�����εĹ����ʼ����Ϊxy
	void generateflag(vector<int> flags, double x, double y);
	bool start_generate;
	void startgenerate(float dt);
	// ���µ�������
	void Enemyupdate(float dt);
	// �����ܲ�Ѫ��
	void carrotHealthUpdate(float dt);
	// implement the "static create()" method manually
	CREATE_FUNC(Game_one);
};

class Game_two : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	cocos2d::Label* mapnum;
	vector<int> flags;
	int current_flag;
	// �������ɷ���λ��
	const Vec2 pairxy[27] = {
		Vec2(128,28) ,Vec2(162,28) ,Vec2(196,28),Vec2(230,28),Vec2(264,28),
		Vec2(298,28) ,Vec2(332,28) ,Vec2(366,28),Vec2(128,72),Vec2(128,160) ,
		Vec2(128,204),Vec2(128,116),Vec2(196,116) ,Vec2(230,116) ,Vec2(264,116),
		Vec2(298,116),Vec2(332,116),Vec2(366,116) ,Vec2(162,204),Vec2(196,204),
		Vec2(230,204),Vec2(264,204),Vec2(298,204) ,Vec2(332,204),Vec2(400,204),
		Vec2(400,248),Vec2(400,160) };
	// ��Ӳ�߷�������ͼ��
	cocos2d::Sprite* tower_zero0;
	cocos2d::Sprite* tower_one0;
	cocos2d::Sprite* tower_two0;
	cocos2d::Sprite* tower_three0;
	cocos2d::Sprite* tower_back0;
	cocos2d::Sprite* tower_back1;
	cocos2d::Sprite* tower_back2;
	cocos2d::Sprite* tower_back3;
	cocos2d::Label* buildcoins0;
	cocos2d::Label* buildcoins1;
	cocos2d::Label* buildcoins2;
	cocos2d::Label* buildcoins3;
	// ���������ͼ��
	cocos2d::Node* layout_delete;
	cocos2d::Node* layout_uplevel;
	cocos2d::Node* layout_return;
	cocos2d::Label* layout_coin;
	cocos2d::Label* layout_nowlevel;
	// ���½�ҵ���ֵ
	void updateGoldCoinsDisplay();
	// ��ͣ
	void Pause(Ref* pSender);
	// ��Ϸʧ��
	void Default(Ref* pSender);
	// �����߷�����������
	void onMouseDown(cocos2d::EventMouse* event);
	void onMouseDown1(cocos2d::EventMouse* event);
	// ��߷���������ʾ
	void createTower0(const std::string& towerImage, const std::string& towerBackImage,
		int upgradeCoins, float positionY, int index);
	// �ж��Ƿ�������߷�����
	int checkTower0Clicked(const cocos2d::Vec2& touchLocation);
	// ��������Ҫ��Ǯ
	int getTowerUpgradeCoins(int towerType);
	// ��Ҳ���ı�
	cocos2d::Label* insufficientGoldLabel;
	// ��ʾ��Ҳ���
	void showInsufficientGoldLabel();
	// �ȼ������ı�
	cocos2d::Label* insufficientLevelLabel;
	// ����λ�ô���ı�
	cocos2d::Label* insufficientPlaceLabel;
	// �ɷ���λ�ñ߿�
	cocos2d::Sprite* board[30];
	// ��ʾ����λ�ô���
	void showInsufficientPlaceLabel();
	// ��ʾ��ɫ������
	void showTowerGrey();
	// ��ʾ�ȼ�����
	void showInsufficientLevelLabel();
	// ��ʱ������
	virtual void step(float Dt);
	// ����һ������
	void generateOneEnemy(vector<CEnemy*>& EnemyExist, int enemyType, double x, double y);
	// ����һ�����εĹ����ʼ����Ϊxy
	void generateflag(vector<int> flags, double x, double y);
	bool start_generate;
	void startgenerate(float dt);
	//���µ�������
	void Enemyupdate(float dt);
	// �����ܲ�Ѫ��
	void carrotHealthUpdate(float dt);
	// implement the "static create()" method manually
	CREATE_FUNC(Game_two);
};
#endif