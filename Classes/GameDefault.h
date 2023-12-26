#ifndef __GAME_DEFAULT__H__
#define __GAME_DEFAULT__H__

#include "cocos2d.h"

USING_NS_CC;

class GameDefault : public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* scene(RenderTexture* sqr);
	CREATE_FUNC(GameDefault);
	// 重新开始
	void RestartGame(Ref *pSender);
	// 返回菜单
	void ReturnMenuGame(Ref *pSender);
};
#endif 