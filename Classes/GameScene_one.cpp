#include "BackgroundMusic.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "Gamepause.h"
#include "GameEnd.h"
#include "GBKtoUTF-8.h"

USING_NS_CC;

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
			origin.y + visibleSize.height- upperboard->getContentSize().height/2));
		this->addChild(upperboard, 1);
	}

	// 加入金币图片
	auto moneypic = Sprite::create("Money.png");
	if (moneypic == nullptr)
	{
		problemLoading("'Money.png'");
	}
	else
	{
		moneypic->setPosition(Vec2(origin.x+22, origin.y+ visibleSize.height-15));
		this->addChild(moneypic, 2);
	}

	// 添加文字
	auto mapnum = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 18);
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

	// 创建菜单
	Vector<MenuItem*> MenuItems;
	MenuItems.pushBack(pauseItem);
	MenuItems.pushBack(returnItem);
	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 2);

	// 添加鼠标位置显示
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(Game_one::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	// 添加 "carrot" 图片
	auto carrot = Sprite::create("carrot.png");
	if (carrot)
	{
		carrot->setPosition(Vec2(86, 248)); //萝卜位置
		this->addChild(carrot, 1);

		auto CarrotHealthBack = Sprite::create("CarrotHealthBack.png");
		CarrotHealthBack->setPosition(Vec2(86, 273));// 萝卜上方位置
		this->addChild(CarrotHealthBack, 1);

		// 添加萝卜血条
		ProgressTimer* healthBar = ProgressTimer::create(Sprite::create("HealthBar.png"));
		healthBar->setType(ProgressTimer::Type::BAR);
		healthBar->setMidpoint(Vec2(0, 0.5));
		healthBar->setBarChangeRate(Vec2(1, 0));
		healthBar->setPosition(Vec2(86, 273));  // 萝卜上方位置
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
		GuideBoard->setPosition(Vec2(433, 75)); //出怪牌位置
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
			origin.y + visibleSize.height - countdown->getContentSize().height-4));
		this->addChild(countdown, 2);
	}
	countdown->setColor(Color3B(255, 255, 255));

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

// 鼠标点击事件回调
void Game_one::onMouseDown(EventMouse* event)
{
	// 获取鼠标点击位置
	Vec2 mousePosition = Director::getInstance()->getRunningScene()->convertToNodeSpace(event->getLocationInView());

	// 输出鼠标位置
	log("Mouse Clicked at (%.2f, %.2f)", mousePosition.x, mousePosition.y);

	// 在屏幕上显示鼠标位置
	drawMousePositionLabel(mousePosition);
}

// 在屏幕上显示鼠标位置
void Game_one::drawMousePositionLabel(const Vec2& position)
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