#ifndef _ScreenSaveLoadGame_h_
#define _ScreenSaveLoadGame_h_
 
#include <iostream>
#include <fstream>

#include "BaseScreen.h"
#include "SaveLoadGame.h"
#include "ScreenMessageBox.h"
#include "ScriptResources.h"


class ScreenSaveLoadGame : public BaseScreen
{
public:
    enum Operate
    {
        SAVE,   // 保存进度
        LOAD    // 读取进度
    };

public:
    ScreenSaveLoadGame(Operate opt);
    virtual ~ScreenSaveLoadGame();
private:
    std::string format(std::string s);

    std::string getSceneNameAndHeads(SaveLoadStream *Buffer, std::vector<ResImage *> &heads);
    
public:
    virtual  void update(long delta){}

    virtual  void draw(Canvas *canvas);

    virtual void onKeyDown(int key);

    virtual void onKeyUp(int key);

    bool loadGame(SaveLoadStream *Buffer);

    static bool saveGame(SaveLoadStream *Buffer);

private:
    int mTextPos[3][2];
    int mIndex;
    std::string mEmpty;
    std::string mText[3];
    std::vector<ResImage *> mHeadImgs[3];
    std::string mFileNames[3];
    Operate mOperate;
    ResImage *mImgBg;   // 背景图片
};

#endif
