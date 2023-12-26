#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "Gamepause.h"
#include "PlaceTower.h"
#include "GameEnd.h"
#include "GBKtoUTF-8.h"
#include "Tower_kind.h"
#include "CEnemy.h"
#include "Enemy_kind.h"
#include "Enemy_kind.h"
#include "GenerateEnemy.h"
#include "GameDefault.h"
#include <algorithm>

USING_NS_CC;

using namespace std;
using namespace cocos2d::ui;

extern int countnum;
extern bool map_two_continue;

// 萝卜相关属性
extern int coins[4];	//1级升2级需要的金币为 coins[1] 
extern int carrot_health[5];//1级的血量为 carrot_health[1] 
extern int carrot_level;
extern int carrot_HP;

Scene* Game_two::createScene()
{
	Scene *scene = Scene::create();
	Game_two *layer = Game_two::create();
	scene->addChild(layer);
	return scene;
}

// 找不到文件时抛出异常
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// 添加侧边防御塔的图标
void Game_two::createTower0(const std::string& towerImage, const std::string& towerBackImage,
	int upgradeCoins, float positionY, int index)
{
	auto tower = Sprite::create(towerImage);
	auto tower_back = Sprite::create(towerBackImage);
	tower_back->setPosition(Vec2(42, positionY));
	this->addChild(tower_back, 1);  // 防御塔背景
	tower->setPosition(Vec2(42, positionY));  // 侧边防御塔位置
	this->addChild(tower, 1);

	Label* build = Label::createWithTTF(to_string(upgradeCoins), "fonts/Marker Felt.ttf", 13);  // 添加文字，需要消耗的金币数量
	if (build == nullptr)
		problemLoading("'fonts/Marker Felt.ttf'");
	else
	{
		build->setPosition(Vec2(63, positionY - 12));  // 添加的防御塔建造所需要的钱的位置
		this->addChild(build, 1);
	}
	build->setColor(Color3B(0, 0, 0));  // 黑色
}

bool Game_two::init()
{
	// 所有的初始化在这里：清空现有防御塔，重置金币，重置一切
	TowerExist.clear();
	current_gold_coins = 1000;
	current_flag = 1;
	carrot_level = 1;
	carrot_HP = 5;

	if (!Scene::init())
	{
		return false;
	}

	map_two_continue = true;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 加入背景图片
	auto map_two = Sprite::create("GameBackground_two.png");
	if (map_two == nullptr)
	{
		problemLoading("'GameBackground_two.png'");
	}
	else
	{
		map_two->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		this->addChild(map_two, 0);
	}

	// 加入上边栏图片
	auto upperboard = Sprite::create("Upperboard.png");
	if (upperboard == nullptr)
	{
		problemLoading("'Upperboard.png'");
	}
	else
	{
		upperboard->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - upperboard->getContentSize().height / 2));
		this->addChild(upperboard, 1);
	}

	// 暂停功能
	auto pauseItem = MenuItemImage::create("Pause.png",
		"Pause.png", CC_CALLBACK_1(Game_two::Pause, this));

	if (pauseItem == nullptr
		|| pauseItem->getContentSize().width <= 0
		|| pauseItem->getContentSize().height <= 0)
	{
		problemLoading("'Pause.png'");
	}
	else
	{
		pauseItem->setPosition(Vec2(origin.x + 160, origin.y + 143));
	}

	// 创建菜单
	Vector<MenuItem*> MenuItems;
	MenuItems.pushBack(pauseItem);
	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 1);

	// 添加 "carrot" 图片
	auto carrot_pic = Button::create("carrot.png", "carrot.png");
	carrot_pic->setPosition(Vec2(95, 248));
	this->addChild(carrot_pic, 1);

	// 升级按钮
	auto levelupcarrotbutton = Button::create("levelup.png");
	levelupcarrotbutton->setPosition(Vec2(106, 224));
	this->addChild(levelupcarrotbutton, 2, "carrot_u");
	levelupcarrotbutton->setVisible(false);

	// 退出按钮
	auto returncarrotbutton = Button::create("exit.png");
	returncarrotbutton->setPosition(Vec2(90, 225));
	this->addChild(returncarrotbutton, 2, "carrot_r");
	returncarrotbutton->setVisible(false);

	// 升级金币标签
	auto levelupcarrotcoin = Label::createWithTTF("20", "fonts/Marker Felt.ttf", 10);
	levelupcarrotcoin->setColor(Color3B(255, 255, 0));
	levelupcarrotcoin->setVisible(false);
	levelupcarrotcoin->setPosition(Vec2(116, 224));
	this->addChild(levelupcarrotcoin, 2, "carrot_c");

	// 等级标签
	auto carrotlevel = Label::createWithTTF("Lv.1", "fonts/Marker Felt.ttf", 10);
	carrotlevel->setColor(Color3B(255, 0, 0));
	carrotlevel->setVisible(false);
	carrotlevel->setPosition(Vec2(95, 268));
	this->addChild(carrotlevel, 2, "carrot_l");

	// 点击萝卜图片
	carrot_pic->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED: {
			layout_uplevel = this->getChildByName("carrot_u");
			layout_return = this->getChildByName("carrot_r");
			layout_coin = (Label*)(getChildByName("carrot_c"));
			layout_nowlevel = (Label*)(getChildByName("carrot_l"));

			int money = coins[carrot_level];
			layout_coin->setString(std::to_string(money));
			std::string levelname = "Lv." + std::to_string(carrot_level);
			layout_nowlevel->setString(levelname);

			layout_uplevel->setVisible(true);
			layout_return->setVisible(true);
			layout_coin->setVisible(true);
			layout_nowlevel->setVisible(true);
		}
			break;
		default:
			break;
		}
	});

	// 点击萝卜的返回按钮
	returncarrotbutton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED: {
			layout_uplevel = this->getChildByName("carrot_u");
			layout_return = this->getChildByName("carrot_r");
			layout_coin = (Label*)(getChildByName("carrot_c"));
			layout_nowlevel = (Label*)(getChildByName("carrot_l"));
			layout_uplevel->setVisible(false);
			layout_return->setVisible(false);
			layout_coin->setVisible(false);
			layout_nowlevel->setVisible(false);
		}
			break;
		default:
			break;
		}
	});

	// 萝卜升级
	levelupcarrotbutton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED: {
			layout_uplevel = this->getChildByName("carrot_u");
			layout_return = this->getChildByName("carrot_r");
			layout_coin = (Label*)(getChildByName("carrot_c"));
			layout_nowlevel = (Label*)(getChildByName("carrot_l"));
			if (carrot_level <= 3)
			{
				if (current_gold_coins >= coins[carrot_level]) {
					current_gold_coins -= coins[carrot_level];
					carrot_level++;
					carrot_HP += 5;
					if (carrot_HP > carrot_health[carrot_level])
						carrot_HP = carrot_health[carrot_level];
					updateGoldCoinsDisplay();
					showTowerGrey();
				}
				else
					showInsufficientGoldLabel();
			}
			else
			{
				showInsufficientLevelLabel();
				layout_uplevel->setVisible(false);
			}
			layout_uplevel->setVisible(false);
			layout_return->setVisible(false);
			layout_coin->setVisible(false);
			layout_nowlevel->setVisible(false);
		}
			break;
		default:
			break;
		}
	});

	// 萝卜血条背景
	auto CarrotHealthBack = Sprite::create("CarrotHealthBack.png");
	CarrotHealthBack->setPosition(Vec2(95, 278));
	this->addChild(CarrotHealthBack, 1);

	// 添加萝卜血条
	ProgressTimer* healthBar = ProgressTimer::create(Sprite::create("HealthBar.png"));
	healthBar->setType(ProgressTimer::Type::BAR);
	healthBar->setMidpoint(Vec2(0, 0.5));
	healthBar->setBarChangeRate(Vec2(1, 0));
	healthBar->setPosition(Vec2(95, 278)); 
	healthBar->setPercentage(100.0f);
	this->addChild(healthBar, 2, "healthBar");
	this->schedule(CC_SCHEDULE_SELECTOR(Game_two::carrotHealthUpdate), 1.0f / 60.0f);

	// 添加出怪牌图片
	auto GuideBoard = Sprite::create("GuideBoard.png");
	if (GuideBoard)
	{
		GuideBoard->setPosition(Vec2(424, 75)); //出怪牌位置
		this->addChild(GuideBoard, 1);
	}
	else
	{
		problemLoading("'GuideBoard.png'");
	}

	// 添加文字
	auto countdown = Label::createWithTTF("Monsters strike 20 seconds later", "fonts/Marker Felt.ttf", 14);
	if (countdown == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		countdown->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - countdown->getContentSize().height - 1));
		countdown->setColor(Color3B(255, 255, 255));
		this->addChild(countdown, 2, 1000);
		schedule(CC_CALLBACK_1(Game_two::step, this), 1.0f, "step_key");
	}

	//显示侧边的防御塔0
	createTower0("tower_zero.png", "tower_back.png", tower0_upgrade_coins[0], 230, 0);

	//显示侧边的防御塔1
	createTower0("tower_one.png", "tower_back.png", tower1_upgrade_coins[0], 185, 1);

	//显示侧边的防御塔2
	createTower0("tower_two.png", "tower_back.png", tower2_upgrade_coins[0], 140, 2);

	//显示侧边的防御塔3
	createTower0("tower_three.png", "tower_back.png", tower3_upgrade_coins[0], 95, 3);

	// 显示侧边的灰色防御塔
	{
		tower_zero0 = Sprite::create("tower_zero0.png");
		tower_back0 = Sprite::create("tower_back0.png");
		tower_back0->setPosition(Vec2(42, 230));
		tower_zero0->setPosition(Vec2(42, 230));  // 侧边防御塔位置
		tower_back0->setVisible(false);
		tower_zero0->setVisible(false);
		this->addChild(tower_back0, 1);
		this->addChild(tower_zero0, 1);
		buildcoins0 = Label::createWithTTF(to_string(getTowerUpgradeCoins(0)), "fonts/Marker Felt.ttf", 13);  // 添加文字，需要消耗的金币数量
		buildcoins0->setPosition(Vec2(63, 230 - 12));
		buildcoins0->setVisible(false);
		buildcoins0->setColor(Color3B(0, 0, 0));
		this->addChild(buildcoins0, 1);

		tower_one0 = Sprite::create("tower_one0.png");
		tower_back1 = Sprite::create("tower_back0.png");
		tower_back1->setPosition(Vec2(42, 185));
		tower_one0->setPosition(Vec2(42, 185));  // 侧边防御塔位置
		tower_back1->setVisible(false);
		tower_one0->setVisible(false);
		this->addChild(tower_back1, 1);
		this->addChild(tower_one0, 1);
		buildcoins1 = Label::createWithTTF(to_string(getTowerUpgradeCoins(0)), "fonts/Marker Felt.ttf", 13);  // 添加文字，需要消耗的金币数量
		buildcoins1->setPosition(Vec2(63, 185 - 12));
		buildcoins1->setVisible(false);
		buildcoins1->setColor(Color3B(0, 0, 0));
		this->addChild(buildcoins1, 1);

		tower_two0 = Sprite::create("tower_two0.png");
		tower_back2 = Sprite::create("tower_back0.png");
		tower_back2->setPosition(Vec2(42, 140));
		tower_two0->setPosition(Vec2(42, 140));  // 侧边防御塔位置
		tower_back2->setVisible(false);
		tower_two0->setVisible(false);
		this->addChild(tower_back2, 1);
		this->addChild(tower_two0, 1);
		buildcoins2 = Label::createWithTTF(to_string(getTowerUpgradeCoins(0)), "fonts/Marker Felt.ttf", 13);  // 添加文字，需要消耗的金币数量
		buildcoins2->setPosition(Vec2(63, 140 - 12));
		buildcoins2->setVisible(false);
		buildcoins2->setColor(Color3B(0, 0, 0));
		this->addChild(buildcoins2, 1);

		tower_three0 = Sprite::create("tower_three0.png");
		tower_back3 = Sprite::create("tower_back0.png");
		tower_back3->setPosition(Vec2(42, 95));
		tower_three0->setPosition(Vec2(42, 95));  // 侧边防御塔位置
		tower_back3->setVisible(false);
		tower_three0->setVisible(false);
		this->addChild(tower_back3, 1);
		this->addChild(tower_three0, 1);
		buildcoins3 = Label::createWithTTF(to_string(getTowerUpgradeCoins(0)), "fonts/Marker Felt.ttf", 13);  // 添加文字，需要消耗的金币数量
		buildcoins3->setPosition(Vec2(63, 95 - 12));
		buildcoins3->setVisible(false);
		buildcoins3->setColor(Color3B(0, 0, 0));
		this->addChild(buildcoins3, 1);
	}

	// 初始化金币不足的标签
	insufficientGoldLabel = Label::createWithTTF("not enough gold coins!", "fonts/Marker Felt.ttf", 14);
	insufficientGoldLabel->setColor(Color3B(255, 0, 0));  // 红色
	insufficientGoldLabel->setVisible(false);  // 初始时设置为不可见
	insufficientGoldLabel->setPosition(Vec2(90, 60));//设置位置
	this->addChild(insufficientGoldLabel, 1);

	// 初始化放置位置错误的标签
	insufficientPlaceLabel = Label::createWithTTF("wrong place!", "fonts/Marker Felt.ttf", 14);
	insufficientPlaceLabel->setColor(Color3B(255, 0, 0));  // 红色
	insufficientPlaceLabel->setVisible(false);  // 初始时设置为不可见
	insufficientPlaceLabel->setPosition(Vec2(90, 60));//设置位置
	this->addChild(insufficientPlaceLabel, 1);

	// 初始化等级已满的标签
	insufficientLevelLabel = Label::createWithTTF("reach highest level!", "fonts/Marker Felt.ttf", 14);
	insufficientLevelLabel->setColor(Color3B(255, 0, 0));  // 红色
	insufficientLevelLabel->setVisible(false);  // 初始时设置为不可见
	insufficientLevelLabel->setPosition(Vec2(90, 60));//设置位置
	this->addChild(insufficientLevelLabel, 1);

	// 防御塔可放置位置边框
	for (unsigned int i = 1; i <= sizeof(pairxy) / sizeof(pairxy[0]); i++) {
		board[i] = Sprite::create("board.png");
		if (board[i] == nullptr)
		{
			problemLoading("'board.png'");
		}
		else
		{
			board[i]->setPosition(pairxy[i - 1]);
			this->addChild(board[i], 1);
			board[i]->setVisible(false);
		}
	}

	// 加入金币图片
	auto moneypic = Sprite::create("Money.png");
	if (moneypic == nullptr)
	{
		problemLoading("'Money.png'");
	}
	else
	{
		moneypic->setPosition(Vec2(origin.x + 18, origin.y + visibleSize.height - 16));
		this->addChild(moneypic, 2);
	}

	// 添加文字 金币数量
	mapnum = Label::createWithTTF(to_string(current_gold_coins), "fonts/Marker Felt.ttf", 18);
	if (mapnum == nullptr) {
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else {
		mapnum->setPosition(Vec2(origin.x + 48, origin.y + visibleSize.height - 17));
		this->addChild(mapnum, 2);
		mapnum->setColor(Color3B(255, 255, 0));
	}
	updateGoldCoinsDisplay();
	showTowerGrey();

	// 添加鼠标位置显示
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(Game_two::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
	auto mouseListener1 = EventListenerMouse::create();
	mouseListener1->onMouseDown = CC_CALLBACK_1(Game_two::onMouseDown1, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener1, this);

	EnemyExist.clear();
	flags = { 1,1,-1, 2,2,-1 , 3,3,-1 ,4,4, };

	generateflag(flags, 420, 72);

	double x_ = 420, y_ = 72;
	for (auto it_enmey = EnemyExist.begin(); it_enmey != EnemyExist.end(); ++it_enmey)
	{
		switch ((*it_enmey)->enemytype)
		{
		case -1:
			(*it_enmey)->enemySprite = nullptr;
			x_ += 300;
			current_flag++;
			continue;
		case 0:
			//(*it_enmey)->enemySprite = Sprite::create("Enemy_zero.png");
			break;
		case 1:
			(*it_enmey)->enemySprite = Sprite::create("Enemy_one.png");
			(*it_enmey)->enemyHealthbar_back = Sprite::create("CarrotHealthBack.png");
			(*it_enmey)->enemyHealthbar = ProgressTimer::create(Sprite::create("HealthBar.png"));
			break;
		case 2:
			(*it_enmey)->enemySprite = Sprite::create("Enemy_two.png");
			(*it_enmey)->enemyHealthbar_back = Sprite::create("CarrotHealthBack.png");
			(*it_enmey)->enemyHealthbar = ProgressTimer::create(Sprite::create("HealthBar.png"));
			break;
		case 3:
			(*it_enmey)->enemySprite = Sprite::create("Enemy_three.png");
			(*it_enmey)->enemyHealthbar_back = Sprite::create("CarrotHealthBack.png");
			(*it_enmey)->enemyHealthbar = ProgressTimer::create(Sprite::create("HealthBar.png"));
			break;
		case 4:
			(*it_enmey)->enemySprite = Sprite::create("Enemy_four.png");
			(*it_enmey)->enemyHealthbar_back = Sprite::create("CarrotHealthBack.png");
			(*it_enmey)->enemyHealthbar = ProgressTimer::create(Sprite::create("HealthBar.png"));
			break;
		default:
			break;
		}

		(*it_enmey)->set_x(x_);
		(*it_enmey)->set_y(y_);
		(*it_enmey)->enemySprite->setPosition(Vec2(x_, y_));
		(*it_enmey)->enemyHealthbar_back->setPosition(Vec2(x_, y_ + 20));
		(*it_enmey)->enemyHealthbar->setPosition(Vec2(x_, y_ + 20));
		(*it_enmey)->enemyHealthbar->setType(ProgressTimer::Type::BAR);
		(*it_enmey)->enemyHealthbar->setMidpoint(Vec2(0, 0.5)); // 设置起始位置为水平左边中点
		(*it_enmey)->enemyHealthbar->setBarChangeRate(Vec2(1, 0)); // 设置减少方向为水平向左
		(*it_enmey)->enemyHealthbar->setPercentage(100.0f);

		if (x_ >= 420)
		{
			(*it_enmey)->enemySprite->setVisible(false);
			(*it_enmey)->enemyHealthbar_back->setVisible(false);
			(*it_enmey)->enemyHealthbar->setVisible(false);
		}
		else
		{
			(*it_enmey)->enemySprite->setVisible(true);
			(*it_enmey)->enemyHealthbar_back->setVisible(true);
			(*it_enmey)->enemyHealthbar->setVisible(true);
		}
		x_ += 50;

		this->addChild((*it_enmey)->enemySprite, 1);
		this->addChild((*it_enmey)->enemyHealthbar_back, 1);
		this->addChild((*it_enmey)->enemyHealthbar, 2, "HealthBar.png");
	}

	// 每帧调用 update 函数
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(Game_two::startgenerate), 20.0f);
	this->schedule(CC_SCHEDULE_SELECTOR(Game_two::Enemyupdate), 1.0f / 60.0f);
	return true;
}

// 更新怪物位置
void Game_two::Enemyupdate(float dt)// 访问全体存在的怪物并且更改其坐标
{
	if (start_generate)
	{
		double speed = 0.5;
		float new_x, new_y;
		for (auto it_enmey = EnemyExist.begin(); it_enmey != EnemyExist.end();)
		{
			if ((*it_enmey)->alive())
			{
				speed = (*it_enmey)->get_velocity();
				new_x = (*it_enmey)->EnemyPositionX(), new_y = (*it_enmey)->EnemyPositionY();

				if (new_x >= 420)
					new_x -= 0.5;
				else if (new_x >= 162 && new_y == 72)
					new_x -= speed;
				else if (new_x >= 161 && new_y >= 72 && new_y <= 160)
					new_y += speed;
				else if (new_y <= 161 && new_x >= 161 && new_x <= 366)
					new_x += speed;
				else if (new_x <= 367 && new_y >= 160 && new_y <= 248)
					new_y += speed;
				else if (new_y <= 249 && new_x >= 120 && new_x <= 367)
					new_x -= speed;
				else if (new_x <= 120 && new_y <= 249) {
					(*it_enmey)->HP_calculate(10000);
					carrot_HP -=1;
					// 游戏结束
					if (carrot_HP <= 0) {
						// 得到窗口的大小
						auto visibleSize = Director::getInstance()->getVisibleSize();
						RenderTexture *renderTexture = RenderTexture::create(visibleSize.width + 48, visibleSize.height);

						// 遍历当前类的所有子节点信息，画入renderTexture中。
						// 这里类似截图。
						renderTexture->begin();
						this->getParent()->visit();
						renderTexture->end();

						Director::getInstance()->pushScene(GameDefault::scene(renderTexture));
					}
				}

				(*it_enmey)->enemySprite->setPosition(Vec2(new_x, new_y));
				(*it_enmey)->enemyHealthbar_back->setPosition(Vec2(new_x, new_y + 20));
				(*it_enmey)->enemyHealthbar->setPosition(Vec2(new_x, new_y + 20));
				(*it_enmey)->enemyHealthbar->setPercentage((*it_enmey)->getHPpercentage() * 100);

				(*it_enmey)->set_x(new_x);
				(*it_enmey)->set_y(new_y);
				if (new_x >= 420)
				{
					(*it_enmey)->enemySprite->setVisible(false);
					(*it_enmey)->enemyHealthbar_back->setVisible(false);
					(*it_enmey)->enemyHealthbar->setVisible(false);
				}
				else
				{
					(*it_enmey)->enemySprite->setVisible(true);
					(*it_enmey)->enemyHealthbar_back->setVisible(true);
					(*it_enmey)->enemyHealthbar->setVisible(true);
				}

			}
			else
			{
				// 移除怪物精灵和删除怪物对象
				if ((*it_enmey)->enemySprite)
				{
					(*it_enmey)->enemySprite->removeFromParent();
					(*it_enmey)->enemyHealthbar->removeFromParent();
					(*it_enmey)->enemyHealthbar_back->removeFromParent();
				}
				it_enmey = EnemyExist.erase(it_enmey);
				// 游戏结束的标志
				if (EnemyExist.empty()&& carrot_HP>0)
				{
					// 得到窗口的大小
					auto visibleSize = Director::getInstance()->getVisibleSize();
					RenderTexture *renderTexture = RenderTexture::create(visibleSize.width + 48, visibleSize.height);

					// 遍历当前类的所有子节点信息，画入renderTexture中。
					// 这里类似截图。
					renderTexture->begin();
					this->getParent()->visit();
					renderTexture->end();

					Director::getInstance()->pushScene(GameEnd::scene(renderTexture));
				}
				continue;  // 继续下一次循环，不需要执行 delete 操作
			}
			++it_enmey;
		}
	}
}

// 萝卜血条更新
void Game_two::Game_two::carrotHealthUpdate(float Dt)
{
	auto healthBar = (ProgressTimer*)(getChildByName("healthBar"));
	double percent = carrot_HP*100.0 / carrot_health[carrot_level];
	healthBar->setPercentage(percent);
}

// 在怪物出生点生成一只怪物
void Game_two::generateOneEnemy(vector<CEnemy*>& EnemyExist, int enemyType, double x, double y)
{
	CEnemy* newEnemy = nullptr;

	// 根据 enemyType 创建不同类型的防御塔
	switch (enemyType) {
	case 0:
		newEnemy = new Enemy0();
		break;
	case 1:
		newEnemy = new Enemy1();
		newEnemy->initial(1, 30, 0.5, 10, 0, 0);
		break;
	case 2:
		newEnemy = new Enemy2();
		newEnemy->initial(2, 30, 0.5, 10, 0, 0);
		break;
	case 3:
		newEnemy = new Enemy3();
		newEnemy->initial(3, 30, 1, 15, 0, 0);
		break;
	case 4:
		newEnemy = new Enemy4();
		newEnemy->initial(4, 100, 0.75, 30, 0, 0);
		break;

	default:
		newEnemy = new Enemy4();
		newEnemy->initial(-1, 0, 0, 0, 0, 0);
		break;
	}

	if (newEnemy)
	{
		newEnemy->set_x(x);
		newEnemy->set_y(y);
		EnemyExist.push_back(newEnemy);
	}
}

// 生成一个波次的怪物，起始坐标为xy
void Game_two::generateflag(vector<int> flags, double x, double y)
{
	for (unsigned int i = 0; i < flags.size(); i++)
	{
		generateOneEnemy(EnemyExist, flags[i], x, y);
	}
}

// 更新金币的数量
void Game_two::updateGoldCoinsDisplay()
{
	// 更新文字金币数量
	if (mapnum != nullptr) {
		mapnum->setString(to_string(current_gold_coins));
	}
}

// 开始释放怪物
void Game_two::startgenerate(float dt)
{
	start_generate = true;
}

// 更新灰色防御塔是否可见
void Game_two::showTowerGrey()
{
	if (current_gold_coins < getTowerUpgradeCoins(0))
	{
		tower_back0->setVisible(true);
		tower_zero0->setVisible(true);
		buildcoins0->setVisible(true);
	}
	else
	{
		tower_back0->setVisible(false);
		tower_zero0->setVisible(false);
		buildcoins0->setVisible(false);
	}
	if (current_gold_coins < getTowerUpgradeCoins(1))
	{
		tower_back1->setVisible(true);
		tower_one0->setVisible(true);
		buildcoins1->setVisible(true);
	}
	else
	{
		tower_back1->setVisible(false);
		tower_one0->setVisible(false);
		buildcoins1->setVisible(false);
	}
	if (current_gold_coins < getTowerUpgradeCoins(2))
	{
		tower_back2->setVisible(true);
		tower_two0->setVisible(true);
		buildcoins2->setVisible(true);
	}
	else
	{
		tower_back2->setVisible(false);
		tower_two0->setVisible(false);
		buildcoins2->setVisible(false);
	}
	if (current_gold_coins < getTowerUpgradeCoins(3))
	{
		tower_back3->setVisible(true);
		tower_three0->setVisible(true);
		buildcoins3->setVisible(true);
	}
	else
	{
		tower_back3->setVisible(false);
		tower_three0->setVisible(false);
		buildcoins0->setVisible(false);
	}
}

// 暂停游戏
void Game_two::Pause(Ref* pSender)
{
	// 得到窗口的大小
	auto visibleSize = Director::getInstance()->getVisibleSize();
	RenderTexture *renderTexture = RenderTexture::create(visibleSize.width+48, visibleSize.height);

	// 遍历当前类的所有子节点信息，画入renderTexture中。
	// 这里类似截图。
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	Director::getInstance()->pushScene(Gamepause::scene(renderTexture));
}

// 建造所需要的金币
int Game_two::getTowerUpgradeCoins(int towerType)
{
	switch (towerType)
	{
	case 0:
		return tower0_upgrade_coins[0];
	case 1:
		return tower1_upgrade_coins[0];
	case 2:
		return tower2_upgrade_coins[0];
	case 3:
		return tower3_upgrade_coins[0];
	default:
		return 0;
	}
}

// 处理xy的值
bool deal_with_xy2(double &x, double& y)
{
	if (x > 67 && x <= 111)
		x = 94;
	else if (x > 111 && x <= 145)
		x = 128;
	else if (x > 145 && x <= 179)
		x = 162;
	else if (x > 179 && x <= 213)
		x = 196;
	else if (x > 213 && x <= 247)
		x = 230;
	else if (x > 247 && x <= 281)
		x = 264;
	else if (x > 281 && x <= 315)
		x = 298;
	else if (x > 315 && x <= 349)
		x = 332;
	else if (x > 349 && x <= 383)
		x = 366;
	else if (x > 383 && x <= 417)
		x = 400;

	if (y > 6 && y <= 50)
		y = 28;
	else if (y > 50 && y <= 94)
		y = 72;
	else if (y > 94 && y <= 138)
		y = 116;
	else if (y > 138 && y <= 182)
		y = 160;
	else if (y > 182 && y <= 226)
		y = 204;
	else if (y > 226 && y <= 270)
		y = 248;

	if (x > 417 || x <= 67 || y > 270 || y <= 6)
		return 0;
	if (y == 248 && x > 67 && x < 383)
		return 0;
	if (y == 160 && x > 145 && x < 383)
		return 0;
	if (y == 72 && x > 145 && x < 417)
		return 0;
	if (x == 162 && y > 50 && y < 182)
		return 0;
	if (x == 366 && y > 138 && y < 270)
		return 0;

	for (unsigned int i = 0; i < TowerExist.size(); i++)
	{
		if (x == TowerExist[i].getPositionX() && y == TowerExist[i].getPositionY())
			return 0;
	}

	return 1;
}

// 已经选中防御塔准备放置
void Game_two::onMouseDown(EventMouse* event)
{
	mousePosition = this->convertToNodeSpace(event->getLocationInView());

	if (already == 1)
	{
		for (unsigned int i = 1; i <= sizeof(pairxy) / sizeof(pairxy[0]); i++)
		{
			board[i]->setVisible(true);
		}

		towerPosition = mousePosition;
		double x = towerPosition.x, y = towerPosition.y;
		bool place_success = deal_with_xy2(x, y);//处理xy坐标，是否成功放置
		bool flag = false; // 是否放在了允许放置的格子内
		for (unsigned int i = 1; i <= sizeof(pairxy) / sizeof(pairxy[0]); i++) {
			if (pairxy[i - 1] == Vec2(x, y))
			{
				flag = true;
				break;
			}
		}

		if (flag && place_success)
		{
			towerPosition = Vec2(x, y);
			placeTower(TowerExist, tower0Clicked, x, y);
			current_gold_coins -= getTowerUpgradeCoins(tower0Clicked);
			updateGoldCoinsDisplay();
			showTowerGrey();
			// 根据点击的防御塔类型创建相应的 Button
			Button* towerSprite;
			switch (tower0Clicked)
			{
			case 0:
				towerSprite = Button::create("tower_zero.png", "tower_zero.png");
				break;
			case 1:
				towerSprite = Button::create("tower_one.png", "tower_one.png");
				break;
			case 2:
				towerSprite = Button::create("tower_two.png", "tower_two.png");
				break;
			case 3:
				towerSprite = Button::create("tower_three.png", "tower_three.png");
				break;
			default:
				break;
			}
			towerSprite->setPosition(towerPosition);
			// 每个防御塔及其相关组件都被命名为他们的坐标
			// 因此可以通过鼠标点击的坐标来找到相应的防御塔
			char*name1 = new char[15], *name2 = new char[15], *name3 = new char[15],
				*name4 = new char[15], *name5 = new char[15], *name6 = new char[15];

			sprintf(name1, "%d%d", int(x), int(y));
			this->addChild(towerSprite, 1, name1);

			// 删除按钮
			auto deletebutton = Button::create("delete.png");
			sprintf(name2, "%d%d_d", int(x), int(y));
			deletebutton->setPosition(Vec2(towerPosition.x + 10, towerPosition.y));
			this->addChild(deletebutton, 2, name2);
			deletebutton->setVisible(false);

			// 升级按钮
			auto levelupbutton = Button::create("levelup.png");
			sprintf(name3, "%d%d_u", int(x), int(y));
			levelupbutton->setPosition(Vec2(towerPosition.x + 10, towerPosition.y + 10));
			this->addChild(levelupbutton, 2, name3);
			levelupbutton->setVisible(false);

			// 退出按钮
			auto returnbutton = Button::create("exit.png");
			sprintf(name4, "%d%d_r", int(x), int(y));
			returnbutton->setPosition(Vec2(towerPosition.x + 10, towerPosition.y - 10));
			this->addChild(returnbutton, 2, name4);
			returnbutton->setVisible(false);

			// 升级金币标签
			auto levelupcoin = Label::createWithTTF("20", "fonts/Marker Felt.ttf", 10);
			levelupcoin->setColor(Color3B(255, 255, 0));
			levelupcoin->setVisible(false);
			levelupcoin->setPosition(Vec2(towerPosition.x + 20, towerPosition.y + 10));
			sprintf(name5, "%d%d_c", int(x), int(y));
			this->addChild(levelupcoin, 2, name5);

			// 防御塔等级标签
			auto towerlevel = Label::createWithTTF("Lv.1", "fonts/Marker Felt.ttf", 10);
			towerlevel->setColor(Color3B(255, 0, 0));
			towerlevel->setVisible(false);
			towerlevel->setPosition(Vec2(towerPosition.x - 10, towerPosition.y - 10));
			sprintf(name6, "%d%d_l", int(x), int(y));
			this->addChild(towerlevel, 2, name6);

			delete[]name1;
			delete[]name2;
			delete[]name3;
			delete[]name4;
			delete[]name5;
			delete[]name6;

			// 点击防御塔
			towerSprite->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
				x = mousePosition.x;
				y = mousePosition.y;
				deal_with_xy2(x, y);

				switch (type)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED: {
					char*name2 = new char[15], *name3 = new char[15],
						*name4 = new char[15], *name5 = new char[15], *name6 = new char[15];
					sprintf(name2, "%d%d_d", int(x), int(y));
					layout_delete = this->getChildByName(name2);

					sprintf(name3, "%d%d_u", int(x), int(y));
					layout_uplevel = this->getChildByName(name3);

					sprintf(name4, "%d%d_r", int(x), int(y));
					layout_return = this->getChildByName(name4);

					sprintf(name5, "%d%d_c", int(x), int(y));
					layout_coin = (Label*)(getChildByName(name5));

					sprintf(name6, "%d%d_l", int(x), int(y));
					layout_nowlevel = (Label*)(getChildByName(name6));

					delete[]name2;
					delete[]name3;
					delete[]name4;
					delete[]name5;
					delete[]name6;

					auto it = TowerExist.begin();
					int i = 0;
					while (it != TowerExist.end())
					{
						if (x == TowerExist[i].getPositionX() && y == TowerExist[i].getPositionY()) {
							int money = TowerExist[i].getUpgradeCost();
							layout_coin->setString(std::to_string(money));
							char* levelname = new char[10];
							sprintf(levelname, "Lv.%d", TowerExist[i].getLevel());
							layout_nowlevel->setString(levelname);
							delete levelname;
							break;
						}
						else {
							i++;
							it++;
						}
					}

					// 点击防御塔，则将删除和升级按钮设为可见
					layout_delete->setVisible(true);
					layout_uplevel->setVisible(true);
					layout_return->setVisible(true);
					layout_coin->setVisible(true);
					layout_nowlevel->setVisible(true);
				}
					break;
				default:
					break;
				}
			});

			// 点击返回按钮
			returnbutton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
				x = mousePosition.x;
				y = mousePosition.y;
				deal_with_xy2(x, y);

				switch (type)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED: {
					char*name2 = new char[15], *name3 = new char[15],
						*name4 = new char[15], *name5 = new char[15], *name6 = new char[15];
					sprintf(name2, "%d%d_d", int(x), int(y));
					layout_delete = this->getChildByName(name2);

					sprintf(name3, "%d%d_u", int(x), int(y));
					layout_uplevel = this->getChildByName(name3);

					sprintf(name4, "%d%d_r", int(x), int(y));
					layout_return = this->getChildByName(name4);

					sprintf(name5, "%d%d_c", int(x), int(y));
					layout_coin = (Label*)(getChildByName(name5));

					sprintf(name6, "%d%d_l", int(x), int(y));
					layout_nowlevel = (Label*)(getChildByName(name6));

					delete[]name2;
					delete[]name3;
					delete[]name4;
					delete[]name5;
					delete[]name6;

					// 点击退出按钮，则将删除和升级按钮设为不可见
					layout_return->setVisible(false);
					layout_delete->setVisible(false);
					layout_uplevel->setVisible(false);
					layout_coin->setVisible(false);
					layout_nowlevel->setVisible(false);
				}
					break;
				default:
					break;
				}
			});

			// 点击删除按钮
			deletebutton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
				x = mousePosition.x;
				y = mousePosition.y;
				deal_with_xy2(x, y);

				switch (type)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED: {
					char*name1 = new char[15], *name2 = new char[15], *name3 = new char[15],
						*name4 = new char[15], *name5 = new char[15], *name6 = new char[15];
					sprintf(name1, "%d%d", int(x), int(y));
					auto layout_tower = this->getChildByName(name1);

					sprintf(name2, "%d%d_d", int(x), int(y));
					layout_delete = this->getChildByName(name2);

					sprintf(name3, "%d%d_u", int(x), int(y));
					layout_uplevel = this->getChildByName(name3);

					sprintf(name4, "%d%d_r", int(x), int(y));
					layout_return = this->getChildByName(name4);

					sprintf(name5, "%d%d_c", int(x), int(y));
					layout_coin = (Label*)(getChildByName(name5));

					sprintf(name6, "%d%d_l", int(x), int(y));
					layout_nowlevel = (Label*)(getChildByName(name6));

					delete[]name1;
					delete[]name2;
					delete[]name3;
					delete[]name4;
					delete[]name5;
					delete[]name6;

					// 点击删除按钮，则将防御塔及其相关组件全部移除
					layout_tower->removeFromParentAndCleanup(true);
					layout_delete->removeFromParentAndCleanup(true);
					layout_uplevel->removeFromParentAndCleanup(true);
					layout_return->removeFromParentAndCleanup(true);
					layout_coin->removeFromParentAndCleanup(true);
					layout_nowlevel->removeFromParentAndCleanup(true);
					// 需要注意的是之前防御塔已经加入vector中，因此这里也要删除
					int i = 0;
					for (auto it = TowerExist.begin(); it != TowerExist.end();) {
						if (x == TowerExist[i].getPositionX() && y == TowerExist[i].getPositionY()) {
							it = TowerExist.erase(it);
							current_gold_coins += 10;
							updateGoldCoinsDisplay();
							showTowerGrey();
							break;
						}
						else {
							i++;
							it++;
						}
					}
				}
					break;
				default:
					break;
				}
			});

			// 点击升级按钮
			levelupbutton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
				x = mousePosition.x;
				y = mousePosition.y;
				deal_with_xy2(x, y);

				switch (type)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED: {
					char*name2 = new char[15], *name3 = new char[15],
						*name4 = new char[15], *name5 = new char[15], *name6 = new char[15];
					sprintf(name2, "%d%d_d", int(x), int(y));
					layout_delete = this->getChildByName(name2);

					sprintf(name3, "%d%d_u", int(x), int(y));
					layout_uplevel = this->getChildByName(name3);

					sprintf(name4, "%d%d_r", int(x), int(y));
					layout_return = this->getChildByName(name4);

					sprintf(name5, "%d%d_c", int(x), int(y));
					layout_coin = (Label*)(getChildByName(name5));

					sprintf(name6, "%d%d_l", int(x), int(y));
					layout_nowlevel = (Label*)(getChildByName(name6));

					delete[]name2;
					delete[]name3;
					delete[]name4;
					delete[]name5;
					delete[]name6;

					// 点击升级按钮，按坐标通过迭代器寻找所要升级的防御塔
					auto it = TowerExist.begin();
					int i = 0;
					while (it != TowerExist.end())
					{
						if (x == TowerExist[i].getPositionX() && y == TowerExist[i].getPositionY()) {
							if (TowerExist[i].getLevel() < 4)
							{
								if (TowerExist[i].upgrade(current_gold_coins)) {
									updateGoldCoinsDisplay();
									showTowerGrey();
								}
								else
									showInsufficientGoldLabel();
							}
							else
							{
								showInsufficientLevelLabel();
								layout_uplevel->setVisible(false);
							}
							break;
						}
						else {
							i++;
							it++;
						}
					}
					layout_delete->setVisible(false);
					layout_uplevel->setVisible(false);
					layout_return->setVisible(false);
					layout_coin->setVisible(false);
					layout_nowlevel->setVisible(false);
				}
					break;
				default:
					break;
				}
			});
			// 建立之后将可建立位置设为不可见
			for (unsigned int i = 1; i <= sizeof(pairxy) / sizeof(pairxy[0]); i++) {
				board[i]->setVisible(false);
			}
		}

		else if (place_success)
		{
			showInsufficientPlaceLabel();
		}
		already = 0;
	}
}

// 还未选中防御塔
void Game_two::onMouseDown1(EventMouse* event)//还未选中防御塔
{
	mousePosition = this->convertToNodeSpace(event->getLocationInView());
	if (already == 0)
	{
		tower0Clicked = checkTower0Clicked(mousePosition);
		if (tower0Clicked != -1)
		{
			// 处理防御塔的逻辑
			if (current_gold_coins < getTowerUpgradeCoins(tower0Clicked))
			{
				showInsufficientGoldLabel();
				already = 0;
			}
			else
			{
				already = 1;
			}

		}
		else
		{
			already = 0;
			for (unsigned int i = 1; i <= sizeof(pairxy) / sizeof(pairxy[0]); i++) {
				board[i]->setVisible(false);
			}
		}
		return;

	}
}

// 是否点击到侧边的防御塔了
int Game_two::checkTower0Clicked(const Vec2& touchLocation)
{
	// 定义侧边防御塔的位置和大小
	Rect towerRects[] = {
		Rect(26, 212, 45, 36),  // 侧边防御塔0，左下角坐标，和宽度，高度
		Rect(26, 167, 45, 36),  // 侧边防御塔1
		Rect(26, 122, 45, 36),  // 侧边防御塔2
		Rect(26, 77,  45, 36)   // 侧边防御塔3
	};

	for (int i = 0; i < 4; ++i)
	{
		if (towerRects[i].containsPoint(touchLocation))
		{
			// 如果点击到防御塔，返回防御塔的种类数值
			return i;
		}
	}

	// 如果没有点击到防御塔，返回-1
	return -1;
}

// 显示金币不足，1秒后消失
void Game_two::showInsufficientGoldLabel()
{
	insufficientGoldLabel->setVisible(true);

	// 使用定时器延迟1秒后隐藏标签
	this->scheduleOnce([this](float dt) {
		insufficientGoldLabel->setVisible(false);
	}, 1.0f, "hideInsufficientGoldLabel");
}

// 显示放置位置错误，1秒后消失
void Game_two::showInsufficientPlaceLabel()
{
	insufficientPlaceLabel->setVisible(true);

	// 使用定时器延迟1秒后隐藏标签
	this->scheduleOnce([this](float dt) {
		insufficientPlaceLabel->setVisible(false);
	}, 1.0f, "hideInsufficientPlaceLabel");
}

// 显示已达到最高级，1秒后消失
void Game_two::showInsufficientLevelLabel()
{
	insufficientLevelLabel->setVisible(true);

	// 使用定时器延迟1秒后隐藏标签
	this->scheduleOnce([this](float dt) {
		insufficientLevelLabel->setVisible(false);
	}, 1.0f, "hideInsufficientLevelLabel");
}

// 波数定时器
void Game_two::step(float Dt)
{
	countnum -= 1;
	char StringOfNum[50] = { 0 };
	if (countnum > 0) {
		sprintf(StringOfNum, "Monsters strike %d seconds later", countnum);
		auto countdown = (Label*)(getChildByTag(1000));
		countdown->setString(StringOfNum);
	}
	else if(countnum<=0&&countnum>-13){
		sprintf(StringOfNum, "The first wave");
		auto countdown = (Label*)(getChildByTag(1000));
		countdown->setString(StringOfNum);
	}
	else if (countnum <= -13 && countnum > -26) {
		sprintf(StringOfNum, "The second wave");
		auto countdown = (Label*)(getChildByTag(1000));
		countdown->setString(StringOfNum);
	}
	else if (countnum <= -26 && countnum > -39) {
		sprintf(StringOfNum, "The third wave");
		auto countdown = (Label*)(getChildByTag(1000));
		countdown->setString(StringOfNum);
	}
	else {
		sprintf(StringOfNum, "The final wave");
		auto countdown = (Label*)(getChildByTag(1000));
		countdown->setString(StringOfNum);
	}
}