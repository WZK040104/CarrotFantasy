#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

class Start : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// �˳���Ϸ����
	void menuCloseCallback(cocos2d::Ref* pSender);
	// ������һ����
	void menuItemSettingCallback(Ref *pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Start);
};

#endif
