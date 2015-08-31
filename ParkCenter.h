/**************************************************************************/
#ifndef PARKCENTERH
#define PARKCENTERH
/*******************************/
#include"CarPlace.h"
#include"AQueue.h"
#include"MyHeaders.h"
#include"Linearlist.h"
/*******************************/
extern LinearList<int> idleList;
extern Time mytime;
/*******************************/
//停车场类
class ParkCenter
{
private:
    CarPlace* mCarPlace;//车位
    AQueue<Car*>* PassRoad;//便道
    int mArriveCarNumPDay;//每天到达的车次
    int mLeaveCarNumPDay;//每天离开的车次
    Time mTotalHour;//停车总时数
    int mProfit;//收入
public:
    //构造函数 param:车位数量，便道停车数
    ParkCenter(int CarPlaceNum,int PassRoadCarNum)
    {
        mCarPlace = new CarPlace[CARPLACENUMBER];
        //为车位编号
        for(int i=1; i<=CarPlaceNum; i++)
        {
            mCarPlace[i-1].SetCarPlaceId(i);
            idleList.InsertLast(i);
        }
        PassRoad = new AQueue<Car*>(PASSROADCARNUMBER);
        mArriveCarNumPDay = 0;
        mLeaveCarNumPDay = 0;
        mProfit = 0;
        mTotalHour.SetTime(0,0,0);
    }
    //析构函数
    ~ParkCenter()
    {
        delete[] mCarPlace;
        delete PassRoad;
    }
    //汽车来到便道等候
    void WaitInPassRoad(Car* car)
    {
        PassRoad->QInsert(car);
    }
    //便道是否已满
    bool IsPassRoadFull()
    {
        return PassRoad->IsFull();
    }
    //便道是否空
    bool IsPassRoadEmpty()
    {
        return PassRoad->IsEmpty();
    }
    //有一辆汽车来到停车场
    void ACarCome(Car* car)
    {
        if(!IsPassRoadFull())
            //在便道等候
            WaitInPassRoad(car);
        else
        {
            //输出：时间  xx车到达  车位已满
            cout<<mytime.GetHour()<<':'<<mytime.GetMin()<<"  "
                <<car->GetCarNumber()<<"车到达"<<"  "
                <<"车位已满"<<endl;
            delete car;
        }
    }
    //是否有空闲车位
    bool HaveIdleCarPlace()
    {
        return !idleList.IsEmpty();
    }
    //得到空闲车位编号(需要找到最小编号)
    int GetIdleCarPlaceNum()
    {
        int item = MAX;
        int tmp,k = -1;
        //查询
        for(int i=1; i<=idleList.Length(); i++)
        {
            idleList.Find(i,tmp);
            if(tmp<item)
            {
                item = tmp;
                k = i;
            }
        }
        idleList.Delete(k);
        return item;
    }
    //汽车开进空闲车位
    void CarGoIntoIdlePlace()
    {
        while(HaveIdleCarPlace())
        {
            if(!IsPassRoadEmpty())
            {
                int i = GetIdleCarPlaceNum();
                Car* ACar = NULL;
                PassRoad->QDelete(ACar);
                mCarPlace[i-1].SetACar(ACar);
            }
            else break;
        }
    }
    //得到车位
    CarPlace* GetCarPlace(int i)
    {
        return &mCarPlace[i-1];
    }
    //得到便道
    AQueue<Car*>* GetPassRoad()
    {
        return PassRoad;
    }
    //统计
    void Total()
    {
        static int day = 1;
        if(mytime.GetDay() == day)
        {
            for(int i=0; i<CARPLACENUMBER; i++)
            {
                mArriveCarNumPDay = mArriveCarNumPDay +
                                    mCarPlace[i].GetCarArriveNum();
                mLeaveCarNumPDay = mLeaveCarNumPDay +
                                   mCarPlace[i].GetCarLeaveNum();
                mProfit = mProfit + mCarPlace[i].GetTotalProfit();
                mTotalHour.SetTime(
                    mTotalHour.GetDay()+
                    mCarPlace[i].GetTotalTime().GetDay(),
                    mTotalHour.GetHour()+
                    mCarPlace[i].GetTotalTime().GetHour(),
                    mTotalHour.GetMin()+
                    mCarPlace[i].GetTotalTime().GetMin()
                );
                mCarPlace[i].Reset();
            }
            //输出
            cout<<"全天到达车次:"<<GetArriveCarNumPDay()<<endl;
            cout<<"全天离开车次:"<<mLeaveCarNumPDay<<endl;
            cout<<"停车总时数:"<<mTotalHour.GetHour()<<
                ':'<<mTotalHour.GetMin()<<endl;
            cout<<"全天收入:"<<mProfit<<"元"<<endl;
            system("PAUSE");//暂停
            //清空
            mArriveCarNumPDay = 0;
            mLeaveCarNumPDay = 0;
            mProfit = 0;
            mTotalHour.SetTime(0,0,0);
            day++;
        }
    }
    //得到每天到达车次
    int GetArriveCarNumPDay()
    {
        return mArriveCarNumPDay;
    }
};
/****/
#endif
/**************************************************************************/
