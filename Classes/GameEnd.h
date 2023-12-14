#ifndef __GAME_END__H__
#define __GAME_END__H__

#include "cocos2d.h"

USING_NS_CC;

class GameEnd : public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* scene(RenderTexture* sqr);
	CREATE_FUNC(GameEnd);
	// 开始下一关卡
	void ContinueGame(Ref *pSender);
	// 返回菜单
	void ReturnMenuGame(Ref *pSender);
};
#endif 