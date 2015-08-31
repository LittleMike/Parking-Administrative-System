#ifndef LINEARLISTH
#define LINEARLISTH

//头文件
/************************/
#include<iostream>
/************************/

//顺序表类
template<typename T>
class LinearList
{
public:
    /********************************************/
    //构造函数
    LinearList(int MaxListSize=50) //默认规模:50
    {
        MaxSize = MaxListSize;
        element = new T[MaxSize];
        length  = 0;
    }
    //析构函数
    ~LinearList()
    {
        delete[] element;
    }
    /********************************************/
    //判断表是否空
    bool IsEmpty()const
    {
        return length==0;
    }
    //判断表是否满
    bool IsFull()const
    {
        return length==MaxSize;
    }
    //返回表的长度
    int Length()const
    {
        return length;
    }
    //清空表
    void Clear()
    {
        length=0;
    }
    /********************************************/
    //~存取:将第k个结点的字段值赋给item
    bool Find(int k,T& item)const
    {
        if(IsEmpty())
        {
            cout<<"<LinearList.Find()>Empty LinearList."<<endl;
            return false;
        }
        if(k<1)
        {
            cout<<"错误.<LinearList.Find()>参数k下溢."<<endl;
            return false;
        }
        if(k>Length())
        {
            cout<<"错误.<LinearList.Find()>参数k上溢."<<endl;
            return false;
        }

        item = element[k-1];
        return true;
    }

    //~插入:在第k个结点后插入字段值为item的结点
    bool Insert(int k,const T& item)
    {
        if(IsFull())
        {
            cout<<"<LinearList.Insert()>Full LinearList."<<endl;
            return false;
        }
        if(k<1)
        {
            cout<<"错误.<LinearList.Insert()>参数k下溢."<<endl;
            return false;
        }
        if(k>length)
        {
            cout<<"错误.<LinearList.Insert()>参数k上溢."<<endl;
            return false;
        }
        for(int i=length-1; i>=k; i--)
        {
            element[i+1]=element[i];//移动元素
        }
        element[k]=item;
        length++;
        return true;
    }

    //~查找:在表中查找字段值为item的结点,并返回其序号
    int Search(const T& item)const
    {
        for(int i=0; i<Length(); i++)
        {
            if(element[i]==item)
                return(i+1);
        }
        return -1;//返回-1表示无这样的结点
    }
    /********************************************/
    //~删除:删除第k个结点并将其字段值赋给item
    void DeleteToItem(int k,T& item)
    {
        if(Find(k,item))
        {
            for(int i=k; i<Length(); i++)
            {
                element[i-1]=element[i];//移动元素
            }
            length--;
        }
    }

    //~删除:删除第k个结点
    void Delete(int k)
    {
        T temp;
        if(Find(k,temp))
        {
            for(int i=k; i<Length(); i++)
            {
                element[i-1]=element[i];//移动元素
            }
            length--;
        }
    }

    //~表头插入
    void InsertFirst(const T& item)
    {
        if(IsFull())
        {
            cout<<"<LinearList.InsertFirst>Full LinearList."<<endl;
            return;
        }
        else
        {
            for(int i=length-1; i>=0; i--)
            {
                element[i+1]=element[i];//移动元素
            }
            element[0]=item;
            length++;
        }
    }

    //~表尾插入
    void InsertLast(const T& item)
    {
        if(IsFull())
        {
            cout<<"<LinearList.InsertLast>Full LinearList."<<endl;
        }
        else
        {
            element[length]=item;
            length++;
        }
    }

    //~显示顺序表元素值
    void Display()
    {
        if(IsEmpty())
        {
            cout<<"<LinearList.Display>Empty LinearList."<<endl;
            return;
        }
        for(int i=0; i<length; i++)
        {
            cout<<' '<<element[i];
        }
        cout<<endl;
    }
    /********************************************/
private:
    int MaxSize;//最大长度
    int length;//实际长度
    T* element;//指向存储顺序表的数组
};

#endif
