#include "ActionMagicHelpOne.h"
#include "Player.h"
#include "FightingCharacter.h"
#include "RaiseAnimation.h"

ActionMagicHelpOne::ActionMagicHelpOne(FightingCharacter *attacker, FightingCharacter *target, BaseMagic *magic)
    :ActionSingleTarget(attacker, target), mState(STATE_PRE)
{
        this->magic = magic;
}

ActionMagicHelpOne::~ActionMagicHelpOne()
{

}

void ActionMagicHelpOne::preproccess()
{
    // TODO �����˺�ֵ���쳣״̬
    mAni = magic->getMagicAni();
    mAni->startAni();
    mAni->setIteratorNum(2);
    mAnix = mTarget->getCombatX();
    mAniy = mTarget->getCombatY();
    mRaiseAni = new RaiseAnimation(mTarget->getCombatX(), mTarget->getCombatTop(), magic->getAffectHp(), 0);

    magic->use(mAttacker, mTarget);
}

bool ActionMagicHelpOne::update(long delta)
{
    // TODO Auto-generated method stub
    ActionSingleTarget::update(delta);
    switch (mState)
    {
    case STATE_PRE:
        if (mCurrentFrame < 10)
        {
            if (mAttacker->bInstanceof_Player)
            {
                mAttacker->getFightingSprite()->setCurrentFrame(
                    mCurrentFrame * 3 / 10 + 6);
            }
            else
            {
                mAttacker->setCombatPos(ox + 2, oy + 2);
            }
        }
        else
        {
            mState = STATE_ANI;
        }
        break;

    case STATE_ANI:
        if (!mAni->update(delta))
        {
            // ħ���������
            mState = STATE_AFT;
            if (mAttacker->bInstanceof_Player)
            {
                static_cast<Player*>(mAttacker)->setFrameByState();
            }
            else
            {
                mAttacker->getFightingSprite()->move(-2, -2);
            }
        }
        break;

    case STATE_AFT:
        return mRaiseAni->update(delta);
        //          break;
    }
    return TRUE;
}

void ActionMagicHelpOne::draw(Canvas *canvas)
{
    if (mState == STATE_ANI)
    {
        mAni->drawAbsolutely(canvas, mAnix, mAniy);
    }
    else if (mState == STATE_AFT)
    {
        mRaiseAni->draw(canvas);
    }
}
