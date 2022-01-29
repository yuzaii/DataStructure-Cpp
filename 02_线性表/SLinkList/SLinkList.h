//静态链表的类定义
template <class T>
class SLinkList
{
	private:
		struct Tcomp
		{
			T data;
			int cur;
		};
		Tcomp *sls;//存储数据元素的一维数组
		int av;//备用链表表头
		int sl;//静态链表表头
		int maxlen;//链表可能的最大长度
	public:
		SLinkList(int maxsz=100);//构造函数， 创建长度为maxsz的空表
		~SLinkList();//析构函数，删除表空间
		void CreateList(int n);//创建具有n个元素的链表
		void Insert(int i,T e);//在表中第i个位置插入元素
		T Delete(int i);//删除表中第i个元素
		T GetElem(int i);//获取第i个元素的值
		int Locate(T e);//在表中查找值为e的元素
		int Empty();//测表空
		int Full();//测表满
		int Length();//测表长
		void Clear();//清空表
		void ListDisplay();//输出表元素
};
//静态链表类的实现
template<class T>
SLinkList<T>::SLinkList(int maxsz):maxlen(maxsz)//构造函数，创建长度为maxsz的空表
{//分配空间并将所分配的空间链成一个备用链表，链头由av指向，链尾由－1表示；
	//将表示静态链表表头的sl设置为－1
	sls=new Tcomp[maxlen];
	sl=-1;
	for(int i=0;i<maxlen;i++)  sls[i].cur=i+1;
	sls[maxlen-1].cur=-1;
	av=0;
	
}

template<class T>
SLinkList<T>::~SLinkList()//析构函数，释放链表所占空间
{
	delete[] sls;
}

template<class T>
void SLinkList<T>::CreateList(int n)//创建具有n个元素的链表
{
	int value;
	if(n>maxlen) throw"参数非法";
	cout<<"请依次输入"<<n<<"个元素值："<<endl;
	for(int i=1;i<=n;i++)
	{
		cin>>value;
		Insert(i,value);
	}
}


template<class T>
void SLinkList<T>::Insert (int i,T e)
{//在指定位置插入元素
	int m,j=0,k;
	m=av;
	if(av==-1) throw"备用链表为空";
	av=sls[av].cur;
	if(sl==-1)   //在空表中插入
	{
		sls[m].data=e;
		sls[m].cur=-1;
		sl=m;
	}
	else if(i==1)//插入在表头
		{
			sls[m].data=e;
			sls[m].cur=sl;
			sl=m;		
		}
	else
	{
		k=sl;    //找前驱结点k，插入在k结点之后
		while(j<i-1 && k!=-1)
		{
			j++;
			if(j<i-1)   k=sls[k].cur;
		}
		if(j!=i-1) throw"位置异常";
		sls[m].data=e;
		sls[m].cur=sls[k].cur;
		sls[k].cur=m;
	}
}

template <class T>
T SLinkList<T>::Delete (int i)
{//删除指定位置元素
	int m,j=0,k;
	
	if(sl==-1)  throw"静态链表为空";
	else if(i==1)  //删除链头
	{
		m=sl;
		sl=sls[sl].cur;
		sls[m].cur=av;
		av=m;
		return sls[m].data;
	}
	else
	{
		k=sl;   //找前驱结点k，删除k结点后的结点
		while(j<i-1  && k!=-1)
		{
			j++;
			if(j<i-1)  k=sls[k].cur;
		}
		if(j!=i-1)  throw"位置异常";
		m=sls[k].cur;
		sls[k].cur=sls[m].cur;
		sls[m].cur=av;
		av=m;   //空结点插入av链
		return sls[m].data;
	}
}

template<class T>
int SLinkList<T>::Locate (T e)
{//求元素e在静态链表中的序号
	int k=sl,j=0;
	while(k!=-1 && sls[k].data!=e)
	{
		k=sls[k].cur;
		j++;
	}
	if(k==-1) return -1;
	else return j+1;
}

template<class T>
void SLinkList<T>::Clear()
{
	sl=-1;
	for(int i=0;i<maxlen;i++)  sls[i].cur=i+1;
	sls[maxlen-1].cur=-1;
	av=0;

}

template<class T>
T SLinkList<T>::GetElem(int i)
{//获取第i个元素的值
	int k,j=0;
	k=sl;
	while(j<i && k!=-1)
	{
		j++;
		if(j<i) k=sls[k].cur;
	}
	if(j==i) return(sls[k].data);
	else throw"位置异常";
}

template<class T>
int SLinkList<T>::Empty()
{//测表空
    if(sl==-1)
		return 1;
	else
		return 0;
}

template<class T>
int SLinkList<T>::Full()
{//测表满
	if(av==-1)
		return 1;
	else
		return 0;
}


template <class T>
int SLinkList<T>::Length()
{
	int k,len=0;//
	k=sl;
	while(k!=-1)
	{
		len++;
		k=sls[k].cur;
	}
	return len;
}//Length

template <class T>
void SLinkList<T>::ListDisplay()
{//显示链表
	int k,i=1;
	k=sl;
	while(k!=-1)
	{
		cout<<i<<"\t";
		cout<<sls[k].data<<endl;
		k=sls[k].cur;
		i++;
	}
}

