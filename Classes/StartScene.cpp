#include "MapScene.h"
#include "StartScene.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
using namespace cocos2d::experimental;

USING_NS_CC;

bool map_one_finish = false;
bool map_two_finish = false;
bool map_two_unlock = false;
bool map_one_continue = false;
bool map_two_continue = false;
bool sound = true;
int backgroundAudioID;

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

	AudioEngine::preload("BackgroundMusic.mp3");
	backgroundAudioID = AudioEngine::play2d("BackgroundMusic.mp3", true);

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

	/* 开启声音按钮 */
	auto soundItem = MenuItemImage::create("SoundButton.png",
		"SoundButton.png", CC_CALLBACK_1(Start::openAndCloseSound, this));

	if (soundItem == nullptr
		|| soundItem->getContentSize().width <= 0
		|| soundItem->getContentSize().height <= 0)
	{
		problemLoading("'SoundButton.png'");
	}
	else
	{
		soundItem->setPosition(Vec2(origin.x + 170, origin.y + 120));
	}

	// 声音关闭按钮
	auto soundCloseItem = MenuItemImage::create("SoundCloseButton.png",
		"SoundCloseButton.png", CC_CALLBACK_1(Start::openAndCloseSound, this));

	if (soundCloseItem == nullptr
		|| soundCloseItem->getContentSize().width <= 0
		|| soundCloseItem->getContentSize().height <= 0)
	{
		problemLoading("'SoundCloseButton.png'");
	}
	else
	{
		soundCloseItem->setPosition(Vec2(origin.x + 170, origin.y + 120));
	}

	// 创建菜单
	Vector<MenuItem*> MenuItems;
	MenuItems.pushBack(startItem);
	MenuItems.pushBack(closeItem);
	MenuItems.pushBack(soundItem);
	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 1);

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
	auto MyMap = MyMap::createScene();
	Director::getInstance()->pushScene(MyMap);
}

void Start::openAndCloseSound(Ref *pSender)
{
	if (!sound) {
		AudioEngine::resume(backgroundAudioID);
		sound = true;
	}
	else{
		AudioEngine::pause(backgroundAudioID);
		sound = false;
	}
}