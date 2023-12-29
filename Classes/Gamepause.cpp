#include "GameScene.h"
#include "Gamepause.h"
#include "PlaceTower.h"

USING_NS_CC;

extern int countnum;
extern bool map_one_continue;
extern bool map_two_continue;
extern int carrot_level;
extern int carrot_HP;

// GBK转UTF-8编码
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
	back_sqr->setPosition(Vec2(visibleSize.width / 2 + 24, visibleSize.height / 2)); // 放置位置,这个相对于中心位置。
	back_sqr->setFlippedY(true);             // 翻转，因为UI坐标和OpenGL坐标不同
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

	continueItem->setPosition(Vec2(origin.x - 70, origin.y + 2));

	// 重新开始按钮
	auto restartItem = MenuItemImage::create("RestartGame.png",
		"RestartGame.png", CC_CALLBACK_1(Gamepause::RestartGame, this));

	restartItem->setPosition(Vec2(origin.x - 23, origin.y + 2));

	// 返回菜单按钮
	auto returnmenuItem = MenuItemImage::create("MapMenu.png",
		"MapMenu.png", CC_CALLBACK_1(Gamepause::ReturnMenuGame, this));

	returnmenuItem->setPosition(Vec2(origin.x + 23, origin.y + 2));

	// 暂停图框
	auto pauseMenu = Sprite::create("PauseMenu.png");
	pauseMenu->setPosition(Vec2(visibleSize.width / 2 + 30, visibleSize.height / 2 + 10));
	this->addChild(pauseMenu, 1);

	// 彩蛋
	auto ctl = Sprite::create("ctl.png");
	ctl->setPosition(Vec2(visibleSize.width / 2 -60, visibleSize.height / 2 -85));
	this->addChild(ctl, 2);

	auto wzk = Sprite::create("wzk.png");
	wzk->setPosition(Vec2(visibleSize.width / 2 +120, visibleSize.height / 2 -85));
	this->addChild(wzk, 2);

	auto label1 = Label::createWithTTF(GBKToUTF8("恭喜你发现了这个小彩蛋！"), "fonts/STHUPO.TTF", 14);
	label1->setColor(Color3B(255, 0, 0));
	label1->setPosition(Vec2(origin.x + visibleSize.width / 2+5,
		origin.y + visibleSize.height - label1->getContentSize().height -20));
	this->addChild(label1, 2);

	auto label2 = Label::createWithTTF(GBKToUTF8("可以给可怜的作者打个赏吗QAQ"), "fonts/STHUPO.TTF", 14);
	label2->setColor(Color3B(255, 0, 0));
	label2->setPosition(Vec2(origin.x + visibleSize.width / 2+5,
		origin.y + visibleSize.height - label2->getContentSize().height - 50));
	this->addChild(label2, 2);

	auto label3 = Label::createWithTTF(GBKToUTF8("1r 5r 648r 都可以的（）"), "fonts/STHUPO.TTF", 14);
	label3->setColor(Color3B(255, 0, 0));
	label3->setPosition(Vec2(origin.x + visibleSize.width / 2+5,
		origin.y + visibleSize.height - label3->getContentSize().height - 80));
	this->addChild(label3, 2);

	// 创建菜单
	Vector<MenuItem*> MenuItems;
	MenuItems.pushBack(continueItem);
	MenuItems.pushBack(restartItem);
	MenuItems.pushBack(returnmenuItem);
	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 2);

	return true;
}

// 返回上一页面
void Gamepause::ContinueGame(Ref *pSender)
{
	Director::getInstance()->popScene();
}

// 重新开始
void Gamepause::RestartGame(Ref *pSender)
{
	TowerExist.clear();
	countnum = 5;
	carrot_level = 1;
	carrot_HP = 5;

	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
	if (map_one_continue) {
		auto Game_one = Game_one::createScene();
		Director::getInstance()->pushScene(Game_one);
	}
	if (map_two_continue) {
		auto Game_two = Game_two::createScene();
		Director::getInstance()->pushScene(Game_two);
	}
}

// 返回菜单
void Gamepause::ReturnMenuGame(Ref *pSender)
{
	TowerExist.clear();
	countnum = 5;
	carrot_level = 1;
	carrot_HP = 5;

	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
	if (map_one_continue)
		map_one_continue = false;
	if (map_two_continue)
		map_two_continue = false;
}