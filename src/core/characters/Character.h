#ifndef _Character_H_
#define _Character_H_

#include <iostream>
#include "ResBase.h"
#include "Canvas.h"
#include "Point.h"
#include "WalkingSprite.h"
#include "Direction.h"

class Character : public ResBase
{
public:
    std::string mName;

    /**
    * 角色的动作状态
    */
    enum
    {
        /**
        * 停止状态，不作运动驱动
        */
        STATE_STOP = 0,
        /**
        * 强制移动状态，效果同2
        */
        STATE_FORCE_MOVE = 1,
        /**
        * 巡逻状态，自由行走
        */
        STATE_WALKING = 2,
        /**
        * 暂停状态，等到延时到了后转变为巡逻状态
        */
        STATE_PAUSE = 3,
        /**
        * 激活状态，只换图片，不改变位置（适合动态的场景对象，比如：伏魔灯）
        */
        STATE_ACTIVE = 4,
    };
private:
    int mState;
    /**
    * 角色在地图中的位置
    */
    Point mPosInMap;
    /**
    * 角色在地图中的面向
    */
    Direction mDirection;

    /**
    * 角色行走图
    */
    WalkingSprite *mWalkingSprite;

public:
    Character();
    virtual ~Character();
    void setName(std::string &name)
    {
        mName = name;
    }

    std::string getName();

    int getCharacterState();

    void setCharacterState(int state);

    Point getPosInMap();

    void setPosInMap(int x, int y);

    Point getPosOnScreen(Point *posMapScreen);

    void setPosOnScreen(Point *p, Point *posMapScreen);

    void setPosOnScreen(int x, int y, Point *posMapScreen);

    Direction getDirection();

    void setDirection(Direction d);

    int getWalkingSpriteId()
    {
        return mWalkingSprite->getId();
    }

    void setWalkingSprite(WalkingSprite *sprite);

    virtual void walk()
    {
        mWalkingSprite->walk();
        updatePosInMap(mDirection);
    }

    virtual void walk(Direction d);

private:
    void updatePosInMap(Direction d);

public:
    /**
     * 原地踏步
     */
    void walkStay(Direction d);

    /**
     * 原地踏步，面向不变
     */
    void walkStay();

    /**
     * 设置脚步
     * @param step 0—迈左脚；1—立正；2—迈右脚
     */
    void setStep(int step);

    int getStep();

    void drawWalkingSprite(Canvas *canvas, Point *posMapScreen);
};
#endif
