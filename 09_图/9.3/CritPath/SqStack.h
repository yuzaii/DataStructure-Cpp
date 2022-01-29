/*------------------------------------顺序存储栈类---------------------------------*/
//#include "Stack.h"

#ifndef SEQLIST
#define SEQLIST
const int LIST_INIT_SIZE = 100;
const int LISTINCREAM  =  10;

template <class T>
class SeqStack{
	protected:
		T       *base;//栈底指针

		T        *top;//栈顶指针

		int stacksize;//栈大小

	public:
		SeqStack(int _stacksize = 100);

		~SeqStack();

		void ClearStack();

		bool IsEmpty() const;

		int GetLength() const;

		T *GetTop() const;

		bool Push(T &elem) ;

		bool Pop(T &elem);

		bool StackTraverse(bool (*Visit)(T &elem)) ;
};


template <class T>
SeqStack<T>::SeqStack(int _stacksize)
{
	if(_stacksize<=0) exit(1);
	stacksize=_stacksize;
	base = new T[stacksize];
	if(!base) return;
	top=base;
}


template <class T>
SeqStack<T>::~SeqStack()
{
	if(base)
		delete base;
}


template <class T>
void SeqStack<T>::ClearStack()
{
	if(base)
		top=base;
}


template <class T>
bool SeqStack<T>::IsEmpty() const
{
	return ((top-base)==0)?true:false;
}


template <class T>
int SeqStack<T>::GetLength() const
{
    return top-base;
}


template <class T>
T *SeqStack<T>::GetTop() const
{
	//if(top==base) exit(1);
	//return *(top-1);
	return top;
}


template <class T>
bool SeqStack<T>::Push(T &elem)
{
	if(top-base>=stacksize)
	{
		T *newbase = new T[stacksize+LISTINCREAM];//创建新的存储空间
		if(!newbase) return false;
		int length = GetLength();
		while(length)//内容复制
		{
			newbase[length-1]=base[length-1];
			length--;
		}
		delete base; //删除原有的存储空间
		base=newbase;
		top = base +stacksize; //stacksize为原有长度;
		stacksize+=LISTINCREAM; //大小改变

	}
	*top++=elem;
	return true;
}


template <class T>
bool SeqStack<T>::Pop(T &elem)
{
	if(top==base) return false;
	elem=*--top;
	return true;
}


template <class T>
bool SeqStack<T>::StackTraverse(bool (*Visit)(T &elem)) //从栈底到栈顶一次遍历
{
    T *temp=base;
	while(temp!=top)
	{
		if(!Visit(*temp))
			return false;
		temp++;
	}
	return true;
}
#endif