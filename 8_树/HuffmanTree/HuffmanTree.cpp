//最优二叉树
#include<iostream>
#include<iomanip>
using namespace std;
//定义结点类型
template <class T>
struct hufnode
{
	T wei;//权值
	int prt;//指向父结点的指针域（结点元素的下标）
	int lch;//左指针域（结点元素的下标）
	int rch;//右指针域（结点元素的下标）
};
//由于数组下标一般是非负数整数，因此可以用-1作为空指针值
template <class T>
class huffman_BT
{
	int nn;//叶子结点的个数
	hufnode<T>*BT;//最优二叉树顺序存储空间的首地址
	public:
		huffman_BT(){BT=NULL;}//构造函数，对最优二叉树进行初始化
		void creat_hufm_BT(int n,T w[]);//生成最优二叉树
		void select(hufnode<T>*p,int k,int *i,int *j);
		void prt_hufm_BT();//输出最优二叉树存储空间状、
};
//生成最优二叉树
template <class T>
void huffman_BT<T>::creat_hufm_BT(int n,T w[])
{//n是叶子结点的个数，w是叶子结点的权值数组
	hufnode<T> *p;
	int k,i,j,m;
	nn=n;
	m=n*2-1;
	BT=new hufnode<T>[m];//申请最优二叉树存储空间
	p=BT;
	for(k=0;k<m;k++)
	{//设置初始状态，所有结点的指针为空
		(p+k)->prt=-1;
		(p+k)->lch=-1;
		(p+k)->rch=-1;
	}
	for(k=0;k<n;k++)
	{//前n个结点的权值分别为个结点的权值
		(p+k)->wei=w[k];
	}
	for(k=n;k<m;k++)
	{//构造最优二叉树
		select(p,k,&i,&j);//在前K-1个结点中选择权值最小的两个根结点i和j
		(p+i)->prt=k;
		(p+j)->prt=k;//合并构成新的二叉树
		(p+k)->lch=i;
		(p+k)->rch=j;
		(p+k)->wei=(p+i)->wei+(p+j)->wei;
	}
}
template <class T>
void huffman_BT<T>::select(hufnode<T>*p,int k,int *i,int *j)
{//在前K-1个结点中选择权值最小的两个根结点i和j
	T w;
	int n=0;
	while(n<k&&(p+n)->prt!=-1)	n++;//寻找指向父结点指针为空的起始结点
	w=(p+n)->wei;
	*i=n;
	while(n<k)
	{
		if((((p+n)->wei)<w)&&((p+n)->prt==-1))
		{
			*i=n;
			w=(p+n)->wei;
			
		}n++;
	}
	n=0;
	while((n<k)&&((p+n)->prt!=-1)||(n==(*i))) n++;
	w=(p+n)->wei;
	*j=n;
	while(n<k)
	{
		if(((p+n)->wei<w)&&(n!=(*i))&&((p+n)->prt==-1))
		{
			*j=n;
			w=(p+n)->wei;
		}
		n++;
	}
	if((*i)>(*j))
	{
		n=(*i);
		*i=*j;
		*j=n;
	}

}
template <class T>
void huffman_BT<T>::prt_hufm_BT()
{
	hufnode <T>*p;
	int k;
	p=BT;
	cout<<"k"<<setw(7)<<"WEI"<<setw(7)<<"PRT"
		<<setw(7)<<"LCH"<<setw(7)<<"RCH"<<endl;
	for(k=0;k<2*nn-1;k++)
	{
		cout<<k<<setw(7)<<(p+k)->wei<<setw(7)<<(p+k)->prt
			<<setw(7)<<(p+k)->lch<<setw(7)<<(p+k)->rch<<endl;
	}
}

void main()
{
	int *w;
	int op;
	int i;
	huffman_BT<int> b;
	do
	{
		cout<<"1-输入结点权值"<<endl;
		cout<<"2-生成最优二叉树"<<endl;
		cout<<"3-退出程序"<<endl;
		cout<<"请选择操作：[ ]";
		cout<<"\b\b";
		cin>>op;
		switch(op)
		{
		case 1:
			cout<<"请输入结点的个数：";
			int sum;
			cin>>sum;
			w=new int[sum];
			cout<<"请依次输入权值："<<endl;
			for(i=0;i<sum;i++)
			{
				cout<<"请输入第"<<i+1<<"个权值：";
				cin>>w[i];
			}
			break;
		case 2:
			b.creat_hufm_BT(sum,w);
			b.prt_hufm_BT();
			system("pause");
			break;
		case 3:
			cout<<"结束运行，Bye-Bye!"<<endl;
			break;
		}
	}while(op!=3);
}
