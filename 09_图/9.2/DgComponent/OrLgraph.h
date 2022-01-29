/*--------------------------有向图的十字链表存储表示-----------------------------*/
#include <string>
  
#define MAX_VERTEX_NUM 20  //最大顶点数  
//#define MAX_INFO 10  //信息的大小 

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
	T finished[MAX_VERTEX_NUM ];
public:
	
	void CreateGraph();                          //v是图的顶点集 vr是图的边集 

	void DestroyGraph();                         //销毁图

	int LocateVex (T u);                    //图存在，图中存在顶点u 则返回该顶点在图中的位置

	 

	int FirstAdjVex(T v);                  //图存在，v是G中某个顶点 返回v的第一个临接点的序号 若无领接点则返回空

	int NextAdjVex(T v,T w);          //图存在，v是图中某个顶点，w是v的邻接点 返回v的相对于w的下一个邻接点的序号，若w是v的最后一个邻接点则返回空

	 
	
//	bool (*VisitFunc)(T v);                 //访问顶点v的方式 
	void DisPlay();                             //输出图 
  void  Get_SGraph( ); //求十字链表结构储存的有向图G的强连通分量
 void   DFS1(  int v);//第一次深度优先遍历的算法 
 void  DFS2(  int v);//第二次逆向的深度优先遍历的算法

};
 int count; //count在第一次深度优先遍历中用于指示finished数组的填充位置
template <class T>
 void OLGraph<T>::Get_SGraph( ) //求十字链表结构储存的有向图G的强连通分量
{   int v,i,j; 
	string w; 
		for (v=0;v<olgraph.vexnum;++v) visited[v]=false;
		for(v=0;v<olgraph.vexnum;++v) 
			if(!visited[v])	DFS1( v);
		 finished[count]=olgraph.xlist[v].data ;  
        for (v=0;v<olgraph.vexnum;++v) visited[v]=false;
		cout<<"有向图的强连通分量"<<endl;
		j=0;
		for( i=olgraph.vexnum-1;i>=0;--i) //第二次逆向的深度优先遍历
		{ //T w;
			w=finished[i]; 
			v=LocateVex(w); 
			if(!visited[v])
			{   j=j+1;  
				cout<<endl<<"第"<<j<<"个强连通分量:"<<endl ; //不同的强连通分量在不同的行输出
				DFS2( v);
			}
		}//for
}//Get_SGraph 
 template <class T>
 void OLGraph<T>:: DFS1( int v)//第一次深度优先遍历的算法 
{   ArcBox *p;
    int w;
	visited[v]=true;
	 
	for(p=olgraph.xlist[v].firstout;p;p=p->tlink)
	{
		w=p->headvex;
		if(!visited[w]) DFS1( w);
	}//for
	finished[count++ ]=olgraph.xlist[v].data ; //在第一次遍历中建立finished数组
	
}//DFS1 
 template <class T>
 void OLGraph<T>:: DFS2(  int v)//第二次逆向的深度优先遍历的算法
 {      ArcBox *p;
        int w;
		visited[v]=true;
		cout<<olgraph.xlist[v].data<<"  "  ; //在第二次遍历中输出结点序号
		for(p=olgraph.xlist[v].firstin;p;p=p->hlink)
		{
			w=p->tailvex;
			if(!visited[w]) DFS2(w);
		}//for
}//DFS2


template <class T>
int OLGraph<T>::LocateVex(T u) //图存在，图中存在顶点u 则返回该顶点在图中的位置
{
	for(int i = 0;i<olgraph.vexnum;i++)
	{
		if(olgraph.xlist[i].data == u)
			return i;
	}
	return -1;
}

template <class T>
void OLGraph<T>::CreateGraph()//v是图的顶点集 vr是图的边集 
{
	int i,j,k;	 
	ArcBox *p;
	T v1,v2;
    cout<<"请输入有向图的顶点个数，弧的个数: ";
	cin>>olgraph.vexnum>>olgraph.arcnum ;
	cout<<"请输入"<<olgraph.vexnum<<"个顶点的值: "<<endl;
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
void OLGraph<T>::DestroyGraph()//销毁图
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
int OLGraph<T>::FirstAdjVex(T v) //图存在，v是G中某个顶点 返回v的第一个临接点的序号 若无领接点则返回空
{
	int i = LocateVex(v);
	ArcBox *p = olgraph.xlist[i].firstout;
	if(p)
		return p->headvex;
	else
		return -1;
}

template <class T>
int OLGraph<T>::NextAdjVex(T v,T w)//图存在，v是图中某个顶点，w是v的邻接点 返回v的相对于w的下一个邻接点的序号，若w是v的最后一个邻接点则返回空
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
void OLGraph<T>::DisPlay()//显示图
{
	ArcBox *p;
	cout<<"共"<<olgraph.vexnum<<"个顶点"<<olgraph.arcnum<<"条弧"<<endl;
	for(int i = 0;i<olgraph.vexnum;i++)
	{
		cout<<"顶点"<<olgraph.xlist[i].data<<"：入度：";
		p = olgraph.xlist[i].firstin;
		if (!p ) cout<<"无"<<" ";
		while(p)
		{
			cout<<olgraph.xlist[p->tailvex].data<<" ";
			p = p->hlink;
		}
		cout<<"出度：";
		p = olgraph.xlist[i].firstout;
       if (!p ) cout<<"无"<<" ";
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



