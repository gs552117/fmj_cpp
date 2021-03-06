#ifndef _ScriptResources_h_
#define _ScriptResources_h_

class SaveLoadStream;

class ScriptResources
{
public:
    virtual ~ScriptResources();
    /**
     * 全局事件标志1-2400
     */
    static bool globalEvents[2401];

    /**
     * 全局变量0-199,局部变量200-239
     */
    static int variables[240];

    /**
     * 初始化局部变量
     */
    static void initLocalVar();

    /**
     * 初始化全局变量
     */
    static void initGlobalVar();

    /**
     * 初始化全局事件
     */
    static void initGlobalEvents();


    /**
     * 将全局事件num标志设置为true
     * @param num 1-2400
     */
    static void setEvent(int num);


    /**
     * 将全局事件num标志设置为false
     */
    static void clearEvent(int num);

    static bool write(SaveLoadStream *Buffer);

    static bool read(SaveLoadStream *Buffer);

};


#endif
