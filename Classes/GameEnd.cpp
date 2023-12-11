#include "GameEnd.h"
#include "GameScene.h"
#include "MapScene.h"

USING_NS_CC;

Scene* GameEnd::scene(RenderTexture* sqr)
{
	Scene *scene = Scene::create();
	GameEnd *layer = GameEnd::create();
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

bool GameEnd::init()
{
	if (!Layer::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ������Ϸ��ť
	auto continueItem = MenuItemImage::create("ContinueGame.png",
		"ContinueGame.png", CC_CALLBACK_1(GameEnd::ContinueGame, this));

	continueItem->setPosition(Vec2(origin.x - 58, origin.y -15));

	// ���ز˵���ť
	auto returnmenuItem = MenuItemImage::create("MapMenu.png",
		"MapMenu.png", CC_CALLBACK_1(GameEnd::ReturnMenuGame, this));

	returnmenuItem->setPosition(Vec2(origin.x + 10, origin.y -15));

	// ��ͣͼ��
	auto successMenu = Sprite::create("Menu.png");
	successMenu->setPosition(Vec2(visibleSize.width / 2 + 30, visibleSize.height / 2-15));
	this->addChild(successMenu, 1);

	auto successPic = Sprite::create("GameSuccess.png");
	successPic->setPosition(Vec2(visibleSize.width / 2 + 30, visibleSize.height / 2+70));
	this->addChild(successPic, 1);

	// �����˵�
	Vector<MenuItem*> MenuItems;
	MenuItems.pushBack(continueItem);
	MenuItems.pushBack(returnmenuItem);
	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 2);

	return true;
}

// ������һ�ؿ�
void GameEnd::ContinueGame(Ref *pSender)
{
	// ջ��������ջ
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
	// �л�ҳ��
	auto Game_two = Game_two::createScene();
	// ��ǰ����ѹ��ջ��
	Director::getInstance()->pushScene(Game_two);
}

// ���ز˵�
void GameEnd::ReturnMenuGame(Ref *pSender)
{
	// ջ��������ջ
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
	// �л�ҳ��
	auto MyMap = MyMap::createScene();
	// ��ǰ����ѹ��ջ��
	Director::getInstance()->pushScene(MyMap);
}