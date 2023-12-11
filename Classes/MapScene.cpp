#include "MapScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "GameEnd.h"

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
	auto maplabel_one = Label::createWithTTF("1", "fonts/Marker Felt.ttf", 24);
	auto maplabel_two = Label::createWithTTF("2", "fonts/Marker Felt.ttf", 24);
	if (maplabel == nullptr || maplabel_one == nullptr || maplabel_two == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		maplabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - maplabel->getContentSize().height));
		maplabel_one->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100,
			origin.y + visibleSize.height - maplabel->getContentSize().height - 50));
		maplabel_two->setPosition(Vec2(origin.x + visibleSize.width / 2 + 100,
			origin.y + visibleSize.height - maplabel->getContentSize().height - 50));

		this->addChild(maplabel, 1);
		this->addChild(maplabel_one, 1);
		this->addChild(maplabel_two, 1);
	}
	maplabel->setColor(Color3B(0, 0, 0));
	maplabel_one->setColor(Color3B(0, 0, 0));
	maplabel_two->setColor(Color3B(0, 0, 0));

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
		float x = origin.x + 175;
		float y = origin.y - 148;
		returnItem->setPosition(Vec2(x, y));
	}

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

	/* 地图一 */
	auto map_one = MenuItemImage::create("Map_one.png",
		"Map_one.png", CC_CALLBACK_1(MyMap::menuItemSettingCallback_one, this));

	if (map_one == nullptr
		|| map_one->getContentSize().width <= 0
		|| map_one->getContentSize().height <= 0)
	{
		problemLoading("'Map_one.png'");
	}
	else
	{
		float x = origin.x;
		float y = origin.y;
		map_one->setPosition(Vec2(origin.x - 125, origin.y - 20));
	}

	GameEnd gameEnd;

	if (gameEnd.map_one_finish) {
		auto finish_one = Sprite::create("Finish.png");
		if (finish_one == nullptr)
			problemLoading("'Finish.png'");
		else
		{
			finish_one->setPosition(Vec2(origin.x - 125, origin.y - 20));
			this->addChild(finish_one, 2);
		}
	}

	/* 地图二 */
	auto map_two = MenuItemImage::create("Map_two.png",
		"Map_two.png", CC_CALLBACK_1(MyMap::menuItemSettingCallback_two, this));

	if (map_two == nullptr
		|| map_two->getContentSize().width <= 0
		|| map_two->getContentSize().height <= 0)
	{
		problemLoading("'Map_two.png'");
	}
	else
	{
		float x = origin.x;
		float y = origin.y;
		map_two->setPosition(Vec2(origin.x + 75, origin.y - 20));
	}

	if (gameEnd.map_two_finish) {
		auto finish_two = Sprite::create("Finish.png");
		if (finish_two == nullptr)
			problemLoading("'Finish.png'");
		else
		{
			finish_two->setPosition(Vec2(origin.x + 12, origin.y + visibleSize.height - 12));
			this->addChild(finish_two, 1);
		}
	}

	// 创建菜单
	Vector<MenuItem*> MenuItems;
	MenuItems.pushBack(returnItem);
	MenuItems.pushBack(map_one);
	MenuItems.pushBack(map_two);
	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 1);

	return true;
}

// 返回上一页面
void MyMap::menuOkCallback(Ref *pSender)
{
	// 栈顶场景弹栈
	Director::getInstance()->popScene();
}

// 进入地图一
void MyMap::menuItemSettingCallback_one(Ref *pSender)
{
	// 切换页面
	auto Game_one = Game_one::createScene();
	// 当前场景压入栈中
	Director::getInstance()->pushScene(Game_one);
}

// 进入地图二
void MyMap::menuItemSettingCallback_two(Ref *pSender)
{
	// 切换页面
	auto Game_two = Game_two::createScene();
	// 当前场景压入栈中
	Director::getInstance()->pushScene(Game_two);
}