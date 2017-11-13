#include "ModalLayer.h"

ModalLayer::ModalLayer()
	:_isClickRemove(false)
	,_isClickVisible(false)
	,_isClickAllRemove(false)
{
	setValue();
}
ModalLayer::~ModalLayer()
{
}
ModalLayer *ModalLayer::create(bool isClickRemove,bool isClickVisible)
{
	ModalLayer *ret = new (std::nothrow) ModalLayer();
	if (ret && ret->initWithColor(Color4B(0,0,0,150)))
	{
		ret->setClickRemove(isClickRemove);
		ret->setClickVisible(isClickVisible);
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

void ModalLayer::setValue()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(ModalLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	 setContentSize(Director::getInstance()->getVisibleSize());
}
bool ModalLayer::onTouchBegan(Touch *touch, Event *event)
{
	Point location = touch->getLocation();
	if(isVisible() && getParent()->isVisible())
	{
		if(_isClickAllRemove)
			this->runAction(RemoveSelf::create());
		else if(_isClickRemove&&checkChildNode(location))//자식 노드 체크 
			this->runAction(RemoveSelf::create());
		else if(_isClickVisible&&checkChildNode(location))
			this->setVisible(false);

		return true;
	}
	else
	{
		return false;
	}
}
void ModalLayer::setClickAllRemove(bool isAllClickRemove)
{
	_isClickAllRemove = isAllClickRemove;
}
void ModalLayer::setClickRemove(bool isClickRemove)
{
	_isClickRemove = isClickRemove;
}
void ModalLayer::setClickVisible(bool isClickVisible)
{
	_isClickVisible = isClickVisible;
}
bool ModalLayer::checkChildNode(const Point &position)
{
	Vector<Node*> children = this->getChildren();
	for(int i=0;i<children.size();i++)
	{
		Node *childeNode = children.at(i);
		Rect childRect = childeNode->getBoundingBox();
		if(!childRect.containsPoint(position))
		{
			return true;
		}
	}
	return false;
}