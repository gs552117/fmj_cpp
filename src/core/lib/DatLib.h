#ifndef _DATLIB_H_
#define _DATLIB_H_


#include <iostream>
#include <hash_map>  
#include <fstream>
#include "Global.h"
#include "ResGut.h"
#include "ResBase.h"
#include "ResImage.h"
#include "ResSrs.h"
#include "ResMap.h"

class BaseGoods;

class DatLib
{
public:
    enum RESEnum
    {
        RES_GUT = 1, // 剧情脚本
        RES_MAP = 2, // 地图资源
        RES_ARS = 3, // 角色资源
        RES_MRS = 4, // 魔法资源
        RES_SRS = 5, // 特效资源
        RES_GRS = 6, // 道具资源
        RES_TIL = 7, // tile资源
        RES_ACP = 8, // 角色图片
        RES_GDP = 9, // 道具图片
        RES_GGJ = 10, // 特效图片
        RES_PIC = 11, // 杂类图片
        RES_MLR = 12, // 链资源
    };

public:
    DatLib();
    ~DatLib();
    static DatLib *getInstance();
    static void InitDatLib();

private:
	/**
	 * 保存资源数据相对文件首字节的偏移量
	 */
    std::hash_map<int, int> mDataOffset;
    typedef std::pair<int, int> Int_Pair;

    void getAllResOffset();

    /**
    * DAT.LIB文件的所有内容
    */
    char *mBuffer;
    long mBufferSize;

    static DatLib *Instance;

public:

	//静态获取资源的工厂
    static ResBase *GetRes(int resType, int type, int index);

	/**
	 * 
	 * @param resType
	 *            资源文件类型号1-12
	 * @param type
	 *            资源类型
	 * @param index
	 *            资源索引号
	 * @return 资源对象，不存在则返回<code>NULL</code>
	 */
    ResBase *getRes(int resType, int type, int index);

    BaseGoods *getGoods(int type, int index);

    ResBase *getMagic(int type, int index);
	
	/**
	 * 
	 * @param resType
	 *            资源文件类型号1-12
	 * @param type
	 *            资源类型
	 * @param index
	 *            资源索引号
	 * @return 资源所在位置, 返回-1表示不存在
	 */
    int getDataOffset(int resType, int type, int index);

	/**
	 * 
	 * @param resType
	 *            资源文件类型号1-12
	 * @param type
	 *            资源类型
	 * @param index
	 *            资源索引号
	 * @return 每个资源唯一的编号，用于哈希表键
	 */
    int getKey(int resType, int type, int index);
};


#endif _DATLIB_H_