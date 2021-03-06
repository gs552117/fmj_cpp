#ifndef _RESBASE_H_
#define _RESBASE_H_

#include <iostream>
#include "Global.h"

/**
 * 每次new一个对象后，必须调用{@link ResBase#setData(byte[], int)}方法
 * 
 * @author Chen
 * 
 */
class ResBase 
{
protected:
    int mType;
	int mIndex;

public:
    virtual ~ResBase(){}
    /**
    * 每次new一个对象后，必须调用该方法填充各个字段
    *
    * @param buf
    *            资源的数据缓冲区
    * @param offset
    *            该资源在数组{@code buf}中的偏移位置，{@code buf[offset]} 为该资源的首字节
    */
    virtual void setData(char *buf, int offset) = 0;
	
    int getType() 
    {
		return mType;
	}
	
	int getIndex() 
    {
		return mIndex;
	}

	/**
	 * 获得GBK编码的字符串
	 * 
	 * @param buf
	 * @param start
	 *            字符串的第一个字节
	 * @return
	 */
    static std::string getString(char *buf, int start);
    static std::string getString(const char *buf, int start);

	/**
	 * 两字节无符号整型
	 * @param buf
	 * @param start
	 * @return
	 */
    int get2BytesInt(char *buf, int start);
	
	/**
	 * 两字节有符号整型
	 * @param buf
	 * @param start
	 * @return
	 */
    int get2BytesSInt(char *buf, int start);
	
    int get1ByteSInt(char *buf, int start);
};

#endif