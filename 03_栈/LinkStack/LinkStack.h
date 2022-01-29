//链栈类的定义
template<class T>
struct Node
{
	T data;
	Node<T> *next;//此处T可以省略
};

template<class T>
class LinkStack
{//构建函数，创建一空栈
	private:
		Node<T> *top;//// 链表首为栈顶
	public:
		LinkStack(){top=NULL;}//构造函数，置空链栈
		~LinkStack();// 析构函数，释放链栈中各结点的存储空间
		void Push(T x);// 元素x入栈
		T Pop();// 栈顶元素出栈
		T GetTop();// 取栈顶元素
		int StackEmpty(); // 判断栈是否为空
		void ClearStack();//清空栈
		void StackTranverse();//遍历输出栈中元素
};
//链栈类的实现
template<class T>
LinkStack<T>::~LinkStack()
{//析构函数，销毁栈
	Node<T> *q;
	while(top)//从栈顶开始释放栈链的每一个结点的存储空间
	{
		q=top;//暂存被释放结点
		top=top->next;//头指针后移指向下一个被释放结点
		delete q;
	}
}

template<class T>
void LinkStack<T>::Push(T x)
{//入栈
	Node<T> *s;
	s=new Node<T>;s->data=x;//创建一新结点，数据域为x的结点s
	s->next=top;top=s;//新结点链入表首，为栈顶
}

template<class T>
T LinkStack<T>::Pop()
{//出栈
	T x;
    Node<T> *p;
	if(top==NULL) throw"下溢";
	x=top->data;//暂存栈顶元素
	p=top;top=top->next;//栈顶后移
	delete p;//删除原栈顶结点
	return x;
}


template <class T>
T LinkStack<T>::GetTop()
{//获取栈顶元素
	if(top==NULL) throw "栈空，栈顶无元素";
	return top->data;
}


template <class T>
void LinkStack<T>::ClearStack()
{//清空栈
	while(top)//从栈顶开始释放栈链的每一个结点的存储空间
	{
		Node<T> *q;
		q=top;//暂存被释放结点
		top=top->next;//头指针后移指向下一个被释放结点
		delete q;
	}
}

template <class T>
int LinkStack<T>::StackEmpty()
{//测栈空
	if(top==NULL) 
		return 1;
	else
		return 0;
}


template <class T>
void LinkStack<T>::StackTranverse()
{//从栈顶起，遍历输出栈元素
   Node<T> *p;
   p=top;
   while(p)
   {
     cout<<p->data<<'\t';
	 p=p->next;
   }
   cout<<endl;
 }


