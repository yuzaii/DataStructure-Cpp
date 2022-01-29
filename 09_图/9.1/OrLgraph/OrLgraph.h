/*--------------------------有向图的十字链表存储表示-----------------------------*/
#include <string>
#include "LinkedQueue.h"  
#define MAX_VERTEX_NUM 20  //最大顶点数  
#define MAX_INFO 10  //信息的大小 

struct ArcBox{
	int tailvex,headvex;//该弧的尾和头顶点位置
	ArcBox *hlink,*tlink;//分别为弧头相同和弧尾相同的弧的链域
	char *info;          //该弧的相关信息指针
};

template <class T>
struct VexNode{
	T data;
	ArcBox *firstin,*firstout;//分别指向该顶点的第一条入弧和出弧
};

template <class T>
struct _OLGraph{
	VexNode<T> xlist[MAX_VERTEX_NUM]; //表头向量
	int vexnum,arcnum;//有向图的顶点数和弧数             
};


template <class T>
class OLGraph{
	
	_OLGraph<T> olgraph;

	bool visited[MAX_VERTEX_NUM];
	
public:
	
	void CreateGraph();                          //v是图的顶点集 vr是图的边集 

	void DestroyGraph();                         //销毁图

	int LocateVex (T u);                    //图存在，图中存在顶点u 则返回该顶点在图中的位置

	T GetVex(int index);                    //图存在，index是图中某个顶点的序号 ：返回v的值

	void PutVex(T v,T value);           //图存在，v是图中某个顶点 则对v赋值value

	int FirstAdjVex(T v);                  //图存在，v是G中某个顶点 返回v的第一个临接点的序号 若无领接点则返回空

	int NextAdjVex(T v,T w);          //图存在，v是图中某个顶点，w是v的邻接点 返回v的相对于w的下一个邻接点的序号，若w是v的最后一个邻接点则返回空

	void InsertVex(T v);                   //图存在 在图中增加新顶点v

	bool DeleteVex(T v);                   //图存在   删除顶点v及其相关的弧

	bool InsertArc(T v,T w);          //图存在，V，w是图的两个顶点 在图中添加弧<v，w>
		
	bool DeleteArc(T v,T w);          //图存在，V，w是图的两个顶点 在图中删除弧<v，w>
	
	bool (*VisitFunc)(T v);                 //访问顶点v的方式

	void DFS(int index);                        //从第index个顶点出发递归的深度优先遍历图

	bool DFSTraverse(bool (*visit)(T v));  //图存在，对图进行深度优先遍历
		
	bool BFSTraverse(bool (*visit)(T v));  //图存在，对图进行广度优先遍历

	void DisPlay();                             //输出图               

};


template <class T>
int OLGraph<T>::LocateVex(T u)
{
	for(int i = 0;i<olgraph.vexnum;i++)
	{
		if(olgraph.xlist[i].data == u)
			return i;
	}
	return -1;
}

template <class T>
void OLGraph<T>::CreateGraph()
{
	int i,j,k;	 
	ArcBox *p;
	T v1,v2;
    cout<<"请输入有向图的顶点个数，弧的个数 ";
	cin>>olgraph.vexnum>>olgraph.arcnum ;
	cout<<"请输入"<<olgraph.vexnum<<"个顶点的值 "<<endl;
    for(i = 0;i<olgraph.vexnum;i++)
		//初始化表头向量
	{
		cin>>olgraph.xlist[i].data;
		olgraph.xlist[i].firstin = false;
		olgraph.xlist[i].firstout = false;
	}
	cout<<"请输入"<<olgraph.arcnum<<"条弧的弧尾和弧头"<<endl;
	for(k = 0;k<olgraph.arcnum;k++)
		//输入各弧构造十字链表
	{
		cin>>v1>>v2;
		i = LocateVex(v1);
		j = LocateVex(v2);
		p = new ArcBox;         //创建一个弧结点
		p->tailvex = i; p->headvex = j; //对弧结点赋值
		//完成在入弧和出弧链表表头的插入
		p->hlink = olgraph.xlist[j].firstin; 
		p->tlink = olgraph.xlist[i].firstout;
		olgraph.xlist[j].firstin = olgraph.xlist[i].firstout = p;
		p->info = false;
	}
}


template <class T>
void OLGraph<T>::DestroyGraph()
{
	int i;
	ArcBox *p,*q;
	for(i = 0;i<olgraph.vexnum;i++)
	{
		p = olgraph.xlist[i].firstout;//仅仅对出弧操作就足够了
		while(p)
		{
			q = p;
			p = p->tlink;
			if(q->info)
			{
				delete q->info;
			}
			delete q;
		}
	}
	olgraph.arcnum = 0;
	olgraph.vexnum = 0;
}

template <class T>
T OLGraph<T>::GetVex(int index)
{
	if(index<0||index>=olgraph.vexnum)
		return "false";
	return olgraph.xlist[index].data;
}


template <class T>
void OLGraph<T>::PutVex(T v,T value)
{
	int i = LocateVex(v);
	if(i<0)
		return;
	olgraph.xlist[i].data = value;
}

template <class T>
int OLGraph<T>::FirstAdjVex(T v)
{
	int i = LocateVex(v);
	ArcBox *p = olgraph.xlist[i].firstout;
	if(p)
		return p->headvex;
	else
		return -1;
}

template <class T>
int OLGraph<T>::NextAdjVex(T v,T w)
{
	int i = LocateVex(v);
	int j = LocateVex(w);
	ArcBox *p = olgraph.xlist[i].firstout;
	while(p&&p->headvex!=j)
	{
		p = p->tlink;
	}
	if(p)
		//w存在
	{
		p = p->tlink;//
	}
	if(p)
		//向对于w的邻接点存在
	{
		return p->headvex;
	}
	else
	{
		return -1;
	}
}


template <class T>
void OLGraph<T>::InsertVex(T v)
{
	olgraph.xlist[olgraph.vexnum].data = v;
    olgraph.xlist[olgraph.vexnum].firstin = olgraph.xlist[olgraph.vexnum].firstout = false;
    olgraph.vexnum++;
}

template <class T>
bool OLGraph<T>::DeleteVex(T v)
{
    if(LocateVex(v)<0)
		//判断顶点是否存在
		return false;
	int j,k;
	ArcBox *p,*q;
	k = LocateVex(v);
	if(k<0)
		return false;
	/*---删除顶点v的出弧---*/
	for(j = 0;j<olgraph.vexnum;j++)
		//删除顶点v的出弧是其它顶点的入弧
	{
		if(j == k)
			continue;
		p = olgraph.xlist[j].firstin;
		while(p)
		{
			if(p->tailvex == k&& p == olgraph.xlist[j].firstin)
				//待删结点为首结点
			{
				olgraph.xlist[j].firstin = p->hlink;
				break;
			}
			else if(p->tailvex != k)
				//未找到待删结点
			{
				q = p;
				p = p->hlink;
			}
			else
				//找到待删结点且不是首结点
			{
				q->hlink = p->hlink;
				break;
			}
		}
	}
	p = olgraph.xlist[k].firstout;
	while(p)
		//删除与顶点v有关的出弧
	{
		q = p->tlink;
		if(p->info)
		{
			delete p->info;
		}
		delete p;
		olgraph.arcnum --;
		p = q;
	}
	/*---删除顶点v的入弧---*/
	for(j = 0;j<olgraph.vexnum;j++)
		//删除顶点v的入弧是其它顶点的出弧
	{
		if(j == k)
			continue;
		p = olgraph.xlist[j].firstout;
		while(p)
		{
			if(p->headvex == k&& p == olgraph.xlist[j].firstout)
				//待删结点为首结点
			{
				olgraph.xlist[j].firstout = p->tlink;
				break;
			}
			else if(p->headvex != k)
				//未找到待删结点
			{
				q = p;
				p = p->tlink;
			}
			else
				//找到待删结点且不是首结点
			{
				q->tlink = p->tlink;
				break;
			}
		}
	}
	p = olgraph.xlist[k].firstin;
	while(p)
		//删除与顶点v有关的出弧
	{
		q = p->hlink;
		if(p->info)
		{
			delete p->info;
		}
		delete p;
		olgraph.arcnum --;
		p = q;
	}

	for(j = k+1;j<olgraph.vexnum;j++)
		//需要大于k的顶点依次前移
	{
		olgraph.xlist[j-1] = olgraph.xlist[j];
	}

    olgraph.vexnum --;

	for(j = 0;j<olgraph.vexnum;j++)
		//结点序号大于k的要-1
	{
		p = olgraph.xlist[j].firstout;
		while(p)
		{
			if(p->tailvex>k)
				p->tailvex--;
			if(p->headvex>k)
				p->headvex--;
			p = p->tlink;
		}
	}
	return true;
}


template <class T>
bool OLGraph<T>::InsertArc(T v,T w)
{
	 
	int i = LocateVex(v);
	int j = LocateVex(w);
	if(i<0||j<0)
		return false;
	ArcBox * p = new ArcBox;
	p->tailvex = i;
	p->headvex = j;
	//插入在入弧和出弧的链头
	p->hlink = olgraph.xlist[j].firstin;
	p->tlink = olgraph.xlist[i].firstout;
    olgraph.xlist[j].firstin = olgraph.xlist[i].firstout = p;
    olgraph.arcnum++; 
		p->info = false;//插入的弧不含有其他信息
	return true;
}


template <class T>
bool OLGraph<T>::DeleteArc(T v,T w)
{
	ArcBox *p1,*p2;
	int i = LocateVex(v);
	int j = LocateVex(w);
	if(i<0||j<0||i==j)
		return false;
	//将弧结点从出弧链表中删去
	p2 = olgraph.xlist[i].firstout;
	if(p2&&p2->headvex == j)
		//待删结点为第一个结点
	{
		olgraph.xlist[i].firstout = p2->tlink;
	}
	else
	{
		while(p2&&p2->headvex != j)
			//向后找
		{
			p1 = p2;
			p2 = p2->tlink;
		}
		if(p2)
			//没到表尾
		{
			p1->tlink = p2->tlink;
		}
	}
	//将弧结点从入弧链表中删去
	p2 = olgraph.xlist[j].firstin;
	if(p2&&p2->tailvex == i)
		//待删结点为第一个结点
	{
		olgraph.xlist[j].firstin = p2->hlink;
	}
	else
	{
		while(p2&&p2->tailvex != i)
			//向后找
		{
			p1 = p2;
			p2 = p2->hlink;
		}
		if(p2)
			//没到表尾
		{
			p1->hlink = p2->hlink;
		}
	}
	if(p2->info)
	{
		delete p2->info;
	}
	delete p2;
	olgraph.arcnum--;
	return true;
}


template <class T>
void OLGraph<T>::DisPlay()
{
	ArcBox *p;
	cout<<"共"<<olgraph.vexnum<<"个顶点"<<olgraph.arcnum<<"条弧"<<endl;
	for(int i = 0;i<olgraph.vexnum;i++)
	{
		cout<<"顶点"<<olgraph.xlist[i].data<<"：入度：";
		p = olgraph.xlist[i].firstin;
		while(p)
		{
			cout<<olgraph.xlist[p->tailvex].data<<" ";
			p = p->hlink;
		}
		cout<<"出度：";
		p = olgraph.xlist[i].firstout;
		while(p)
		{
			cout<<olgraph.xlist[p->headvex].data<<" ";
			p = p->tlink;
		}
		p = olgraph.xlist[i].firstout;
		while(p)
			//输出信息
		{
			if(p->info)
				cout<<"弧信息："<<p->info<<" ";
			p = p->tlink;
		}
		cout<<endl;
	}
}


template <class T>
void OLGraph<T>::DFS(int index)
{
	ArcBox *p;
	visited[index] = true;
	if(!VisitFunc(olgraph.xlist[index].data))
		return;
	p = olgraph.xlist[index].firstout;
	while(p&&visited[p->headvex])
		//p没到表尾且该弧的头顶点已经被访问
	{
		p = p->tlink; //查找下一个结点
	}
	if(p&&!visited[p->headvex])
		//该弧的头顶点未被访问
	{
		DFS(p->headvex);
	}

}


template <class T>
bool OLGraph<T>::DFSTraverse(bool (*visit)(T v))
{
	int i ;
    VisitFunc = visit;
   	for(i = 0;i<MAX_VERTEX_NUM;i++)
	{
		visited[i] = false;
	}
    for(i = 0;i<olgraph.vexnum;i++)
		//对每个未被访问的顶点进行深度优先遍历
    {
	   if(!visited[i])
		   DFS(i);
    }
	cout<<endl;
    return true;
}


template <class T>
bool OLGraph<T>::BFSTraverse(bool (*visit)(T v))
{
	LinkedQueue<int> q;int i,j,receive; T u1;
	for(i = 0;i<MAX_VERTEX_NUM;i++)
	{
		visited[i] = false;
	}
	for(i = 0;i<olgraph.vexnum;i++)
		//对每个未被访问的顶点进行广度优先遍历
	{
		if(!visited[i])
		{
			visited[i] = true;
			if(!visit(olgraph.xlist[i].data))
				return false;
			q.EnQueue(i);
			while(!q.IsEmpty())
			{
				q.DeQueue(receive); //对头元素出队并置为receive
				u1 = GetVex(receive);
				for(j = FirstAdjVex(u1);j>=0;j = NextAdjVex(u1,GetVex(j)))
				{
					if(!visited[j])
					{
						visited[j] = true;
						if(!visit(olgraph.xlist[j].data))
							return false;
						q.EnQueue(j);
					}
				}
			}
		}
	}
	cout<<endl;
	return true;
}
