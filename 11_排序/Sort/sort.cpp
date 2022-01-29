#include<iostream>
#include"assert.h"
#include"sort.h"
using namespace std;

void main()
{
	int file,choice1,choice2,choice3,choice4,choice5;
	SqList<int> sl;
	cout<<"* 主  菜  单  *"<<endl;
	cout<<"  0 退出程序"<<endl
		<<"  1 插入排序"<<"【进入子菜单】"<<endl
		<<"  2 交换排序"<<"【进入子菜单】"<<endl
		<<"  3 选择排序"<<"【进入子菜单】"<<endl
		<<"  4 归并排序"<<"【进入子菜单】"<<endl
		<<"  5 基数排序"<<"【进入子菜单】"<<endl; //添加排序函数类别
		cout<<"请选择主菜单：";
	cin>>file;
	while(file!=0)
	{
		switch(file)
		{
		case 1:
			cout<<"* 插  入  排  序 * "<<endl
				<<"  0 退出插入排序"<<endl
				<<"  1 直接插入排序"<<endl
				<<"  2 折半插入排序"<<endl
				<<"  3 表插入排序"<<endl
				<<"  4 希尔排序"<<endl;
			cout<<"请选择插入排序方法：";
			cin>>choice1;
			while(choice1!=0)//数值跟随函数个数变化！！！！！！！！！！！！！
			{
				switch(choice1)
				{
				case 1:
					CreateSqList(sl);
					InsertSort(sl);
					cout<<"直接插入排序结果如下："<<endl;
					OutPut(sl);
					delete sl.key;
					break;
				case 2: 
					CreateSqList(sl);
					BInsertSort(sl);
					cout<<"折半插入排序结果如下："<<endl;
	                OutPut(sl);
					break;
				case 3:
					StaListInsertSort();
					break;
				case 4:
					int *p,n;
					cout<<"请输入增量个数"<<endl;
					cin>>n;
					p=new int[n];
					assert(p);
					cout<<"请输入各个增量的值："<<endl;
					for(int i=0;i<n;i++)
						cin>>p[i];
                    CreateSqList(sl);
					ShellSort(sl,p,n);
					cout<<"哈希排序结果如下："<<endl;
					OutPut(sl);
					delete p;
					break;

				}
				cout<<"*  插  入  排  序  *："<<endl
					<<"  0 退出插入排序"<<endl
					<<"  1 直接插入排序"<<endl
					<<"  2 折半插入排序"<<endl
					<<"  3 表插入排序"<<endl
					<<"  4 希尔排序"<<endl;
				cout<<"请选择插入排序方法：";
				cin>>choice1;
			}
			break;
		case 2:
			cout<<"* 快  速  排  序 *"<<endl
				<<" 0 退出快速排序"<<endl
				<<" 1 起泡排序"<<endl
				<<" 2 快速排序"<<endl;
			cout<<"请选择快速排序方法：";
			cin>>choice2;
			while(choice2!=0)
			{
				switch(choice2)
				{
				case 1:
					CreateSqList(sl);
					BubbleSort(sl);
					cout<<"起泡排序结果如下："<<endl;
					OutPut(sl);
					delete sl.key;
					break;
				case 2:
					CreateSqList(sl);
					QuitSort(sl);
					cout<<"快速排序结果如下："<<endl;
					OutPut(sl);
					break;
				}
               cout<<"* 快  速  排  序 *"<<endl
				   <<" 0 退出快速排序"<<endl
				   <<" 1 起泡排序"<<endl
				   <<" 2 快速排序"<<endl;
			    cout<<"请选择快速排序方法：";
			    cin>>choice2;			
			}
			break;
		case 3:
			cout<<"* 选   择   排   序 *"<<endl
				<<"  0 退出选择排序"<<endl
				<<"  1 简单选择排序"<<endl
				<<"  2 树形选择排序"<<endl
				<<"  3 堆排序"<<endl;
               cout<<"请选择选择排序方法：";
			cin>>choice3;
			while(choice3!=0)
			{
				switch(choice3)
				{
				case 1:
					CreateSqList(sl);
					SelectSort(sl);
					cout<<"简单选择排序结果如下："<<endl;
					OutPut(sl);
					delete sl.key;
					break;
				case 2:
					{
						int *date,n;
						cout<<"请输入数据个数"<<endl;
						cin>>n;
						date=new int[n];
						assert(date);
						cout<<"请输入数据"<<endl;
						for(int  i=0;i<n;i++)
							cin>>date[i];
						TreeSort(date,n);
						cout<<"树形选择排序结果如下："<<endl;
						OutPut(date,n);
						delete date;
						break;
					}
				case 3:
					CreateSqList(sl);
					HeapSort(sl);
				    cout<<"堆排序结果如下："<<endl;
					OutPut(sl);
					delete sl.key;
					break;
				}
            cout<<"* 选   择   排   序 *"<<endl
				<<"  0 退出选择排序"<<endl
				<<"  1 简单选择排序"<<endl
				<<"  2 树形选择排序"<<endl
				<<"  3 堆排序"<<endl;
               cout<<"请选择选择排序方法：";
			cin>>choice3;
			}
			break;
		case 4:
			cout<<"* 归   并   排   序  *"<<endl
				<<"  0 退出归并排序"<<endl
				<<"  1 归并排序"<<endl;
				cout<<"请选择归并排序方法：";
			cin>>choice4;
			while(choice4!=0)
			{
				switch(choice4)
				{
				case 1:
					CreateSqList(sl);
					MergeSort(sl);
					cout<<"归并排序结果如下："<<endl;
					OutPut(sl);
					delete sl.key;
					break;
				}
				cout<<"* 归   并   排   序  *"<<endl
				<<"  0 退出归并排序"<<endl
				<<"  1 归并排序"<<endl;
				cout<<"请选择归并排序方法：";
			cin>>choice4;
			}
			break;
		case 5:
			cout<<"* 基  数  排  序  "<<endl
				<<"  0 退出基数排序"<<endl
				<<"  1 链式基数排序"<<endl;
			cout<<"请选择基数排序方法：";
			cin>>choice5;
			while(choice5!=0)
			{
				switch(choice5)
				{
				case 1:
					SLList<int> SL;
					InitSLList(SL);
					RadixSort(SL);
					cout<<"链式基数排序结果如下："<<endl;
					OutPut(SL);
					RelList(SL);
					break;
				}
				cout<<"* 基  数  排  序  "<<endl
				<<"  0 退出基数排序"<<endl
				<<"  1 链式基数排序"<<endl;
			cout<<"请选择基数排序方法：";
			cin>>choice5;
			}
			break;
		}
		cout<<"* 主  菜  单  *"<<endl;
	    cout<<"  0 退出程序"<<endl
		    <<"  1 插入排序"<<"【进入子菜单】"<<endl
		    <<"  2 交换排序"<<"【进入子菜单】"<<endl
		    <<"  3 选择排序"<<"【进入子菜单】"<<endl
		    <<"  4 归并排序"<<"【进入子菜单】"<<endl
		    <<"  5 基数排序"<<"【进入子菜单】"<<endl; //添加排序函数类别
		cout<<"请选择主菜单：";
	    cin>>file;
	}
	cout<<"程序运行结束，Bye-Bye!"<<endl;
 }
	


