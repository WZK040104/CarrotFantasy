#ifndef __GAME_PAUSE__H__
#define __GAME_PAUSE__H__

#include "cocos2d.h"
USING_NS_CC;

class Gamepause : public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* scene(RenderTexture* sqr);
	CREATE_FUNC(Gamepause);
	// 继续游戏
	void ContinueGame(Ref *pSender);
	// 返回菜单
	void ReturnMenuGame(Ref *pSender);
};
#endif 