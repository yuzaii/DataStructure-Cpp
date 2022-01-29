#include<iostream.h>//cout,cin
#include"process.h"//exit()
#include"stdio.h"//EOF,NULL
#include"SqStack.h"

template<class T>
void convert(T n,T m)
{//把十进制数n转换为m进制数
	T e;
	char c;
	SqStack<int> s(10);
	cout<<"需转换的十进制数是："<<n<<endl;
	while(n)
	{
		try
		{ 
			s.Push(n%m);}
		catch(char *err)
			{ cout<<err<<endl;	 }
		n=n/m;
	}
	cout<<"转换为"<<m<<"进制数为：";
	while(!s.StackEmpty())
	{
		try
			{    e=s.Pop ();
		         if(e<10)
					 cout<<e<<'\t';  
				 else 
				 {
					 c='A'+e-10;
					 cout<<c<<'\t'; 
				 }
		}
	    catch(char *err)
		   {   cout<<err<<endl;  }
	}//
	cout<<endl;
}
void main()
{
	int n,m;//分别存放被转换的数及转换数制
	char ans; //工作变量，存放是否继续的应答
	int flag=1;//工作变量，是否继续的标志
	while(flag)
	{
		cout<<"输入需转换的十进制数: ";
	    cin>>n;
	    cout<<"输入需转换的数制: ";
	    cin>>m;
	    convert(n,m);
		cout<<"继续吗(Y/N)？"<<endl;
		cin>>ans;
		if(ans=='Y'||ans=='y') 
			flag=1;
		else 
		{
			flag=0;
			cout<<"程序运行结束，BYe-Bye!"<<endl;
		}
	}//while
}//main