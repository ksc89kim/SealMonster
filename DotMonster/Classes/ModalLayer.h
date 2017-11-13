#ifndef __MODALLAYER_H__
#define __MODALLAYER_H__

#include "Define.h"

class ModalLayer:public LayerColor
{
private:
	bool _isClickAllRemove;
	bool _isClickRemove;
	bool _isClickVisible;

public:
	ModalLayer();
	~ModalLayer();
	
	static ModalLayer *create(bool isClickRemove=false, bool isClickVisible=false);
	void setValue();

	virtual bool onTouchBegan(Touch *touch, Event *event);

	void setClickAllRemove(bool isAllClickRemove);

	bool checkChildNode(const Point &position);
	void setClickRemove(bool isClickRemove);
	void setClickVisible(bool isClickVisible);
};

#endif
