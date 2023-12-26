#include "MapScene.h"
#include "StartScene.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"

using namespace cocos2d::experimental;
using namespace cocos2d::ui;

USING_NS_CC;

bool map_one_finish = false; // ��һ���Ƿ����
bool map_two_finish = false; // �ڶ����Ƿ����
bool map_two_unlock = false; // �ڶ����Ƿ����
bool map_one_continue = false; // ��һ���Ƿ����ڽ���
bool map_two_continue = false; // �ڶ����Ƿ����ڽ���
bool sound = true; // �����Ƿ���
int backgroundAudioID;

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

	AudioEngine::preload("BackgroundMusic.mp3");
	backgroundAudioID = AudioEngine::play2d("BackgroundMusic.mp3", true);

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

	// ��ʼ��Ϸ��ť
	auto startItem = Button::create("StartButton.png", "StartButton_selected.png");

	if (startItem == nullptr
		|| startItem->getContentSize().width <= 0
		|| startItem->getContentSize().height <= 0)
	{
		problemLoading("'StartButton.png'");
	}
	else
	{
		float x = origin.x + 140;
		float y = origin.y + 50;
		startItem->setPosition(Vec2(x, y));
	}

	startItem->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED: {
			auto MyMap = MyMap::createScene();
			Director::getInstance()->pushScene(TransitionFade::create(0.5, MyMap, Color3B(255, 255, 255)));
		}
			break;
		default:
			break;
		}
	});
	this->addChild(startItem);

	// �ر���Ϸ��ť
	auto closeItem = Button::create("EndButton.png", "EndButton_selected.png");

	if (closeItem == nullptr
		|| closeItem->getContentSize().width <= 0
		|| closeItem->getContentSize().height <= 0)
	{
		problemLoading("'EndButton.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width-145;
		float y = origin.y + 50;
		closeItem->setPosition(Vec2(x, y));
	}

	closeItem->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED: {
			// �ر�ҳ�棬�˳���Ϸ
			Director::getInstance()->end();

			#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				exit(0);
			#endif
		}
			break;
		default:
			break;
		}
	});
	this->addChild(closeItem);

	// ����������ť
	auto soundItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Start::openAndCloseSound, this),
		MenuItemImage::create("SoundButton.png","SoundButton.png"),
		MenuItemImage::create("SoundCloseButton.png", "SoundCloseButton.png"),nullptr);

	if (soundItem == nullptr
		|| soundItem->getContentSize().width <= 0
		|| soundItem->getContentSize().height <= 0)
	{
		problemLoading("'SoundButton.png'");
	}
	else
	{
		soundItem->setPosition(Vec2(origin.x + 170, origin.y + 120));
	}

	// �����˵�
	Vector<MenuItem*> MenuItems;
	MenuItems.pushBack(soundItem);
	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 1);

	return true;
}

// �������ֿ�����ر�
void Start::openAndCloseSound(Ref *pSender)
{
	if (!sound) {
		AudioEngine::resume(backgroundAudioID);
		sound = true;
	}
	else{
		AudioEngine::pause(backgroundAudioID);
		sound = false;
	}
}