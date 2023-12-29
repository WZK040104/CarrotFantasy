#include "GameDefault.h"
#include "GameScene.h"
#include "MapScene.h"
#include "PlaceTower.h"

USING_NS_CC;

extern int countnum;
extern int carrot_level;
extern int carrot_HP;

Scene* GameDefault::scene(RenderTexture* sqr)
{
	Scene *scene = Scene::create();
	GameDefault *layer = GameDefault::create();
	scene->addChild(layer, 1);
	// ���Ӳ��֣�ʹ��Game�����н�ͼ��sqr����ͼƬ����Sprite
	// ����Sprite��ӵ�GamePause��������
	// �õ����ڵĴ�С
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto back_sqr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	back_sqr->setPosition(Vec2(visibleSize.width / 2 + 24, visibleSize.height / 2)); // ����λ��,������������λ�á�
	back_sqr->setFlippedY(true);               // ��ת����ΪUI�����OpenGL���겻ͬ
	back_sqr->setColor(Color3B(80, 80, 80)); // ͼƬ��ɫ���ɫ
	scene->addChild(back_sqr);
	return scene;
}

extern bool map_one_finish;
extern bool map_two_finish;
extern bool map_one_continue;
extern bool map_two_continue;

bool GameDefault::init()
{
	if (!Layer::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ���¿�ʼ��ť
	auto restartItem = MenuItemImage::create("RestartGame.png",
		"RestartGame.png", CC_CALLBACK_1(GameDefault::RestartGame, this));

	restartItem->setPosition(Vec2(origin.x - 58, origin.y - 15));

	// ���ز˵���ť
	auto returnmenuItem = MenuItemImage::create("MapMenu.png",
		"MapMenu.png", CC_CALLBACK_1(GameDefault::ReturnMenuGame, this));

	returnmenuItem->setPosition(Vec2(origin.x + 10, origin.y - 15));

	// ͨ��ͼ��
	auto defaultMenu = Sprite::create("Menu.png");
	defaultMenu->setPosition(Vec2(visibleSize.width / 2 + 30, visibleSize.height / 2 - 15));
	this->addChild(defaultMenu, 1);

	auto defaultPic = Sprite::create("GameDefault.png");
	defaultPic->setPosition(Vec2(visibleSize.width / 2 + 30, visibleSize.height / 2 + 70));
	this->addChild(defaultPic, 1);

	// �����˵�
	Vector<MenuItem*> MenuItems;
	MenuItems.pushBack(restartItem);
	MenuItems.pushBack(returnmenuItem);
	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 2);

	return true;
}

// ���ز˵�
void GameDefault::ReturnMenuGame(Ref *pSender)
{
	TowerExist.clear();
	countnum = 5;
	carrot_level = 1;
	carrot_HP = 5;

	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();

	if (map_one_continue) 
		map_one_continue = false;
	else if (map_two_continue) 
		map_two_continue = false;

	auto MyMap = MyMap::createScene();
	Director::getInstance()->pushScene(MyMap);
}

// ���¿�ʼ
void GameDefault::RestartGame(Ref *pSender)
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