#ifndef _RESGUT_H_
#define _RESGUT_H_

#include <iostream>
#include <string.h>

#include "ResBase.h"

class ResGut: public ResBase 
{

private:
    /**
    * 脚本说明
    */
    std::string mDescription;

	/**
	 * 脚本长度，字节总数
	 */
	int mLength;

	/**
	 * 场景事件个数
	 */
	int mNumSceneEvent;

	/**
	 * 场景事件
	 */
	int *mSceneEvent;

	/**
	 * 脚本，格式为 指令号+数据
	 */
    char * mScriptData;
    int mScriptDataLen;

public:
    virtual ~ResGut();
    void setData(char *buf, int offset);

	/**
	 * 
	 * @return 脚本说明
	 */
    std::string getDescription()
    {
        return mDescription;
    }
	/**
	 * 场景事件，255个(1-255)。分为NPC事件、地图事件和其他事件。 NPC事件由1到40，与其资源操作号对应；地图事件由41到255，
	 * 即地图编辑器中设置的事件为1，在场景中的事件为1+40=41； 其他事件可用1到255。
	 * 
	 * @return 场景事件
	 */
    int *getSceneEvent()
    {
        return mSceneEvent;
    }

    int getSceneEventNum() const
    {
        return mNumSceneEvent;
    }
	/**
	 * 
	 * @return 脚本，格式为 指令号+数据
	 */
    char* getScriptData()
    {
        return mScriptData;
    }

    int getScriptDataLen()
    {
        return mScriptDataLen;
    }
};

#endif _RESGUT_H_