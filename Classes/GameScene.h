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
extern Vec2 towerPosition;  // 用于存储防御塔的位置
extern int tower0Clicked;
extern int already;//是否选中防御塔
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
	// 防御塔可放置位置
	const Vec2 pairxy[23] = {
		Vec2(155,211) ,Vec2(190,211) ,Vec2(190,177) ,Vec2(190,211) ,Vec2(225,211)
		,Vec2(225,177) ,Vec2(225,143) ,Vec2(225,109) ,Vec2(225,75)  ,Vec2(225,41)
		,Vec2(260,41)  ,Vec2(295,41)  ,Vec2(330,41)  ,Vec2(365,41)  ,Vec2(400,41)
		,Vec2(295,109) ,Vec2(330,109) ,Vec2(365,109) ,Vec2(400,109) ,Vec2(295,143)
		,Vec2(295,177) ,Vec2(295,211) ,Vec2(295,245) };
	// 添加侧边防御塔的图标
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
	// 防御塔组件图标
	cocos2d::Node* layout_delete;
	cocos2d::Node* layout_uplevel;
	cocos2d::Node* layout_return;
	cocos2d::Label* layout_coin;
	cocos2d::Label* layout_nowlevel;
	// 暂停
	void Pause(Ref* pSender);
	// 游戏失败
	void Default(Ref* pSender);
	// 点击侧边防御塔并放置
	void onMouseDown(cocos2d::EventMouse* event);
	void onMouseDown1(cocos2d::EventMouse* event);
	// 侧边防御塔的显示
	void createTower0(const std::string& towerImage, const std::string& towerBackImage,
		int upgradeCoins, float positionY, int index);
	// 判断是否点击到侧边防御塔
	int checkTower0Clicked(const cocos2d::Vec2& touchLocation);
	//建造所需要的钱
	int getTowerUpgradeCoins(int towerType);
	//更新金币的数值
	void updateGoldCoinsDisplay();
	//金币不足的标
	cocos2d::Label* insufficientGoldLabel;
	//显示金币不足
	void showInsufficientGoldLabel();
	// 放置位置错误的标
	cocos2d::Label* insufficientPlaceLabel;
	// 可放置位置边框
	cocos2d::Sprite* board[25];
	// 等级已满的标
	cocos2d::Label* insufficientLevelLabel;
	// 显示放置位置错误
	void showInsufficientPlaceLabel();
	// 显示等级已满
	void showInsufficientLevelLabel();
	// 显示灰色防御塔
	void showTowerGrey();
	// 定时器倒数
	virtual void step(float Dt);
	// 生成一个敌人
	void generateOneEnemy(vector<CEnemy*>& EnemyExist, int enemyType, double x, double y);
	// 生成一个波次的怪物，起始坐标为xy
	void generateflag(vector<int> flags, double x, double y);
	bool start_generate;
	void startgenerate(float dt);
	// 更新敌人坐标
	void Enemyupdate(float dt);
	// 更新萝卜血条
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
	// 防御塔可放置位置
	const Vec2 pairxy[27] = {
		Vec2(128,28) ,Vec2(162,28) ,Vec2(196,28),Vec2(230,28),Vec2(264,28),
		Vec2(298,28) ,Vec2(332,28) ,Vec2(366,28),Vec2(128,72),Vec2(128,160) ,
		Vec2(128,204),Vec2(128,116),Vec2(196,116) ,Vec2(230,116) ,Vec2(264,116),
		Vec2(298,116),Vec2(332,116),Vec2(366,116) ,Vec2(162,204),Vec2(196,204),
		Vec2(230,204),Vec2(264,204),Vec2(298,204) ,Vec2(332,204),Vec2(400,204),
		Vec2(400,248),Vec2(400,160) };
	// 添加侧边防御塔的图标
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
	// 防御塔组件图标
	cocos2d::Node* layout_delete;
	cocos2d::Node* layout_uplevel;
	cocos2d::Node* layout_return;
	cocos2d::Label* layout_coin;
	cocos2d::Label* layout_nowlevel;
	// 更新金币的数值
	void updateGoldCoinsDisplay();
	// 暂停
	void Pause(Ref* pSender);
	// 游戏失败
	void Default(Ref* pSender);
	// 点击侧边防御塔并放置
	void onMouseDown(cocos2d::EventMouse* event);
	void onMouseDown1(cocos2d::EventMouse* event);
	// 侧边防御塔的显示
	void createTower0(const std::string& towerImage, const std::string& towerBackImage,
		int upgradeCoins, float positionY, int index);
	// 判断是否点击到侧边防御塔
	int checkTower0Clicked(const cocos2d::Vec2& touchLocation);
	// 建造所需要的钱
	int getTowerUpgradeCoins(int towerType);
	// 金币不足的标
	cocos2d::Label* insufficientGoldLabel;
	// 显示金币不足
	void showInsufficientGoldLabel();
	// 等级已满的标
	cocos2d::Label* insufficientLevelLabel;
	// 放置位置错误的标
	cocos2d::Label* insufficientPlaceLabel;
	// 可放置位置边框
	cocos2d::Sprite* board[30];
	// 显示放置位置错误
	void showInsufficientPlaceLabel();
	// 显示灰色防御塔
	void showTowerGrey();
	// 显示等级已满
	void showInsufficientLevelLabel();
	// 定时器倒数
	virtual void step(float Dt);
	// 生成一个敌人
	void generateOneEnemy(vector<CEnemy*>& EnemyExist, int enemyType, double x, double y);
	// 生成一个波次的怪物，起始坐标为xy
	void generateflag(vector<int> flags, double x, double y);
	bool start_generate;
	void startgenerate(float dt);
	//更新敌人坐标
	void Enemyupdate(float dt);
	// 更新萝卜血条
	void carrotHealthUpdate(float dt);
	// implement the "static create()" method manually
	CREATE_FUNC(Game_two);
};
#endif