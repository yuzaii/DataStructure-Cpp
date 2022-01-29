/*---------无向图的连通分量和生成树（图采用邻接表存储结构举例表示）----------*/
#include "AdjLGraph.h" 

template <class T>
bool visit(T v)
{
	cout<<v<<" ";
	return true;
}


template <class T>
void ALGraph<T>::DFSTree(int index,CSTree<T>* &t)
//从第index个顶点出发深度优先遍历图，建根为t的生成树
{

	CSTree<T> *p,*q;
	T v1;int w;
	visited[index] = true;
	bool firsttag = true; 
	v1 = GetVex(index);
	for(w = FirstAdjVex(v1);w>=0;w = NextAdjVex(v1,GetVex(w)))
		//w依次为v的邻接顶点
	{
		if(visited[w] == false)
		{
			p = new CSTree<T>;//分配孩子结点
			p->data = GetVex(w);
			p->firstchild = false;
			p->nextsibling = false;
			if(firsttag)
				//w是v的第一个未被访问的邻接顶点，作为根的左孩子结点
			{
				t->firstchild = p;
				firsttag = false;
			}
			else
				//w是v的其它未被访问的邻接顶点，作为上一邻接顶点的右兄弟
			{
				q->nextsibling = p;
			}
			q = p;
			DFSTree(w,q);//从第w个顶点出发深度优先遍历图G，建立生成子树*q
		}
	}
}


template <class T>
void ALGraph<T>::DFSForest(CSTree<T> * &t) 
//建立无向图的深度优先生成森林的孩子兄弟链表  
{
	CSTree<T> *p,*q;
	int index;
	t = false;
	for(index = 0;index<algraph.vexnum;index++)
	{
		visited[index] = false;
	}
	for(index = 0;index<algraph.vexnum;index++)
		//从第0个位置的顶点找起
	{
		if(visited[index] == false)
			//第index个顶点不曾被访问 
		{
			//建立以第index个顶点为根的生成树
			p = new CSTree<T>;
			p->data = GetVex(index);
			p->firstchild = false;
			p->nextsibling = false;
			if(!t)
			{
				t = p;//t是第一棵生成树的根
			}
			else
			{
				q->nextsibling = p;//前一棵的根的兄弟是其它生成树的根
			}
			q = p;  //q指示当前生成树的根
			DFSTree(index,p);//建立以p为根的生成树

		}
	}
}

template <class T>
void ALGraph<T>::PreOrderTraverse(CSTree<T> * &t,bool (*visit)(T v))
//先根遍历二叉链表结构的树t
{
	if(t)
	{
		visit(t->data);//遍历根
		PreOrderTraverse(t->firstchild,visit); //遍历左子树
		PreOrderTraverse(t->nextsibling,visit);//遍历右子树
	}
}


template <class T>
void ALGraph<T>::BTreetoForest(CSTree<T> * &t)//二叉树（左分支是孩子，右分支是兄弟）转换成森林；
{   CSTree<T>  *q;
    int j=0;
	while(t )
	{
		 	q=t;
			t=t->nextsibling;
			if(t) 
			{	j=j+1;  
				q->nextsibling=false;
			}
			else
			{
				if(j>0)
					j++;
			 }
			if (j==0)
			{	cout<<"先序遍历生成树为："<<endl;
			}
			else
			{	cout<<"先序遍历生成森林第"<<j<<"棵树为："<<endl; 
			}

			PreOrderTraverse(q,visit);
			cout<<endl;
	}
}