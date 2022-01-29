/*----------------------图的邻接表示存储------------------------*/

#include "SeqStack.h" 
 #include <string> 
#ifndef ALGRAPH
#define ALGRAPH 
#define MAX_VERTEX_NUM 20  //最大顶点数 
struct ArcNode{
	int adjvex;      //该弧所指向的顶点的位置
	struct ArcNode *nextarc; //指向下一条弧的指针
	int *info;       //该弧相关信息的指针(权值)
};

template <class T>
struct VNode{
	T data;    //顶点信息
	ArcNode *firstarc;//指向第一条依附该顶点的指针
};


template <class T>
struct _ALGraph{
	VNode<T> vertices[MAX_VERTEX_NUM];
	int vexnum;
	int arcnum;
	int kind;
};

template <class T>
class ALGraph{
	_ALGraph<T> algraph;
	bool visited[MAX_VERTEX_NUM];
	int ve[MAX_VERTEX_NUM];//各顶点最早发生时间
public:
	void CreateGraph();   //v是图的顶点集 vr是图的边集  //构造函数
    int LocateVex (T u);  //图存在，图中存在顶点u 则返回该顶点在图中的位置
	void DestroyGraph();   //析构函数销毁图
    void DisPlay();    //输出图   
    void FindInDegree(int indegree[]); //求顶点的入度
    bool TopologicalSort(); //若图无回路，则输出图的顶点的一个拓扑序列并返回true，否则返回false
	bool TopologicalOrder(SeqStack<int> &T); // 求各顶点事件的最早发生时间ve
};


template <class T>
int ALGraph<T>::LocateVex(T u)
{
	for(int i = 0;i<algraph.vexnum;i++)
	{
		if(algraph.vertices[i].data == u)
		{
			return i;
		}
	}
	return -1;

}
template <class T>
void ALGraph<T>::CreateGraph()
{
	int i,j,k;
	T v1,v2;
	cout<<"请输入有向图的顶点数，边数: ";
	cin>>algraph.vexnum>>algraph.arcnum;
	cout<<"请输入"<<algraph.vexnum<<"个顶点的值: ";
	for(i = 0;i<algraph.vexnum;i++)
		// 初始化顶点结点
	{
		cin>>algraph.vertices[i].data;
		algraph.vertices[i].firstarc = false;
	}
 
    for(k = 0;k<algraph.arcnum;k++)
	{
		cout<<"请输入一条弧（边）的弧尾、弧头: ";
		cin>>v1>>v2;
        i = LocateVex(v1);
		j = LocateVex(v2);
        ArcNode *p = new ArcNode; //创建一个新的弧结点
		p->adjvex = j; p->nextarc = false;
		p->info = false;
		p->nextarc = algraph.vertices[i].firstarc; //插在表头
		algraph.vertices[i].firstarc = p;
		}
}
template <class T>
void ALGraph<T>::DestroyGraph()
{
	int i;
	ArcNode *p,*q;
	for(i = 0;i<algraph.vexnum;i++)
		//从顶点序号为0的顶点开始依次释放掉相应的邻接表
	{
		p = algraph.vertices[i].firstarc;
		while(p)
		{
			q = p->nextarc;
			delete p;//删除弧结点
			p = q;
		}
	}
	algraph.arcnum = 0;
	algraph.vexnum = 0;
}

template <class T>
void ALGraph<T>::DisPlay()
{
	int i;
	ArcNode *p; 
	cout<<algraph.vexnum<<"个顶点:"<<endl;
	//输出顶点
	for(i = 0;i<algraph.vexnum;i++)
	{
		cout<<algraph.vertices[i].data<<" ";
	}
	cout<<endl;
	cout<<algraph.arcnum<<"条弧（边）:"<<endl;
	for(i = 0;i<algraph.vexnum;i++)
	{
		p = algraph.vertices[i].firstarc;
		while(p)
		{ 
				cout<<algraph.vertices[i].data<<"->"<<algraph.vertices[p->adjvex].data<<'\t';
				 cout<<endl; 
			p = p->nextarc;
		}
	}
}
/*----------------拓扑排序（图采用邻接表存储结构举例表示）--------------*/

template <class T>
void ALGraph<T>::FindInDegree(int indegree[]) 
// 求顶点的入度
{
	int i;
	ArcNode *p;
	for(i = 0;i<algraph.vexnum;i++)
		//初始化indegree
	{
		indegree[i] = 0; 
	}
	for(i = 0;i<algraph.vexnum;i++)
	{
		p = algraph.vertices[i].firstarc;
		while(p)
		{
			indegree[p->adjvex]++;
			p = p->nextarc;
		}
	}
}

template <class T>
bool ALGraph<T>::TopologicalSort()
// 若图无回路，则输出图的顶点的一个拓扑序列并返回true，否则返回false
{
	int i,k,count=0; // 已输出顶点数，初值为0
	int indegree[MAX_VERTEX_NUM]; // 入度数组，存放各顶点当前入度数
	SeqStack<int> S;//创建int型静态栈
	ArcNode *p;
	FindInDegree(indegree); // 对各顶点求入度indegree[] 函数被两个方法公用，所以在ALGraph.h中实现
	for(i = 0;i<algraph.vexnum;i++) 
		// 对所有顶点i
	{
		if(!indegree[i]) 
			// 若其入度为0
		{
			S.Push(i); // 将i入零入度顶点栈S
		}
	}
	while(!S.IsEmpty()) 
		// 当零入度顶点栈S不空
	{
		S.Pop(i); // 出栈1个零入度顶点的序号，并将其赋给i
		cout<<algraph.vertices[i].data<<" "; // 输出i号顶点
		++count; // 已输出顶点数+1
		for(p = algraph.vertices[i].firstarc;p;p = p->nextarc)
			// 对i号顶点的每个邻接顶点
		{ 
			k = p->adjvex; // 其序号为k
			if(!(--indegree[k])) 
				// k的入度减1，若减为0，则将k入栈S
			{
				S.Push(k);
			}
		}
	}
	if(count<algraph.vexnum) 
		// 零入度顶点栈S已空，图G还有顶点未输出
	{
		cout<<"此有向图有回路"<<endl;
		return false;
	}
	else
	{
		cout<<"为一个拓扑序列"<<endl;
		return true;
	}
}
#endif