/**************************************************************************/
#ifndef OTHERH
#define OTHERH
/******************************/
#include<stdlib.h>
#include<time.h>//for time(NULL)
#include"ParkCenter.h"
#include"LinearList.h"
#include"MyHeaders.h"
#include<iostream>
#include"SLList.h"
/***************************************/
//定义一个空闲车位表
LinearList<int> idleList(CARPLACENUMBER);
//定义一个车号表
SLList<int> CarNumberList;
//时间控制
Time mytime;
/***************************************/
//产生从0到n之间的随机整数(包括0和n)
int randint(int n)
{
    static bool flag = false;
    if(flag==false)
    {
        srand(time(NULL));
        flag = true;
    }
    return (int)(rand()/(float)RAND_MAX*n);
}

//车号生成
int CarID()
{
    int id = randint(5000);
    if(!CarNumberList.IsEmpty())
    {
        while(CarNumberList.Search(id) != -1)
        {
            id = randint(5000);
        }
    }
    return id;
}

//时间管理(管理所有计时单元)
void TimeManager(Time& time,ParkCenter& pc)
{
    //为已存车的车位计时，汽车可能离开
    for(int i = 1; i<=CARPLACENUMBER; i++)
    {
        if(!((pc.GetCarPlace(i))->IsTheCarPlaceIdle()))
        {
            (pc.GetCarPlace(i))->CarLeave();
            ((pc.GetCarPlace(i))->CarPlaceTime())->GoTime();
        }
    }
    //统计每天的数据
    pc.Total();
    //时间运行
    time.GoTime();
    //有汽车离开后，在这一时刻，还要安排汽车入位吗？
    //pc.CarGoIntoIdlePlace();
}
//显示一些状态(调试用)
void DisplayState(Time& time,ParkCenter& pc,int num)
{
    time.Display();
    cout<<"来了"<<num<<"辆车"<<endl;
    //显示车位的空闲状态
    for(int i = 1; i<=CARPLACENUMBER; i++)
    {
        cout<<pc.GetCarPlace(i)->IsTheCarPlaceIdle()<<' ';
        if(i%5 == 0) cout<<endl;
    }
    cout<<"便道车辆数:"<<pc.GetPassRoad()->GetSize()<<endl;
}
/****/
#endif
/**************************************************************************/
