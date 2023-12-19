#include "GameScene.h"
#include "Gamepause.h"
#include "Externgame.h"

USING_NS_CC;

extern int countnum;

Scene* Gamepause::scene(RenderTexture* sqr)
{
	Scene *scene = Scene::create();
	Gamepause *layer = Gamepause::create();
	scene->addChild(layer, 1);
	// ���Ӳ��֣�ʹ��Game�����н�ͼ��sqr����ͼƬ����Sprite
	// ����Sprite��ӵ�GamePause��������
	// �õ����ڵĴ�С
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto back_sqr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	back_sqr->setPosition(Vec2(visibleSize.width / 2 + 24, visibleSize.height / 2)); // ����λ��,������������λ�á�
	back_sqr->setFlipY(true);            // ��ת����ΪUI�����OpenGL���겻ͬ
	back_sqr->setColor(Color3B(80, 80, 80)); // ͼƬ��ɫ���ɫ
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

	// ������Ϸ��ť
	auto continueItem = MenuItemImage::create("ContinueGame.png",
		"ContinueGame.png", CC_CALLBACK_1(Gamepause::ContinueGame, this));

	continueItem->setPosition(Vec2(origin.x - 70, origin.y + 2));

	// ���¿�ʼ��ť
	auto restartItem = MenuItemImage::create("RestartGame.png",
		"RestartGame.png", CC_CALLBACK_1(Gamepause::RestartGame, this));

	restartItem->setPosition(Vec2(origin.x - 23, origin.y + 2));

	// ���ز˵���ť
	auto returnmenuItem = MenuItemImage::create("MapMenu.png",
		"MapMenu.png", CC_CALLBACK_1(Gamepause::ReturnMenuGame, this));

	returnmenuItem->setPosition(Vec2(origin.x + 23, origin.y + 2));

	// ��ͣͼ��
	auto pauseMenu = Sprite::create("PauseMenu.png");
	pauseMenu->setPosition(Vec2(visibleSize.width / 2 + 30, visibleSize.height / 2 + 10));
	this->addChild(pauseMenu, 1);

	// �����˵�
	Vector<MenuItem*> MenuItems;
	MenuItems.pushBack(continueItem);
	MenuItems.pushBack(restartItem);
	MenuItems.pushBack(returnmenuItem);
	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 2);

	return true;
}

// ������һҳ��
void Gamepause::ContinueGame(Ref *pSender)
{
	Director::getInstance()->popScene();
}

// ���¿�ʼ
void Gamepause::RestartGame(Ref *pSender)
{
	countnum = 20;
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

// ���ز˵�
void Gamepause::ReturnMenuGame(Ref *pSender)
{
	countnum = 20;
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
	if (map_one_continue)
		map_one_continue = false;
	if (map_two_continue)
		map_two_continue = false;
}