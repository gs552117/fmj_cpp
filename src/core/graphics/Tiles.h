#ifndef _Tiles_H_
#define _Tiles_H_

#include "DatLib.h"
#include "ResImage.h"
#include "Canvas.h"

class Tiles
{
public:
    Tiles(int index);
    virtual ~Tiles();

    /**
     *
     * @param canvas
     * @param x
     * @param y
     * @param i
     *            图块的序号
     */
    void draw(Canvas *canvas, int x, int y, int i);

public:
    /**
     * 地图块的宽
     */
    static const int WIDTH = 16;
    /**
     * 地图块的高
     */
    static const int HEIGHT = 16;

private:
    ResImage *mTileRes;
};

#endif
