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

// �Ҳ����ļ�ʱ�׳��쳣
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

	// ���뱳��ͼƬ
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

	/* ��ʼ��Ϸ��ť */
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

	/* �ر���Ϸ��ť */
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

	// �����˵�
	Vector<MenuItem*> MenuItems;
	MenuItems.pushBack(startItem);
	MenuItems.pushBack(closeItem);
	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 1);

	/* ���ű������� */
	//SoundManager::BackgroundMusic();
	//SoundManager::MusicSet();
	return true;
}


void Start::menuCloseCallback(Ref* pSender)
{
	// �ر�ҳ�棬�˳���Ϸ
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
	// �л�ҳ��
	auto MyMap = MyMap::createScene();
	// ��ǰ����ѹ��ջ��
	Director::getInstance()->pushScene(MyMap);
}