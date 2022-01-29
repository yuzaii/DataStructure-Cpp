//第十章 内部排序
#include<iostream>
using namespace std;

template<class type>
struct SqList{
	type * key;
	int length;
};
template<class type>
void CreateSqList(SqList<type> &sl)//type为int
{
	int n;
	cout<<"建立顺序表"<<endl<<"请输入顺序表的长度"<<endl;
	cin>>n;
	sl.length=n;
	sl.key=new int[sl.length+1];
	assert(sl.key);
	cout<<"请输入数据："<<endl;
	for(int i=1;i<=sl.length;i++)
	{
		cin>>sl.key[i];
	}
}
template<class type>
void OutPut(SqList<type> &L)
{
	for(int j=1;j<=L.length;++j)
		cout<<L.key[j]<<"\t";
	cout<<endl;
}
//一（1）插入排序
template<class type>
void InsertSort(SqList<type> & L)
{//对顺序表L作直接插入排序
	for(int i=2;i<=L.length;i++)
		if(L.key[i]<=L.key[i-1])//"<"需将L.key[i]插入有序子表
		{
			L.key[0]=L.key[i];//复制为哨兵
			L.key[i]=L.key[i-1];
			for(int j=i-2;L.key[0]<=L.key[j];--j)
				L.key[j+1]=L.key[j];//记录后移
			L.key[j+1]=L.key[0];//插入到正确位置
		}
}
//（2）折半插入排序
template<class type>
void BInsertSort(SqList<type> &L)
{//对顺序表L作折半插入排序
	int high,low,m;
	for(int i=2;i<=L.length;i++)
	{
		L.key[0]=L.key[i];//将L.key[i]暂存到L.key[0]
		low=1;
		high=i-1;
		while(low<=high)//在key[low]到key[high]中折半查找有序插入的位置
		{
			m=(low+high)/2;//折半
			if(L.key[0]<=L.key[m])
				high=m-1;//插入低半区
			else 
				low=m+1;//插入高半区
		}
		for(int j=i-1;j>=high+1;--j)
			L.key[j+1]=L.key[j];      //记录后移
			L.key[high+1]=L.key[0];   //插入
	}
}
//(3)表插入排序
const int SIZE=100;//静态链表最大容量
const int  MAXINT=10000;
template<class type>
struct StaListNode{
	type data;//记录项
	int next;//指针项
};
template<class type>
class StaticList{
	public:
		StaListNode<type> node[SIZE];
		int curlen;//链表实际长度
		StaticList()//构造函数
		{
			cout<<"建立静态链表"<<endl;
			cout<<"请输入静态链表的实际长度:"<<endl;
			cin>>curlen;
			cout<<"请输入各结点数据："<<endl;
			node[0].data=MAXINT;
			node[0].next=0;
			for(int i=1;i<=curlen;i++)
			{
				node[i].next=0;
				cin>>node[i].data;
			}
		}
		~StaticList()//析构函数
		{
		}
};
void StaListInsertSort()
{
	StaticList<int> sl;
	int min,max;//标记最大值最小值
	sl.node[0].next=1;
	sl.node[1].next=0;//初始化形成只有头结点的循环链表
	max=min=1;
	for(int i=2;i<=sl.curlen;i++)//向有序循环链表中加入结点，共n-1趟
	{

		if(sl.node[i].data<=sl.node[min].data)
		{
			sl.node[0].next=i;
			sl.node[i].next=i-1;
			min=i;
		}
		if(sl.node[i].data>=sl.node[max].data)
		{
			sl.node[i].next=0;
			sl.node[max].next=i;
			max=i;
		}
		if(sl.node[i].data<sl.node[max].data&&sl.node[i].data>sl.node[min].data)
		{
			int index1=min,index2;//index2用来标记index1的前一个下标
			while(sl.node[i].data>=sl.node[index1].data)
			{
				index2=index1;
				index1=sl.node[index1].next;
			}
			sl.node[i].next=index1;
			sl.node[index2].next=i;
		}

	}
	cout<<"表插入排序结果如下："<<endl;
	int index=sl.node[0].next;
	while(index!=0)
	{
		cout<<sl.node[index].data<<"\t";
		index=sl.node[index].next;
	}
	cout<<endl;
}
//(4)希尔排序
template<class type>
void ShellInsert(SqList<type> &L,int dk)
{//对顺序表进行一趟希尔插入排序
	for(int i=dk+1;i<=L.length;i++)
		if(L.key[i]<=L.key[i-dk])
		{
			L.key[0]=L.key[i];
			for(int j=i-dk;j>0&&L.key[0]<=L.key[j];j-=dk)
				L.key[j+dk]=L.key[j];
			L.key[j+dk]=L.key[0];
		}
}
template<class type>
void ShellSort(SqList<type> &L,int dlta[],int t)
{
	//按增量序列dl[0]--dl[t-1]对顺序表L作哈希排序
	for(int k=0;k<t;k++)
		ShellInsert(L,dlta[k]);
}
//二快速排序
//（1）起泡排序
template<class type>
void BubbleSort(SqList<type> & L)
{
	for(int i=1;i<L.length;i++)//用i控制比较趟数共n-1趟
	{
		type t;
		for(int j=1;j<=L.length-i;j++)
			if(L.key[j]>L.key[j+1])
			{
				t=L.key[j];
				L.key[j]=L.key[j+1];
				L.key[j+1]=t;
			}
	}
}
//(2)快速排序
template<class type>
int Partition(SqList<type>& L,int low,int high)
{//交换顺序表L中子表key[low]--key[high]中的记录，枢轴记录到位，并返回其所在位置，
//此时在它之前（后）的记录均不大（小）于它
	type pivotkey;
	L.key[0]=L.key[low];//用子表的第一个记录作枢轴记录
	pivotkey=L.key[low];//关键字
	while(low<high)//从表的两端交替向中间扫描
	{
		while(low<high&&L.key[high]>=pivotkey) --high;
		L.key[low]=L.key[high];//将比枢轴小的记录移至低端
		while(low<high&&L.key[low]<=pivotkey) ++low;
		L.key[high]=L.key[low];//将比枢轴大的记录移至高端
	}
	L.key[low]=L.key[0];//枢轴记录到位
	return low;//返回枢轴位置
}
template<class type>
void QSort(SqList<type>& L,int low,int high)
{
	int mid;//接收枢轴位置
	if(low<high)
	{
		mid=Partition(L,low,high);
		QSort(L,low,mid-1);//对低子表进行排序
		QSort(L,mid+1,high);//对高子表进行排序
	}
}
template<class type>
void QuitSort(SqList<type>& L)//对顺序表进行快速排序
{
	QSort(L,1,L.length);

}
//三选择排序
//(1)简单选择排序
template<class type>
int SelectMinKey(SqList<type>& L,int n)
{
	int min=n;
	type minkey;//最小值
	minkey=L.key[n];
	for(int i=n+1;i<=L.length;i++)
		if(L.key[i]<minkey)
		{
			minkey=L.key[i];
			min=i;
		}
		return min;
}
template<class type>
void SelectSort(SqList<type>& L)
{
	//对顺序表L作简单选择排序
	int j;
	type t;
	for(int i=1;i<=L.length;i++)
	{
		j=SelectMinKey(L,i);//在L.key[i]--L.key[L.length]中选择最小的记录并将其地址赋给j
		if(i!=j)//交换记录
		{
			t=L.key[i];
			L.key[i]=L.key[j];
			L.key[j]=t;
		}
	}
}
//(2)树形选择排序

template<class type>
class TreeNode{
	public:
	type data;//结点数据值
	int index;//树中位置
	int active;//是否继续比较标志
	TreeNode<type>& operator=(TreeNode<type>& treenode)
	{
		this->data=treenode.data;
		this->index=treenode.index;
		this->active=treenode.active;
		return *this;
	}
};
template<class type>
void ChangeTree(TreeNode<type>*tree,int i)
{
	if(i%2==0)
		tree[(i-1)/2]=tree[i-1];//当i为偶数时，和左结点比较
	else
		tree[(i-1)/2]=tree[i+1];//当i为奇数时，和右结点比较
	i=(i-1)/2;//重新比较，i上升到父亲结点位置
	int j;
	while(i)
	{
		if(i%2==0)//确定i的比较结点位置
			j=i-1;
		else
			j=i+1;
		if(!tree[i].active||!tree[j].active)
			if(tree[i].active)
				tree[(i-1)/2]=tree[i];
			else
				tree[(i-1)/2]=tree[j];
		else
			if(tree[i].data<tree[j].data)
				tree[(i-1)/2]=tree[i];
			else
				tree[(i-1)/2]=tree[j];
		i=(i-1)/2;
	}

}
int Power(int n)//计算2的n次方
{
	int result=1;
	if(n>=1)
	{
		for(int i=1;i<=n;i++)
			result*=2;
		return result;
	}
	else
		return 1;
}
int LeapNum(int n)//计算满足满二叉树的叶子结点总数
{
	for(int i=1;i<100;i++)
		if(Power(i-1)<n&&n<Power(i))
			return Power(i);
		else if(Power(i-1)==n)
			return Power(i-1);
}
template<class type>
void TreeSort(type a[],int n)
{//本排序方法只适用于满二叉树
	TreeNode<type>* tree;
	int bottsize=LeapNum(n);//树底层结点个数，此处必须满足满二叉树
	int size=2*bottsize-1;//树中结点总数
	int externalindex=bottsize-1;//开始进行比较的结点位置
	tree=new TreeNode<type>[size];
	assert(tree);
	int j=0;
	for(int i=externalindex;i<size;i++)
	{
		tree[i].index=i;//下标赋值
		if(j<n)
		{
			tree[i].active=1;//设置访问标志。可以访问
			tree[i].data=a[j++];//载入数据
		}
		else 
			tree[i].active=0;//额外结点设置成active=0
	}
	i=externalindex;
	while(i)//比较找到最小结点
	{
		j=i;
		while(j<2*i)
		{
			if(!tree[j+1].active||tree[j].data<=tree[j+1].data)
			{
				if(!tree[j+1].active&&!tree[j].active)
					tree[(j-1)/2].active=0;//其孩子结点都是额外结点的结点不可访问
				tree[(j-1)/2]=tree[j];//较小结点赋值给其双亲结点
			}
			else
				tree[(j-1)/2]=tree[j+1];
			j+=2;
		}
		i=(i-1)/2;
	}
	for(i=0;i<n-1;i++)//处理前面n-1个结点
	{
		a[i]=tree[0].data;
		tree[tree[0].index].active=0;//不在参加比较
		ChangeTree(tree,tree[0].index);//修改树结构
	}
	a[n-1]=tree[0].data;//处理数值最大的结点
}
template<class type>
void OutPut(type a[],int n)//输出函数
{
	for(int i=0;i<n;i++)
		cout<<a[i]<<"\t";
	cout<<endl;
}
//堆排序
template<class type>
void HeapAdjust(SqList<type>& L,int s,int m)
{//对顺序表做查找，从值最大的孩子结点向下筛选，找到最大值
	type rc=L.key[s];
	for(int j=2*s;j<=m;j*=2)
	{
		if(j<m&&L.key[j]<=L.key[j+1])//找到值相对较大的孩子结点，并依次向下筛选
			j++;
		if(rc>L.key[j]) break;//如果rc最大则推出while循环
		L.key[s]=L.key[j];//最大值赋值
		s=j;//交换位置
	}
	L.key[s]=rc;
}
template<class type>
void HeapSort(SqList<type>& L)
{//对顺序表L进行堆排序
	type value;
	for(int i=L.length/2;i>0;i--)//把L.key[1...L.length]调整为大顶堆
		HeapAdjust(L,i,L.length);
	for(i=L.length;i>1;--i)
	{
		value=L.key[1];
		L.key[1]=L.key[i];
		L.key[i]=value;
		HeapAdjust(L,1,i-1);//将L.key[1...i-1]重新调整为大顶堆
	}

}
//四
//归并排序
template<class type>
void Merge(type *SR,type *TR,int i,int m,int n)
{//将有序的SR[i...m]和SR[m+1...n]归并为有序的TR[i...n]
	for(int j=m+1,k=i;i<=m&&j<=n;k++)//将SR中的记录由大到小并入TR
	{
		if(SR[i]<=SR[j])
			TR[k]=SR[i++];
		else
			TR[k]=SR[j++];
	}
	if(i<=m)//将剩余的SR[i...m]赋值到TR
		for(int a=i;a<=m;a++)
			TR[k++]=SR[a];
	else if(j<=n)//将剩余的SR[j...n]复制到TR
		for(int b=j;b<=n;b++)
			TR[k++]=SR[b];
}
template<class type>
void MSort(type *SR,type *TR1,int s,int t)
{
	type TR2[100];//数组大小可以根据实际情况重新定义
	int m;
	//将SR[s...t]归并排序为TR[s...t]
	if(s==t)
		TR1[s]=SR[s];
	else
	{
		m=(s+t)/2;//将SR[s...t]平分为SR[s...m]和SR[m+1...t]
		MSort(SR,TR2,s,m);//递归地将SR[s...m]归并为有序的TR2[s...m]
		MSort(SR,TR2,m+1,t);//递归地将SR[m+1...t]归并为TR2[m+1...t]
		Merge(TR2,TR1,s,m,t);//将TR2[s...m]和TR2[m+1...t]归并到TR1[s...t]
	}
}
template<class type>
void MergeSort(SqList<type> &L)
{//对顺序表L作归并排序
	MSort(L.key,L.key,1,L.length);
}
//五 基数排序
//链式基数排序
const RADIX=10;
typedef int ArrType[RADIX];
ArrType f,e;
template<class type>
struct SLCell{
	type *keys;
	int next;
};
template<class type>
struct SLList{
	SLCell<type>* SList;
	int keynum;
	int recnum;
};
template<class type>
void InitSLList(SLList<type>& SL)//创建静态链表
{
	cout<<"建立静态链表"<<endl<<"请输入数据个数："<<endl;
	cin>>SL.recnum;
	SL.SList=new SLCell<type>[SL.recnum+1];
	assert(SL.SList);
	cout<<"请输入关键字项数"<<endl;
	cin>>SL.keynum;
	for(int i=1;i<=SL.recnum;i++)
	{
		SL.SList[i].keys=new type[SL.keynum+1];
		assert(SL.SList[i].keys);
	}
	SL.SList[0].next=1;
	cout<<"请输入数据"<<endl;
	for(i=1;i<=SL.recnum;i++)
	{
		cout<<"请输入第"<<i<<"个数据"<<endl;
		for(int j=1;j<=SL.keynum;j++)
			cin>>SL.SList[i].keys[j];
		if(i!=SL.recnum)
			SL.SList[i].next=i+1;
		else
			SL.SList[i].next=0;
	}
}
template<class type>
void RelList(SLList<type> &SL)//释放内存空间
{
	for(int i=1;i<=SL.recnum;i++)
		delete SL.SList[i].keys;
	delete SL.SList;
}


template<class type>
void OutPut(SLList<type>& SL)//输出静态链表
{
	for(int i=SL.SList[0].next;i;i=SL.SList[i].next)
	{
		//cout<<i<<endl;
		for(int j=1;j<=SL.keynum;j++)
			cout<<SL.SList[i].keys[j];
		cout<<'\t';
	}
	cout<<endl;
}
template<class type>
void Distrbute(SLCell<type>* r,int i,ArrType &f,ArrType& e)
{//按第i个关键字keys[i]建立RADIX个子表，使同一子表中记录的keys[i]相同
//f[0...RADIX]和e[0...RADIX]分别指向各个子表中第一个和最后一个记录
	int j;
	for(j=0;j<RADIX;j++)//各子表初始化为空
		f[j]=0;
	for(int a=r[0].next;a;a=r[a].next)
	{
		j=r[a].keys[i];
		if(!f[j])
			f[j]=a;
		else
			r[e[j]].next=a;
		e[j]=a;
	}
}
template<class type>
void Collect(SLCell<type>* r,int i,ArrType &f,ArrType& e)
{//按keys[i]自小至大将f[0...RADIX]所指各个子表依次链接成一个链表
	int j;
	for( j=0;!f[j];j++);//找第一个非空子表
	r[0].next=f[j];//r[0].next指向第一个非空子表中第一个结点
	int t=e[j];
	while(j<RADIX)
	{
		for(j++;j<RADIX-1&&!f[j];j++);//找下一个非空子表
		if(f[j])
		{r[t].next=f[j];t=e[j];}//链接两个非空子表
	}
	r[t].next=0;//t指向最后一个非空子表中的左后一个结点
}
template<class type>
void RadixSort(SLList<type> &SL)
{//对L作基数排序，使得L按关键字自小到大有序
	for(int i=SL.keynum;i>=1;i--)//按最高位优先依次对各关键字进行分配和收集
	{
        Distrbute(SL.SList,i,f,e);//第i趟分配
		Collect(SL.SList,i,f,e);//第i趟收集
	}
}






