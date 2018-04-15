#include "GoodsEquipment.h"

#include "Player.h"


GoodsEquipment::GoodsEquipment()
{
    bFatherOfGoodsWeapon = false;
}

void GoodsEquipment::setOtherData(char * buf, int offset)
{
    mMpMax = get1ByteSInt(buf, offset + 0x16);
    mHpMax = get1ByteSInt(buf, offset + 0x17);
    mdf = get1ByteSInt(buf, offset + 0x18);
    mat = (int)buf[offset + 0x19] & 0xff;
    mlingli = get1ByteSInt(buf, offset + 0x1a);
    mSpeed = get1ByteSInt(buf, offset + 0x1b);
    mBitEffect = (int)buf[offset + 0x1c] & 0xff;
    mLuck = get1ByteSInt(buf, offset + 0x1d);
}

void GoodsEquipment::putOn(Player *p)
{
    if (canPlayerUse(p->getIndex()))
    {
        p->setMaxMP(p->getMaxMP() + mMpMax);
        p->setMaxHP(p->getMaxHP() + mHpMax);
        p->setDefend(p->getDefend() + mdf);
        p->setAttack(p->getAttack() + mat);
        p->setLingli(p->getLingli() + mlingli);
        p->setSpeed(p->getSpeed() + mSpeed);

        //�жϵ�ǰ�ǲ���GoodsWeapon��Ŀ���
        //���������һ�����������ֻ��GoodsWeapon����Ϊ1���������ܹ�ʶ����
        //if (!(this instanceof GoodsWeapon))
        if (!bFatherOfGoodsWeapon)
        {
            p->addBuff(mBitEffect); // �������Ч��
        }
        p->setLuck(p->getLuck() + mLuck);
        if (getEventId() != 0)
        {
            // ����װ���������¼�
            ScriptResources::setEvent(getEventId());
        }
    }
}

void GoodsEquipment::takeOff(Player *p)
{
    p->setMaxMP(p->getMaxMP() - mMpMax);
    p->setMaxHP(p->getMaxHP() - mHpMax);
    p->setDefend(p->getDefend() - mdf);
    p->setAttack(p->getAttack() - mat);
    p->setLingli(p->getLingli() - mlingli);
    p->setSpeed(p->getSpeed() - mSpeed);

    //�жϵ�ǰ�ǲ���GoodsWeapon��Ŀ���
    if (!bFatherOfGoodsWeapon)
    {
        p->delBuff(mBitEffect); // ɾ������Ч��
    }
    p->setLuck(p->getLuck() - mLuck);
    if (getEventId() != 0)
    {
        // ȡ�����¼�
        ScriptResources::clearEvent(getEventId());
    }
}
