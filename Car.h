/**************************************************************************/
#ifndef CARH
#define CARH
/********************************/
#include<iostream>
#include"SLList.h"
/********************************/
extern SLList<int> CarNumberList;
/********************************/
//汽车类
class Car
{
private:
    int mNum;//车号
public:
    //构造函数 Param 车号
    Car(int num)
    {
        mNum = num;
        //车号加入车号表中
        CarNumberList.InsertFromTail(num);
    }
    //析构函数
    ~Car()
    {
        int i = CarNumberList.Search(mNum);
        //将车号从车号表中删除
        CarNumberList.DeleteK(i,i);
    }
    //得到车号
    int GetCarNumber()
    {
        return mNum;
    }
};
/****/
#endif
/**************************************************************************/
