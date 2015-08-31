#ifndef SLLISTH
#define SLLISTH

#include<iostream>
#include"SLNode.h"

//单链表类
template<typename T>
class SLList
{
private:
    SLNode<T>* head;
    SLNode<T>* tail;//尾指针
    SLNode<T>* currptr;//当前指针
    int size;//链表长度

public:
    SLList()
    {
        head=tail=currptr=new SLNode<T>();
        size=0;
    }

    SLList(T& item);

    ~SLList();

    bool IsEmpty()const
    {
        return head->next==NULL;
    }

    int length()const
    {
        return size;
    }

    bool Find(int k,T& item)const;//存取第k个节点的值
    bool FindCurr(T&)const;//存取当前结点的值

    int Search(const T&)const;//查找,返回其在表中位置
    //删除链表中第k个结点并将其字段值赋给item
    bool DeleteK(int k,T& item)
    {
        SLNode<T>* p=head->next;
        SLNode<T>* q=head;
        if(k<1||k>size)
        {
            return false;
        }
        for(int i=1; i<k; i++)
        {
            q=q->next;
            p=p->next;
        }
        q->next=p->next;
        if(q->next==NULL)
        {
            tail=q;
        }
        item=p->data;
        delete p;
        size--;
        return true;
    }
    bool Delete(T&);		//删除当前结点的后继并将其data值赋给de_item
    bool DeleteFromHead(T&);//删除表头结点并将其data值赋给de_item
    bool DeleteFromTail(T&);//删除表尾结点并将其data值赋给de_item
    //在链表中第k个结点后插入字段值为item的结点
    void InsertK(int k,const T& item)
    {
        if(k<1||k>size) return;
        SLNode<T>* p=new SLNode<T>(item,NULL);
        SLNode<T>* q=head->next;
        for(int i=1; i<k; i++) //q指向第k个结点
        {
            q=q->next;
        }
        currptr=q->next;//currptr指向原第k+1个结点
        if(currptr!=NULL)
        {
            (p->next)=currptr;
            (q->next)=p;
        }
        else
        {
            (q->next)=p;
        }
        size++;
    }
    void Insert(const T&);//在当前结点后插入data域值为item的结点
    void InsertFromTail(const T&);//表尾插入
    void InsertFromHead(const T&);//表头插入
};

//implement
template<typename T>
SLList<T>::SLList(T& item)
{
    tail=currptr=new SLNode<T>(item);
    head=new SLNode<T>(currptr);//创建哨位
    size=1;
}

template<class T>
SLList<T>::~SLList()
{
    while(!IsEmpty())
    {
        currptr=head->next;
        head->next=currptr->next;
        delete currptr;
    }
    delete head;
}

template<class T>
bool SLList<T>::Delete(T& de_item)
{
    if(currptr==tail||IsEmpty())
    {
        cout<<"No next node or empty list!";
        return false;
    }
    SLNode<T>* temp=currptr->next;
    currptr->next=temp->next;
    size--;
    de_item=temp->data;
    if(temp==tail)
    {
        tail=currptr;
    }
    delete temp;
    return true;
}

template<class T>
bool SLList<T>::DeleteFromHead(T& de_item)
{
    if(IsEmpty())
    {
        cout<<"Empty list!";
        return false;
    }
    SLNode<T>* temp=head->next;
    head->next=temp->next;
    size--;
    de_item=temp->data;
    if(temp==tail)
    {
        tail=head;
    }
    delete temp;
    return true;
}

template<class T>
bool SLList<T>::DeleteFromTail(T& de_item)
{
    if(IsEmpty())
    {
        cout<<"Empty list!";
        return false;
    }

    SLNode<T>* temp=head;
    while(temp->next!=tail)
    {
        temp=temp->next;
    }

    de_item=tail->data;
    temp->next=NULL;
    size--;
    delete tail;
    tail=currptr;
    return true;
}

template<class T>
void SLList<T>::Insert(const T& item)
{
    currptr->next=new SLNode<T>(item,currptr->next);
    if(tail==currptr)
    {
        tail=currptr->next;
    }
    size++;
}

template<class T>
void SLList<T>::InsertFromTail(const T& item)
{
    tail->next=new SLNode<T>(item,NULL);
    tail=tail->next;
    size++;
}

template<class T>
void SLList<T>::InsertFromHead(const T& item)
{
    if(IsEmpty())
    {
        head->next=new SLNode<T>(item,head->next);
        tail=head->next;
    }
    else
        head->next=new SLNode<T>(item,head->next);
    size++;
}

template<class T>
int SLList<T>::Search(const T& item)const
{
    SLNode<T>* p=head->next;
    int i=1;
    while(p!=NULL && p->data!=item)
    {
        p=p->next;
        i++;
    }
    if(p!=NULL) return i;
    //cout<<"无此结点!"<<endl;
    return -1;
}

template<class T>
bool SLList<T>::Find(int k,T& item)const
{
    SLNode<T>* p=head->next;
    if(k<1||k>size)
    {
        return false;
    }
    for(int i=1; i<k; i++)
    {
        p=p->next;
    }
    item=p->data;
    return true;
}

template<class T>
bool SLList<T>::FindCurr(T& item)const
{
    if(IsEmpty())
    {
        cout<<"empty!"<<endl;
        return false;
    }
    if(currptr==NULL)
    {
        cout<<"Error!"<<endl;
        return false;
    }
    if(currptr==head)
    {
        cout<<"当前指针指在哨位!"<<endl;
        return false;
    }
    item=currptr->data;
    return true;
}//存取当前结点的值

#endif
