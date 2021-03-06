#ifndef _ResImage_h_
#define _ResImage_h_
#include <iostream>
#include<vector>
#include <string.h>


#include "ResBase.h"
#include "Bitmap.h"

#include "Canvas.h"
#include "TextRender.h"


class ResImage : public ResBase
{
protected:
    /**
    * 切片宽
    */
    int mWidth;

    /**
    * 切片高
    */
    int mHeight;

    /**
    * 切片数量
    */
    int mNumber;

    /**
    * 是否透明
    */
    bool mTransparent;

protected:
    /**
    * 图像数据 不透明：一位一像素，0白，1黑。
    * 透明：两位一像素，高位（0不透明，1透明），低位（0白，1黑）。
    * 注意：有冗余数据。
    */
    char *mData;
    int mDataLen;

    /**
    * 图片数组
    */
    std::vector<Bitmap *> mBitmaps;

public:
    ResImage();
    virtual ~ResImage();
    virtual void setData(char *buf, int offset);

private:
    /**
    * 根据{@link #mData}创建位图数组
    */
    void createBitmaps();



public:
    /**
    *
    * @param canvas
    *            目标画布
    * @param num
    *            要画的切片编号,>0
    * @param left
    *            画到画布的最左端位置
    * @param top
    *            画到画布的最上端位置
    */
    void draw(Canvas *canvas, int num, int left, int top);

    Bitmap *getBitmap(int index);
    /**
    *
    * @return 切片数量
    */
    int getNumber()
    {
        return mNumber;
    }

    int getWidth()
    {
        return mWidth;
    }

    int getHeight()
    {
        return mHeight;
    }

    /**
    * 得到资源的大小
    * @return
    */
    int getBytesCount()
    {
        return mDataLen + 6;
    }
};

#endif