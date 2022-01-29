// 数组表示法
#include "iostream"
#include "string"
#include "iomanip"
#include "LinkQueue.h"
using namespace std;

#define MAX_VERTEX_NUM 20 //最大顶点数
const int infinity = INT_MAX;

struct ArcCell{
	int adj;    //对无权图有1，0表示是否相邻，对带权图，则为权值类型
    char *info; //该弧的相关信息
};


template <class T>
struct _MGraph{
    T vexs[MAX_VERTEX_NUM];//顶点表
	ArcCell arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//邻接矩阵，即边表
	int vexnum;//顶点数
	int arcnum;//边数
	int kind;//是以邻接矩阵存储的图类型
};


template <class T>
class MGraph{
	_MGraph<T> mgraph;
    bool visited[MAX_VERTEX_NUM];
public:		
	void CreateGraph();                                //v是图的顶点集 vr是图的边集 
	void DestroyGraph();                               //销毁图	 
	int LocateVex (T u);                 //图存在，图中存在顶点u 则返回该顶点在图中的位置
	T GetVex(int index);                 //图存在，index是图中某个顶点的序号 则返回index的顶点
	void PutVex(T v,T value);        //图存在，v是图中某个顶点 则对v赋值value
	int FirstAdjVex(T v);                //图存在，v是G中某个顶点 返回v的第一个临接点的序号 若无领接点则返回空
	int NextAdjVex(T v,T w);         //图存在，v是图中某个顶点，w是v的邻接点 返回v的相对于w的下一个邻接点的序号 若w是v的最后一个邻接点则返回空
	bool InsertVex(T v);                 //图存在 在图中增加新顶点v
	bool DeleteVex(T v);                 //图存在   删除顶点v及其相关的弧
	bool InsertArc(T v,T w);         //图存在，V，w是图的两个顶点 在图中添加弧<v，w>若是无向图，则还应增加对称弧<w，v>
	bool DeleteArc(T v,T w);         //图存在，V，w是图的两个顶点 在图中删除弧<v，w>若是无向图，则还应删除对称弧<w，v>
	bool CreateDG();                         //构造有向图
	bool CreateDN();                         //构造有向网
	bool CreateUDG();                        //构造无向图
	bool CreateUDN();                        //构造无向网
	void DFS(int index);                     //从第index出发递归的深度优先遍历图
	bool (*VisitFunc)(T v);              //访问顶点v的方式
	void DisPlay();                          //输出邻接矩阵
	bool DFSTraverse(bool (*visit)(T v));//图存在，对图进行深度优先遍历
	bool BFSTraverse(bool (*visit)(T v));//图存在，对图进行广度优先遍历

};
template <class T>
bool visit(T v)
{
	cout<<v<<" ";
	return true;
}

template <class T>
void MGraph<T>::CreateGraph()//ok
{
	cout<<"请输入您要的图的种类!  有向图(0)，有向网(1)，无向图(2)，无向网(3)";
	cin>>mgraph.kind;
	switch(mgraph.kind)
	{
	case 0 :CreateDG();break;
	case 1 :CreateDN();break;
	case 2:CreateUDG();break;
	case 3:CreateUDN();break;
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
T MGraph<T>::GetVex(int index)//ok
{
	if(index<0||index>=mgraph.vexnum)
		return false;//越界返回空
	return mgraph.vexs[index];
}

template <class T>
void MGraph<T>::PutVex(T v,T value)//ok
{
	int index = LocateVex(v);
	if(index<0)
		return;
	mgraph.vexs[index] = value;
}

template <class T>
bool MGraph<T>::CreateDG()//ok
//构造有向图
{
	  int i , j ;T v1,v2;
	cout<<"请输入有向图的顶点个数，弧的个数: ";
	cin>>mgraph.vexnum>>mgraph.arcnum;
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
			mgraph.arcs[i][j].adj = 0;
            mgraph.arcs[i][j].info = false;
		}
	}
	for(i = 0;i<mgraph.arcnum;i++)
	//构造邻接矩阵
	{
		cout<<"请输入一条弧的起点,终点: ";
		cin>>v1>>v2;
		int m = LocateVex(v1);
		int n = LocateVex(v2);
		mgraph.arcs[m][n].adj = 1;// <v1, v2>
	}
	mgraph.kind = 0;
	return true;
}

template <class T>
bool MGraph<T>::CreateDN()//ok
//构造有向网
{
	  int i,j ,w;T v1, v2;
	cout<<"请输入有向网的顶点个数，弧的个数: ";
	cin>>mgraph.vexnum>>mgraph.arcnum;
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
		cout<<"请输入一条弧的起点,终点,权值";
		cin>>v1>>v2>>w;
		int m = LocateVex(v1);
		int n = LocateVex(v2);
		mgraph.arcs[m][n].adj = w;// <v1, v2>的权值
	}
	mgraph.kind = 1;
	return true;
}


template <class T>
bool MGraph<T>::CreateUDG()//ok
//构造无向图
{
	  int i , j ;T v1, v2;
	cout<<"请输入无向图的顶点个数，边的个数: ";
	cin>>mgraph.vexnum>>mgraph.arcnum;
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
			mgraph.arcs[i][j].adj = 0;
            mgraph.arcs[i][j].info = false;
		}
	}
	for(i = 0;i<mgraph.arcnum;i++)
	//构造邻接矩阵
	{
		cout<<"请输入一条边依附的两个顶点: ";
		cin>>v1>>v2 ;
		int m = LocateVex(v1);
		int n = LocateVex(v2);
		mgraph.arcs[m][n].adj = 1;// <v1, v2>
        mgraph.arcs[n][m].adj = 1;// <v2, v1>
	}
	mgraph.kind = 2;
	return true;
}

template <class T>
bool MGraph<T>::CreateUDN()//ok
//构造无向网
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
		cout<<"请输入一条边依附的两个顶点、权值: ";
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
int MGraph<T>::FirstAdjVex(T v)//ok
{
	int temp = LocateVex(v); int j = 0;
	if(mgraph.kind==1||mgraph.kind==3)
		j = infinity;
	for(int i = 0 ;i<mgraph.vexnum;i++)
	{
		if(mgraph.arcs[temp][i].adj!=j)
		{
			return i;
		}
	}
	return -1; //无邻接点返回空
}


template <class T>
int MGraph<T>::NextAdjVex(T v,T w)//ok
{
	int id_v = LocateVex(v);
	int id_w = LocateVex(w);
	int j = 0;
	if(mgraph.kind==1||mgraph.kind==3)
		j = infinity;
	for(int i = id_w+1;i<mgraph.vexnum;i++)
	{
		if(mgraph.arcs[id_v][i].adj!=j)
		{
			return i;
		}
	}
	return -1;
}


template <class T>
bool MGraph<T>::InsertVex(T v)//ok
{
	if(mgraph.vexnum>=MAX_VERTEX_NUM)
		return false;
	if(LocateVex(v)>=0)
		return false;
	mgraph.vexs[mgraph.vexnum] = v;
	for(int i = 0;i<=mgraph.vexnum;i++)
	{
		if(mgraph.kind%2)
		//网
		{
			mgraph.arcs[mgraph.vexnum][i].adj = infinity; //底下一行
			mgraph.arcs[i][mgraph.vexnum].adj = infinity; //右边一行
		}
		else
		//图
		{
			mgraph.arcs[mgraph.vexnum][i].adj = 0; //底下一行
			mgraph.arcs[i][mgraph.vexnum].adj = 0; //右边一行
		}
		mgraph.arcs[mgraph.vexnum][i].info = false;
		mgraph.arcs[i][mgraph.vexnum].info = false;
	}
	mgraph.vexnum++;
	return true;
}


template <class T>
bool MGraph<T>::InsertArc(T v,T w)//ok
{
	int v1,w1,weight ;
	v1 = LocateVex(v);
	w1 = LocateVex(w);
	if(v1<0||w1<0)
		return false;
	mgraph.arcnum++;
	if(mgraph.kind%2)//网
	{
		cout<<"请输入此弧或边的权值";
		cin>>weight;
		mgraph.arcs[v1][w1].adj = weight;
	}
	else//图
	{
		mgraph.arcs[v1][w1].adj = 1;
	}

	if(mgraph.kind>1) //无向
	{
		mgraph.arcs[w1][v1].adj = mgraph.arcs[v1][w1].adj;
        mgraph.arcs[w1][v1].info = mgraph.arcs[v1][w1].info;//公用一块内存

	}
	return true;
}


template <class T>
bool MGraph<T>::DeleteVex(T v)//ok
{
	int delpos,vrtype = 0,i,j;
	delpos = LocateVex(v);
	if(delpos<0)
		return false;
	if(mgraph.kind%2)
		vrtype = infinity;
	for(i = 0;i<mgraph.vexnum;i++)
	{
		if(mgraph.arcs[i][delpos].adj != vrtype)
		//有入弧或边
		{
			if(mgraph.arcs[i][delpos].info != false)
				//删除信息
			{
				delete [](mgraph.arcs[i][delpos].info);
                mgraph.arcs[i][delpos].info = false;
				mgraph.arcs[delpos][i].info = false;
			}
			mgraph.arcnum--;
		}
	}

	if(mgraph.kind<2)//有向
	{
		 for(j = 0;j<mgraph.vexnum;j++)
		 {
			 if(mgraph.arcs[delpos][j].adj != vrtype)
				 //有出弧
			 {
				 if(mgraph.arcs[delpos][j].info)
				 {
					 delete []mgraph.arcs[delpos][j].info;
					 mgraph.arcs[delpos][i].info = false;
				 }
				 mgraph.arcnum--;
			 }
		 }
	}
	for(i = delpos+1;i<mgraph.vexnum;i++)
		//序号delpos后的顶点向量依次次前移
	{
		mgraph.vexs[i-1] = mgraph.vexs[i];
	}
	for(i = 0;i<mgraph.vexnum;i++)
	{
		for(j = delpos+1;j<mgraph.vexnum;j++)
			//移动删除顶点之右的矩阵元素
		{
			mgraph.arcs[i][j-1] = mgraph.arcs[i][j];
		}
	}
	for(i = 0;i<mgraph.vexnum;i++)
	{
		for(j = delpos+1;j<mgraph.vexnum;j++)
			//移动待删除顶点之下的矩阵元素
		{
		    mgraph.arcs[j-1][i] = mgraph.arcs[j][i];
		}
	}
	mgraph.vexnum--;
	return true;
}

template <class T>
bool MGraph<T>::DeleteArc(T v,T w)//ok
{
	int v1,w1;
	v1 = LocateVex(v);
	w1 = LocateVex(w);
	if(v1<0||w1<0)
		return false;
	if(mgraph.kind%2 == 0)
		//图
	{
		mgraph.arcs[v1][w1].adj = 0;
	}
	else
		//网
	{
		mgraph.arcs[v1][w1].adj = infinity;
	}
	if(mgraph.arcs[v1][w1].info)
	{
		delete []mgraph.arcs[v1][w1].info;
		mgraph.arcs[v1][w1].info = false;
	}
	if(mgraph.kind>1)
		//无向，删除<w,v>
	{
		mgraph.arcs[w1][v1].adj = mgraph.arcs[v1][w1].adj;
		mgraph.arcs[w1][v1].info = false;
	}
	mgraph.arcnum--;
	return true;
}

template <class T>
void MGraph<T>::DisPlay()
{
	int i,j;
	char graphkind[7];
	char arckind[3];
	switch(mgraph.kind)
	{
	case 0:strcpy(graphkind,"有向图");
		   strcpy(arckind,"弧");
		   break;
	case 1:strcpy(graphkind,"有向网");
		   strcpy(arckind,"弧"); 
		   break;
	case 2:strcpy(graphkind,"无向图");
		   strcpy(arckind,"边");
		   break;
	case 3:strcpy(graphkind,"无向网");
		   strcpy(arckind,"边");
		   break;
	}
	cout<<mgraph.vexnum<<"个顶点"<<mgraph.arcnum<<"条"<<arckind<<"的"<<graphkind<<endl;
	//输出顶点
	cout<<"顶点为";
	for(i = 0;i<mgraph.vexnum;i++)
	{
		cout<<mgraph.vexs[i]<<" ";
	}
	//输出权值的邻接矩阵
	cout<<"权值的邻接矩阵为: "<<endl;
	for(i = 0;i<mgraph.vexnum;i++)
	{
		for(j = 0;j<mgraph.vexnum;j++)
		{
			if(mgraph.arcs[i][j].adj==infinity)
				cout<<setw(5)<<"∞"<<'\t';
			else
				cout<<setw(5)<<mgraph.arcs[i][j].adj<<'\t';
		}
		cout<<endl<<endl;
	}
}


template <class T>
void MGraph<T>::DFS(int index)
//从第index个顶点出发递归地深度优先遍历图
{
	T v1;int i;
	visited[index] = true;//已访问
	VisitFunc(mgraph.vexs[index]);//访问index 的顶点
	v1 = GetVex(index);
	for(i = FirstAdjVex(v1);i>=0;i = NextAdjVex(v1,GetVex(i)))
	{
		if(!visited[i])
			DFS(i);//对v的尚未访问的邻接顶点w递归调用DFS
	}
}

template <class T>
bool MGraph<T>::DFSTraverse(bool (*visit)(T v))
{
	int i ;
    VisitFunc = visit;
   	for(i = 0;i<MAX_VERTEX_NUM;i++)
	{
		visited[i] = false;
	}
    for(i = 0;i<mgraph.vexnum;i++)
		//对每个未被访问的顶点进行深度优先遍历
    {
	   if(!visited[i])
		   DFS(i);
    }
	cout<<endl;
    return true;
}

template <class T>
 bool MGraph<T>::BFSTraverse(bool (*visit)(T v))
{
	LinkedQueue<int> q;int i,j,receive; T u1;
	for(i = 0;i<MAX_VERTEX_NUM;i++)
	{
		visited[i] = false;
	}
	for(i = 0;i<mgraph.vexnum;i++)
		//对每个未被访问的顶点进行广度优先遍历
	{
		if(!visited[i])
		{
			visited[i] = true;
			if(!visit(mgraph.vexs[i]))
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
						if(!visit(mgraph.vexs[j]))
							return false;
						q.EnQueue(j);
					}
				}
			}
		}
	}
	cout<<endl;
	return true;

}; 

//菜单 
void ShowOper()
{
	cout<<endl;
	cout<<"0.  建立图"<<endl;
	cout<<"1.  返回顶点v在图中的位置"<<endl;
	cout<<"2.  返回所需位置的顶点的值"<<endl;
	cout<<"3.  改变某个已知顶点v的值"<<endl;
	cout<<"4.  在图中增加新顶点v"<<endl;
	cout<<"5.  在图中删除顶点v以及所有和顶点v相关联的边或弧"<<endl;
	cout<<"6.  在图中增添一条从顶点v到顶点w的边或弧"<<endl;
	cout<<"7.  在图中删除一条从顶点v到顶点w的边或弧"<<endl;
	cout<<"8.  在图中，从第一个顶点出发深度优先遍历图"<<endl;
	cout<<"9.  在图中，从第一个顶点广度优先遍历图"<<endl;
    cout<<"10. 显示图"<<endl;
	cout<<"11. 销毁图"<<endl;
	cout<<"12. 退出"<<endl;
	cout<<"请选择你要的操作: "<<endl;
}

void main()
{
	int opchoice;
	MGraph<string> g;//case0
    g.CreateGraph();
	do
	{   ShowOper();
		cin>>opchoice;
   	   switch(opchoice)
			{
				case 0:
					{
						g.CreateGraph();
						cout<<endl;
						break;
					}
				case 1:
					{
						string a;
						cout<<"请输入您要的所要查询位置的顶点的名称 ";
						cin>>a;
						cout<<"顶点"<<a<<"在图中的位置为"<<g.LocateVex(a)<<endl;
						cout<<endl;
						break;
					}
				case 2:
					{
						int index;
						cout<<"请输入您要的所要查询顶点的位置";
						cin>>index;
						cout<<"位置为"<<index<<"的顶点为"<<g.GetVex(index)<<endl;
						cout<<endl;
						break;
					}
				case 3:
					{
						string v;
						 string value;
						cout<<"请输入您要的所要更改的顶点的值";
						cin>>v;
						cout<<"请输入您要的所要更改的顶点的新值";
						cin>>value;
						g.PutVex(v,value);
						cout<<endl;
						break;
					}
				case 4:
					{
						string v;
						cout<<"请输入您所要增加的顶点的值";
						cin>>v;
						g.InsertVex(v);
						cout<<endl;
						break;
					}
				case 5:
					{
						string v;
						cout<<"请输入您所要删除的顶点的值";
						cin>>v;
						g.DeleteVex(v);
						g.DisPlay();
						cout<<endl;
						break;
					}
				case 6:
					{
						string v,w;
						cout<<"请输入您所要增添一条从顶点v到顶点w的边或弧的顶点v和顶点w";
						cin>>v>>w;
						g.InsertArc(v,w);
						cout<<endl;
						break;
					}
				case 7:
					{
						string v,w;
						cout<<"请输入您所要删除一条从顶点v到顶点w的边或弧的顶点v和顶点w";
						cin>>v>>w;
						g.DeleteArc(v,w);
						cout<<endl;
						break;
					}
				case 8:
					{
						cout<<"从第一个顶点出发深度优先遍历图的序列为"<<endl;
						g.DFSTraverse(visit);
						cout<<endl;
						break;
					}
				case 9:
					{
						cout<<"从第一个顶点出发广度优先遍历图的序列为"<<endl;
						g.BFSTraverse(visit);
						cout<<endl;
					break;
					}
				case 10:
					{
						g.DisPlay();
						cout<<endl;
						break;
					}
				case 11:
					{
						g.DestroyGraph();
						cout<<endl;
						break;
					}
				case 12:
					cout<<"结束运行，Bye-Bye!"<<endl;
					break;
				default:
					cout<<"选择不合理，请重选!"<<endl;
			}//case
		}while(opchoice!=12);
}//main
		 