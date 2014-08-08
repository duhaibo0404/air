#ifndef  _APP_PLANE_H_
#define  _APP_PLANE_H_

#include "cocos2d.h"

USING_NS_CC;

//PlaneLayer.h
class PlaneLayer :public Layer
{
public:
 
	PlaneLayer(void){isAlive=true;};
     
	~PlaneLayer(void){};
 
    static PlaneLayer* create();//ʵ��create����

	void MoveTo(Point location);
 
    virtual bool init();
 
public:
    bool isAlive;
    static PlaneLayer* sharedPlane;//�ṩsharedPlaneȫ��ָ��
};

#endif