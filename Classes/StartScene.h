#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

class Start : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// 退出游戏函数
	void menuCloseCallback(Ref* pSender);
	// 进入下一界面
	void menuItemSettingCallback(Ref *pSender);
	// 开启和关闭声音
	void openAndCloseSound(Ref *pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(Start);
};

#endif
