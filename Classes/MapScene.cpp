#include "MapScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* MyMap::createScene()
{
	return MyMap::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MyMap::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 添加文字
	auto maplabel = Label::createWithTTF("Map", "fonts/Marker Felt.ttf", 24);
	if (maplabel == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		maplabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - maplabel->getContentSize().height));

		this->addChild(maplabel, 1);
	}
	maplabel->setColor(Color3B(0, 0, 0));

	// 返回按钮
	auto returnItem = MenuItemImage::create("Return.png",
		"Return.png", CC_CALLBACK_1(MyMap::menuOkCallback, this));

	if (returnItem == nullptr
		|| returnItem->getContentSize().width <= 0
		|| returnItem->getContentSize().height <= 0)
	{
		problemLoading("'Return.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - returnItem->getContentSize().width / 2;
		float y = origin.y + returnItem->getContentSize().height / 2;
		returnItem->setPosition(Vec2(x, y));
	}

	auto menu = Menu::create(returnItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	// 加入背景图片
	auto mapBackground = Sprite::create("MapBackground.png");
	if (mapBackground == nullptr)
	{
		problemLoading("'MapBackground.png'");
	}
	else
	{
		mapBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(mapBackground, 0);
	}

	return true;
}

// 返回上一页面
void MyMap::menuOkCallback(Ref *pSender)
{
	// 栈顶场景弹栈
	Director::getInstance()->popScene();
}