/*---------------最小生成树（图采用数组存储结构举例表示）----------*/
//#include "MGraph.h"
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

#ifndef MGRAPH
#define MGRAPH
 
#define MAX_VERTEX_NUM 20 //最大顶点数 
 
#define MAXEDGE 190 //图中的最大边数
const int infinity = INT_MAX;

struct ArcCell{
	int adj;    //对无权图有1，0表示是否相邻，对带权图，则为权值类型
    char *info; //该弧的相关信息
};


template <class T>
	struct miniside{
		//记录从顶点集U到顶点集V-U的代价最小的边的辅助数组定义
		T adjvex;
		int lowcost;
	};

template <class T>
	struct EdgeType{
		T v1;
		T v2;
		int cost;
	};

template <class T>
	struct _MGraph{
		T vexs[MAX_VERTEX_NUM];
		ArcCell arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
		int vexnum;
		int arcnum;
		int kind;
	};

template <class T>
	class MGraph{

		_MGraph<T> mgraph;

		bool visited[MAX_VERTEX_NUM];

	public:	
		bool  CreateUDN();                    //创建无向图   
	    int Minimum(miniside<T> *SZ);        //求辅助数组sz中的lowcost的最小正值
        int LocateVex (T u);                 //图存在，图中存在顶点u 则返回该顶点在图中的位置
		void DisPlay();						//显示图
		void MiniSpanTree_PRIM(T u);         //用普利姆算法从顶点u开始构造网的最小生成树，并输出各条边
        void DestroyGraph();                      //析构函数销毁图
	};
template <class T>
void MGraph<T>::DisPlay()
{
	int i,j;	 
	 
	//输出权值的邻接矩阵
	cout<<"无向网的邻接矩阵为"<<endl;
	for(i = 0;i<mgraph.vexnum;i++)
	{
		for(j = 0;j<mgraph.vexnum;j++)
		{	if (mgraph.arcs[i][j].adj==infinity)
				cout<<setw(15)<<"∞"<<'\t';
			else
				cout<<setw(15)<<mgraph.arcs[i][j].adj<<'\t';
		}
		cout<<endl<<endl;
	}
}



template <class T>
bool MGraph<T>::CreateUDN()  //构造无向网
{
	  int i , j ,w;T v1, v2;
	cout<<"请输入无向网的顶点个数，边的个数: ";
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
	mgraph.kind = 3;
	return true;
}
template <class T>
void MGraph<T>::DestroyGraph()//销毁图
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
	 
	mgraph.vexnum = 0;
	mgraph.arcnum = 0;
}

template <class T>
int MGraph<T>::LocateVex(T u)//确定顶点在图中的位置
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
	int MGraph<T>::Minimum(miniside<T> SZ[MAX_VERTEX_NUM])
	//求辅助数组sz中的lowcost的最小正值
	{
		int i = 0,min,k,j;
		while(!SZ[i].lowcost)
		{
			i++;
		}
		min = SZ[i].lowcost;//找到第一个非0值
		k = i;//k先存放第一个非0值的位置
		for(j = i+1;j<mgraph.vexnum;j++)
			//在第一个非0值之后开始依次寻找较小值并且记录位置
		{
			if(SZ[j].lowcost>0)
			{
				if(min>SZ[j].lowcost)
					//找到较小值
				{
					min = SZ[j].lowcost;
					k = j;//记录较小值的位置
				}
			}
		}
		return k;
	}

template <class T>
	void MGraph<T>::MiniSpanTree_PRIM(T u) 	//用普利姆算法从顶点u开始构造网的最小生成树，并输出各条边
	{
		int i,j,k;
		miniside<T> closedge[MAX_VERTEX_NUM];
		k = LocateVex(u);
		for(j = 0;j<mgraph.vexnum;j++)
			//初始化辅助数组
		{
			if(j != k)
			{
				closedge[j].adjvex = u;
				closedge[j].lowcost = mgraph.arcs[k][j].adj;
			}
		}
		closedge[k].lowcost = 0 ;//初始化顶点集 U = {u}
		cout<<"最小生成树的各条边依次为："<<endl;
		for(i = 1;i<mgraph.vexnum;i++)
			//期许mgraph.vexnumge-1个顶点
		{
			k = Minimum(closedge);//求出下一个结点的位置
			cout<<closedge[k].adjvex<<"-"<<mgraph.vexs[k]<< "权值："<<closedge[k].lowcost <<endl;
			closedge[k].lowcost = 0;//将位置为k的顶点并入u集合
			for(j = 0;j<mgraph.vexnum;j++)
				//新顶点并入u集后重新选择最小边
			{
				if(mgraph.arcs[k][j].adj<closedge[j].lowcost)
				{
					closedge[j].adjvex = mgraph.vexs[k];
					closedge[j].lowcost = mgraph.arcs[k][j].adj;
				}
			}
		}
}
#endif

