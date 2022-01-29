//------------------------------------------------------------------------------------------------------------------------
//                     对二叉树的基本操作的类模板封装
//------------------------------------------------------------------------------------------------------------------------
#include<iostream>
using namespace std;
//------------------------------------------------------------------------------------------------------------------------
//定义二叉树的结点类型BTNode,其中包含数据域、左孩子，右孩子结点。
template <class T>
struct BTNode
{
	T data ;			//数据域
	BTNode* lchild;		//指向左子树的指针
	BTNode* rchild;		//指向右子树的指针
};
//------------------------------------------------------------------------------------------------------------------------
//CBinary的类模板
template <class T>
class BinaryTree
{
	BTNode<T>* BT;
	public: 
		BinaryTree(){BT=NULL;}					// 构造函数,将根结点置空
		~BinaryTree(){clear(BT);}				// 调用Clear()函数将二叉树销毁
		void ClearBiTree(){clear(BT);BT=NULL;};	// 销毁一棵二叉树
		void CreateBiTree(T end);				// 创建一棵二叉树，end为空指针域标志
		bool IsEmpty();							// 判断二叉树是否为空
		int BiTreeDepth();						// 计算二叉树的深度
		bool RootValue(T &e);					// 若二叉树不为空用e返回根结点的值，函数返回true，否则函数返回false
		BTNode<T>*GetRoot();					// 二叉树不为空获取根结点指针，否则返回NULL
		bool Assign(T e,T value);				// 找到二叉树中值为e的结点，并将其值修改为value。
		T GetParent(T e);						// 若二叉树不空且e是二叉树中的一个结点那么返回其双亲结点值
		T GetLeftChild(T e);					// 获取左孩子结点值
		T GetRightChild(T e);					// 获取右孩子结点值
		T GetLeftSibling(T e);					// 获取左兄弟的结点值
		T rightsibling(BTNode<T>*p,T e);
		T GetRightSibling(T e);					// 获取右孩子的结点值
		bool InsertChild(BTNode<T>* p,BTNode<T>* c,int RL);// 插入操作
		bool DeleteChild(BTNode<T>* p,int RL);  //删除操作
		void PreTraBiTree();					// 递归算法：先序遍历二叉树
		void InTraBiTree();						// 递归算法：中序遍历二叉树
		void PostTraBiTree();					// 递归算法：后序遍历二叉树
		void PreTraBiTree_N();					// 非递归算法：先序遍历二叉树
		void InTraBiTree_N();					// 非递归算法：中序遍历二叉树
		void LevelTraBiTree();				    // 利用队列层次遍历二叉树
		int  LeafCount();						// 计算叶子结点的个数
		BTNode<T>* SearchNode(T e);				// 寻找到结点值为e的结点，返回指向结点的指针
		void DisplayBTreeShape(BTNode<T>*bt,int level=1);
};
//二叉树的树形显示算法
template <class T>
void BinaryTree<T>::DisplayBTreeShape(BTNode<T>*bt,int level)
{
   if(bt)//空二叉树不显示
   { DisplayBTreeShape(bt->rchild,level+1);//显示右子树
     cout<<endl; //显示新行
     for(int i=0;i<level-1;i++)
        cout<<"   "; //确保在第level列显示节点
     cout<<bt->data; //显示节点
    DisplayBTreeShape(bt->lchild,level+1);//显示左子树  
   }//if
}//DisplayBTree

template <class T>
static int clear(BTNode<T>*bt)   
{   //销毁一棵二叉树
	if(bt)//根结点不空
	{   
		clear(bt->lchild);	 //递归调用Clear()函数销毁左子树
		clear(bt->rchild);	 //递归调用Clear()函数销毁右子树
		cout<<"释放了指针"<<bt<<"所指向的空间。"<<endl;
		delete   bt;		 //释放当前访问的根结点  
	}
	return 0;
}

template <class T>
void BinaryTree<T>::CreateBiTree(T end)
{	//创建一棵二叉树：先序序列的顺序输入数据，end为结束的标志
	cout<<"请按先序序列的顺序输入二叉树,-1为空指针域标志："<<endl;
	BTNode<T>*p;
	T x;
	cin>>x;				//输入根结点的数据
	if(x==end) return ;	//end 表示指针为空，说明树为空
	p=new BTNode<T>;	//申请内存
	if(!p)
	{
		cout<<"申请内存失败！"<<endl;
		exit(-1);//申请内存失败退出
	}
	p->data=x;
	p->lchild=NULL;
	p->rchild=NULL;
	BT=p;			//根结点
	create(p,1,end);//创建根结点左子树，1为标志，表示左子树
	create(p,2,end);//创建根结点右子树，2为标志，表示右子树
}

template <class T>
static int create(BTNode<T>*p,int k,T end)
{//静态函数，创建二叉树，k为创建左子树还是右子树的标志，end为空指针域的标志
	BTNode<T>*q;
	T x;
	cin>>x;
	if(x!=end)
	{						//先序顺序输入数据
		q=new BTNode<T>;
		q->data=x;
		q->lchild=NULL;
		q->rchild=NULL;
		if(k==1) p->lchild=q;	//q为左子树
		if(k==2) p->rchild=q;	//p为右子树
		create(q,1,end);		//递归创建左子树
		create(q,2,end);		//递归创建右子树
	}
	return 0;
}


template <class T>
bool BinaryTree<T>::IsEmpty()
{//判断二叉树是否为空
	if(BT==NULL) return true;//树根结点为空，说明树为空
	return false;
}

template <class T>
int BinaryTree<T>::BiTreeDepth()
{//利用递归算法计算树的深度
	BTNode<T>*bt=BT;//树根结点
	int depth=0;//开始的时候数的深度初始化为0
	if(bt)//如果树不为空
	Depth(bt,1,depth);
	return depth;
}
template <class T>
static int Depth(BTNode<T>* p,int level,int &depth)
{	//这个函数由BiTreeDepth()函数调用完成树的深度的计算
	//其中p是根结点，Level 是层，depth用来返回树的深度
	if(level>depth) depth=level;
	if(p->lchild) Depth(p->lchild,level+1,depth);//递归的遍历左子树，并且层数加1
	if(p->rchild) Depth(p->rchild,level+1,depth);//递归的遍历右子树，并且层数加1
	return 0;
}

template <class T>
bool BinaryTree<T>::RootValue(T &e)
{//若二叉树不为空用e返回根结点的值，函数返回true，否则函数返回false
	if(BT!=NULL)	//判断二叉树是否为空
	{
		e=BT->data;	//若不空，则将根结点的数据赋值给e
		return true;//操作成功，返回true
	}
	return false;	//二叉树为空，返回false
}

template <class T>
BTNode<T>*BinaryTree<T>::GetRoot()
{//获取根信息
	return BT;//返回根结点的指针，若二叉树为空那么返回NULL
}

template <class T>
bool BinaryTree<T>::Assign(T e,T value)
{//结点赋值
	if(SearchNode(e)!=NULL)
	{
		(SearchNode(e))->data=value;
		return true;
	}
	return false;
}

template <class T>
T BinaryTree<T>::GetParent(T e)
{//获取双亲信息
	BTNode<T>*Queue[200],*p;
	int rear,front;
	rear=front=0;
	if(BT)
	{
		Queue[rear++]=BT;
		while(rear!=front)
		{
			p=Queue[front++];
			if(p->lchild&&p->lchild->data==e||p->rchild&&p->rchild->data==e)
				return p->data;
			else
			{
				if(p->lchild) Queue[rear++]=p->lchild;
				if(p->rchild) Queue[rear++]=p->rchild;
			}
		}
	}
	return NULL;
}

template <class T>
T BinaryTree<T>::GetRightChild(T e)
{//如果二叉树存在，e是二叉树中的一个结点，右子树存在那么返回右子树的结点值，否则返回0并提示右子树为空
	BTNode<T>*p=SearchNode(e);
	if(p->rchild) return p->rchild->data;//右子树不空，返回右子树根结点的值
	cout<<"结点"<<e<<"的右子树为空"<<endl;
	return 0;
}

template <class T>
T BinaryTree<T>::GetLeftChild(T e)
{//如果二叉树存在，e是二叉树中的一个结点，左子树存在那么返回左子树的结点值，否则返回0并提示左子树为空
	BTNode<T>*p=SearchNode(e);
	if(p->lchild) return p->lchild->data;
	cout<<"结点"<<e<<"的左子树为空"<<endl;
	return 0;
}

template <class T>
T BinaryTree<T>::GetLeftSibling(T e)
{//获取左兄弟信息
	if(BT!=NULL)
	{
		return leftsibling(BT,e);
	}
	else
	{//二叉树为空
		cout<<"二叉树为空！"<<endl;
		return 0;
	}
}

template <class T>
T leftsibling(BTNode<T>*p,T e)
{
	T q=0;
	if(p==NULL) return 0;
	else
	{
		if(p->rchild)
		{
			if(p->rchild->data==e)
			{
				if(p->lchild) return p->lchild->data;
				else
					return NULL;
			}
		}
		q=leftsibling(p->lchild,e);
		if(q)return q;
		q=leftsibling(p->rchild,e);
		if(q)return q;
	}
	return 0;
}
//------------------------------------------------------------------------------------------------------------------------
template <class T>
T BinaryTree<T>::GetRightSibling(T e)
{//获取右兄弟信息
	if(BT!=NULL)
	{
		return rightsibling(BT,e);
	}
	else
	{//二叉树为空
		cout<<"二叉树为空！"<<endl;
		return 0;
	}
}
template <class T>
 T BinaryTree<T>::rightsibling(BTNode<T>*p,T e)
{
	BTNode<T> *q=SearchNode(e);
	BTNode<T> *pp;
	if(q)
	{
		pp=SearchNode(GetParent(e));
		if(pp)
		{
			if(pp->rchild) return pp->rchild->data;
			else return 0;
		}
		else return 0;

	}
	return 0;
}

template <class T>
bool BinaryTree<T>::InsertChild(BTNode<T>* p,BTNode<T>* c,int LR)
{//插入孩子
	if(p)
	{
		if(LR==0)
		{
			c->rchild=p->lchild;
			p->lchild=c;
		}
		else
		{
			c->rchild=p->rchild;
			p->rchild=c;
		}
		return true;
	}
	return false;//p为空
}
//------------------------------------------------------------------------------------------------------------------------
template <class T>
bool BinaryTree<T>::DeleteChild(BTNode<T>* p,int RL)  
{//删除结点
	if(p)
	{
		if(RL==0)
		{
			clear(p->lchild);//释放p右子树的所有结点空间
			p->lchild=NULL;
		}
		else
		{
			clear(p->rchild);
			p->rchild=NULL;
		}
		return true;//删除成功
	}
	return false;//p为空
}
//------------------------------------------------------------------------------------------------------------------------
template <class T>
void BinaryTree<T>::PreTraBiTree()
{//先序遍历二叉树
	cout<<"----------------------------------------------"<<endl;
	cout<<"先序遍历二叉树:";
	BTNode<T>*p;
	p=BT;			//根结点
	PreTraverse(p); //从根结点开始先序遍历二叉树
	cout<<endl;
	cout<<"----------------------------------------------"<<endl;
}
template <class T>
static int PreTraverse(BTNode<T>*p)
{
	if(p!=NULL)
	{
		cout<<p->data<<' ';		//输出结点上的数据
		PreTraverse(p->lchild);	//递归的调用前序遍历左子树
		PreTraverse(p->rchild);	//递归的调用前序遍历右子树
	}
	return 0;
}			
//------------------------------------------------------------------------------------------------------------------------
template <class T>
void BinaryTree<T>::InTraBiTree()
{//中序遍历二叉树
	cout<<"----------------------------------------------"<<endl;
	cout<<"中序遍历二叉树:";
	BTNode<T>*p;
	p=BT;//根结点
	InTraverse(p);//从根结点开始中序遍历二叉树
	cout<<endl;
	cout<<"----------------------------------------------"<<endl;
}
template <class T>
static int InTraverse(BTNode<T>*p)
{
	if(p!=NULL)
	{
		InTraverse(p->lchild);	//递归的调用中序遍历左子树
		cout<<p->data<<' ';		//输出结点上的数据
		InTraverse(p->rchild);	//递归的调用中序遍历右子树
	}
	return 0;
}
//------------------------------------------------------------------------------------------------------------------------
template <class T>
void BinaryTree<T>::PostTraBiTree()
{//后序遍历二叉树
	cout<<"----------------------------------------------"<<endl;
	cout<<"后序遍历二叉树:";
	BTNode<T>*p;
	p=BT;//根结点
	PostTraverse(p);//从根结点开始遍历二叉树
	cout<<endl;
	cout<<"----------------------------------------------"<<endl;
}
template <class T>
static int PostTraverse(BTNode<T>*p)
{
	if(p!=NULL)
	{
		PostTraverse(p->lchild);//递归调用后序遍历左子树
		PostTraverse(p->rchild);//递归调用后序遍历右子树
		cout<<p->data<<' ';		//输出结点上的数据
	}
	return 0;
}
//------------------------------------------------------------------------------------------------------------------------
template <class T>
void BinaryTree<T>::PreTraBiTree_N()
{//
	cout<<"----------------------------------------------"<<endl;
	cout<<"先序(非递归)遍历二叉树得：";
	BTNode<T> *Stack[200];//利用指针数组作为栈
	int top=0;
	BTNode<T>*p=BT;//将根结点的指针赋值给p
	while(p!=NULL||top!=0)
	{
		while(p!=NULL)
		{
			cout<<p->data<<" ";
			Stack[top++]=p->rchild;
			p=p->lchild;
		}
		if(top!=0)
		{
			p=Stack[--top];
		}
	}
	cout<<"\n----------------------------------------------"<<endl;
}
//------------------------------------------------------------------------------------------------------------------------
template <class T>
void BinaryTree<T>::InTraBiTree_N()
{//非递归中序遍历二叉树
	cout<<"----------------------------------------------"<<endl;
	cout<<"中序(非递归)遍历二叉树得：";
	int top=0;
	BTNode<T> *Stack[200];
	BTNode<T> *p=BT;
	while(p||top)
	{
		while(p)
		{
			Stack[top++]=p;
			p=p->lchild;
		}
		
		if(top)
		{
			p=Stack[--top];
			cout<<p->data<<' ';
			p=p->rchild;
		}
	}
	cout<<"\n----------------------------------------------"<<endl;
	
}

//------------------------------------------------------------------------------------------------------------------------
template <class T>
void BinaryTree<T>::LevelTraBiTree()
{//利用队列Queue层次遍历二叉树
	BTNode<T> *Queue[100];	//利用一维数组作为队列，存放结点的指针
	BTNode<T> *b;
	int front,rear;			//指向队列的头和尾下标
	front=rear=0;			//队列初始为空
	cout<<"----------------------------------------------"<<endl;
	if(BT)					//若二叉树不为空。
	{
		Queue[rear++]=BT;	//二叉树的根结点指针进队列。
		while(front!=rear)	//队列不为空。
		{
			b=Queue[front++];			//队首的元素出队列
			if(b)cout<<b->data<<' ';	//输出结点的值
			if(b->lchild) Queue[rear++]=b->lchild;//如果左子树不空，进队。
			if(b->rchild) Queue[rear++]=b->rchild;//如果右子树不空，进队。
		}

	}
	cout<<"\n----------------------------------------------"<<endl;
}

template <class T>
int BinaryTree<T>::LeafCount()
{//计算叶子的个数

	int count=0;
	return Leaf(BT,count);
}
template <class T>
static int Leaf(BTNode<T>* p,int &count)
{
	//static int count=0;//静态变量，存放叶子结点的个数
	if(p)
	{
		if(p->lchild==NULL&&p->rchild==NULL) count++;//判断是否为叶子结点
		Leaf(p->lchild,count);//递归遍历左子树
		Leaf(p->rchild,count);//递归遍历右子树
	}
	return count;

}

template <class T>
BTNode<T>* BinaryTree<T>::SearchNode(T e)
{//结点查询
	BTNode<T>*t;
	if(BT)
	{
		
		if(BT->data==e)	return BT;
		t=search(BT->lchild,e);//在左子树中查找
		if(t)return t;
		
		t=search(BT->rchild,e);//在右子树查找
		if(t) return t;
	}

	return NULL;
}
template <class T>
static BTNode<T>* search(BTNode<T>*bn,T e)
{BTNode<T>*t;
	if(bn)
	{	
		if(bn->data==e)	{return bn;}
		t=search(bn->lchild,e);//递归查找左子树
		if(t) return t;
		t=search(bn->rchild,e);//递归查找右子树
		if(t) return t;
	}
	return NULL;
}
//------------------------------------------------------------------------------------------------------------------------
