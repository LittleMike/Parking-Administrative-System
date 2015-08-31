/**************************************************************************/
#include<windows.h>//Sleep()
#include<iostream>
using namespace std;
#include"ParkCenter.h"
#include"Time.h"
#include"other.h"
/****************************************************/
/*说明：我对车辆进出的安排是：某时刻某些汽车离开车
位，下一时刻便道中的车入位，这样为了方便观察出车情况*/
/*说明:在便道上等候的汽车没有显示信息*/
/*计时由车位负责，车离开的概率由随机数设计*/
/****************************************************/
//主函数
int main()
{
    //停车场
    ParkCenter myparkcenter(CARPLACENUMBER,PASSROADCARNUMBER);
    //存放随机生成的汽车数目
    int carNumber = -1;

    while(true)
    {

        mytime.Display();
        //安排汽车入位
        myparkcenter.CarGoIntoIdlePlace();

        carNumber = 0;
        //汽车产生的随机性
        if(randint(3) == 1)
        {
            //随机产生汽车的数量
            carNumber = randint(CARNUMBERPH);

            if(carNumber!=0)
            {

                for(int i=0; i<carNumber; i++)
                {

                    Car* ACar = new Car(CarID());
                    //汽车开往停车场
                    myparkcenter.ACarCome(ACar);
                    //停车场安排汽车进入车位
                    myparkcenter.CarGoIntoIdlePlace();

                }
                //若便道上还有汽车,需要安排入位
            }
            else myparkcenter.CarGoIntoIdlePlace();
            //若便道上还有汽车,需要安排入位
        }
        else myparkcenter.CarGoIntoIdlePlace();

        //时间管理(管理所有计时单元)
        TimeManager(mytime,myparkcenter);
        //显示状态(调试需要显示的信息)
        //DisplayState(mytime,myparkcenter,carNumber);

        //system("PAUSE");//暂停

        Sleep(1000);//睡眠1秒

    }

    return 0;

}
/**************************************************************************/
