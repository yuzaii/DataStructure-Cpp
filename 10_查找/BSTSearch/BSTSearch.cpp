#include<iostream>
using namespace std;
#define TRUE  1;
#define FALSE  0;
typedef int T;
const maxsize=50;

template <class T>
struct Node
{
	T key;
	/*.....*/
};

template <class T>
struct bitree
{
	Node<T> data;
    bitree<T> *lchild;
	bitree<T> *rchild;
};


template <class T>
class BSTree
{
public:
	Node<T> *ST;
	int len;        //无素个数
	bitree<T> *t;	//根指针
	bitree<T> *f;	//根指针的双亲指针
	bitree<T> *p;	//指向查找路径上最后访问的节点
	BSTree();//构造函数
	~BSTree();//析构函数
	void SearchBST(bitree<T> *t,T key);//二叉排序树查找
	void InsertBST(bitree<T> *(&t),Node<T> e);//元素插入
	int DeleteBST(bitree<T> *(&t),T key);//二叉排序树中元素删除
	int Delete(bitree<T> *(&p));//
	void DeleteElem(T key);//查找表元素删除
	void InDisplay(bitree<T> *t);//中序遍历二叉排序树
	void Display();//查找表显示
};

template <class T>
BSTree<T>::BSTree()
{//构造函数，初始化查找表
	ST=new Node<T>[maxsize];//顺序存放查找表
	len=0;
	t=NULL;//查找树初始化
}

template <class T>
BSTree<T>::~BSTree()
{//析构函数，销毁查找表
	delete [] ST;
    len=0;
	delete t;
	cout<<"成功销毁二叉排序树\n";
}

template <class T>
void BSTree<T>::SearchBST(bitree<T> *t,T key)
{//元素查找
   if(t==NULL || key==t->data.key)
	{
		if(key==t->data.key)                    
			cout<<"找到"<<key<<"的节点"<<endl;
		else
		cout<<"不存在"<<key<<"的节点"<<endl;
	}
	else if(key<t->data.key)
		SearchBST(t->lchild,key);
	else
		SearchBST(t->rchild,key);
}

template <class T>
void BSTree<T>::InsertBST(bitree<T> *(&t),Node<T> e)
{//元素插入
	ST[len]=e;
	len++;
    p=t;
   while(p)
	{
		if(p->data.key==e.key)
		{
		cout<<"二叉排序树中已经存在值为:"<<e.key<<"的节点\n";
		exit(1);
		}
		f=p;
		if(e.key<p->data.key)
			p=p->lchild;
		else
			p=p->rchild;
		p=new bitree<T>;
		p->data=e;
		p->lchild=p->rchild=NULL;
		if(t==NULL)
			t=p;
		else
		{
			if(e.key<f->data.key)
				f->lchild=p;
			else
				f->rchild=p;
		}
	}
}
template <class T>
int BSTree<T>::DeleteBST(bitree<T> *(&t),T key)
{// 元素删除		
	if(!t)
	{
	  cout<<"二叉树为空,无法删除\n";
	  return FALSE;
	}
	else
	{
    	if(key==t->data.key)
			return Delete(t);
		else if(key<t->data.key)
	     	return DeleteBST(t->lchild,key);
		else
		return DeleteBST(t->rchild,key);
	}
}

template <class T>
int BSTree<T>::Delete(bitree<T> *(&p))
{
		bitree<T> *q,*s;
		if(!p->rchild)
		{
			q=p;
			p=p->lchild;
			delete q;
			cout<<"成功删除"<<endl;
			
		}
		else if(!p->lchild)
		{
			q=p;
			p=p->rchild;
			delete q;
			cout<<"成功删除"<<endl;
		}
		else
		{
			q=p;
			s=p->lchild;
			while(s->rchild)
			{
				q=s;
				s=s->rchild;
			}
			p->data=s->data;
		   if(q!=p)
			q->rchild=s->lchild;
		   else
			q->lchild=s->lchild;
		  delete s;
		  cout<<"成功删除"<<endl;
		}
		return TRUE;
}

template <class T>
void BSTree<T>::DeleteElem(T key)
{//顺序表元素删除 
	for(int i=0;i<len && ST[i].key!=key;i++);
	if(i<len)
	{
		for(int j=i+1;j<len;j++)
			ST[i]=ST[j];
		len--;
	}
}
		
template <class T>
void BSTree<T>::InDisplay(bitree<T> *t)
{//中序遍历输出
	if(t!=NULL)
	{
		InDisplay(t->lchild);
		cout<<t->data.key<<"    ";	
	   	InDisplay(t->rchild);
	}
}

template <class T>
void BSTree<T>::Display()
{//输出查找表中的数据元素
	cout<<"查找表中的数据元素关键字依次为:\n";
	for(int i=0;i<len;i++)
		cout<<ST[i].key<<"   ";
	cout<<endl;
}

void main()
{
	int m,l,i;
	BSTree<int> a;
	do  {
	  cout<<"---- 二叉排序树的基本操作--------"<<endl;
	  cout<<"--- 1. 创建查找表 --------------\n"
	      <<"----2. 插入元素-------------\n" 
	      <<"--- 3. 删除元素  ---------------\n"
	      <<"--- 4. 查找元素 ----------------\n"
		  <<"--- 5. 中序遍历二叉排序树输出---\n"
	      <<"--- 6. 查找表输出  -------------\n"
	      <<"--- 7. 退出  -------------------\n"
		  <<"请选择操作:";
	  cin>>m;
	 if(m==1)
		{
			Node<T> e;
			cout<<"输入要插入的数据元素个数\n";
			cin>>l;
			cout<<"输入"<<l<<"个不同的数据元素\n";
			for(i=0;i<l;i++)
			{
				cin>>e.key;	
				a.InsertBST(a.t,e);
			}
		}
	  else if(m==2)
		{
			Node<T> e;
			cout<<"输入要插入的数据元素\n";
			cin>>e.key;
			a.InsertBST(a.t,e);
		}
	  else if(m==3)
		{
			T key;
			cout<<"输入要删除的数据元素:";
			cin>>key;
			a.DeleteBST(a.t,key);
			a.DeleteElem(key);
		}
	  else if(m==4)
		{
			T key;
			cout<<"输入查找的数据元素: ";
			cin>>key;
			a.SearchBST(a.t,key);
		}
		else if(m==5)
		{
			cout<<"中序遍历的输出结果为:\n";
			a.InDisplay(a.t);
			cout<<endl;
		}
		else if(m==6)
		{
			cout<<"二叉排序树输出:\n";
			a.Display();
			cout<<endl;
		}
		else if(m==7)
			cout<<"结束运行!\n";
		else
			cout<<"输入代码非法,代码在0--7之间,请重新输入"<<endl;
		//cout<<endl;
		cout<<"请继续选择操作"<<endl;
	}while(m!=7);
}