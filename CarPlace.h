/**************************************************************************/
#ifndef CARPLACEH
#define CARPLACEH
/******************************/
#include"Car.h"
#include"LinearList.h"
#include"Time.h"
#include"MyHeaders.h"
/******************************/
extern LinearList<int> idleList;
extern Time mytime;
int randint(int n);
/******************************/
//车位类
class CarPlace
{
private:
    bool mIdle;//空闲状态
    int mNumber;//车位编号
    int mProfit;//费用
    int mArriveNum;//到达车辆计数
    int mLeaveNum;//离开车辆计数
    int totalProfit;//累计费用每天
    Time mTime;//停车时计时
    Time totalTime;//累计时间每天
    Time mArriveTime;//汽车到达时间
    Time mLeaveTime;//汽车离去时间
    Car* mCar;//停放的车
public:
    //构造函数
    CarPlace()
    {
        mIdle = true;
        mCar = NULL;
        mArriveNum = 0;
        mLeaveNum = 0;
        totalTime.SetTime(0,0,0);
        totalProfit = 0;
    }
    //析构函数
    //~CarPlace();
    //是否空闲
    bool IsTheCarPlaceIdle()
    {
        return mIdle;
    }
    //停放一辆车
    void SetACar(Car* car)
    {
        mCar = car;
        SetIdle(false);
        mTime.SetTime(0,0,0);
        mArriveTime = mytime;
        mArriveNum++;//计数

        //输出：到达时间  xx车  车位编号
        int min = GetCarArriveTime().GetMin();
        int hour = GetCarArriveTime().GetHour();
        cout<<"时间"<<hour<<':'<<min<<"  "
            <<car->GetCarNumber()<<"号车到达"<<"  "
            <<GetCarPlaceNumber()<<"车位"<<endl;
    }
    //汽车离开
    void Leave()
    {
        mLeaveTime = mytime;
        //计费
        if(mTime.GetMin() == 0)
            mProfit = PROFITPH*mTime.GetHour();
        else mProfit = PROFITPH*(mTime.GetHour()+1);
        //输出：时间  xx车离开  停放时间  费用
        cout<<"时间"<<mLeaveTime.GetHour()<<':'
            <<mLeaveTime.GetMin()<<"  "<<mCar->GetCarNumber()
            <<"号车离开"<<"  "<<"停放时间"<<mTime.GetHour()
            <<':'<<mTime.GetMin()<<"  "<<"费用:"<<mProfit
            <<"元"<<endl;
        //累计
        mLeaveNum++;
        totalTime.SetTime(totalTime.GetDay()+mTime.GetDay(),
                          totalTime.GetHour()+mTime.GetHour(),
                          totalTime.GetMin()+mTime.GetMin());
        totalProfit = totalProfit + mProfit;

        delete mCar;
        mCar = NULL;
        mIdle = true;
        //加入到空闲表中
        idleList.InsertLast(mNumber);
    }
    //汽车离开按概率
    void CarLeave()
    {
        //一小时后离开概率为25%
        if(mTime.GetHour() == 1)
            if(randint(4) == 1) Leave();
        //二小时后离开概率为50%
        if(mTime.GetHour() == 2)
            if(randint(2) == 1) Leave();
        //三小时后离开概率为75%
        if(mTime.GetHour() == 3)
            if(randint(4) != 1) Leave();
        //四小时后肯定离开
        if(mTime.GetHour() == 4) Leave();
    }
    //得到计时器
    Time* CarPlaceTime()
    {
        return &mTime;
    }
    //设置空闲状态(true闲false忙)
    void SetIdle(bool i)
    {
        mIdle = i;
    }
    //得到汽车到达时间
    Time GetCarArriveTime()
    {
        return mArriveTime;
    }
    int GetCarPlaceNumber()
    {
        return mNumber;
    }
    void SetCarPlaceId(int id)
    {
        mNumber = id;
    }
    //得到汽车到达数量
    int GetCarArriveNum()
    {
        return mArriveNum;
    }
    int GetCarLeaveNum()
    {
        return mLeaveNum;
    }
    Time GetTotalTime()
    {
        return totalTime;
    }
    int GetTotalProfit()
    {
        return totalProfit;
    }
    //重置各统计量
    void Reset()
    {
        mArriveNum = 0;
        mLeaveNum = 0;
        totalTime.SetTime(0,0,0);
        totalProfit = 0;
    }
};
/****/
#endif
/**************************************************************************/
