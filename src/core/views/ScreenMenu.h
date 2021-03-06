#ifndef _ScreenMenu_h_
#define _ScreenMenu_h_

#include "BaseScreen.h"
#include "ScreenSaveLoadGame.h"
#include "SaveLoadGame.h"
#include <iostream>

class ScreenMenu : public BaseScreen
{

public:
    ScreenMenu();
    virtual ~ScreenMenu();
    virtual  void update(long delta);
    virtual  void draw(Canvas *canvas);
    virtual  void onKeyDown(int key);
    virtual  void onKeyUp(int key);

private:
    ResImage *mImgMenu;
    int mLeft, mTop;
    ResSrs *mSrsSelector[2];
    int mCurSelect;
    bool isCancelKeyDown;

};
#endif
