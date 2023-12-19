#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "Gamepause.h"
#include "PlaceTower.h"
#include "GameEnd.h"
#include "GBKtoUTF-8.h"
#include "Tower_kind.h"
#include <algorithm>

USING_NS_CC;

using namespace std;
using namespace cocos2d::ui;

int current_gold_coins = 100000;
int countnum = 20;

Scene* Game_one::createScene()
{
	Scene *scene = Scene::create();
	Game_one *layer = Game_one::create();
	scene->addChild(layer);
	return scene;
}
// 找不到文件时抛出异常
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

std::string GBKToUTF8(const std::string& strGBK)
{
	std::string strOutUTF8 = "";
	WCHAR* str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char* str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	strOutUTF8 = str2;
	delete[]str1;
	str1 = NULL;
	delete[]str2;
	str2 = NULL;
	return strOutUTF8;
}

extern bool map_two_unlock;
extern bool map_one_continue;

// 添加侧边防御塔的图标
void Game_one::createTower0(const std::string& tower0Image, const std::string& tower0BackImage,
	const std::string& towerImage, const std::string& towerBackImage,
	int upgradeCoins, float positionY, int index)
{
	// 显示侧边的防御塔0
	auto tower0 = Sprite::create(tower0Image);
	if (tower0)
	{
		auto tower_back0 = Sprite::create(tower0BackImage);
		tower_back0->setPosition(Vec2(42, positionY));
		this->addChild(tower_back0, 1);  // 防御塔背景
		tower0->setPosition(Vec2(42, positionY));  // 侧边防御塔位置
		this->addChild(tower0, 1);

		// 判断金币是否足够购买防御塔
		if (current_gold_coins >= upgradeCoins)
		{
			auto tower = Sprite::create(towerImage);
			if (tower)
			{
				auto tower_back = Sprite::create(towerBackImage);
				tower_back->setPosition(Vec2(42, positionY));
				this->addChild(tower_back, 1);  // 防御塔背景
				tower->setPosition(Vec2(42, positionY));  // 侧边防御塔位置
				this->addChild(tower, 1);
			}
			else
			{
				//problemLoading("'" + towerImage + "'");
			}
		}
		else
		{
			//problemLoading("'" + towerImage + "' (Not enough gold coins)");
		}

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
	else
	{
		//problemLoading("'" + tower0Image + "'");
	}
}

bool Game_one::init()
{
	if (!Scene::init())
	{
		return false;
	}

	map_one_continue = true;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 加入背景图片
	auto map_one = Sprite::create("GameBackground_one.png");
	if (map_one == nullptr)
	{
		problemLoading("'GameBackground_one.png'");
	}
	else
	{
		map_one->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		this->addChild(map_one, 0);
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
		"Pause.png", CC_CALLBACK_1(Game_one::Pause, this));

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

	// 返回按钮
	auto returnItem = MenuItemImage::create("Return.png",
		"Return.png", CC_CALLBACK_1(Game_one::Success, this));

	if (returnItem == nullptr
		|| returnItem->getContentSize().width <= 0
		|| returnItem->getContentSize().height <= 0)
	{
		problemLoading("'Return.png'");
	}
	else
	{
		float x = origin.x + 175;
		float y = origin.y - 148;
		returnItem->setPosition(Vec2(x, y));
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
		this->addChild(moneypic, 1);
	}

	// 添加文字 金币数量
	auto mapnum = Label::createWithTTF(to_string(current_gold_coins), "fonts/Marker Felt.ttf", 18);
	if (mapnum == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		mapnum->setAnchorPoint(Vec2(0, 0.5));
		mapnum->setPosition(Vec2(origin.x + 35, origin.y + visibleSize.height - 18));
		this->addChild(mapnum, 1);
	}
	mapnum->setColor(Color3B(255, 255, 0));

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
		schedule(CC_CALLBACK_1(Game_one::step, this), 1.0f, "step_key");
	}

	// 显示侧边的防御塔0
	createTower0("tower_zero0.png", "tower_back0.png", "tower_zero.png", "tower_back.png", tower0_upgrade_coins[0], 230, 0);

	// 显示侧边的防御塔1
	createTower0("tower_one0.png", "tower_back0.png", "tower_one.png", "tower_back.png", tower1_upgrade_coins[0], 185, 1);

	// 显示侧边的防御塔2
	createTower0("tower_two0.png", "tower_back0.png", "tower_two.png", "tower_back.png", tower2_upgrade_coins[0], 140, 2);

	// 显示侧边的防御塔3
	createTower0("tower_three0.png", "tower_back0.png", "tower_three.png", "tower_back.png", tower3_upgrade_coins[0], 95, 3);

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

	// 防御塔可放置位置边框
	for (unsigned int i = 1; i <= sizeof(pairxy) / sizeof(pairxy[0]); i++) {
		board[i] = Sprite::create("board.png");
		if (board[i] == nullptr)
		{
			problemLoading("'board.png'");
		}
		else
		{
			board[i]->setPosition(pairxy[i-1]);
			this->addChild(board[i], 1);
			board[i]->setVisible(false);
		}
	}

	// 创建菜单
	Vector<MenuItem*> MenuItems;
	MenuItems.pushBack(pauseItem);
	MenuItems.pushBack(returnItem);
	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 1);

	// 添加 "carrot" 图片
	auto carrot = Sprite::create("carrot.png");
	if (carrot)
	{
		carrot->setPosition(Vec2(86, 248)); //萝卜位置
		this->addChild(carrot, 1);

		auto CarrotHealthBack = Sprite::create("CarrotHealthBack.png");
		CarrotHealthBack->setPosition(Vec2(86, 278));// 萝卜上方位置
		this->addChild(CarrotHealthBack, 1);

		// 添加萝卜血条
		ProgressTimer* healthBar = ProgressTimer::create(Sprite::create("HealthBar.png"));
		healthBar->setType(ProgressTimer::Type::BAR);
		healthBar->setMidpoint(Vec2(0, 0.5));
		healthBar->setBarChangeRate(Vec2(1, 0));
		healthBar->setPosition(Vec2(86, 278));  // 萝卜上方位置
		healthBar->setPercentage(100.0f);  // 初始血量百分比
		this->addChild(healthBar, 2, "healthBar");
	}
	else
	{
		problemLoading("'carrot.png'");
	}

	// 添加出怪牌图片
	auto GuideBoard = Sprite::create("GuideBoard.png");
	if (GuideBoard)
	{
		GuideBoard->setPosition(Vec2(433, 75)); //出怪牌位置
		this->addChild(GuideBoard, 1);
	}
	else
	{
		problemLoading("'GuideBoard.png'");
	}

	// 添加鼠标位置显示
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(Game_one::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
	auto mouseListener1 = EventListenerMouse::create();
	mouseListener1->onMouseDown = CC_CALLBACK_1(Game_one::onMouseDown1, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener1, this);

	return true;
}

// 暂停游戏
void Game_one::Pause(Ref* pSender)
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

// 游戏通关
void Game_one::Success(Ref* pSender)
{
	map_two_unlock = true;

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

Vec2 towerPosition;  // 用于存储防御塔的位置
int tower0Clicked = -1;

// 建造所需要的金币
int Game_one::getTowerUpgradeCoins(int towerType)
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
bool deal_with_xy1(double &x ,double& y)
{
	if (x > 102 && x <= 137)
		x = 120;
	else if (x > 137 && x <= 172)
		x = 155;
	else if (x > 172 && x <= 207)
		x = 190;
	else if (x > 207 && x <= 242)
		x = 225;
	else if (x > 242 && x <= 277)
		x = 260;
	else if (x > 277 && x <= 312)
		x = 295;
	else if (x > 312 && x <= 347)
		x = 330;
	else if (x > 347 && x <= 382)
		x = 365;
	else if (x > 382 && x <= 417)
		x = 400;

	if (y > 24 && y <= 58)
		y = 41;
	else if (y > 58 && y <= 92)
		y = 75;
	else if (y > 92 && y <= 126)
		y = 109;
	else if (y > 126 && y <= 160)
		y = 143;
	else if (y > 160 && y <= 194)
		y = 177;
	else if (y > 194 && y <= 228)
		y = 211;
	else if (y > 228 && y <= 262)
		y = 245;

	if (x <= 71 && y > 75 && y <= 250)
		return 0;

	for (unsigned int i = 0; i < TowerExist.size(); i++)
	{
		if (x == TowerExist[i].getPositionX() && y == TowerExist[i].getPositionY())
			return 0;
	}

	return 1;
}

int already = 0;//是否选中防御塔
Vec2 mousePosition;

// 已经选中防御塔准备放置
void Game_one::onMouseDown(EventMouse* event)
{
	mousePosition = this->convertToNodeSpace(event->getLocationInView());
	if (already == 1)
	{
		for (unsigned int i = 1; i <= sizeof(pairxy) / sizeof(pairxy[0]); i++)
		{
			board[i]->setVisible(true);
		}
		towerPosition = mousePosition;
		double x= towerPosition.x, y= towerPosition.y;
		bool place_success=deal_with_xy1(x, y); // 处理xy坐标，是否成功放置
		bool it = false;
		for (unsigned int i = 1; i <= sizeof(pairxy) / sizeof(pairxy[0]); i++){
			if (pairxy[i-1] == Vec2(x, y)) 
			{
				it = true;
				break;
			}
		}
		if (it&&place_success)
		{
			towerPosition = Vec2(x, y);
			placeTower(TowerExist, tower0Clicked, x, y);
			current_gold_coins -= getTowerUpgradeCoins(tower0Clicked);
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
			this->addChild(towerSprite, 1,"towerSprite");

			towerSprite->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
				switch (type)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED: {
					this->removeChildByName("towerSprite");
				}
					break;
				default:
					break;
				}
			});
			

			for (unsigned int i = 1; i <= sizeof(pairxy) / sizeof(pairxy[0]); i++) {
				board[i]->setVisible(false);
			}
		}
		else if(place_success)
		{
			showInsufficientPlaceLabel();
		}
		already = 0;
	}
}

// 还未选中防御塔
void Game_one::onMouseDown1(EventMouse* event)
{
	mousePosition = this->convertToNodeSpace(event->getLocationInView());
	if(already==0)
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
			// 如果没有点击到防御塔，在屏幕上显示鼠标位置
			drawMousePositionLabel(mousePosition);
			already = 0;
			for (unsigned int i = 1; i <= sizeof(pairxy)/sizeof(pairxy[0]); i++) {
				board[i]->setVisible(false);
			}
		}
	}
}

// 在屏幕上显示鼠标位置
void Game_one::drawMousePositionLabel(const Vec2& position)
{
	// 移除之前的标签
	removeChildByTag(123);

	// 创建标签并显示鼠标位置
	auto label = Label::createWithTTF(StringUtils::format("(%.2f, %.2f)", position.x, position.y),
		"fonts/arial.ttf", 24);
	label->setPosition(Vec2(120, 60));
	label->setTag(123);
	addChild(label);
}

// 是否点击到侧边的防御塔了
int Game_one::checkTower0Clicked(const Vec2& touchLocation)
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
void Game_one::showInsufficientGoldLabel()
{
	insufficientGoldLabel->setVisible(true);

	// 使用定时器延迟1秒后隐藏标签
	this->scheduleOnce([this](float dt) {
		insufficientGoldLabel->setVisible(false);
	}, 1.0f, "hideInsufficientGoldLabel");
}

// 显示放置位置错误，1秒后消失
void Game_one::showInsufficientPlaceLabel()
{
	insufficientPlaceLabel->setVisible(true);

	// 使用定时器延迟1秒后隐藏标签
	this->scheduleOnce([this](float dt) {
		insufficientPlaceLabel->setVisible(false);
	}, 1.0f, "hideInsufficientPlaceLabel");
}

// 波数定时器
void Game_one::step(float Dt)
{
	countnum -= 1;
	char StringOfNum[50] = { 0 };
	if (countnum > 0) {
		sprintf(StringOfNum, "Monsters strike %d seconds later", countnum);
		auto countdown = (Label*)(getChildByTag(1000));
		countdown->setString(StringOfNum);
	}
	else {
		sprintf(StringOfNum, "The first wave");
		auto countdown = (Label*)(getChildByTag(1000));
		countdown->setString(StringOfNum);
	}
}