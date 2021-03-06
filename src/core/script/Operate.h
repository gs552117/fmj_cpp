#ifndef _Operate_h_
#define _Operate_h_

#include "Canvas.h"

class Operate
{
public:
    virtual ~Operate(){}
    /**
    * 处理一条指令
    *
    * @return <code>true</code>继续执行 {@link #update(long)} {@link #draw(Canvas)}
    *         <p>
    *         <code>false</code>指令执行完毕
    */
    virtual bool process() = 0;

    /**
     *
     * @param delta
     * @return <code>false</code>退出当前操作
     */
    virtual bool update(long delta) = 0;

    virtual void draw(Canvas *canvas) = 0;

    virtual void onKeyDown(int key) = 0;

    virtual void onKeyUp(int key) = 0;

    /**
     *
     * @return 是否全屏
     */
    bool isPopup()
    {
        return false;
    }
};
#endif
