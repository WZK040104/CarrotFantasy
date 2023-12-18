#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "Gamepause.h"
#include "GameEnd.h"
#include "GBKtoUTF-8.h"
#include "Tower_kind.h"

USING_NS_CC;
using namespace std;

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

extern bool map_two_continue;

bool Game_two::init()
{
	if (!Scene::init())
	{
		return false;
	}

	map_two_continue=true;

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

	//显示侧边的防御塔0
	createTower0("tower_zero0.png", "tower_back0.png", "tower_zero.png", "tower_back.png", tower0_upgrade_coins[0], 230, 0);

	//显示侧边的防御塔1
	createTower0("tower_one0.png", "tower_back0.png", "tower_one.png", "tower_back.png", tower1_upgrade_coins[0], 185, 1);

	//显示侧边的防御塔2
	createTower0("tower_two0.png", "tower_back0.png", "tower_two.png", "tower_back.png", tower2_upgrade_coins[0], 140, 2);

	//显示侧边的防御塔3
	createTower0("tower_three0.png", "tower_back0.png", "tower_three.png", "tower_back.png", tower3_upgrade_coins[0], 95, 3);

									   // 加入金币图片
	auto moneypic = Sprite::create("Money.png");
	if (moneypic == nullptr)
	{
		problemLoading("'Money.png'");
	}
	else
	{
		moneypic->setPosition(Vec2(origin.x + 22, origin.y + visibleSize.height - 15));
		this->addChild(moneypic, 2);
	}

	// 添加文字 金币数量
	auto mapnum = Label::createWithTTF(to_string(current_gold_coins), "fonts/Marker Felt.ttf", 18);
	if (mapnum == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		mapnum->setPosition(Vec2(origin.x + 43, origin.y + visibleSize.height - 17));
		this->addChild(mapnum, 2);
	}
	mapnum->setColor(Color3B(255, 255, 0));

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

	// 返回按钮
	auto returnItem = MenuItemImage::create("Return.png",
		"Return.png", CC_CALLBACK_1(Game_two::Success, this));

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

	// 创建菜单
	Vector<MenuItem*> MenuItems;
	MenuItems.pushBack(pauseItem);
	MenuItems.pushBack(returnItem);
	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 1);

	// 添加鼠标位置显示
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(Game_two::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	// 添加 "carrot" 图片
	auto carrot = Sprite::create("carrot.png");
	if (carrot)
	{
		carrot->setPosition(Vec2(103, 250));
		this->addChild(carrot, 1);

		auto CarrotHealthBack = Sprite::create("CarrotHealthBack.png");
		CarrotHealthBack->setPosition(Vec2(103, 275));// 萝卜上方位置
		this->addChild(CarrotHealthBack, 1);

		// 添加萝卜血条
		ProgressTimer* healthBar = ProgressTimer::create(Sprite::create("HealthBar.png"));
		healthBar->setType(ProgressTimer::Type::BAR);
		healthBar->setMidpoint(Vec2(0, 0.5));  // 血条从左到右减少
		healthBar->setBarChangeRate(Vec2(1, 0));
		healthBar->setPosition(Vec2(103, 275));  // 萝卜上方位置
		healthBar->setPercentage(100.0f);  // 初始血量百分比
		this->addChild(healthBar, 2, "healthBar");
	}
	else
	{
		problemLoading("'carrot.png'");
	}

	//添加出怪牌图片
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
	auto countdown = Label::createWithTTF(GBKToUTF8("5秒后怪物来袭"), "fonts/STHUPO.TTF", 10);
	if (countdown == nullptr)
	{
		problemLoading("'fonts/STHUPO.TTF'");
	}
	else
	{
		countdown->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - countdown->getContentSize().height - 4));
		this->addChild(countdown, 2);
	}
	countdown->setColor(Color3B(255, 255, 255));

	return true;
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

// 游戏通关
void Game_two::Success(Ref* pSender)
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

void Game_two::onMouseDown(EventMouse* event)
{
	// 获取鼠标点击位置
	Vec2 mousePosition = Director::getInstance()->getRunningScene()->convertToNodeSpace(event->getLocationInView());

	// 输出鼠标位置
	log("Mouse Clicked at (%.2f, %.2f)", mousePosition.x, mousePosition.y);

	drawMousePositionLabel(mousePosition);
}

// 在屏幕上显示鼠标位置
void Game_two::drawMousePositionLabel(const Vec2& position)
{
	// 移除之前的标签
	removeChildByTag(123);

	// 创建标签并显示鼠标位置
	auto label = Label::createWithTTF(StringUtils::format("(%.2f, %.2f)", position.x, position.y),
		"fonts/arial.ttf", 24);
	label->setPosition(Vec2(100, 100));
	label->setTag(123);
	addChild(label);
}

void Game_two::createTower0(const std::string& tower0Image, const std::string& tower0BackImage,
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