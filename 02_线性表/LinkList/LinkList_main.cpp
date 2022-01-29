#include<iostream.h>//cout,cin
#include"process.h"//exit()
#include"stdio.h"//EOF,NULL
#include "LinkList.h"
char pause;
typedef  int T;
 //主函数
int main()
{
	int i;
	T e,prior_e;
	LinkList<int> L;//
	system("cls");//执行系统命令cls，清屏
	int choice;
    do
	{//显示主菜单
		cout<<"1-创建链表\n";
		cout<<"2-按位序插入\n";
		cout<<"3-按位序删除\n";
		cout<<"4-按位序查找\n";
		cout<<"5-按值查找\n";
		cout<<"6-按值求前驱\n";
		cout<<"7-测表空\n";
		cout<<"8-测表长\n";
		cout<<"9-显示链表\n";
		cout<<"10-退出\n";
		cout<<"Enter choice:";
		cin>>choice;
		switch(choice)
			{
			case 1://创建链表
				cout<<"请输入要创建的链表中元素个数:";
				cin>>i;
				cout<<endl;
				L.CreateList(i);
				break;
			case 2://在指定位置插入元素
				cout<<"请输入插入位置:";
				cin>>i;
				cout<<endl;
				cout<<"请输入插入元素的值:";
				cin>>e;
				cout<<endl;
				try
				{
					L.Insert(i,e);
				}
				catch(char *err)
					{
					 cout<<err<<endl;
					 }
				break;
			case 3://删除指定位置元素
				cout<<"请输入删除位置:";
				cin>>i;
				cout<<endl;
				try
				{
					e=L.Delete(i);
					cout<<"被删除元素为："<<e<<endl;
				}
				catch(char *err)
					{
					 cout<<err<<endl;
					 }
				
				cin.get(pause);
				system("pause");
				break;
			case 4://按位序查找
				cout<<"请输入要查询的元素位置:";
				cin>>i;
				try
				{
					e=L.GetElem(i);
					cout<<"第"<<i<<"个元素值为："<<e<<endl;
				}
				catch(char *err)
					{
					 cout<<err<<endl;
					 }
				cin.get(pause);
				system("pause");
				break;
			case 5:// 按值查找
				cout<<"请输入要查询的元素值:";
				cin>>e;//
				i=L.Locate(e);
				cout<<"查询元素"<<e<<"位于链表的位置为:"<<i<<endl;
				cin.get(pause);
				system("pause");
				break;
			case 6://求元素前驱
				cout<<"请输入要求前驱元素的值:";
				cin>>e;
				try
				{
					prior_e=L.prior(e);
					cout<<"元素"<<e<<"的前驱值为："<<prior_e<<endl;
				}
				catch(char *err)
					{
					 cout<<err<<endl;
					 }
				cin.get(pause);
				system("pause");
				break;
			case 7://测表空
				i=L.Empty();
				if(i) 
					cout<<"表空"<<endl;
				else
					cout<<"表不空"<<endl;
				cin.get(pause);
				system("pause");
				break;
			case 8://测表长
				cout<<"链表长度为："<<L.Length()<<endl;
				cin.get(pause);
				system("pause");
				break;	
			case 9://显示表
				L.ListDisplay();
				cout<<endl;
				cin.get(pause);
				system("pause");
				break;	
			case 10://退出
				cout<<"结束运行"<<endl;
				break;
			default://
				cout<<"Invalid choice\n";
				break;
			}
	}while(choice!=10);//
	return 0;
}