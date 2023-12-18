#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "Gamepause.h"
#include "GameEnd.h"
#include "GBKtoUTF-8.h"
#include "Tower_kind.h"

USING_NS_CC;
using namespace std;
int current_gold_coins = 15;

Scene* Game_one::createScene()
{
	Scene *scene = Scene::create();
	Game_one *layer = Game_one::create();
	scene->addChild(layer);
	return scene;
}
// �Ҳ����ļ�ʱ�׳��쳣
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

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

extern bool map_two_unlock;
extern bool map_one_continue;



bool Game_one::init()
{
	if (!Scene::init())
	{
		return false;
	}

	map_one_continue = true;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ���뱳��ͼƬ
	auto map_one = Sprite::create("GameBackground_one.png");
	if (map_one == nullptr)
	{
		problemLoading("'GameBackground_one.png'");
	}
	else
	{
		map_one->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		this->addChild(map_one, 0);
	}

	// �����ϱ���ͼƬ
	auto upperboard = Sprite::create("Upperboard.png");
	if (upperboard == nullptr)
	{
		problemLoading("'Upperboard.png'");
	}
	else
	{
		upperboard->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - upperboard->getContentSize().height / 2));
		this->addChild(upperboard, 1);
	}

	// ��ͣ����
	auto pauseItem = MenuItemImage::create("Pause.png",
		"Pause.png", CC_CALLBACK_1(Game_one::Pause, this));

	if (pauseItem == nullptr
		|| pauseItem->getContentSize().width <= 0
		|| pauseItem->getContentSize().height <= 0)
	{
		problemLoading("'Pause.png'");
	}
	else
	{
		pauseItem->setPosition(Vec2(origin.x + 160, origin.y + 143));
	}

	// ���ذ�ť
	auto returnItem = MenuItemImage::create("Return.png",
		"Return.png", CC_CALLBACK_1(Game_one::Success, this));

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

	// �����˵�
	Vector<MenuItem*> MenuItems;
	MenuItems.pushBack(pauseItem);
	MenuItems.pushBack(returnItem);
	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 1);


	// ��� "carrot" ͼƬ
	auto carrot = Sprite::create("carrot.png");
	if (carrot)
	{
		carrot->setPosition(Vec2(86, 248)); //�ܲ�λ��
		this->addChild(carrot, 1);

		auto CarrotHealthBack = Sprite::create("CarrotHealthBack.png");
		CarrotHealthBack->setPosition(Vec2(86, 278));// �ܲ��Ϸ�λ��
		this->addChild(CarrotHealthBack, 1);

		// ����ܲ�Ѫ��
		ProgressTimer* healthBar = ProgressTimer::create(Sprite::create("HealthBar.png"));
		healthBar->setType(ProgressTimer::Type::BAR);
		healthBar->setMidpoint(Vec2(0, 0.5));
		healthBar->setBarChangeRate(Vec2(1, 0));
		healthBar->setPosition(Vec2(86, 278));  // �ܲ��Ϸ�λ��
		healthBar->setPercentage(100.0f);  // ��ʼѪ���ٷֱ�
		this->addChild(healthBar, 2, "healthBar");
	}
	else
	{
		problemLoading("'carrot.png'");
	}

	//��ӳ�����ͼƬ
	auto GuideBoard = Sprite::create("GuideBoard.png");
	if (GuideBoard)
	{
		GuideBoard->setPosition(Vec2(433, 75)); //������λ��
		this->addChild(GuideBoard, 1);
	}
	else
	{
		problemLoading("'GuideBoard.png'");
	}

	// �������
	auto countdown = Label::createWithTTF(GBKToUTF8("5��������Ϯ"), "fonts/STHUPO.TTF", 10);
	if (countdown == nullptr)
	{
		problemLoading("'fonts/STHUPO.TTF'");
	}
	else
	{
		countdown->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - countdown->getContentSize().height - 4));
		this->addChild(countdown, 2);
	}
	countdown->setColor(Color3B(255, 255, 255));

	//��ʾ��ߵķ�����0
	createTower0("tower_zero0.png", "tower_back0.png", "tower_zero.png", "tower_back.png", tower0_upgrade_coins[0], 230, 0);

	//��ʾ��ߵķ�����1
	createTower0("tower_one0.png", "tower_back0.png", "tower_one.png", "tower_back.png", tower1_upgrade_coins[0], 185, 1);

	//��ʾ��ߵķ�����2
	createTower0("tower_two0.png", "tower_back0.png", "tower_two.png", "tower_back.png", tower2_upgrade_coins[0], 140, 2);

	//��ʾ��ߵķ�����3
	createTower0("tower_three0.png", "tower_back0.png", "tower_three.png", "tower_back.png", tower3_upgrade_coins[0], 95, 3);

	//��ʼ����Ҳ���ı�ǩ
	insufficientGoldLabel = Label::createWithTTF("not enough gold coins!", "fonts/Marker Felt.ttf", 14);
	insufficientGoldLabel->setColor(Color3B(255, 0, 0));  // ��ɫ
	insufficientGoldLabel->setVisible(false);  // ��ʼʱ����Ϊ���ɼ�
	insufficientGoldLabel->setPosition(Vec2(90,60));//����λ��
	this->addChild(insufficientGoldLabel, 1);

	// ������ͼƬ
	auto moneypic = Sprite::create("Money.png");
	if (moneypic == nullptr)
	{
		problemLoading("'Money.png'");
	}
	else
	{
		moneypic->setPosition(Vec2(origin.x + 16, origin.y + visibleSize.height - 16));
		this->addChild(moneypic, 1);
	}

	// ������� �������
	auto mapnum = Label::createWithTTF(to_string(current_gold_coins), "fonts/Marker Felt.ttf", 18);
	if (mapnum == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		mapnum->setPosition(Vec2(origin.x + 40, origin.y + visibleSize.height - 18));
		this->addChild(mapnum, 1);
	}
	mapnum->setColor(Color3B(255, 255, 0));

	// ������λ����ʾ
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(Game_one::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	return true;
}

// ��ͣ��Ϸ
void Game_one::Pause(Ref* pSender)
{
	// �õ����ڵĴ�С
	auto visibleSize = Director::getInstance()->getVisibleSize();
	RenderTexture *renderTexture = RenderTexture::create(visibleSize.width+48, visibleSize.height);

	// ������ǰ��������ӽڵ���Ϣ������renderTexture�С�
	// �������ƽ�ͼ��
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	Director::getInstance()->pushScene(Gamepause::scene(renderTexture));
}

// ��Ϸͨ��
void Game_one::Success(Ref* pSender)
{
	map_two_unlock = true;

	// �õ����ڵĴ�С
	auto visibleSize = Director::getInstance()->getVisibleSize();
	RenderTexture *renderTexture = RenderTexture::create(visibleSize.width + 48, visibleSize.height);

	// ������ǰ��������ӽڵ���Ϣ������renderTexture�С�
	// �������ƽ�ͼ��
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	Director::getInstance()->pushScene(GameEnd::scene(renderTexture));
}

// ������¼��ص�
void Game_one::onMouseDown(EventMouse* event)
{
	// ��ȡ�����λ��
	Vec2 mousePosition = this->convertToNodeSpace(event->getLocationInView());

	// ������λ��
	log("Mouse Clicked at (%.2f, %.2f)", mousePosition.x, mousePosition.y);

	int tower0Clicked = checkTower0Clicked(mousePosition);

	// ���������Ĳ�߷�����
	if (tower0Clicked != -1)
	{
		switch (tower0Clicked)
		{
		case 0:
		{
			if (current_gold_coins < tower0_upgrade_coins[0])
				showInsufficientGoldLabel();
			break;
		}
		case 1:
		{
		if (current_gold_coins < tower1_upgrade_coins[0])
			showInsufficientGoldLabel();
		break;
		}
		case 2:
		{
			if (current_gold_coins < tower2_upgrade_coins[0])
				showInsufficientGoldLabel();
			break;
		}
		case 3:
		{
			if (current_gold_coins < tower3_upgrade_coins[0])
				showInsufficientGoldLabel();
			break;
		}
		default:
			break;
		}
	}
	else// ���û�е��������������Ļ����ʾ���λ��
	{
		drawMousePositionLabel(mousePosition);
	}
}

// ����Ļ����ʾ���λ��
void Game_one::drawMousePositionLabel(const Vec2& position)
{
	// �Ƴ�֮ǰ�ı�ǩ
	removeChildByTag(123);

	// ������ǩ����ʾ���λ��
	auto label = Label::createWithTTF(StringUtils::format("(%.2f, %.2f)", position.x, position.y),
		"fonts/arial.ttf", 24);
	label->setPosition(Vec2(120, 60));
	label->setTag(123);
	addChild(label);
}

//��Ӳ�߷�������ͼ��
void Game_one::createTower0(const std::string& tower0Image, const std::string& tower0BackImage,
	const std::string& towerImage, const std::string& towerBackImage,
	int upgradeCoins, float positionY, int index)
{
	// ��ʾ��ߵķ�����0
	auto tower0 = Sprite::create(tower0Image);
	if (tower0)
	{
		auto tower_back0 = Sprite::create(tower0BackImage);
		tower_back0->setPosition(Vec2(42, positionY));
		this->addChild(tower_back0, 1);  // ����������
		tower0->setPosition(Vec2(42, positionY));  // ��߷�����λ��
		this->addChild(tower0, 1);

		// �жϽ���Ƿ��㹻���������
		if (current_gold_coins >= upgradeCoins)
		{
			auto tower = Sprite::create(towerImage);
			if (tower)
			{
				auto tower_back = Sprite::create(towerBackImage);
				tower_back->setPosition(Vec2(42, positionY));
				this->addChild(tower_back, 1);  // ����������
				tower->setPosition(Vec2(42, positionY));  // ��߷�����λ��
				this->addChild(tower, 1);
			}
			else
			{
				//problemLoading("'" + towerImage + "'");
			}
		}
		else
		{
			//problemLoading("'" + towerImage + "' (Not enough gold coins)");
		}

		Label* build = Label::createWithTTF(to_string(upgradeCoins), "fonts/Marker Felt.ttf", 13);  // ������֣���Ҫ���ĵĽ������
		if (build == nullptr)
			problemLoading("'fonts/Marker Felt.ttf'");
		else
		{
			build->setPosition(Vec2(63, positionY - 12));  // ��ӵķ�������������Ҫ��Ǯ��λ��
			this->addChild(build, 1);
		}
		build->setColor(Color3B(0, 0, 0));  // ��ɫ
	}
	else
	{
		//problemLoading("'" + tower0Image + "'");
	}
}

// �Ƿ�������ߵķ�������
int Game_one::checkTower0Clicked(const Vec2& touchLocation)
{
	// �����߷�������λ�úʹ�С
	Rect towerRects[] = {
		Rect(26, 212, 45, 36),  // ��߷�����0�����½����꣬�Ϳ�ȣ��߶�
		Rect(26, 167, 45, 36),  // ��߷�����1
		Rect(26, 122, 45, 36),  // ��߷�����2
		Rect(26, 77,  45, 36)   // ��߷�����3
	};

	for (int i = 0; i < 4; ++i)
	{
		if (towerRects[i].containsPoint(touchLocation))
		{
			// �������������������ط�������������ֵ
			return i;
		}
	}

	// ���û�е����������������-1
	return -1;
}

// ��ʾ��Ҳ��㣬1�����ʧ
void Game_one::showInsufficientGoldLabel()
{
	insufficientGoldLabel->setVisible(true);

	// ʹ�ö�ʱ���ӳ�1������ر�ǩ
	this->scheduleOnce([this](float dt) {
		insufficientGoldLabel->setVisible(false);
	}, 1.0f, "hideInsufficientGoldLabel");
}