#include"sqstack.h"
#include<iostream.h>//cout,cin
#include"process.h"//exit()
#include"stdio.h"//EOF,NULL

template <class T>
SqStack<T>::SqStack(int m)
{
	
	base=new T[m];
	if(base==NULL) 
	{
		cout<<"栈创建失败，退出!"<<endl;exit(1);
	}
	stacksize=m;
	top=-1;
}

template <class T>
void SqStack<T>::Push(T x)
{
	if(top==stacksize-1) throw "栈满，无法入栈";
	top++;
	base[top]=x;
}


template <class T>
T SqStack<T>::Pop()
{
	T x;
	if(top==-1) throw "栈空，不能出栈";
	x=base[top--];
	return x;
}

template <class T>
T SqStack<T>::GetTop()
{
	if(top==-1) throw "栈空，栈顶无元素";
	return base[top];
}

template <class T>
int SqStack<T>::StackEmpty()
{
	if(top==-1) 
		return 0;
	else
		return 1;
}

template <class T>
void SqStack<T>::ClearStack()
{
	top=-1;
}

template <class T>
void SqStack<T>::StackTranverse()
{
	int i=top;
   while(i>=0)
     cout<<base[i--]<<'\t';
   cout<<endl;
 }
