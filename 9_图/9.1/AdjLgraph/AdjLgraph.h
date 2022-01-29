/*----------------------图的邻接表示存储------------------------*/

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
	VNode<T> vertices[MAX_VERTEX_NUM];//顶点集
	int vexnum;//顶点数
	int arcnum;//边数
	int kind;//图类型
};

/*#ifndef CSNODE
#define CSNODE
template <class T>
struct CSTree{
	//树的二叉链表存储
	T data;
	CSTree *firstchild; //孩子
	CSTree *nextsibling;//兄弟
};
#endif */


template <class T>
class ALGraph{
	_ALGraph<T> algraph;
	bool visited[MAX_VERTEX_NUM];
public:
	void CreateGraph();                                //v是图的顶点集 vr是图的边集 
	void DestroyGraph();                               //销毁图
	int LocateVex (T u);                    //图存在，图中存在顶点u 则返回该顶点在图中的位置
	T GetVex(int index);                    //图存在，index是图中某个顶点的序号 ：返回v的值
	void PutVex(T v,T value);           //图存在，v是图中某个顶点 则对v赋值value
	int FirstAdjVex(T v);                  //图存在，v是G中某个顶点 返回v的第一个临接点的序号 若无领接点则返回空
	int NextAdjVex(T v,T w);          //图存在，v是图中某个顶点，w是v的邻接点 返回v的相对于w的下一个邻接点的序号，若w是v的最后一个邻接点则返回空
	void InsertVex(T v);                   //图存在 在图中增加新顶点v
	bool DeleteVex(T v);                   //图存在   删除顶点v及其相关的弧
	bool InsertArc(T v,T w);          //图存在，V，w是图的两个顶点 在图中添加弧<v，w>若是无向图，则还应增加对称弧<w，v>
	void DeleteArc(T v,T w);          //图存在，V，w是图的两个顶点 在图中删除弧<v，w>若是无向图，则还应删除对称弧<w，v>
	bool (*VisitFunc)(T v);                 //访问顶点v的方式
	void DFS(int index);                        //从第index个顶点出发递归的深度优先遍历图
	bool DFSTraverse(bool (*visit)(T v));  //图存在，对图进行深度优先遍历
	bool BFSTraverse(bool (*visit)(T v));  //图存在，对图进行广度优先遍历
	void DisPlay();             //输出图  
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
	int w;//权值
	T v1,v2;
	cout<<"请输入您要的图的种类!  有向图(0)，有向网(1)，无向图(2)，无向网(3): ";
	cin>>algraph.kind;
	cout<<"请输入图的顶点数，边数: ";
	cin>>algraph.vexnum>>algraph.arcnum;
	cout<<"请输入"<<algraph.vexnum<<"个顶点的值" ;
	for(i = 0;i<algraph.vexnum;i++)
		// 初始化顶点结点
	{
		cin>>algraph.vertices[i].data;
		algraph.vertices[i].firstarc = false;
	}
	if(algraph.kind%2)
	{
		cout<<"请输入每条弧（边）的权值、弧尾、弧头! "<<endl;
	}
	else
	{
		cout<<"请输入每条弧（边）的弧尾、弧头! "<<endl;
	}
	//构造表结点链表
	for(k = 0;k<algraph.arcnum;k++)
	{
		
		if(algraph.kind%2)
		{
			cout<<"请输入一条弧（边）的权值、弧尾、弧头: ";
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
			p->info = new int;
			*(p->info) = w;
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
				p->info = new int;
				*(p->info) = w;
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
T ALGraph<T>::GetVex(int index)
{
	if(index<0||index>=algraph.vexnum)
		return false;
	return algraph.vertices[index].data;
}

template <class T>
void ALGraph<T>::PutVex(T v,T value)
{
	int i = LocateVex(v);
	if(i<0) //该顶点不存在
		return;
	algraph.vertices[i].data = value;
}

template <class T>
int ALGraph<T>::FirstAdjVex(T v)
{
	int i = LocateVex(v);
	ArcNode * p = algraph.vertices[i].firstarc;//p指向下标为i的第一个邻接点
	if(p)
	{
		return p->adjvex;
	}
	else
	{
		return -1;
	}
}

template <class T>
int ALGraph<T>::NextAdjVex(T v,T w)
{
	ArcNode *p;
	int i = LocateVex(v);
	int j = LocateVex(w);
	p = algraph.vertices[i].firstarc;
	while(p&&(p->adjvex!=j))
		//让p指向顶点w
	{
		p = p->nextarc;
	}
	if(!p||!p->nextarc) //没找到w或w是最后一个顶点
		return -1;
	else
		//找到w且w不是最后一个顶点
	{
		return p->nextarc->adjvex;
	}
}

template <class T>
void ALGraph<T>::InsertVex(T v)
{
	if(algraph.vexnum > MAX_VERTEX_NUM)
		return ;//无法插入
	if(LocateVex(v)>=0)
		return;
	algraph.vertices[algraph.vexnum].data = v;
	algraph.vertices[algraph.vexnum].firstarc = false;
	algraph.vexnum++;
}

template <class T>
bool ALGraph<T>::DeleteVex(T v)
{
	if(algraph.vexnum>=MAX_VERTEX_NUM)
		return false;
	int i,j; ArcNode *p,*q;
	i = LocateVex(v);
	if(i<0)
		return false;
	p = algraph.vertices[i].firstarc;
	
	while(p)
		//删除以v为出度的弧或边
	{
		q = p;
		p = p->nextarc;
		if(algraph.kind%2)
			//网
		{
			delete q->info;
		}
		delete q;
		algraph.arcnum--;
	}
	algraph.vexnum--;
	for(j = i;j<algraph.vexnum;j++) 
		//顶点v后面的顶点前移
	{
		algraph.vertices[j] = algraph.vertices[j+1];
	}

	for(j = 0;j<algraph.vexnum;j++)
		//删除以v为入度的弧或边
	{
		p = algraph.vertices[j].firstarc;
		while(p)
			//有弧或边
		{
			if(p->adjvex == i)
				//找到待删结点
			{
				if(p == algraph.vertices[j].firstarc)
					//待删除结点为第一个邻接点
				{
					algraph.vertices[j].firstarc = p->nextarc;
					if(algraph.kind%2)
						//网
					{
						delete p->info;
					}
					delete p;
					p = algraph.vertices[j].firstarc;
					if(algraph.kind<2)
						//有向
					{
						algraph.arcnum--;
					}
				}
				else
				{
					q->nextarc = p->nextarc;
					if(algraph.kind%2)
						//网
					{
						delete p->info;
					}
					delete p;
					p = q->nextarc;
					if(algraph.kind<2)
						//有向
					{
						algraph.arcnum--;
					}
				}
			}
			else
			{
				if(p->adjvex>i)
					//修改表结点的顶点位置序号
				{
					p->adjvex--;
				}
				q = p;
				p = p->nextarc;
			}

		}
	}
	return true;
}


template <class T>
bool ALGraph<T>::InsertArc(T v,T w)
{
	ArcNode *p;
	int i,j;
	int w1;
	i = LocateVex(v);
	j = LocateVex(w);
	if(i<0||j<0)
		return false;
	algraph.arcnum++;
	if(algraph.kind%2)
		//网
	{
		cout<<"请输入弧（边）"<<v<<"->"<<w<<"的权值";
		cin>>w1;
	}
	p = new ArcNode;
	p->adjvex = j; p->nextarc = false;
	if(algraph.kind%2)
		//网
	{
		p->info = new int;
		*(p->info) = w1;
	}
	else
		//图
	{
		p->info = false;
	}
	//插在表头
	p->nextarc = algraph.vertices[i].firstarc;
	algraph.vertices[i].firstarc = p;
	if(algraph.kind>1)//无向
	{
		p = new ArcNode;
	    p->adjvex = i; p->nextarc = false;
		if(algraph.kind == 3)
			//无向网
		{
			p->info = new int;
		    *(p->info) = w1;
		}
		else
			//无向图
		{
			p->info = false;
		}
		//插在表头
		p->nextarc = algraph.vertices[j].firstarc;
	    algraph.vertices[j].firstarc = p;
	}
	return true;
}

template <class T>
void ALGraph<T>::DeleteArc(T v,T w)
{
	ArcNode *p,*q;
	int i,j;
	i = LocateVex(v);
	j = LocateVex(w);
	if(i<0||j<0||i == j)
		return;
	p = algraph.vertices[i].firstarc;
	while(p&&p->adjvex!=j)
		//p不空且q指向的不是待删弧结点
	{
		q = p;
		p = p->nextarc;
	}

	if(p&&p->adjvex ==j)
		//找到弧<v,w>
	{
		if(p == algraph.vertices[i].firstarc)
		{
			algraph.vertices[i].firstarc = p->nextarc;
		}
		else
		{
			q->nextarc = p->nextarc;
		}
		if(algraph.kind%2)
			//网
		{
			delete p->info;
		}
		delete p;
		algraph.arcnum--;
	}
	if(algraph.kind>1)
		//无向则删除对称弧<w，v>
	{
		p = algraph.vertices[j].firstarc;
		while(p&&p->adjvex!=i)
			//p不空且q指向的不是待删弧结点
		{
			q = p;
			p = p->nextarc;
		}
	}
	if(p&&p->adjvex ==i)
		//找到弧<w,v>
	{
		if(p == algraph.vertices[j].firstarc)
		{
			algraph.vertices[j].firstarc = p->nextarc;
		}
		else
		{
			q->nextarc = p->nextarc;
		}
		if(algraph.kind == 3)
			//无向网
		{
			delete p->info;
		}
		delete p;
	}
}

template <class T>
void ALGraph<T>::DFS(int index)
{
	T v1;int i;
	visited[index] = true;//已访问
	VisitFunc(algraph.vertices[index].data);//访问index 的顶点
	v1 = GetVex(index) ;
	for(i = FirstAdjVex(v1);i>=0;i = NextAdjVex(v1,GetVex(i)))
	{
		if(!visited[i])
			DFS(i);
	}
}


template <class T>
bool ALGraph<T>::DFSTraverse(bool (*visit)(T v))
{
	int i ;
    VisitFunc = visit;
   	for(i = 0;i<MAX_VERTEX_NUM;i++)
	{
		visited[i] = false;
	}
    for(i = 0;i<algraph.vexnum;i++)
		//对每个未被访问的顶点进行深度优先遍历
    {
	   if(!visited[i])
		   DFS(i);
    }
	cout<<endl;
    return true;
}


template <class T>
bool ALGraph<T>::BFSTraverse(bool (*visit)(T v))
{
	LinkedQueue<int> q;int i,j,receive; T u1;
	for(i = 0;i<MAX_VERTEX_NUM;i++)
	{
		visited[i] = false;
	}
	for(i = 0;i<algraph.vexnum;i++)
		//对每个未被访问的顶点进行广度优先遍历
	{
		if(!visited[i])
		{
			visited[i] = true;
			if(!visit(algraph.vertices[i].data))
				return false;
			q.EnQueue(i);
			while(!q.IsEmpty())
			{
				q.DeQueue(receive); //对头元素出队并置为receive
				u1= GetVex(receive);
				for(j = FirstAdjVex(u1);j>=0;j = NextAdjVex(u1,GetVex(j)))
				{
					if(!visited[j])
					{
						visited[j] = true;
						if(!visit(algraph.vertices[j].data))
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


