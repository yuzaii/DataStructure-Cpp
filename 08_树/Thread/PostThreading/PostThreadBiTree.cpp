//后序线索三叉链表
#include<iostream>
using namespace std;
//定义后序线索三叉链表结点类型
template <class T>
struct TTTNode
{
	T data;						//数据域
	int lflag;					//左标志域
	int rflag;					//有标志域
	TTTNode<T> *pre;			//双亲结点指针域
	TTTNode<T> *lchild;			//左孩子指针域
	TTTNode<T> *rchild;			//有孩子指针域
};
//后序线索三叉链表类
template <class T>
class PostThreadBiTree
{
	TTTNode<T> * BT;						//三叉链表根结点指针
	public:									//成员函数
		PostThreadBiTree(){BT=NULL;}		//构造函数，对三叉链表初始化
		void CreateBiTree(T end);			//创建三叉链表
		void CreateThreadBT();				//线索化三叉链表
		void TraverseTree();				//遍历后序线索三叉链表

};

template <class T>
void PostThreadBiTree<T>::CreateBiTree(T end)
{
	TTTNode<T> *p;				//三叉链表结点
	T x;
	cin>>x;						//输入第一个结点值
	if(x==end) return;			//三叉链表树为空
	p=new TTTNode<T>;			//申请三叉链表结点
	p->data=x;					//数据域赋值
	p->pre=NULL;				//双亲结点初始状态为NULL
	p->lchild=NULL;				//左孩子域初始状态为NULL
	p->rchild=NULL;				//右孩子域初始状态为NULL
	p->lflag=0;
	p->rflag=0;
	BT=p;						//三叉链表的根结点
	create(p,1,end);			//创建左子树
	create(p,2,end);			//创建右子树
}
template <class T>
static int create(TTTNode<T>*p,int k,T end)
{
	TTTNode<T> *Q;				//三叉链表结点
	T x;
	cin>>x;						//输入结点值
	if(x!=end)
	{
		Q= new TTTNode<T>;		//申请三叉链表结点
		Q->data=x;
		Q->lchild=NULL;
		Q->rchild=NULL;
		Q->lflag=0;
		Q->rflag=0;
		Q->pre=p;
		if(k==1) p->lchild=Q;	//连接到左子树
		if(k==2) p->rchild=Q;	//链接到右子树
		create(Q,1,end);		//递归创建左子树
		create(Q,2,end);		//递归创建右子树	
	}
	return 0;
}
//-------------------------------------------------------------------------------------------------
template <class T>
void PostThreadBiTree<T>::CreateThreadBT()
{
	//线索化
	TTTNode<T> *p=BT,*q=NULL;
	Thread(p,&q);
}
template <class T>
static int Thread(TTTNode<T> *p,TTTNode<T> **h)
{
	if(p!=NULL)
	{
		Thread(p->lchild,h);//递归线索左子树
		Thread(p->rchild,h);//递归线索右子树
		//若上次访问的结点的有指针为空
		//则将当前访问的结点序号填入，并置右标志域1
		if(*h!=NULL&&(*h)->rchild==NULL)
		{
			(*h)->rchild=p;
			(*h)->rflag=1;
		}
		//若上次访问的结点的左指针为空
		//则将当前访问的的结点序号填入，并置右标志域为1
		if((*h!=NULL)&&(p->lchild==NULL))
		{
			p->lchild=(*h);
			p->lflag=1;
		}
		*h=p;//记住当前访问的结点
	}
	return 0;
}
//-------------------------------------------------------------------------------------------------
template <class T>
void PostThreadBiTree<T>::TraverseTree()
{//遍历后序线索三叉树
	TTTNode<T> *p,*h;
	if(BT==NULL) return ;//三叉树为空
	h=BT;//三叉树的根结点
	while(h->lchild!=NULL||h->rflag==0&&h->rchild!=NULL)
	{//左子树不空，或右子树不空
		if(h->lchild!=NULL)
		h=h->lchild;
		else
			h=h->rchild;
	}
	//按后序遍历找第一个结点
	cout<<h->data<<"→";//输出后序序列中的第一个结点值
	while(h->pre!=NULL)//
	{
		if(h->rflag!=0) h=h->rchild;
		else
		{
			p=h->pre;
			if((p->rchild==h)||(p->lchild==h)&&((p->rflag!=0)||(p->rchild==NULL)))
				h=p;//双亲结点作为后件
			else
			{
				h=p->rchild;
				while(((h->lflag==0)&&(h->lchild!=NULL))||
					((h->rflag==0)&&(h->rchild!=NULL)))
				{
					if((h->lflag==0)&&h->lchild!=NULL)
						h=h->lchild;
					else
						h=h->rchild;
				}
			}
		}
		cout<<h->data<<"→";
	}
	cout<<"NULL"<<endl;
}

int main()
{
	PostThreadBiTree<char> PT;
	int op;//选择的操作
	do
	{
		system("cls");
		cout<<"----------菜   单----------------"<<endl;
		cout<<"\t1：创建一棵二叉树"<<endl;
		cout<<"\t2：生成后序线索二叉树"<<endl;
		cout<<"\t3：遍历后序线索二叉树"<<endl;
		cout<<"\t4：退出"<<endl;
		cout<<"-----------------------------------"<<endl;
		cout<<"请选择操作：[ ]";
		cout<<"\b\b";
		cin>>op;
		switch(op)
		{
		case 1:
			cout<<"按先序顺序输入树的各个结点，'#'为空指针标志：";
			PT.CreateBiTree('#');
			system("pause");
			break;
		case 2:
			PT.CreateThreadBT();
			system("pause");
			break;
		case 3:
			PT.TraverseTree();
			system("pause");
			break;
		case 4:
			cout<<"结束运行，Bye-Bye!"<<endl;
			break;
		default:
			cout<<"选择的操作有误！"<<endl;
		}
	}while(op!=4);
	return 0;
}