#pragma once
#include <iostream>
#include "Bitmap.h"
#include "BaseScreen.h"
#include "HMStack.h"
#include "Point.h"

class Rect;
class GoodsEquipment;

using namespace std;

class  ScreenActorWearing : public BaseScreen
{
private:
    Point mPos[8];
    GoodsEquipment *mEquipments[8];
    string mItemName[8];
    int mCurItem;
    int mActorIndex;
    bool showingDesc;
    Bitmap *bmpName;
    Bitmap *bmpDesc;
    string mTextName;
    string mTextDesc;
    int mToDraw; // ��ǰҪ���������е��ֽ�
    int mNextToDraw; // ��һ��Ҫ���������е��ֽ�
    HMStack<int> mStackLastToDraw; // �����ϴ���������λ��
    static Rect *sRectDesc;

public:
    ScreenActorWearing();
    ~ScreenActorWearing();

    virtual void update(long delta){}
    virtual void draw(Canvas *canvas);
    virtual void onKeyDown(int key);
    virtual void onKeyUp(int key);

private:
    vector<BaseGoods*> *getTheEquipList(int type);
    void resetDesc();
};
