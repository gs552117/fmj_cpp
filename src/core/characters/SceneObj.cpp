#include "SceneObj.h"
#include "SaveLoadStream.h"


SceneObj::SceneObj()
{
    bInstanceOf_SceneObj = true;
}

void SceneObj::setData(char* buf, int offset)
{
    mType = (int)buf[offset] & 0xFF;
    mIndex = (int)buf[offset + 1] & 0xFF;
    // ����״̬
    setCharacterState((int)buf[offset + 4] & 0xFF);
    // ����
    setName(getString(buf, offset + 9));
    // ��ʱ
    mDelay = (int)buf[offset + 0x15] & 0xFF;
    // ����ͼ
    setWalkingSprite(new WalkingSprite(4, (int)buf[offset + 0x16] & 0xFF));
    // ����
    setDirection(North);
    // �Ų�
    setStep((int)buf[offset + 3] & 0xFF);
}

void SceneObj::write(SaveLoadStream *buff)
{
    buff->writeInt(mType);
    buff->writeInt(mIndex);
    buff->writeInt(getCharacterState());
    buff->writeString(getName());
    buff->writeInt(mDelay);
    buff->writeInt(getWalkingSpriteId());
    buff->writeInt(getDirection());
    buff->writeInt(getStep());
    buff->writeInt(getPosInMap().x);
    buff->writeInt(getPosInMap().y);
}

void SceneObj::read(SaveLoadStream *buff)
{
    mType = buff->readInt();
    mIndex = buff->readInt();
    setCharacterState(buff->readInt());
    setName(buff->readString());
    mDelay = buff->readInt();
    setWalkingSprite(new WalkingSprite(4, buff->readInt()));
    setDirection((Direction)buff->readInt());
    setStep(buff->readInt());
    int x = buff->readInt();
    int y = buff->readInt();
    setPosInMap(x, y);
}
void SceneObj::walk()
{

}

void SceneObj::walk(Direction d)
{

}

void SceneObj::walkStay(Direction d)
{

}
