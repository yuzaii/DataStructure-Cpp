/*--------------------------无向图的邻接多重表表示-----------------------------*/
#include "LinkQueue.h" 
using namespace std;

#define MAX_VERTEX_NUM 20  //最大顶点数
 
#define MAX_INFO 10  //信息的大小 

struct EBox{
	bool mark; //访问标记0未被访问,1已被访问
	int ivex,jvex;//该边依附的两个顶点的位置
	EBox *ilink,*jlink;//分别指向依附这两个顶点的下一条边
	char *info; //该边信息
};

template <class T>
struct VexBox{
	T data; //顶点信息
	EBox *firstedge;//指向第一条依附该顶点的边
};


template <class T>
struct _AMGraph{
	VexBox<T> adjmulist[MAX_VERTEX_NUM];
	int vexnum,edgenum;//顶点数和边数
};


template <class T>
class AMGraph{
	
	_AMGraph<T> amgraph;

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

	bool InsertArc(T v,T w);          //图存在，V，w是图的两个顶点 在图中添加弧<v，w>并增加对称弧<w，v>
		
	bool DeleteArc(T v,T w);          //图存在，V，w是图的两个顶点 在图中删除弧<v，w>并删除对称弧<w，v>
	
	bool (*VisitFunc)(T v);                 //访问顶点v的方式

	void DFS(int index);                        //从第index个顶点出发递归的深度优先遍历图

	bool DFSTraverse(bool (*visit)(T v));  //图存在，对图进行深度优先遍历
		
	bool BFSTraverse(bool (*visit)(T v));  //图存在，对图进行广度优先遍历

	void MarkUnVisited();                       //置边的访问标记为未访问

	void DisPlay();                             //输出图               

};


template <class T>
int AMGraph<T>::LocateVex(T v)
{
	for(int i = 0;i<amgraph.vexnum;i++)
	{
		if(amgraph.adjmulist[i].data == v)
		{
			return i;
		}
	}
	return -1;
}


template <class T>
void AMGraph<T>::CreateGraph()
{
	int i,j,k;	 
	T va,vb;
	EBox *p;
	cout<<"请输入无向图的顶点个数，边的个数 ";
	cin>>amgraph.vexnum>>amgraph.edgenum ;
	cout<<"请输入"<<amgraph.vexnum<<"个顶点的值"<<endl;
	for(i = 0;i<amgraph.vexnum;i++)
	{
		cin>>amgraph.adjmulist[i].data;
		amgraph.adjmulist[i].firstedge = false;
	}
	cout<<"请顺序输入每条边的两个端点"<<endl;
	for(k = 0;k<amgraph.edgenum;k++)
	{
		cin>>va>>vb;
		i = LocateVex(va);
		j = LocateVex(vb);
		p = new EBox;
		p->mark = 0;
		p->ivex = i;
		p->jvex = j;
		p->info = false;
		//插在表头
		p->ilink = amgraph.adjmulist[i].firstedge;
		amgraph.adjmulist[i].firstedge = p;
		//插在表头
		p->jlink = amgraph.adjmulist[j].firstedge;
		amgraph.adjmulist[j].firstedge = p;		 
			p->info = false;//该弧的相关信息
		 
	}
}


template <class T>
T AMGraph<T>::GetVex(int index)
{
	if(index<0||index>=amgraph.vexnum)
		return false;
	return amgraph.adjmulist[index].data;
}


template <class T>
void AMGraph<T>::PutVex(T v,T value)
{
	int i = LocateVex(v);
	if(i<0)
		return;
	amgraph.adjmulist[i].data = value;
}


template <class T>
int AMGraph<T>::FirstAdjVex(T v)
{
	int i = LocateVex(v);
	if(i<0)
		return -1;
	if(amgraph.adjmulist[i].firstedge)
		//v有邻接点
	{
		if(amgraph.adjmulist[i].firstedge->ivex == i)
		{
			return amgraph.adjmulist[i].firstedge->jvex;
		}
		else
		{
			return amgraph.adjmulist[i].firstedge->ivex;
		}
	}
	else
	{
		return -1;
	}
}


template <class T>
int AMGraph<T>::NextAdjVex(T v,T w)
{
	EBox *p;
	int i = LocateVex(v);
	int j = LocateVex(w);
	if(i<0||j<0)
		return -1;
	p = amgraph.adjmulist[i].firstedge;
	while(p)
	{
		if(p->ivex == i&&p->jvex != j)
			//不是邻接点，有两个方向找邻接点
		{
			//方向1
			p = p->ilink;
		}
		else if(p->jvex == i&&p->ivex != j)
		{
			//方向2
			p = p->jlink;
		}
		else
		{
			break;
		}
	}
	if(p&&p->ivex == i&&p->jvex ==j)
		//在方向1找到
	{
		p = p->ilink;
		if(p&&p->ivex == i)
			return p->jvex;
		else if(p&&p->jvex ==i)
			return p->ivex;
	}
	if(p&&p->ivex == j&&p->jvex == i)
		//在方向2找到
	{
		p = p->jlink;
		if(p&&p->ivex == i)
			return p->jvex;
		else if(p&&p->jvex == i)
			return p->ivex;
	}
	return -1;
}


template <class T>
void AMGraph<T>::InsertVex(T v)
{
	if(amgraph.vexnum>=MAX_VERTEX_NUM)
		return;
	if(LocateVex(v)>=0)
		return;
	amgraph.adjmulist[amgraph.vexnum].data = v;
    amgraph.adjmulist[amgraph.vexnum].firstedge = false;
	amgraph.vexnum++;
}

template <class T>
bool AMGraph<T>::DeleteArc(T v,T w)
{
	EBox *p,*q;
	int i = LocateVex(v);
	int j = LocateVex(w);
	if(i<0||j<0||i == j)
		return false;
	//以下使指向待删除边的第一个指针绕过这条边
	p = amgraph.adjmulist[i].firstedge;
	/*------------- 第一条边为待删边---------------*/
	if(p&&p->jvex == j)
		//case 1
	{
		amgraph.adjmulist[i].firstedge = p->ilink;
	}
	else if(p&&p->ivex == j)
		//case 2
	{
		amgraph.adjmulist[i].firstedge = p->jlink;
	}
	/*------------- 第一条边不为待删边---------------*/
	else
	{
		while(p)
			//找弧<v,w>
		{
			if(p->ivex == i&&p->jvex != j)
				//不是待删边
			{
				//case1
				q = p;
				p = p->ilink;
			}
			else if(p->jvex == i&&p->ivex != j)
			{
				//case2
				q = p;
				p = p->jlink;
			}
			else
			{
				//是邻接点w
				break;
			}
		}
		if(!p)
			return false;
		if(p->ivex == i&&p->jvex == j)
			//case 1
		{
			if(q->ivex == i)
				q->ilink = p->ilink;
			else
				q->jlink = p->ilink;
		}
		else if(p->ivex == j&&p->jvex == i)
			//case2
		{
			if(q->ivex == i)
				q->ilink = p->jlink;
			else
				q->jlink = p->jlink;
		}

	}
	//以下从另一顶点起删除待删除边
	p = amgraph.adjmulist[j].firstedge;
	/*------------- 第一条边为待删边---------------*/
	if(p->jvex == i)
		//case 1
	{
		amgraph.adjmulist[j].firstedge = p->ilink;
		if(p->info)
			delete p->info;
		delete p;
	}
	else if(p->ivex == i)
		//case 2
	{
		amgraph.adjmulist[j].firstedge = p->jlink;
		if(p->info)
			delete p->info;
		delete p;
	}
	/*------------- 第一条边不为待删边---------------*/
	else
	{
		while(p)
			//找弧<v,w>
		{
			if(p->ivex == j&&p->jvex != i)
				//不是待删边
			{
				//case1
				q = p;
				p = p->ilink;
			}
			else if(p->jvex == j&&p->ivex != i)
			{
				//case2
				q = p;
				p = p->jlink;
			}
			else
			{
				break;
			}
		}
		if(p->ivex == i&&p->jvex ==j)
			//case 1
		{
			if(q->ivex == j)
				q->ilink = p->jlink;
			else
				q->jlink = p->jlink;
		}
		else if(p->ivex == j&&p->jvex == i)
			//case2
		{
			if(q->ivex == j)
				q->ilink = p->ilink;
			else
				q->jlink = p->ilink;
			if(p->info)
				delete p->info;
			delete p;
		}
	}
    amgraph.edgenum--;
	return true;
}


template <class T>
bool AMGraph<T>::DeleteVex(T v)
{
	int i,j;
	T w;
	EBox *p;
	i = LocateVex(v);
	if(i<0)
		return false;
	for(j = 0;j<amgraph.vexnum;j++)
		//删除存在的与顶点v相连的边
	{
		if(j == i)
			continue;
		w = GetVex(j);
		DeleteArc(v,w);
	}
	//排在顶点v后面的顶点的序号减1
	for(j = i+1;j<amgraph.vexnum;j++)
	{
		amgraph.adjmulist[j-1] = amgraph.adjmulist[j];
	}
	amgraph.vexnum--;
	//修改顶点序号
	for(j = i;j<amgraph.vexnum;j++)
	{
		p = amgraph.adjmulist[j].firstedge;
		while(p)
		{
			if(p->ivex == j+1)
			{
				p->ivex--;
				p = p->ilink;
			}
			else
			{
				p->jvex--;
				p = p->jlink;
			}
		}
	}
	return true;
}


template <class T>
void AMGraph<T>::DestroyGraph()
{
	for(int i = amgraph.vexnum-1;i>=0;i--)
	{
		DeleteVex(amgraph.adjmulist[i].data);
	}
}


template <class T>
bool AMGraph<T>::InsertArc(T v,T w)
{ 	int i = LocateVex(v);
	int j = LocateVex(w);
	if(i<0||j<0)
		return false;
	EBox * p = new EBox;
	p->mark = 0;
	p->ivex = i;
	p->jvex = j;
	p->info = false;

	p->ilink = amgraph.adjmulist[i].firstedge;
    amgraph.adjmulist[i].firstedge = p;
	p->jlink = amgraph.adjmulist[j].firstedge;
	amgraph.adjmulist[j].firstedge = p; 	 
	amgraph.edgenum++;
	return true;
}


template <class T>
void AMGraph<T>::DFS(int index)
{
	int j;
	VisitFunc(amgraph.adjmulist[index].data);
	visited[index] = true;//先访问index
	EBox *p = amgraph.adjmulist[index].firstedge;
	while(p)
	{
		//找下一个按深度访问的顶点
		j = (p->ivex == index) ? p->jvex : p->ivex;
		//未被访问则对其递归深度访问
		if(!visited[j])
			DFS(j);
        p = (p->ivex == index) ? p->ilink :p->jlink;
	}
}



template <class T>
bool AMGraph<T>::DFSTraverse(bool (*visit)(T v))
{
	VisitFunc = visit;
	int i;
	for(i = 0;i<amgraph.vexnum;i++)
		//访问标识向量初始化
	{
		visited[i] = false;
	}
	for(i = 0;i<amgraph.vexnum;i++)
		//对每个顶点进行深度递归
	{
		if(!visited[i])
			DFS(i);
	}
	cout<<endl;
	return true;
}


template <class T>
bool AMGraph<T>::BFSTraverse(bool (*visit)(T v))
{
	int i,receive,j;
	T u;
	for(i = 0;i<amgraph.vexnum;i++)
		//访问标识向量初始化
	{
		visited[i] = false;
	}
	LinkedQueue<int> q;
	for(i = 0;i<amgraph.vexnum;i++)
		//对每个未被访问的顶点进行广度优先遍历
	{
		if(!visited[i])
		{
			visited[i] = true;
			visit(amgraph.adjmulist[i].data);
			q.EnQueue(i);
			while(q.IsEmpty() == false)
			{
				q.DeQueue(receive);
				u = GetVex(receive);
				for(j = FirstAdjVex(u);j>=0;j = NextAdjVex(u,GetVex(j)))
				{
					if(!visited[j])
					{
						visited[j] = true;
						visit(amgraph.adjmulist[j].data);
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
void AMGraph<T>::MarkUnVisited()
{
	EBox *p;
	for(int i = 0;i<amgraph.vexnum;i++)
	{
		p = amgraph.adjmulist[i].firstedge;
		while(p)
		{
			p->mark = 0;
			p = (p->ivex == i) ? p->ilink : p->jlink;
		}
	}
}


template <class T>
void AMGraph<T>::DisPlay()
{
	int i; EBox *p;
	//置边的访问标记为未访问
	MarkUnVisited();
	cout<<amgraph.vexnum<<"个顶点"<<endl;
	for(i = 0;i<amgraph.vexnum;i++)
	{
		cout<<amgraph.adjmulist[i].data<<" ";
	}
	cout<<endl;
	cout<<amgraph.edgenum<<"条边"<<endl;
	for(i = 0;i<amgraph.vexnum;i++)
		//依次从每个顶点出发访问
	{
		p = amgraph.adjmulist[i].firstedge;
		while(p)
		{
			if(p->ivex == i)
				//边的i端与该顶点有关
			{
				if(p->mark == 0)
					//避免重复输出
				{
					cout<<amgraph.adjmulist[i].data<<"<->"<<amgraph.adjmulist[p->jvex].data<<" ";
					p->mark = 1;
					if(p->info)
					cout<<"该边的相关信息"<<p->info<<" ";
					cout<<endl;
				}
				p = p->ilink;
			}
			else
				//边的j端与该顶点有关
			{
				if(p->mark == 0)
					//避免重复输出
				{
					cout<<amgraph.adjmulist[p->ivex].data<<"-"<<amgraph.adjmulist[i].data<<" ";
					p->mark = 1;
					if(p->info)
					cout<<"该边的相关信息"<<p->info<<" ";
					cout<<endl;
				}
				p = p->jlink;
			}
		}
	}
}

