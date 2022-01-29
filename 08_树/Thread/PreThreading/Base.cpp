#include<iostream>
using namespace std;
//定义线索二叉树的结点类型
template <class T>
struct BiThrNode
{
	T data;				//数据域
	int lflag;			//左标志域
	int rflag;			//右标志域
	BiThrNode<T> *lchild;	//左指针域
	BiThrNode<T> *rchild;	//右指针域
};
//--------------------------------------------------------------------------------
//基类
template <class T>
class CThr
{
								
public:
	BiThrNode<T>*BT;	//二叉树的根结点指针										
	CThr(){BT=NULL;};						//构造函数，对二叉链表进行初始化
	~CThr();								//析构函数，释放结点占用的空间
	void DeleteNode(){Clear(BT,0);}				//释放结点空间
	void Clear(BiThrNode<T>*bt,int flag);
	void CreateBiTree(T end);					//创建二叉链表
	void create(BiThrNode<T>*p,int flag,T end);	
	BiThrNode<T>* GetRoot()
	{
		return BT;
	}
};

//--------------------------------------------------------------------------------
template <class T>
CThr<T>::~CThr()
{
	DeleteNode();
	BT=NULL;
}
//------------------------------------------------------------------------------
template <class T>
void CThr<T>::Clear(BiThrNode<T>*bt,int flag)   
{   
	if(bt&&flag!=1)
	{   
		Clear(bt->lchild,bt->lflag);//释放左子树的结点 
		Clear(bt->rchild,bt->rflag);//释放右子树的结点
		cout<<bt->data<<" :释放了指针 "<<bt<<" 所指向的空间。"<<endl;
		delete   bt;				//释放当前访问的结点
		   
	}   
}
//--------------------------------------------------------------------------------
template <class T>
void CThr<T>::CreateBiTree(T end)
{//创建二叉链表，创建好的二叉树还没有线索化。
	cout<<"按先序序列输入二叉树结点值，-1未结束标志： ";
	BiThrNode<T>*p;
	T x;
	cin>>x;
	if(x!=end)				//线索二叉树不为空
	{
		p=new BiThrNode<T>;
		p->data=x;
		p->lchild=NULL;
		p->rchild=NULL;
		p->lflag=0;
		p->rflag=0;
		BT=p;				//p作为二叉线索树的根结点
		create(p,1,end);	//创建左子树
		create(p,2,end);	//创建右子树
	}
}
//--------------------------------------------------------------------------------
template <class T>
void CThr<T>::create(BiThrNode<T>*p,int flag,T end)
{//创建一棵二叉树，flag为1时创建左子树，2时创建右子树，end为结束的标志
	BiThrNode<T>*q;
	T x;
	cin>>x;		//输入结点的值
	if(x!=end)
	{
		q=new BiThrNode<T>;	//申请二叉链表结点
		q->data=x;
		q->lchild = NULL;
		q->rchild = NULL;
		q->lflag = 0;
		q->rflag = 0;
		if(flag==1)p->lchild=q;	//链接到左子树
		if(flag==2)p->rchild=q;	//链接到右子树
		create(q,1,end);		//创建左子树
		create(q,2,end);		//创建右子树
	}	
}