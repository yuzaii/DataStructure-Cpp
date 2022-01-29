#include<iostream.h>//cout,cin
#include"process.h"//exit()
#include"stdio.h"//EOF,NULL

typedef int T;  //定义关键字的类型,这里就以整形来处理
//查找表类定义
template <class T>
struct Node
{
	T key;     //关键字域
	/*
	........		//其他域,可以自己根据需要添加	
	*/
};

template <class T>
class SSearch {
private:
	Node<T> *ST;
	int len;//表长
public:	
    SSearch();//
    ~SSearch();//析构函数，删除表空间
	void Create(int n);    //创建时根据用户实际需求,再为相应的数据元素赋值
	void Display();	 //输出静态表中的数据元素
	int SeSearch(T key);	 //从表中最后一个元素开始顺序查找
	void Ascendsort();    //升序排列
	int BiSearch_1(T key);//折半查找，非递归算法
	int BiSearch_2(T key);//折半查找，递归算法
    int BiSearch2(int x,int y,T key);
};

template <class T>
SSearch<T>::SSearch()
{//
	ST=NULL;
	len=0;   
}

template <class T>
SSearch<T>::~SSearch()
{//释放表空间
	delete [] ST;
	len=0; 
}


template <class T>
void SSearch<T>::Create(int n)                            
	{
		len=n;
		ST=new Node<T>[len];
		Node<T> e;
		int i=0;
		cout<<"输入"<<len<<"个数据元素"<<endl;
		while(i<len)
		{
			cin>>e.key;
			ST[i]=e;
			i++;
		}
}

template <class T>
int SSearch<T>::SeSearch(T key)   
{//从表中最后一个元素开始顺序查找，若找到，返回位序，否则，返回-1
	for(int i=len-1;i>=0;i--)
		if(ST[i].key==key)
			{
				cout<<"查找成功!位居第"<<i+1<<endl;
				return i;
			}
		cout<<"末找到!"<<endl;
		return -1;
}


template <class T>
void SSearch<T>::Ascendsort()
	{
		T t;
		for(int i=0;i<len-1;i++)
		{
			for(int j=0;j<len-i-1;j++)
				if(ST[j].key>ST[j+1].key)
				{
					t=ST[j].key;
					ST[j].key=ST[j+1].key;
					ST[j+1].key=t;
				}
		}
	}


template <class T>
int SSearch<T>::BiSearch_1(T key) 
{ //折半查找非递归算法
		if(len==0 && ST==NULL)
		{
			cout<<"顺序表不存在,请先建立表\n";
				return -1;
		}
		else
		{
			int low=0,high=len-1;
			int mid;
			while(low<=high)
			{
				mid=(high+low)/2;
				if(ST[mid].key==key)
				{
					cout<<"找到!位居"<<mid+1<<endl;
					return mid;
				}
				if(ST[mid].key>key)
					high=mid-1;
				else
					low=mid+1;
			}
			cout<<"末找到!"<<endl;
			return -1;
		}
	}

template <class T>
int SSearch<T>::BiSearch2(int x,int y,T key)
{//折半查找递归算法
		int mid=(x+y)/2;
		if(ST[mid].key==key)
			return mid;
		if(x>y)
			return -1;    //表示没有找到
		if(key<ST[mid].key)
			return BiSearch2(x,mid-1,key);
		else
			return BiSearch2(mid+1,y,key);
}//
template <class T>
int SSearch<T>::BiSearch_2(T key)
{
    int k;
    k=BiSearch2(0,len-1,key);
    return k;
}

template <class T>
void SSearch<T>::Display()    
{//输出静态表中的数据元素
		cout<<"静态表中的数据元素关键字依次为:\n";
		for(int i=0;i<len;i++)
		{
			cout<<ST[i].key<<"   ";
		}
		cout<<endl;
}

void main()
{
	int choice,n,k;
	SSearch<int> a;
	cout<<"注意：必须先创建静态表)\n";
	cout<<"=======================\n";
	T key;

		cout<<"--- 1.  创建查找表 ------------------------\n"
	        <<"--- 2.  顺序查找  -------------------------\n"
		    <<"--- 3.  折半查找<递归>----------------------\n"
		    <<"--- 4.  折半查找<非递归> -------------------\n"
		    <<"--- 5.  输出静态表中的所有数据元素关键字----\n"
		    <<"--- 6.  退出 ------------------------- -----\n";
		    
    do
	{	cout<<"请选择操作:";
		cin>>choice;
		switch(choice)
		{
		 case 1://
            cout<<"输入静态查找表的长度"<<endl;
		    cin>>n;			
            a.Create(n);
			break;
		 case 2://
			cout<<"请输入查找关键字："<<endl;
			cin>>key;
		   	a.SeSearch(key);
			break;
		 case 3:
			a.Ascendsort();
			cout<<"输入查找关键字："<<endl;
			cin>>key;
			k=a.BiSearch_2(key);
			if(k==-1)
				cout<<"末找到!"<<endl;
			else
				cout<<"找到!位居第"<<k+1<<endl;
		    break;
		 case 4:
			a.Ascendsort();
            cout<<"输入查找关键字："<<endl;
			cin>>key;
			a.BiSearch_1(key);
		    break;
		 case 5:
			a.Display();
			break;
		 case 6:
		    cout<<"运行结束"<<endl;
		    break;
		 default:
			cout<<"输入代码非法，应在0--7之间"<<endl;
		     cout<<"请继续选择操作";
		    break;
		}//switch
	}while(choice!=6);
}//main
