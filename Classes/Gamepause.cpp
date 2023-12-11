#include "Gamepause.h"

USING_NS_CC;

Scene* Gamepause::scene(RenderTexture* sqr)
{
	Scene *scene = Scene::create();
	Gamepause *layer = Gamepause::create();
	scene->addChild(layer, 1);
	// 增加部分：使用Game界面中截图的sqr纹理图片创建Sprite
	// 并将Sprite添加到GamePause场景层中
	// 得到窗口的大小
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto back_sqr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	back_sqr->setPosition(Vec2(visibleSize.width / 2+24, visibleSize.height / 2)); // 放置位置,这个相对于中心位置。
	back_sqr->setFlipY(true);            // 翻转，因为UI坐标和OpenGL坐标不同
	back_sqr->setColor(Color3B(80, 80, 80)); // 图片颜色变灰色
	scene->addChild(back_sqr);
	return scene;
}

bool Gamepause::init()
{

	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 继续游戏按钮
	auto continueItem = MenuItemImage::create("ContinueGame.png",
		"ContinueGame.png", CC_CALLBACK_1(Gamepause::ContinueGame, this));

	continueItem->setPosition(Vec2(origin.x-58, origin.y+2));

	// 返回菜单按钮
	auto returnmenuItem = MenuItemImage::create("MapMenu.png",
		"MapMenu.png", CC_CALLBACK_1(Gamepause::ReturnMenuGame, this));

	returnmenuItem->setPosition(Vec2(origin.x+10, origin.y+2));

	// 暂停图框
	auto pauseMenu = Sprite::create("PauseMenu.png");
	pauseMenu->setPosition(Vec2(visibleSize.width / 2+30, visibleSize.height / 2+10));
	this->addChild(pauseMenu, 1);

	// 创建菜单
	Vector<MenuItem*> MenuItems;
	MenuItems.pushBack(continueItem);
	MenuItems.pushBack(returnmenuItem);
	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 2);

	return true;
}

// 返回上一页面
void Gamepause::ContinueGame(Ref *pSender)
{
	// 栈顶场景弹栈
	Director::getInstance()->popScene();
}
// 返回菜单
void Gamepause::ReturnMenuGame(Ref *pSender)
{
	// 栈顶场景弹栈
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
}