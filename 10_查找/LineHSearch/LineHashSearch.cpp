#include<iostream>
#include<cmath>
using namespace std;
#define SUCCESS 1;
#define UNSUCCESS 0;
#define NULLKEY -1;
#define TableLength 13;
#define p 13;// H(key)=key % p
            
typedef int T;
template <class T>
struct ElemType
{
	T key;//关键字
	/*     //其它
	....
	*/
};


template <class T>
class LHSearch
{
private:
	ElemType<T> *HT; //开放定址哈希表
	int count; //当前数据元素个数
	int size; //哈希表长度
public:
	 LHSearch(); //
    ~LHSearch(); //
    void InitHashTable(int n);//
    int Hash(T key); //计算哈希地址
	void Collision(int &s);//冲突,计算下一个地址
	int Search(T key,int &s);//哈希查找
	int Insert(ElemType<T> e); //元素插入
	void Display(); //显示哈希表
};

template <class T>
LHSearch<T>::LHSearch()
{
	HT=NULL;
	size=0;
	count=0;
}

template <class T>
LHSearch<T>::~LHSearch()
{ delete [] HT;
  count=0;
}

template <class T>
int LHSearch<T>::Hash(T key)  
{//由哈希函数求哈希地址
	return key%p;
}

template <class T>
void LHSearch<T>::Collision(int &s)
{//开放定址法解决冲突
	s=s++;
}

template <class T>
int LHSearch<T>::Search(T key,int &s)
{//查找，找到返回
	//int s;
	s=Hash(key);
	while((HT[s].key!=-1) && (key!=HT[s].key))
		Collision(s);
	if(HT[s].key==key)
		return 1;
	else 
		return 0;
}

template <class T>
int LHSearch<T>::Insert(ElemType<T> e)
{//插入元素
	int s;
	if(count==size)
	{
		cout<<"表满，不能插入!"<<endl;
		return UNSUCCESS;
	}
	else
	{
		s=Hash(e.key);
		int f;
	    f=Search(e.key,s);
  	    if(f)   //表中已有和e的关键字相同的元素,不进行插入操作
		{
		   cout<<"该元素已存在，不能插入!"<<endl;
		 return UNSUCCESS; 	}
	   else
	   {
		  HT[s].key=e.key;
    	  cout<<"插入成功!"<<endl;
		  count++;
		 return SUCCESS; }
	 }
}

template<class T>
void LHSearch<T>::InitHashTable(int n)
{
	size=n;
	HT=new ElemType<T>[size];
	for(int i=0;i<size;i++) //初始化，把哈希表置空
		HT[i].key=NULLKEY;
}

template<class T>
void LHSearch<T>::Display()
{
	for(int i=0;i<size;i++)
	{
		cout<<i<<'\t';
		if(HT[i].key!=-1)
			cout<<HT[i].key;
        else
			cout<<'\t';
		cout<<endl;
	}
}

void main()
{
	int m;
	T key;
	int s=0;
	ElemType<int> e;
	LHSearch<int> a;
	cout<<"输入相应代码，必须先创建哈希表)\n";
	do { 
	    cout<<"--- 1. 创建查找表  --\n"
		    <<"--- 2. 插入----------\n"
		    <<"--- 3. 查找----------\n"
		    <<"--- 4. 显示 ---------\n"
		    <<"--- 5. 退出 ---------\n"
		    <<"请选择操作:";
	        cin>>m;
			switch(m)
			{
			case 1://创建查找表
				cout<<"请输入表容量：\n";
				cin>>m;
				a.InitHashTable(m);
				cout<<"依次输入表元素，-1结束:\n";
				for(cin>>e.key;e.key!=-1;cin>>e.key)
					a.Insert(e);
				break;
			case 2:  //插入元素
				cout<<"输入元素:\n";
				cin>>e.key;
				a.Insert(e);
				break;
			case 3: //查找
				cout<<"请输入查找关键字：\n";
				cin>>key;
				if(a.Search(key,s))
					cout<<"找到!\n";
				else
					cout<<"不存在，末找到!\n";
				break;
			case 4://显示哈希表
				a.Display();
				break;
	        case 5://
			   cout<<"结束!\n";
			   break;
			}
	}while(m!=5);
}