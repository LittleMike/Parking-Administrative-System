/**************************************************************************/
#ifndef TIMEH
#define TIMEH
/********************/
#include"MyHeaders.h"
/********************/
//时间类
class Time
{
private:
    int mDay;

    int mHour;

    int mMin;
public:
    //构造函数
    Time()
    {
        mDay=mHour=mMin=0;
    }
    //运行时间
    void GoTime()
    {
        mMin++;
        if(mMin >= MINTOHOUR)
        {
            mMin = 0;
            mHour++;
            if(mHour >= HOURTODAY)
            {
                mHour = 0;
                mDay++;
            }
        }
    }
    int GetMin()
    {
        //时间转化
        if(mMin>=MINTOHOUR)
        {
            mHour = mHour + mMin/MINTOHOUR;
            mMin = mMin%MINTOHOUR;
        }
        return mMin;
    }
    int GetHour()
    {
        return mHour;
    }
    int GetDay()
    {
        return mDay;
    }
    //设置时间
    void SetTime(int d,int h,int m)
    {
        mDay = d;
        mHour = h;
        mMin = m;
    }
    //显示时间
    void Display()
    {
        cout<<mDay<<':'<<mHour<<':'<<mMin<<endl;
    }
};
/****/
#endif
/**************************************************************************/
