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
	// ������Ϸ
	void ContinueGame(Ref *pSender);
	// ���ز˵�
	void ReturnMenuGame(Ref *pSender);
};
#endif 