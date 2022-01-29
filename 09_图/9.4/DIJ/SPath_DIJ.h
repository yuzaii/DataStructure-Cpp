/*-------------------从某个源点到其余各个顶点的最短路径（图采用数组存储结构举例表示）---------------*/

#include "ArrayGraph.h"

template <class T>
void MGraph<T>::ShortestPath_DIJ(int v0,PathMatrix_1 &P,ShortPathTable &D)
//用Dijkstra算法求有向网的v0顶点到其余顶点v的最短路径P[v]及带权长度
//D[v]。若P[v][w]为true，则w是从v0到v当前求得最短路径上的顶点。
//final[v]为true当且仅当v∈S，即已经求得从v0到v的最短路径
{ 
	int v,w,i,j,min;
	bool final[MAX_VERTEX_NUM]; // 辅助矩阵，为真表示该顶点到v0的最短距离已求出，初值为假
	for(v = 0;v<mgraph.vexnum;v++)
	{
		final[v] = false; // 设初值
		D[v] = mgraph.arcs[v0][v].adj; // D[]存放v0到v的最短距离，初值为v0到v的直接距离
		for(w = 0;w<mgraph.vexnum;w++)
			// 设空路径
		{
			P[v][w] = false; 
		}
		if(D[v]<infinity) 
			// v0到v有直接路径
		{
			P[v][v0] = P[v][v] = true; // 一维数组p[v][]表示源点v0到v最短路径通过的顶点
		}
	}
	D[v0] = 0; // v0到v0距离为0
	final[v0] = true; // v0顶点并入S集
	for(i = 1;i<mgraph.vexnum;i++) 
		// 其余G.vexnum-1个顶点
	{ 
		// 开始主循环，每次求得v0到某个顶点v的最短路径，并将v并入S集
		min = infinity; // 当前所知离v0顶点的最近距离，设初值为∞
		for(w = 0;w<mgraph.vexnum;w++) 
			// 对所有顶点检查
		{
			if(!final[w]&&D[w]<min) //在S集之外的顶点中找离v0最近的顶点，并将其赋给v，距离赋给min
			{
				v = w;
				min = D[w];
			}
		}
		final[v] = true; // 离v0最近的v并入S集
		for(w = 0;w<mgraph.vexnum;w++) 
			// 根据新并入的顶点，更新不在S集的顶点到v0的距离和路径数组
		{
			if(!final[w]&&min<infinity&&mgraph.arcs[v][w].adj<infinity&&
				(min+mgraph.arcs[v][w].adj<D[w]))
				// w不属于S集且v0→v→w的距离<目前v0→w的距离
			{ 
				D[w] = min+mgraph.arcs[v][w].adj; // 更新D[w]
				for(j = 0;j<mgraph.vexnum;j++) 
					// 修改P[w]，v0到w经过的顶点包括v0到v经过的顶点再加上顶点w
				{
					P[w][j] = P[v][j];
				}
				P[w][w] = true;
			}
		}
	}
}

