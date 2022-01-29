//#include<iostream.h>//cout,cin
#include"process.h"//exit()
#include"stdio.h"//EOF,NULL

template<class T>
struct Node
{
	T data;
	Node<T> *next;//此处T可以省略
};

template<class T>
class LinkQueue
{
	private:
		Node<T> *front;//队头指针
		Node<T> *rear;//队尾指针
	public:
		LinkQueue();//构造空队列
		~LinkQueue();// 析构函数，释放链队各结点的存储空间
		void EnQueue(T x);// 元素x入队
		T DeQueue();// 队顶元素出队
		T GetHead();// 取队头元素
		T GetLast();//取队尾元素
		int QueueEmpty(); // 判断队是否为空
		void ClearQueue();//
		void QueueTranverse();//
};

template<class T>
LinkQueue<T>::LinkQueue()
{
	front=new Node<T>;//创建队头结点
	front->next=NULL;
	rear=front;//空队
}

template<class T>
LinkQueue<T>::~LinkQueue()
{
	Node<T> *p;
	while(front!=NULL)//从队头开始逐个删除队列中的结点
	{
		p=front;//暂存被释放结点
		front=front->next;//头指针后移指向下一个被释放结点
		delete p;
	}
}

template<class T>
void LinkQueue<T>::EnQueue(T x)
{
	Node<T> *s;
	s=new Node<T>; s->data=x; //申请一数据域为x的结点s
	s->next=rear->next;
	rear->next=s; //新结点插在链队尾
	rear=s; //修改尾指针
	if(front->next==NULL)//如果创建的是首元结点，front->next指向它
		front->next=s;
}

template<class T>
T LinkQueue<T>::DeQueue()
{
	T x;
    Node<T> *p;
	if(rear==front) throw"下溢";//队空，则下溢
	p=front->next;
	x=p->data;//暂存队头元素
	front->next=p->next;//将队头结点从链表中摘除
	if(p->next==NULL) rear=front;//如果出队后为空队，修改队尾指针
	delete p;
	return x;
}


template <class T>
T LinkQueue<T>::GetHead()
{
	Node<T> *p;
	if(front==rear) throw "队空，无队头元素";//
	p=front->next;
	return p->data;
}

template <class T>
T LinkQueue<T>::GetLast()
{
	if(front==rear) throw "队空，无队尾元素";
	return rear->data;
}


template <class T>
void LinkQueue<T>::ClearQueue()
{
	Node<T> *p;
	p=front->next;
	while(p)//从队头开始逐个删除队列中的结点
	{
		front->next=p->next;//暂存被释放结点
		delete p;
        p=front->next;
	}
	rear=front;
}

template <class T>
int LinkQueue<T>::QueueEmpty()
{
	if(front==rear) 
		return 1;
	else
		return 0;
}


template <class T>
void LinkQueue<T>::QueueTranverse()
{
   Node<T> *p;
   p=front->next;
   while(p)
   {
     cout<<p->data<<'\t';
	 p=p->next;
   }
   cout<<endl;
 }


