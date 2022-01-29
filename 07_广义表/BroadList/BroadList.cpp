#include "BroadList.h" //引用广义表的头文件
#include <string> //引用string库函数的头文件     
using namespace std;//指出后续的所有的程序语句都在名字空间std内

template <class T>
GLists<T>::GLists(string st)
{
	ls=Crtlists(st);
}

template <class T>
GLNode<T>* GLists<T>::Crtlists(string st)
{
  GLNode<T> *ls,*p,*q;
  string sub,hsub;
  if(st == "()")//当广义表st为空时，则ls = NULL
    ls = NULL;
  else
    if(st.length()==1) //当广义表st为单元素时，生成一个元素节点，填入值，并把节点赋给ls
    {
      ls = new GLNode<T> ;
			ls->tag = 0;
			ls->data = st[0];
    }
    else //当广义表st为非空时，进行如下的处理
    {
      ls = new GLNode<T> ;
			ls->tag = 1;   //射出一个表节点作当前节点
      p = ls;sub = st.substr(1,st.length()-2); //去掉字符串两头的"()"
      do // 反复执行这个过程，直到st中成员全处理完毕
      {
        Server(sub,hsub); //从st中取第一成员
        p->ptr.hp = Crtlists(hsub);q=p;
        if(sub!="")
        {
          p = new GLNode<T> ;
					p->tag = 1;
					q->ptr.tp= p;
        };
      }while(sub!="");
      q->ptr.tp = NULL;
    }
    return(ls); 
}


template <class T>
void GLists<T>::Server(string &st,string &hst)
{
  char ch;string sch;
  int i,k,n;
  n=st.length();i=1;k=0;
  do //寻找分界符
  {
    
		sch = st.substr(i-1,1);ch = sch[0];//得到st中的第一字符
    switch(ch) //判断是否为  '(' ')'
    {
      case '(':k++;break;
      case ')':k--;break;
    };
    i++;
  }while(!((i>n)||((ch==',')&&(k==0))));
  if(i<=n)//取第一个成员
  {
    hst = st.substr(0,i-2);
    st = st.substr(i-1,n-i+1);
  }
  else  //扫描结束时还没有碰到',', st全存入hst，st置为空值。
  {
    hst = st;
    st = "";
  };
}

template <class T>
void GLists<T>::Prt(GLNode<T>* ls)
{
  GLNode<T>* p;
  if(ls !=NULL)       //如果ls为空退出，不空执行下面的操作
  {
    if(ls->tag == 1)  //判断节点是不是表节点
    {
      Ena('(');       // 先输出"("
      Prt(ls->ptr.hp);p = ls->ptr.tp; // 再递归调用本过程输出该广义表的第一个成员，
      while(p!=NULL) //重复该过程处理所有其它成员
      {
        Ena(',');    //成员之间加个逗号
        Prt(p->ptr.hp);p = p->ptr.tp;
      };
      Ena(')');
    }
    else // ls指向元素节点时输出元素节点的值
			Ena(ls->data);
	}

}

template <class T>
void GLists<T>::Ena(char ch)
{
  stprt[chnumber]=ch;chnumber++;
}

template <class T>
void GLists<T>:: Setinfo()
{
	chnumber=0;
}

template <class T>
void GLists<T>::Prnt()
{
  Setinfo();
	Prt(ls);
	for(int i=0;i<chnumber;i++)
	cout<<stprt[i];
	cout<<endl;
}

template <class T>
int GLists<T>::DepthGList()
{
	return Depth(ls);
}

template <class T>
int GLists<T>::Depth(GLNode<T>* ls)
{
  if (ls==NULL) return 1;         //空表深度为1
  if (ls->tag==0) return 0;       //单元素深度为0
  int max=0,dep; GLNode<T>*p = ls;
  while (p)
  {
    dep = Depth(p->ptr.hp);      //求以pàptr.hp为头指针的子表即表头的深度
    if (dep>max) max = dep;
    p = p->ptr.tp;              //准备求表尾的深度
  }
  return max+1;                 //非空表的深度是各元素的深度的最大值加1
}

template <class T>
int GLists<T>::Length()
{
  if (ls==NULL) return 0;         //空表长度为0
  int max=1; 
  GLNode<T>*p = ls->ptr.tp;
  while (p)
  {
    max++;
    p = p->ptr.tp;              //准备求表尾的长度
  }
  return max;                
}

template <class T>
GLists<T> * GLists<T>::Head()
{
  GLists<T> * hlists = new GLists<T>;   //生成一个新广义表
  if(ls->tag==1)                //如果ls有表头，则赋值给hlists
    hlists->ls = ls->ptr.hp;
  return (hlists);
}

template <class T>
GLists<T> *GLists<T>::Tail()
{
  GLists<T> * tlists = new GLists<T>;  //生成一个新广义表
  if(ls->tag==1)                     //如果ls有表尾，则赋值给hlists
    tlists->ls = ls->ptr.tp;
  return (tlists);
}

template <class T>
GLists<T>::GLists(GLists ls1, GLists ls2)
{
	GLNode<T> *p,*q,*ls;
  ls = new GLNode<T>;//建立广义表的头指针
  ls->tag = 1;       //设置这个节点为子表
	p = new GLNode<T> ;
	q = new GLNode<T> ;
	*p = *ls1.ls;
	*q = *ls2.ls;
  ls->ptr.hp = p;  //把头指针指向ls1
  ls->ptr.tp = q;  //把尾指针指向ls2
}
