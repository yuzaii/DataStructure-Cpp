//树的双亲表存储表示，利用C++模板封装成类
#define MAX_TREE_SIZE 200
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "LinkQueue.h"
using namespace std;
//------------------------------------------------------------------------------------------------------
template <class T>
struct PTNode
{
	T data;//结点数据域
	int parent;//双亲结点位置域
};
//------------------------------------------------------------------------------------------------------
template <class T>
struct PTree
{
	PTNode<T> nodes[MAX_TREE_SIZE];//结点数组
	int n;//结点数
};
//------------------------------------------------------------------------------------------------------
template <class T>
class CTree
{
	PTree<T> Tree;
	public:
		CTree();								// 构造函数，构造一棵空树
		bool CreateTree(T end);					//创建一棵树
		void ClearTree();						//清空一棵树
		bool IsEmpty();							//判断树是否为空
		int TreeDepth();						//返回树的深度
		T Root();								//返回树根
		T Value(int i);							//i是树中的结点序号，返回结点的值
		bool Assign(T cur_e,T value);			//将树中结点值为cur_e修改成value
		T parent(T cur_e);						//cur_e是树中结点值，若其双亲结存在，返回双亲的值，否则返回空
		T LeftChild(T cur_e);					//cur_e是树中结点值,若cur_e是非叶子结点，返回其最左边的孩子值，否则返回空
		T RightSibling(T cur_e);				//cur_e是树中的某个结点，若有右兄弟那么返回右兄弟的值
		void Print();							//输出树
		bool InsertChild(T p,int i,PTree<T> c);	//插入操作
		void DeleteChild(T p,int i);			//删除操作
		void TraverseTree();					//遍历一棵树
		PTree<T> GetTree(){return Tree;}		//返回树

};
//------------------------------------------------------------------------------------------------------
template <class T>
CTree<T>::CTree()
{
	Tree.n=0;
}
//------------------------------------------------------------------------------------------------------
//template <class T>
struct QElemType
{//定义队列元素类型
	int num;
	char name;
};
template <class T>
bool CTree<T>::CreateTree(T end)
{//创建一棵树
	LinkQueue<QElemType> Q;//队列
	QElemType p,qq;//队列类型变量
	int i=0;
	int j;
	int len;
	T c[MAX_TREE_SIZE];//临时存放孩子结点数组
	cout<<"请输入根结点：";
	cin>>Tree.nodes[0].data;//根结点的序号为0
	if(Tree.nodes[0].data!=end)//树不空
	{
		Tree.nodes[0].parent=-1;//根结点没有双亲
		qq.name=Tree.nodes[0].data;
		qq.num=0;//序号
		i++;
		Q.EnQueue(qq);//根结点入队列
		while(i<MAX_TREE_SIZE&&Q.QueueEmpty()!=1)//数组未满且队列不空
		{
			qq=Q.DeQueue();
			cout<<"请按长幼顺序输入结点 "<<qq.name<<" 的所有孩子：(没有孩子输入"<<end<<')';
			//cin>>noskipws;
			cin>>c;
			if(c[0]==end) continue;
			len=strlen(c);//获取字符串的长度
			for(j=0;j<len;j++)
			{
				Tree.nodes[i].data=c[j];
				Tree.nodes[i].parent=qq.num;
				p.name=c[j];
				p.num=i;
				Q.EnQueue(p);
				i++;
			}
		}
		if(i>MAX_TREE_SIZE)
		{
			cout<<"结点数超过数组容量！"<<endl;
			exit(-1);
		}
		Tree.n=i;
	}
	else
	{
		Tree.n=0;//树为空
	}
	return true;
}
//------------------------------------------------------------------------------------------------------
template <class T>
void CTree<T>::ClearTree()
{
	Tree.n=0;//和树的初始化是相同的
}
//------------------------------------------------------------------------------------------------------
template <class T>
bool CTree<T>::IsEmpty()
{
	if(Tree.n==0) return true;//树为空返回true;
	return false;//树不空，返回false.
}
//------------------------------------------------------------------------------------------------------
template <class T>
int CTree<T>::TreeDepth()					//返回树的深度
{
	int k,m,def,max=0;
	for(k=0;k<Tree.n;k++)
	{
		def=1;
		m=Tree.nodes[k].parent;
		while(m!=-1)
		{//沿着双亲结点一直找到根结点
			m=Tree.nodes[m].parent;
			def++;
		}
		if(max<def)
		{
			max=def;
		}
	}
	return max;//最大的深度
}
//------------------------------------------------------------------------------------------------------
template <class T>
T CTree<T>::Root()
{
	if(Tree.n==0)
	return 0;
	else
		return Tree.nodes[0].data;
}
//------------------------------------------------------------------------------------------------------
template <class T>
T CTree<T>::Value(int i)
{
	if(i<Tree.n)
	{
		return Tree.nodes[i].data;
	}
	else
		return 0;
}
//------------------------------------------------------------------------------------------------------
template <class T>
bool CTree<T>::Assign(T cur_e,T value)
{
	if(Tree.n==0) return false;//树为空
	for(int i=0;i<Tree.n;i++)
	{
		if(Tree.nodes[i].data==cur_e)
		{//找到值为cur_e结点，修改值为value
			Tree.nodes[i].data=value;
			return true;//修改成功，返回true
		}		
	}
	return false;//树中不存在值为cur_e的结点，返回false
}
//------------------------------------------------------------------------------------------------------
template <class T>
T CTree<T>::parent(T cur_e)
{
	for(int i=1;i<Tree.n;i++)
	{//跳过根序号为0的情况
		if(Tree.nodes[i].data==cur_e)
			return Tree.nodes[Tree.nodes[i].parent].data;
	}
	return 0;//此结点恰好是根结点，或没有找到此结点
}
//------------------------------------------------------------------------------------------------------
template <class T>
T CTree<T>::LeftChild(T cur_e)
{//初始条件：cur_e是树中的结点，若cur_e是非叶子结点返回其最左边的孩子否则返回“空”
	int i;
	for(i=1;i<Tree.n;i++)
	{
		if(Tree.nodes[Tree.nodes[i].parent].data==cur_e)
			return Tree.nodes[i].data;
	}
	return 0;

}
//------------------------------------------------------------------------------------------------------
template <class T>
T CTree<T>::RightSibling(T cur_e)
{//初始条件：树存在，cur_e是书中的某个结点
 //操作结果：若cur_e有右兄弟，返回它的右兄弟，否则返回“空”
	for(int i=0;i<Tree.n;i++)
	{
		if(Tree.nodes[i].data==cur_e)
			break;//找到值为cur_e的结点，i记录的是其序号
	}
	if(Tree.nodes[i].parent==Tree.nodes[i+1].parent)//若cur_e有右兄弟，那么右兄弟应该紧跟其后
		return Tree.nodes[i+1].data;
	return 0;//没有右兄弟，或该结点不存在
}
//------------------------------------------------------------------------------------------------------
template <class T>
void CTree<T>::Print()
{
	int i;
	cout<<"结点的个数为："<<Tree.n<<endl;
	cout<<"结点   双亲"<<endl;;
	for(i=0;i<Tree.n;i++)
	{
		cout<<Value(i)<<'\t';
		if(Tree.nodes[i].parent>=0)
		{
			cout<<Value(Tree.nodes[i].parent)<<' ';
		}
		cout<<endl;
	}
}
//------------------------------------------------------------------------------------------------------
template <class T>
bool CTree<T>::InsertChild(T p,int i,PTree<T> c)
{
	int j,k,len,f=1,n=0;
	//设交换标志f的初值为1，p孩子数n的初值0
	PTNode<T> t;
	if(IsEmpty()!=true)//树不空
	{
		for(j=0;j<Tree.n;j++)//寻找p在树中的序号
		{
			if(Tree.nodes[j].data==p)//找到p的序号为 j
				break;
		}
		len=j+1;	//如果c是p的第1棵子树，则插入到j+1处
		if(i>1)	//c不是p的第1棵子树
		{
			for(k=j+1;k<Tree.n;k++)
			{
				if(Tree.nodes[k].parent==j)
				{
					n++;//孩子树加1
					if(n==i-1)//找到p的第i-1个孩子，其序号为k
						break;
				}

			}
			len=k+1;
		}
		if(len<Tree.n)
		{//插入点len不在最后
			for(k=Tree.n-1;k>=len;k--)
			{
				Tree.nodes[k+c.n]=Tree.nodes[k];
				if(Tree.nodes[k].parent>=len)
				{
					Tree.nodes[k+c.n].parent+=c.n;
				}
			}
		}
		for(k=0;k<c.n;k++)
		{//依次将树c的所有结点插入此处
			Tree.nodes[len+k].data=c.nodes[k].data;
			Tree.nodes[len+k].parent=c.nodes[k].parent+len;
		}
		Tree.nodes[len].parent=j;//树c的根结点的双亲为p
		Tree.n+=c.n;
		while(f)
		{//从插入点之后，将结点仍按层次排列
			f=0;
			for(j=len;j<Tree.n-1;j++)
			{
				if(Tree.nodes[j].parent>Tree.nodes[j+1].parent)
				{//如果结点j的双亲排在结点j+1的双亲之后（树没有按层序排列），交换两结点
					t=Tree.nodes[j];
					Tree.nodes[j]=Tree.nodes[j+1];
					Tree.nodes[j+1]=t;
					f=1;//交换的标志置1
					for(k=j;k<Tree.n;k++)
					{
						if(Tree.nodes[k].parent==j)
							Tree.nodes[k].parent++;
						else if(Tree.nodes[k].parent==j+1)
						{
							Tree.nodes[k].parent--;
						}
					}
					
				}
			}
		}
		
		return true;
	}//if(IsEmpty()!=true)
	else
		return false;
}
//------------------------------------------------------------------------------------------------------
int deleted[MAX_TREE_SIZE+1];
template <class T>
void CTree<T>::DeleteChild(T p,int i)
{//初始条件：树存在，p是树中的某个节点，1≤i≤p所指结点的度
   // 操作结果：删除树中结点p的第i棵子树
   int j,k,n=0;
   LinkQueue<QElemType> q;
   QElemType pq,qq;
   for(j=0;j<=Tree.n;j++)
     deleted[j]=0; // 置初值为0(不删除标记)
   pq.name='a'; // 此成员不用
   //InitQueue(q); // 初始化队列
   for(j=0;j<Tree.n;j++)
     if(Tree.nodes[j].data==p)
       break; // j为结点p的序号
   for(k=j+1;k<Tree.n;k++)
   {
     if(Tree.nodes[k].parent==j)
       n++;
     if(n==i)
       break; // k为p的第i棵子树结点的序号
   }
   if(k<Tree.n) // p的第i棵子树结点存在
   {
     n=0;
     pq.num=k;
     deleted[k]=1; // 置删除标记
     n++;
     q.EnQueue(pq);
     while(!q.QueueEmpty())
     {
       qq=q.DeQueue();
       for(j=qq.num+1;j<Tree.n;j++)
         if(Tree.nodes[j].parent==qq.num)
         {
           pq.num=j;
           deleted[j]=1; // 置删除标记
           n++;
           q.EnQueue(pq);
         }
     }
     for(j=0;j<Tree.n;j++)
       if(deleted[j]==1)
       {
         for(k=j+1;k<=Tree.n;k++)
         {
           deleted[k-1]=deleted[k];
           Tree.nodes[k-1]=Tree.nodes[k];
           if(Tree.nodes[k].parent>j)
             Tree.nodes[k-1].parent--;
         }
         j--;
       }
     Tree.n-=n; // n为待删除结点数
   }
 
}
//------------------------------------------------------------------------------------------------------
template <class T>
void CTree<T>::TraverseTree()
{//层次遍历树
	cout<<"-----------------------------------------------------------------------"<<endl;
	cout<<"层次遍历树为：";
	for(int i=0;i<Tree.n;i++)
	{
		cout<<Tree.nodes[i].data<<" -> ";
	}
	cout<<"\n-----------------------------------------------------------------------"<<endl;

}

