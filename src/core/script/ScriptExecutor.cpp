#include "ScriptExecutor.h"

ScriptExecutor::ScriptExecutor(std::vector<Operate *> &list, std::vector<int> &eventIndex, std::hash_map<int, int> &map, int headerCnt)
{
    mOperateList = list;
    mEventIndex = eventIndex;
    mCurExeOperateIndex = 0;
    mIsExeUpdateDraw = false;
    mMapAddrOffsetIndex = map;
    mHeaderCnt = headerCnt;
}

ScriptExecutor::~ScriptExecutor()
{
    for (unsigned int i = 0; i < mOperateList.size(); i++)
    {
        if (NULL != mOperateList[i])
        {
            delete mOperateList[i];
        }
    }
}

bool ScriptExecutor::triggerEvent(int eventId)
{
    if (eventId > (int)(mEventIndex.size()))
    {
        return false;
    }

    int index = mEventIndex[eventId - 1];
    if (index != -1)
    {
        mCurExeOperateIndex = index;
        mIsExeUpdateDraw = false;
        return true;
    }
    return false;
}

void ScriptExecutor::gotoAddress(int address)
{
    std::hash_map <int, int> ::const_iterator iter = mMapAddrOffsetIndex.find(address - mHeaderCnt);
    mCurExeOperateIndex = iter->second;;

    if (mIsExeUpdateDraw)   // ����Operate.process()�е��õ�gotoAddress
    {
        mIsExeUpdateDraw = false;
        --mCurExeOperateIndex;
    }
    else     // ��Operate.process()�е��õ�gotoAddress
    {
        goonExecute = false; // mark �´ε���process��ִ��
    }
}

void ScriptExecutor::process()
{
    if (!mIsExeUpdateDraw)
    {
        for (; mCurExeOperateIndex < (int)(mOperateList.size()) && goonExecute;)
        {
            Operate *oper = mOperateList.at(mCurExeOperateIndex);
            if (oper != NULL && oper->process())   // ִ�� update draw
            {
                mIsExeUpdateDraw = true;
                return;
            }
            if (!goonExecute)
            {
                goonExecute = true;
                return;
            }
            ++mCurExeOperateIndex;
        }
        // �����������ִ�е�����ű����һ����callback
    }
}

void ScriptExecutor::update(long delta)
{
    if (mIsExeUpdateDraw)
    {
        if (!mOperateList.at(mCurExeOperateIndex)->update(delta))   // �˳���ǰ����
        {
            mIsExeUpdateDraw = false;
            ++mCurExeOperateIndex;
        }
    }
}

void ScriptExecutor::draw(Canvas *canvas)
{
    if (mIsExeUpdateDraw)
    {
        mOperateList.at(mCurExeOperateIndex)->draw(canvas);
    }
}

void ScriptExecutor::keyDown(int key)
{
    if (mIsExeUpdateDraw)
    {
        mOperateList.at(mCurExeOperateIndex)->onKeyDown(key);
    }
}

void ScriptExecutor::keyUp(int key)
{
    if (mIsExeUpdateDraw)
    {
        mOperateList.at(mCurExeOperateIndex)->onKeyUp(key);
    }
}

bool ScriptExecutor::goonExecute = true;
