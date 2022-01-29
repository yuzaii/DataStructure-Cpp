//循环单链表类的定义
template<class T>
struct Node
{
	T data;
	Node *next;
};

template <class T>
class CLinkList
{
	private:
		Node<T> *Head;
	public:
		CLinkList() ;//构造函数， 创建空单循环链表
		~CLinkList();//析构函数，删除表空间
		void CreateList(int n);//创建具有n个元素的单循环链表
		void Insert(int i,T e);//在表中第i个位置插入元素
		T Delete(int i);//删除表中第i个元素
		T GetElem(int i);//获取第i个元素的值
		int Locate(T e);//在链表中查找值为e的元素
		T prior(T e);//返回元素e的前驱
		int Empty();//测表空
		int Length();//测表长
		//void CLear();//清空表
		void ListDisplay();//输出表元素
};
//循环单链表类的实现
template<class T>
CLinkList<T>::CLinkList()//构建函数，建一空单循环链表
{
	
	Head=new Node<T>;
	Head->next=Head;
}

template<class T>
CLinkList<T>::~CLinkList()//析构函数，释放链表所占空间
{
	Node<T> *p,*q;
	q=Head;
	while(q->next!=Head)  q=q->next;   //定位q到尾结点 
	while(Head!=Head->next)
	{//从头结点开始，依次释放结点
		p=Head;
		Head=Head->next;
		q->next=Head;
	    delete p;
	}
	Head=NULL;//头结点指向空
}

template<class T>
void CLinkList<T>::CreateList(int n)
{//尾插法(正序)创建具有n个元素的单循环链表
	Node<T> *p,*s;//设置工作指针。p指向尾结点
	p=Head;
	cout<<"请依次输入"<<n<<"个元素值："<<endl;
	for(int i=1;i<=n;i++)
	{
		s=new Node<T>;//新建元素结点
	    cin>>s->data;//输入新建数据元素值
		s->next=p->next;//新结点链入表尾
		p->next=s;
		p=s;
	}
}

template<class T>
void CLinkList<T>::Insert (int i,T e)
{//在指定位置插入元素
	
	int j=0;
	Node<T> *p;
	p=Head;//工作指针初始化
	while(p->next!=Head&& j<i-1)//定位到插入点之前
	{
		p=p->next;//
		j++;
	}
	if(p->next==Head||j>i-1) throw"位置异常";//插入位置不合理，i<0或i>表长
	else
	{
		Node<T> *s;
		s=new Node<T>;//
		s->data=e;//
		s->next=p->next;//结点S链接到p结点之后
		p->next=s;//
	}
}

template <class T>
T CLinkList<T>::Delete (int i)
{//删除指定位置元素
	T x;
	Node<T> *p,*q;//设置工作指针
	p=Head;//查找从头结点开始
	int j=0;//计数器初始化
	while(p->next!=Head && j<i-1)//p定位到删除点的前驱
	{
		p=p->next;//
		j++;
	}
	if(p->next==Head||j>i-1) throw"位置异常";//删除位置不合理
	else  //删除位置合理
	{
		q=p->next;// 暂存删除结点位置
		p->next=q->next;//从链表中摘除删除结点
		x=q->data;//取删除数据元素的值
		delete q;// 释放删除点
		return x;//返回删除元素的值
	}
}

template<class T>
int CLinkList<T>::Locate (T e)
{//按值定位
	int j=1;
	Node<T> *p;
	p=Head->next;
	while(p!=Head && p->data!=e)
	{
		p=p->next;
		j++;
	}
	if(p==Head) return 0;
	else return j;
}


template<class T>
T CLinkList<T>::GetElem(int i)
{//获取第i个元素的值
	Node<T> *p;//设置工作指针
	p=Head->next;//从首结点开始
	int j=1;//计数器初始化
	while(p!=Head&&j<i)//定位到第i个元素结点
	{
		p=p->next;j++;
	}
	if(p==Head||j>i)//定位位置不合理：空表或i小于0或i大于表长
		throw "位置不合理";
	else //位置合理
		return p->data;
}

template<class T>
int CLinkList<T>::Empty()
{//测表空
	if(Head->next==Head)
		return 1;
	else
		return 0;
}

template<class T>
T CLinkList<T>::prior(T e)
{//返回元素前驱
	Node<T> *p,*q;
	p=Head;q=p->next;
	while(q!=Head&&q->data!=e)
	{
		p=q;q=q->next;
	}
	if(p==Head)    //首元素,其前驱为尾元素????
	   throw"首元素，无前驱";
	else if(q==Head)
		throw"元素不存在";		
	else
		return p->data;
		
}

template <class T>
int CLinkList<T>::Length()
{
	int len=0;//
	Node<T> *p;
	p=Head;//指向头结点
	while(p->next!=Head)
	{
		len++;p=p->next;
	}
	return len;
}//Length

template <class T>
void CLinkList<T>::ListDisplay()
{//显示链表
	Node<T> *p;
	p=Head->next;
	int i=1;
	while(p!=Head)
	{
		cout<<i<<"\t";
		cout<<p->data<<endl;
		p=p->next;
		i++;
	}
}


