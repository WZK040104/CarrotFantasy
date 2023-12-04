#include "MapScene.h"
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
	if (!MyMap::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	return true;
}

void MyMap::menuItemSettingCallback(Ref *pSender)
{
	// �л�ҳ��
	auto sc = MyMap::createScene();
	// ��ǰ����ѹ��ջ��
	Director::getInstance()->pushScene(sc);
}