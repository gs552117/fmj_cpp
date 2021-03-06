
#include "ResSrs.h"

void ResSrs::setData(char *buf, int offset)
{
    mType = buf[offset];
    mIndex = (int)buf[offset + 1] & 0xFF;
    mFrameNum = (int)buf[offset + 2] & 0xFF;
    mImageNum = (int)buf[offset + 3] & 0xFF;
    mStartFrame = (int)buf[offset + 4] & 0xFF;
    mEndFrame = (int)buf[offset + 5] & 0xFF;

    int ptr = offset + 6;

    mFrameHeader.resize(mFrameNum);
    for (int i = 0; i < mFrameNum; i++)
    {
        mFrameHeader[i].data[0] = (int)buf[ptr++] & 0xFF; // x
        mFrameHeader[i].data[1] = (int)buf[ptr++] & 0xFF; // y
        mFrameHeader[i].data[2] = (int)buf[ptr++] & 0xFF; // Show
        mFrameHeader[i].data[3] = (int)buf[ptr++] & 0xFF; // nShow
        mFrameHeader[i].data[4] = (int)buf[ptr++] & 0xFF; // 图号
    }

    // 读入mImageNum个ResImage
    mImage.resize(mImageNum);
    for (int i = 0; i < mImageNum; i++)
    {
        mImage[i] = new ResImage();
        mImage[i]->setData(buf, ptr);
        ptr += mImage[i]->getBytesCount();
    }
}



/**
 * 开始特效动画
 */
void ResSrs::startAni()
{
    mShowList.clear();
    mShowList.push_back(new Key(0, mFrameHeader));
}

/**
 *
 * @return 返回false动画播放完毕
 */
bool ResSrs::update(long delta)
{
    std::list<Key *>::const_iterator iter;
    for (int j = 0; j < mIterator; j++)
    {
        for (iter = mShowList.begin(); iter != mShowList.end(); ++iter)
        {
            --(*iter)->show;
            --(*iter)->nshow;

            // 下一帧开始显示
            if ((*iter)->nshow == 0 && (*iter)->index + 1 < mFrameNum)
            {
                mShowList.push_back(new Key((*iter)->index + 1,mFrameHeader));
            }
        }

        for (iter = mShowList.begin(); iter != mShowList.end();)
        {
            //该帧的图片显示完成
            if ((*iter)->show <= 0)
            {
                Key *key = (*iter);
                mShowList.remove((*iter));
                delete key;

                if (mShowList.empty())
                {
                    break;
                }

                //更新头
                iter = mShowList.begin();
            }
            ++iter;
        }

        if (mShowList.empty())
        {
            return false;
        }
    }
    return true;
}

void ResSrs::draw(Canvas *canvas, int dx, int dy)
{
    for (std::list<Key *>::const_iterator i = mShowList.begin(); i != mShowList.end(); ++i)
    {
        ResImage *image = mImage[mFrameHeader[(*i)->index].data[4]];
        image->draw(canvas, 1, mFrameHeader[(*i)->index].data[0] + dx, mFrameHeader[(*i)->index].data[1] + dy);
    }
}

void ResSrs::drawAbsolutely(Canvas *canvas, int x, int y)
{
    for (std::list<Key *>::const_iterator i = mShowList.begin(); i != mShowList.end(); ++i)
    {
        mImage[mFrameHeader[(*i)->index].data[4]]->draw(canvas, 1,
            mFrameHeader[(*i)->index].data[0] - mFrameHeader[0].data[0] + x,
            mFrameHeader[(*i)->index].data[1] - mFrameHeader[0].data[1] + y);
    }
}

void ResSrs::setIteratorNum(int n)
{
    mIterator = n;
    if (mIterator < 1)
    {
        mIterator = 1;
    }
}

ResSrs::ResSrs():
mIterator(1)
{

}

ResSrs::~ResSrs()
{
    int i;
    for (i = 0; i < (int)(mImage.size()); i++)
    {
        delete mImage[i];
    }
    mImage.clear();

    std::list<Key *>::const_iterator iter;
    for (iter = mShowList.begin(); iter != mShowList.end(); ++iter)
    {
        Key *key = *iter;
        delete key;
    }
}
