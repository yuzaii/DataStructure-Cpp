//顺序栈类定义
template <class T> 
class SqStack
{
	private:
		T *base;//栈底指针
		int top;//栈顶
		int stacksize;//栈容量
	public:
		SqStack(int m);//构建函数
		~SqStack(){delete [] base;top=0;stacksize=0;}//析构函数
		void Push(T x);//入栈
		T Pop();//出栈
		T GetTop();//获取栈顶元素
		int StackEmpty();//测栈空
		void ClearStack();//清空栈
		void StackTop();//返回栈顶指针
		void StackTranverse();//显示栈中元素
};
//顺序栈类实现
template <class T>
SqStack<T>::SqStack(int m)
{
	
	base=new T[m];
	if(base==NULL) 
	{
		cout<<"栈创建失败，退出!"<<endl;
		exit(1);
	}
	stacksize=m;
	top=-1;
}

template <class T>
void SqStack<T>::Push(T x)
{//入栈
	if(top==stacksize-1) throw "栈满，无法入栈";
	top++;
	base[top]=x;
}


template <class T>
T SqStack<T>::Pop()
{//出栈
	T x;
	if(top==-1) throw "栈空，不能出栈";
	x=base[top--];
	return x;
}

template <class T>
T SqStack<T>::GetTop()
{//获取栈顶元素
	if(top==-1) throw "栈空，栈顶无元素";
	return base[top];
}

template <class T>
int SqStack<T>::StackEmpty()
{//测栈空
	if(top==-1) 
		return 1;
	else
		return 0;
}

template <class T>
void SqStack<T>::ClearStack()
{//清空栈
	top=-1;
}

template <class T>
void SqStack<T>::StackTop()
{//返回栈顶指针
	cout<<"栈顶top= "<<top;
}

template <class T>
void SqStack<T>::StackTranverse()
{//从栈顶起遍历栈
	int i=top;
   while(i>=0)
     cout<<base[i--]<<'\t';
   cout<<endl;
 }