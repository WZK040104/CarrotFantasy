#include "BackgroundMusic.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "Gamepause.h"
#include "GameEnd.h"

USING_NS_CC;

Scene* Game_two::createScene()
{
	Scene *scene = Scene::create();
	Game_two *layer = Game_two::create();
	scene->addChild(layer);
	return scene;
}
// �Ҳ����ļ�ʱ�׳��쳣
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Game_two::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ���뱳��ͼƬ
	auto map_two = Sprite::create("GameBackground_two.png");
	if (map_two == nullptr)
	{
		problemLoading("'GameBackground_two.png'");
	}
	else
	{
		map_two->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		this->addChild(map_two, 0);
	}

	// ������ͼƬ
	auto moneypic = Sprite::create("Money.png");
	if (moneypic == nullptr)
	{
		problemLoading("'Money.png'");
	}
	else
	{
		moneypic->setPosition(Vec2(origin.x + 12, origin.y + visibleSize.height - 12));
		this->addChild(moneypic, 0);
	}

	// �������
	auto mapnum = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 18);
	if (mapnum == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		mapnum->setPosition(Vec2(origin.x + 35, origin.y + visibleSize.height - 14));
		this->addChild(mapnum, 1);
	}
	mapnum->setColor(Color3B(255, 255, 0));

	// ���ذ�ť
	auto returnItem = MenuItemImage::create("Return.png",
		"Return.png", CC_CALLBACK_1(Game_two::menuOkCallback, this));

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

	// ��ͣ����
	auto pauseItem = MenuItemImage::create("Pause.png",
		"Pause.png", CC_CALLBACK_1(Game_two::Pause, this));

	pauseItem->setPosition(Vec2(origin.x + 175, origin.y + 148));

	// �����˵�
	Vector<MenuItem*> MenuItems;
	MenuItems.pushBack(returnItem);
	MenuItems.pushBack(pauseItem);
	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 1);

	return true;
}

// ������һҳ��
void Game_two::menuOkCallback(Ref *pSender)
{
	// ջ��������ջ
	Director::getInstance()->popScene();
}
// ��ͣ��Ϸ
void Game_two::Pause(Ref* pSender)
{
	// �õ����ڵĴ�С
	auto visibleSize = Director::getInstance()->getVisibleSize();
	RenderTexture *renderTexture = RenderTexture::create(visibleSize.width+48, visibleSize.height);

	// ������ǰ��������ӽڵ���Ϣ������renderTexture�С�
	// �������ƽ�ͼ��
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	// ����Ϸ������ͣ��ѹ�볡����ջ�����л���GamePause����
	Director::getInstance()->pushScene(Gamepause::scene(renderTexture));
}

// ��Ϸͨ��
void Game_two::Success(Ref* pSender)
{
	// �õ����ڵĴ�С
	auto visibleSize = Director::getInstance()->getVisibleSize();
	RenderTexture *renderTexture = RenderTexture::create(visibleSize.width + 48, visibleSize.height);

	// ������ǰ��������ӽڵ���Ϣ������renderTexture�С�
	// �������ƽ�ͼ��
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	// ����Ϸ������ͣ��ѹ�볡����ջ�����л���GamePause����
	Director::getInstance()->pushScene(GameEnd::scene(renderTexture));
}