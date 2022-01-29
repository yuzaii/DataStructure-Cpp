/*---------------数组表示法(部分代码)--------------*/


#include <iostream>
using namespace std;

#ifndef MGRAPH
#define MGRAPH
 
#define MAX_VERTEX_NUM 20 //最大顶点数
  
const int infinity = INT_MAX;

struct ArcCell{
	int adj;    //对无权图有1，0表示是否相邻，对带权图，则为权值类型
    char *info; //该弧的相关信息
};

template <class T>
struct _MGraph{
    T vexs[MAX_VERTEX_NUM];
	ArcCell arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum;
	int arcnum;
	int kind;
};

typedef int PathMatrix_1[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 路径矩阵，二维数组
typedef int ShortPathTable[MAX_VERTEX_NUM]; // 最短距离表，一维数组


typedef int PathMatrix_2[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 3维数组
typedef int DistancMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 2维数组



template <class T>
class MGraph{
public:		
	_MGraph<T> mgraph;
    bool visited[MAX_VERTEX_NUM];
   void CreateGraph();                                //v是图的顶点集 vr是图的边集  //构造函数
	void DestroyGraph();                               //析构函数销毁图
	int LocateVex (T u);                 //图存在，图中存在顶点u 则返回该顶点在图中的位置
	bool CreateDN();                         //构造有向网
	bool CreateUDN();                        //构造无向网
	bool (*VisitFunc)(T v);              //访问顶点v的方式
	void DisPlay();                          //输出邻接矩阵
	void ShortestPath_DIJ(int v0,PathMatrix_1 &P,ShortPathTable &D); 
	void ShortestPath_FLOYD(PathMatrix_2 &P,DistancMatrix &D);
};


template <class T>
void MGraph<T>::CreateGraph()//ok
{
	cout<<"请输入您要的图的种类!   有向网(0)， 无向网(1)";
	cin>>mgraph.kind;
	switch(mgraph.kind)
	{ 
	case 0 :CreateDN();break; 
	case 1:CreateUDN();break;
	default: {cout<<"输入图的种类错误"<<endl; MGraph();}
	}
}

template <class T>
void MGraph<T>::DestroyGraph()//ok
{
	if(mgraph.kind<2)
		//有向
	{
		for(int i = 0 ;i<mgraph.vexnum;i++)
			for(int j = 0;j<mgraph.vexnum;j++)
			{
				if(mgraph.arcs[i][j].info)
				{
					delete []mgraph.arcs[i][j].info;
					mgraph.arcs[i][j].info = false;
				}
			}
	}
	else
        //无向
	{
		for(int i = 0 ;i<mgraph.vexnum;i++)
			for(int j = i+1;j<mgraph.vexnum;j++)
			{
				if(mgraph.arcs[i][j].info)
				{
					delete []mgraph.arcs[i][j].info;
					mgraph.arcs[i][j].info = mgraph.arcs[j][i].info = false;
				}
			}
	}
	mgraph.vexnum = 0;
	mgraph.arcnum = 0;
}


 

 

template <class T>
bool MGraph<T>::CreateDN()//ok
//构造有向网
{
	 int i,j ,w;
	 T v1, v2;
	cout<<"请输入有向网的顶点个数，弧的个数: ";
	cin>>mgraph.vexnum>>mgraph.arcnum ;
	cout<<"请输入各个顶点: ";
	for(i = 0;i<mgraph.vexnum;i++)
	//构造顶点向量
	{
		cin>>mgraph.vexs[i];
	}
	for(i = 0;i<mgraph.vexnum;i++)	
	//初始化邻接矩阵
	{
		for(j = 0;j<mgraph.vexnum;j++)
		{
			if(i==j)
				mgraph.arcs[i][j].adj = 0;
			else
			    mgraph.arcs[i][j].adj = infinity;
            mgraph.arcs[i][j].info = false;
		}
	}
	for(i = 0;i<mgraph.arcnum;i++)
	//构造邻接矩阵
	{
		cout<<"请输入一条弧的起点,终点,权值: ";
		cin>>v1>>v2>>w;
		int m = LocateVex(v1);
		int n = LocateVex(v2);
		mgraph.arcs[m][n].adj = w;// <v1, v2>的权值
		 
	}
	mgraph.kind = 0;
	return true;
}

template <class T>
bool MGraph<T>::CreateUDN()//ok
//构造无向网
{
	  int i , j ,w;
	  T v1, v2;
	cout<<"请输入无向网的顶点个数，边的个数: ";
	cin>>mgraph.vexnum>>mgraph.arcnum ;
	cout<<"请输入各个顶点 ";
	for(i = 0;i<mgraph.vexnum;i++)
	//构造顶点向量
	{
		cin>>mgraph.vexs[i];
	}
	for(i = 0;i<mgraph.vexnum;i++)	
	//初始化邻接矩阵
	{
		for(j = 0;j<mgraph.vexnum;j++)
		{
			if(i==j)
				mgraph.arcs[i][j].adj = 0;
			else
				mgraph.arcs[i][j].adj = infinity;
            mgraph.arcs[i][j].info = false;
		}
	}
	for(i = 0;i<mgraph.arcnum;i++)
	//构造邻接矩阵
	{
		cout<<"请输入一条边依附的两个顶点,权值: ";
		cin>>v1>>v2>>w;
		int m = LocateVex(v1);
		int n = LocateVex(v2);
		mgraph.arcs[m][n].adj = w;// <v1, v2>
        mgraph.arcs[n][m].adj = w;// <v2, v1>
		 
	}
	mgraph.kind = 1;
	return true;
}

template <class T>
int MGraph<T>::LocateVex(T u)//ok
{
	for(int i = 0 ;i<MAX_VERTEX_NUM;i++)
	{
		if(u == mgraph.vexs[i])
		{
			return i;
		}
	}
	return -1;
}
  

template <class T>
void MGraph<T>::DisPlay()
{
	int i,j;
	char graphkind[7];
	char arckind[3];
	switch(mgraph.kind)
	{
	case 0:strcpy(graphkind,"有向网");
		   strcpy(arckind,"弧"); 
		   break; 
	case 1:strcpy(graphkind,"无向网");
		   strcpy(arckind,"边");
		   break;
	}
	cout<<mgraph.vexnum<<"个顶点"<<mgraph.arcnum<<"条"<<arckind<<"的"<<graphkind<<endl;
	//输出顶点
	cout<<"顶点为";
	for(i = 0;i<mgraph.vexnum;i++)
		cout<<mgraph.vexs[i]<<" ";
	//输出权值的邻接矩阵
	cout<<"权值的邻接矩阵为"<<endl;
	for(i = 0;i<mgraph.vexnum;i++)
	{
		for(j = 0;j<mgraph.vexnum;j++)
			if(mgraph.arcs[i][j].adj==infinity)
				cout<<"∞"<<'\t';
			else
				cout<<mgraph.arcs[i][j].adj<<'\t';
		cout<<endl;
	}//for
}
#endif
