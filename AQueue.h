#ifndef AQUEUEH
#define AQUEUEH

#include<iostream>

//顺序队列类
template<class T>
class AQueue
{
private:
    int front;//队首下标
    int rear;//队尾下标
    int count;//元素个数
    T* QArray;//存放队列元素之数组
    int size;//数组规模
public:
    AQueue(int MaxQueueSize=10)
    {
        size=MaxQueueSize;
        QArray=new T[MaxQueueSize];
        front=0;
        rear=0;
        count=0;
    }//构造

    ~AQueue()
    {
        delete[] QArray;
    }

    bool QInsert(const T& item)
    {
        if(IsFull())
        {
            cout<<"队列满!"<<endl;
            return false;
        }
        QArray[rear]=item;
        rear=(rear+1)%size;//调整尾针
        count++;
        return true;
    }//队尾插入item

    bool QDelete(T& item)
    {
        if(IsEmpty())
        {
            cout<<"空队列!"<<endl;
            return false;
        }
        item=QArray[front];
        front=(front+1)%size;//front顺时针移动一格
        count--;
        return true;
    }//删除队首，存入item

    void QClear()
    {
        front=rear=count=0;   //清空
    }

    bool QFront(T& item)const
    {
        if(IsEmpty())
        {
            cout<<"空队列!"<<endl;
            return false;
        }
        item=QArray[front];
        return true;
    }//存取队首

    bool IsEmpty()const
    {
        return count==0;   //检测是否空
    }

    bool IsFull()const
    {
        return count==size;   //检测是否满
    }

    int GetSize()
    {
        return count;
    }
};

#endif
