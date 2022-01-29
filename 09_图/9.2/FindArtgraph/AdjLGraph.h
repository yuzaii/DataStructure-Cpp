/*----------------------图的邻接表示存储------------------------*/
// #include "CSTree.h"

#ifndef ALGRAPH
#define ALGRAPH


#ifndef MAX_VERTEX_NUM 
#define MAX_VERTEX_NUM 20  //最大顶点数
#endif


struct ArcNode{
	int adjvex;      //该弧所指向的顶点的位置
	struct ArcNode *nextarc; //指向下一条弧的指针
	char *info;       //该弧相关信息的指针
};


template <class T>
struct VNode{
	T data;    //顶点信息
	ArcNode *firstarc;//指向第一条依附该顶点的指针
};

template <class T>
struct _ALGraph{
	VNode<T> vertices[MAX_VERTEX_NUM];//顶点集
	int vexnum;//顶点数
	int arcnum;//边数
	int kind;//图类型
};



template <class T>
class ALGraph{
	
public:
	_ALGraph<T> algraph;
	int visited[MAX_VERTEX_NUM];
    int count;  //在关节点和重连通分量中对访问计数
	int low[MAX_VERTEX_NUM]; 
	void CreateGraph();                                  //v是图的顶点集 vr是图的边集  //构造函数
	void DestroyGraph();                                 //函数销毁图
	int LocateVex (T u);                    //图存在，图中存在顶点u 则返回该顶点在图中的位置
	void DisPlay();             //输出图
	bool (*VisitFunc)(T v);                 //访问顶点v的方式
	void DFSArticul(int index); //从第index个顶点出发深度优先遍历图，找到并输出关节点
	void FindArticul();   //查找并输出G上全部关节点
};

template <class T>
int ALGraph<T>::LocateVex(T u) //图存在，图中存在顶点u 则返回该顶点在图中的位置
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
void ALGraph<T>::CreateGraph()//创建图
{
	int i,j,k;
	char w[10];//权值
	T v1,v2;
	cout<<"请输入您要的图的种类!  有向图(0)，有向网(1)，无向图(2)，无向网(3)";
	cin>>algraph.kind;
	cout<<"请输入图的顶点数，边数: ";
	cin>>algraph.vexnum>>algraph.arcnum;
	cout<<"请输入"<<algraph.vexnum<<"个顶点的值: ";
	for(i = 0;i<algraph.vexnum;i++)
		// 初始化顶点结点
	{
		cin>>algraph.vertices[i].data;
		algraph.vertices[i].firstarc = false;
	}
	if(algraph.kind%2)
	{
		cout<<"请输入每条弧（边）的权值(小于10个字符)、弧尾、弧头: "<<endl;
	}
	else
	{
		cout<<"请输入每条弧（边）的弧尾、弧头: "<<endl;
	}
	//构造表结点链表
	for(k = 0;k<algraph.arcnum;k++)
	{
		
		if(algraph.kind%2)
		{
			cout<<"请输入一条弧（边）的权值(小于10个字符)、弧尾、弧头: ";
			cin>>w>>v1>>v2;
		}
		else
		{
			cout<<"请输入一条弧（边）的弧尾、弧头: ";
			cin>>v1>>v2;
		}
		i = LocateVex(v1);
		j = LocateVex(v2);
        ArcNode *p = new ArcNode; //创建一个新的弧结点
		p->adjvex = j; p->nextarc = false;
		if(algraph.kind%2)
			//网
		{
			p->info = new char[strlen(w)+1];
			strcpy(p->info,w);
		}
		else
			//图
		{
			p->info = false;
		}
		p->nextarc = algraph.vertices[i].firstarc; //插在表头
		algraph.vertices[i].firstarc = p;
		
		if(algraph.kind>1)
			//无向
		{
			ArcNode *p = new ArcNode; //创建一个新的弧结点
			p->adjvex = i; p->nextarc = false;
			if(algraph.kind == 3)
				//无向网
			{
				p->info = new char[strlen(w)+1];
				strcpy(p->info,w);
			}
			else
				//无向图
			{
				p->info = false;
			}
			p->nextarc = algraph.vertices[j].firstarc; //插在表头
			algraph.vertices[j].firstarc = p;
		}
	}
}


template <class T>
void ALGraph<T>::DestroyGraph()//函数销毁图
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
			if(algraph.kind%2)
				//网,则释放权值信息
			{
				delete p->info;
			}
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
	switch(algraph.kind)
	{
	case 0:cout<<"有向图"<<endl;
		   break;
	case 1:cout<<"有向网"<<endl;
		   break;
	case 2:cout<<"无向图"<<endl;
		   break;
	case 3:cout<<"无向网"<<endl;
		   break;
	}
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
			if(algraph.kind<2)
				//有向
			{
				cout<<algraph.vertices[i].data<<"->"<<algraph.vertices[p->adjvex].data<<'\t';
				if(algraph.kind == 1)
					//有向网
				{
					cout<<*(p->info);
				}
				cout<<endl;
			}
			else
				//无向
			{
				if(i<p->adjvex)
					//避免了无向的时候一条边被输出两次
				{
					cout<<algraph.vertices[i].data<<"-"<<algraph.vertices[p->adjvex].data<<'\t';
					if(algraph.kind == 3)
						//无向网
					{
						cout<<*(p->info);
					}
					cout<<endl;
				}
			}
			p = p->nextarc;
		}
	}
} 
#endif