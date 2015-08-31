#ifndef SLNODEH
#define SLNODEH

template<class T>
struct SLNode
{

    T data;//数据域
    SLNode<T>* next;//指针域
    //构造1
    SLNode(SLNode* nextNode=NULL)//默认指针域是空
    {
        next=nextNode;
    }
    //构造2
    SLNode(const T& item,SLNode* nextNode=NULL)
    {
        data=item;
        next=nextNode;
    }
};

#endif
