#include "BackgroundMusic.h"
#include "MapScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* Start::createScene()
{
	return Start::create();
}

// 找不到文件时抛出异常
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Start::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 加入背景图片
	auto startBackground = Sprite::create("StartBackground.png");
	if (startBackground == nullptr)
	{
		problemLoading("'StartBackground.png'");
	}
	else
	{
		startBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		this->addChild(startBackground, 0);
	}

	/* 开始游戏按钮 */
	auto startItem = MenuItemImage::create("StartButton.png",
		"StartButton.png", CC_CALLBACK_1(Start::menuItemSettingCallback, this));

	if (startItem == nullptr
		|| startItem->getContentSize().width <= 0
		|| startItem->getContentSize().height <= 0)
	{
		problemLoading("'StartButton.png'");
	}
	else
	{
		float x = origin.x - 100;
		float y = origin.y - 110;
		startItem->setPosition(Vec2(x, y));
	}

	/* 关闭游戏按钮 */
	auto closeItem = MenuItemImage::create("EndButton.png",
		"EndButton.png", CC_CALLBACK_1(Start::menuCloseCallback, this));

	if (closeItem == nullptr
		|| closeItem->getContentSize().width <= 0
		|| closeItem->getContentSize().height <= 0)
	{
		problemLoading("'EndButton.png'");
	}
	else
	{
		float x = origin.x + 40;
		float y = origin.y - 110;
		closeItem->setPosition(Vec2(x, y));
	}

	// 创建菜单
	Vector<MenuItem*> MenuItems;
	MenuItems.pushBack(startItem);
	MenuItems.pushBack(closeItem);
	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 1);

	/* 播放背景音乐 */
	//SoundManager::BackgroundMusic();
	//SoundManager::MusicSet();
	return true;
}


void Start::menuCloseCallback(Ref* pSender)
{
	// 关闭页面，退出游戏
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}

void Start::menuItemSettingCallback(Ref *pSender)
{
	// 切换页面
	auto MyMap = MyMap::createScene();
	// 当前场景压入栈中
	Director::getInstance()->pushScene(MyMap);
}