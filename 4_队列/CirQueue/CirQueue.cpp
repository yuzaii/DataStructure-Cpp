

template <class T> //
class CirQueue
{
	private:
		T *base;// 存储空间基址
		int front;// 队头指针
		int rear;// 队尾指针
		int queuesize;// 队容量
	public:
		CirQueue(int m);//构造空队列
		~CirQueue();// 析构函数，释放链队各结点的存储空间
		void EnQueue(T x);// 元素x入队
		T DeQueue();// 队顶元素出队
		T GetHead();// 取队头元素
		T GetLast();//取队尾元素
		int QueueEmpty(); // 判队空
		int QueueFull();//判队满
		void ClearQueue();//清空队
		void QueueTranverse();//遍历队，输出队列元素
};


template <class T>
CirQueue<T>::CirQueue(int m)//构造函数
{//创建一空队
	base=new T[m];
	if(base==NULL) 
	{
		cout<<"队创建失败，退出!"<<endl;
		exit(1);
	}
	front=rear=0;
	queuesize=m;
}

template <class T>
CirQueue<T>::~CirQueue()//析构函数
{//释放队列所占存储空间
	delete [] base;
	rear=0;
	front=0;
	queuesize=0;
}

template <class T>
void CirQueue<T>::EnQueue(T x)
{//元素入队
	if((rear+1)%queuesize==front) throw "上溢，无法入队";
	base[rear]=x;
	rear=(rear+1)%queuesize;
	cout<<"入队成功，新队尾为："<<rear<<endl;
}

template <class T>
T CirQueue<T>::DeQueue()
{
	T x;
	if(front==rear) throw "下溢，不能出队";
	x=base[front];
	front=(front+1)%queuesize;
	cout<<"出队成功，新队头为："<<front<<endl;
	return x;
}

template <class T>
T CirQueue<T>::GetHead()
{
	T x;
	if(front==rear) throw "队空，队顶无元素";
	x=base[front];
    cout<<"取队头元素成功，队头为："<<front<<endl;
	return x;
}

template <class T>
T CirQueue<T>::GetLast()
{
	T x;
	if(front==rear) throw "队空，队顶无元素";
	x=base[rear-1];
	cout<<"取队尾元素成功，队尾为："<<rear<<endl;
	return x;
}


template <class T>
int CirQueue<T>::QueueEmpty()
{
	if(front==rear) 
		return 1;
	else
		return 0;
}

template <class T>
int CirQueue<T>::QueueFull()
{
	if((rear+1)%queuesize==front)
		return 1;
	else
		return 0;
}

template <class T>
void CirQueue<T>::ClearQueue()
{
	front=rear=0;
}

template <class T>
void CirQueue<T>::QueueTranverse()
{
	int i=front;
   while(i!=rear)
   {
     cout<<base[i]<<'\t';
	 i=(i+1)%queuesize;
   }
   cout<<endl;
}