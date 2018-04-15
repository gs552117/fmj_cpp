#include "ScreenTakeMedicine.h"
#include "ScreenMainGame.h"
#include "GoodsMedicine.h"
#include "BaseGoods.h"

GoodsMedicine * ScreenTakeMedicine::sMedicine = new GoodsMedicine();

ScreenTakeMedicine::ScreenTakeMedicine(BaseGoods *goods)
{
    mStatePageIndex = 0; // ��������ҳ������ҳ
    mActorIndex = -1;

    *sMedicine = *(static_cast<GoodsMedicine*>(goods));

    if (ScreenMainGame::sPlayerList.size() > 0)
    {
        mActorIndex = 0;
    }
}

ScreenTakeMedicine::~ScreenTakeMedicine()
{
}

void ScreenTakeMedicine::draw(Canvas *canvas)
{
    canvas->drawColor(Manager::sCOLOR_WHITE);
    ScreenMainGame::sPlayerList.at(mActorIndex)->drawState(canvas, mStatePageIndex);
    ScreenMainGame::sPlayerList.at(mActorIndex)->drawHead(canvas, 5, 60);
    if (sMedicine->getGoodsNum() > 0)
    {
        sMedicine->draw(canvas, 5, 10);
        TextRender::drawText(canvas, string("") + int_to_string(sMedicine->getGoodsNum()), 13, 35);
    }
}


void ScreenTakeMedicine::onKeyDown(int key)
{
    if (key == KEY_PAGEDOWN)
    {
        mStatePageIndex = 1;
    }
    else if (key == KEY_PAGEUP)
    {
        mStatePageIndex = 0;
    }
    else if (key == KEY_LEFT && mActorIndex > 0)
    {
        --mActorIndex;
    }
    else if (key == KEY_RIGHT && mActorIndex < ScreenMainGame::sPlayerList.size() - 1)
    {
        ++mActorIndex;
    }
}

void ScreenTakeMedicine::onKeyUp(int key)
{
    if (key == KEY_CANCEL)
    {
        GameView::getInstance()->popScreen();
    }
    else if (key == KEY_ENTER)
    {
        if (sMedicine->getGoodsNum() > 0)
        {
            if (sMedicine->getType() == 9 && sMedicine->effectAll())
            {
                // ��ͨҩ��ж��Ƿ�ȫ��
                for (int i = ScreenMainGame::sPlayerList.size() - 1; i >= 0; i--)
                {
                    sMedicine->eat(ScreenMainGame::sPlayerList.at(i));
                }
            }
            else
            {
                // ��ҩ����ҩ ������ȫ��Ч��
                sMedicine->eat(ScreenMainGame::sPlayerList.at(mActorIndex));
            }

            //ʹ��֮���һ
            sMedicine->setGoodsNum(sMedicine->getGoodsNum() - 1);
        }
        else
        {
            GameView::getInstance()->popScreen();
        }
    }
}
