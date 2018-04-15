#include "ScreenChgEquipment.h"
#include "Player.h"
#include "GoodsEquipment.h"
#include "GameView.h"

ScreenChgEquipment::ScreenChgEquipment(Player *actor, GoodsEquipment *goods)
    :mPage(0)
{
    mActor = actor;
    if (actor->hasSpace(goods->getType()))
    {
        mGoods.clear();
        mGoods.push_back(goods);
        mSelIndex = 0;
    }
    else
    {
        mGoods.clear();
        mGoods.push_back(actor->getCurrentEquipment(goods->getType()));
        mGoods.push_back(goods);
        mSelIndex = 1;
        // û�пռ䣬�ѵ���ǰװ����
        actor->takeOff(goods->getType());
    }
    actor->putOn(goods);
}

void ScreenChgEquipment::draw(Canvas *canvas)
{
    canvas->drawColor(Manager::sCOLOR_WHITE);
    if (mActor != NULL)
    {
        mActor->drawState(canvas, mPage);
        mActor->drawHead(canvas, 5, 60);
    }
    for (int i = 0; i < mGoods.size(); i++)
    {
        if (mGoods[i] != NULL)
        {
            mGoods[i]->draw(canvas, 8, 2 + 32 * i);
        }
    }
    Util::drawTriangleCursor(canvas, 1, 10 + 32 * mSelIndex);
}

void ScreenChgEquipment::onKeyDown(int key)
{
    if (key == KEY_UP && mSelIndex > 0)
    {
        mActor->takeOff(mGoods[mSelIndex]->getType());
        --mSelIndex;
        mActor->putOn(mGoods[mSelIndex]);
    }
    else if (key == KEY_DOWN && mSelIndex < mGoods.size() - 1)
    {
        mActor->takeOff(mGoods[mSelIndex]->getType());
        ++mSelIndex;
        mActor->putOn(mGoods[mSelIndex]);
    }
    else if (key == KEY_PAGEDOWN || key == KEY_PAGEUP)
    {
        mPage = 1 - mPage;
    }
}

void ScreenChgEquipment::onKeyUp(int key)
{
    if (key == KEY_CANCEL)
    {
        // ����ԭ����װ��
        mActor->takeOff(mGoods[0]->getType());
        if (mGoods.size() > 1)
        {
            mActor->putOn(mGoods[0]);
        }
        GameView::getInstance()->popScreen();
    }
    else if (key == KEY_ENTER)
    {
        if (mSelIndex == mGoods.size() - 1)
        {
            // ������װ��
            // ��Ʒ����ɾ����װ��
            Player::sGoodsList->deleteGoods(mGoods[mGoods.size() - 1]->getType(),
                mGoods[mGoods.size() - 1]->getIndex());
            // ��Ʒ���м�����װ��
            if (mGoods.size() > 1)
            {
                Player::sGoodsList->addGoods(mGoods[0]->getType(), mGoods[0]->getIndex());
            }
        }
        GameView::getInstance()->popScreen();
    }
}
