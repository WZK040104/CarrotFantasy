#include "BackgroundMusic.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"

USING_NS_CC;

Scene* Game_one::createScene()
{
	return Game_one::create();
}
// 找不到文件时抛出异常
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Game_one::init()
{
	if (!Scene::init())
	{
		return false;
	}

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

	// 返回按钮
	auto returnItem = MenuItemImage::create("Return.png",
		"Return.png", CC_CALLBACK_1(Game_one::menuOkCallback, this));

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

	/* 播放背景音乐 */
	auto musicItem = MenuItemImage::create("SoundButton.png",
		"SoundButton.png", CC_CALLBACK_1(SoundManager::BackgroundMusic, this));

	float x = origin.x+175;
	float y = origin.y+148;
	musicItem->setPosition(Vec2(x, y));

	// 创建菜单
	Vector<MenuItem*> MenuItems;
	MenuItems.pushBack(returnItem);
	MenuItems.pushBack(musicItem);
	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 1);

	return true;
}

// 返回上一页面
void Game_one::menuOkCallback(Ref *pSender)
{
	// 栈顶场景弹栈
	Director::getInstance()->popScene();
}

void Game_one::menuCloseCallback(Ref* pSender)
{
	// 关闭页面，退出游戏
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("Game_one_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}

void SoundManager::BackgroundMusic(Ref* pSender)
{
	auto audio = SimpleAudioEngine::getInstance();
	// 预加载
	audio->preloadBackgroundMusic("BackgroundMusic.mp3");
	// 控制音量
	audio->setEffectsVolume(0.5);
	audio->setBackgroundMusicVolume(0.5);
	// 反复播放
	audio->playBackgroundMusic("BackgroundMusic.mp3", true);
}