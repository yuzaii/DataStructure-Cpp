#ifndef __BROADLIST_H_
#define __BROADLIST_H_
#include <string> //引用string库函数的头文件  
using namespace std; //指出后续的所有的程序语句都在名字空间std内

template <class T>
struct  GLNode
{
    int  tag;                //标志域，用于区分元素结点和表结点
    T data;                  //data是元素结点的数据域
    struct atom
    {
      GLNode *hp, *tp;       //hp和tp分别指向表头和表尾
    } ptr;

};

template <class T>
class GLists
{
public:
  GLists(){ls = NULL;}//无参构造函数，初始化为空的广义表
  GLists(string st);//有参构造函数，按广义表的书面格式建立广义表的存储结构
  GLists(GLists ls1, GLists ls2);   //有参构造函数，用表头ls1和表尾ls2构造广义表
  ~GLists(){delete [] ls;}   //析构函数，释放广义表中各结点的存储空间
  int DepthGList();   //求广义表的深度
  int Length(); //求广义表的长度
  GLists<T> *Head();  //求广义表的表头
  GLists<T> *Tail();   //求广义表的表尾
  void Prnt(); //将广义表显示出来
private:
  GLNode<T>* ls;  //ls是指向广义表的头指针
  GLNode<T>* Crtlists(string st);//把广义表的书面格式st转化为广义表的头尾存储结构
  void Server(string &st,string &hst); // 从st中取出第一成员存入到hst，其余的成员留在st中
  void Ena(char ch);//存储广义表的输出信息
  int Depth(GLNode<T>* ls);   //求广义表的深度
  char stprt[50];//显示一些操作信息
  int chnumber;
  void  Setinfo();//初始化广义表的信息
  void Prt(GLNode<T>* ls);//将ls所指的广义表显示出来
};
#endif

