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
	// ��ʼ��һ�ؿ�
	void ContinueGame(Ref *pSender);
	// ���ز˵�
	void ReturnMenuGame(Ref *pSender);
};
#endif 