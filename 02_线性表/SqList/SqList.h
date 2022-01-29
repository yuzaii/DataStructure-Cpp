//类的定义
template <class T>
class SqList   //顺序表类
{
	private:
		T *elem; //表首址
		int length; //表长
		int listsize;//表容量
	public:
		SqList(int m) ;//构造函数， 创建容量为m的空表
		~SqList();//析构函数，删除表空间
		void CreateList(int n);//创建具有n个元素的线性表
		void Insert(int i,T e);//在表中第i个位置插入元素
		T Delete(int i);//删除表中第i个元素
		T GetElem(int i);//获取第i个元素的值
		int Locate(T e);//元素定位
		void Clear();//清空表
		int Empty();//测表空
		int Full();//测表满
		int Length();//测表长
		void ListDisp();//输出表元素
};
//类的实现
template<class T>
SqList<T>::SqList(int m)
{//构建函数，创建一表容量为m的空表
	elem=new T[m];// 申请表空间
	length=0;// 空表，表长为0
	listsize=m;//表容量为m
}

template<class T>
SqList<T>::~SqList()//析构函数
{//释放表空间
	delete [] elem;
	length=0; 
	listsize=0; 
}

template<class T>
void SqList<T>::CreateList(int n)
{//创建表长度为n的顺序表
	if(n>listsize) throw"参数非法";
	cout<<"请依次输入"<<n<<"个元素值："<<endl;
	for(int i=1;i<=n;i++)
	   cin>>elem[i-1];
	length=n;
}

template<class T>
void SqList<T>::Insert (int i,T e)
{// 在第i个位置插入元素，如不能插入，显示异常信息
	if(length>=listsize) throw "上溢";
	if(i<1||i>length+1) throw "插入位置异常";
	for(int j=length;j>=i;j--)
		elem[j]=elem[j-1];
	elem[i-1]=e;
	length++;
}

template <class T>
T SqList<T>::Delete (int i)
{// 删除表中第i个位置元素，如不能删除，显示异常信息。
	T x;
	if(length==0) throw "下溢";
	if(i<1||i>length+1) throw "删除位置异常";
	x=elem[i-1];
	for(int j=i;j<length;j++)
		elem[j-1]=elem[j];
	length--;
	return x;
}

template<class T>
int SqList<T>::Locate (T e)
{// 元素定位，若找到，返回该元素在表中的位序；末找到，返回0。
	for(int i=0;i<length;i++)
		if(elem[i]==e) return i+1;
		return 0;
}

template<class T>
void SqList<T>::Clear()
{//把表清空
	length=0;
}

template<class T>
T SqList<T>::GetElem(int i)
{//获取第i个元素的值
	T e;
	if(i<1||i>length) throw "位置不合法";
	e=elem[i-1];
	return e;
}

template<class T>
int SqList<T>::Empty()
{//判表空。若空，返回1；否则，返回0
	if(length==0)
		return 1;
	else
		return 0;
}

template<class T>
int SqList<T>::Full()
{//判表满。若满，返回1；否则，返回0
	if(length==listsize)
		return 1;
	else
		return 0;
}


template <class T>
int SqList<T>::Length()
{//返回表长
	return length;
}

template <class T>
void SqList<T>::ListDisp()
{//显示表内容
	for(int i=0;i<length;i++)
	{
		cout<<elem[i]<<"\t";
		
	}
	cout<<endl;
}