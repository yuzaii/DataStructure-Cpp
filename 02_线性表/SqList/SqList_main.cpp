#include<iostream.h>//cout,cin
#include"process.h"//exit()
#include"stdio.h"//EOF,NULL
#include "SqList.h"
char pause;
typedef int T;

 //主函数
int main()
{
	int i;
	T e;
	SqList<int> L(20);//建立容量为20、元素类型为整型的空顺序表
	system("cls");//执行系统命令cls，清屏
	int choice;
    do
	{//显示主菜单
		cout<<"1-创建顺序表\n";
		cout<<"2-在链表第i个位置插入元素\n";
		cout<<"3-删除顺序表中第i个位置的元素\n";
		cout<<"4-返回第i个元素的值\n";
		cout<<"5-元素定位\n";
		cout<<"6-清空表\n";
		cout<<"7-测表空\n";
		cout<<"8-测表满\n";	
		cout<<"9-测试表长\n";
		cout<<"10-显示链表\n";
		cout<<"11-退出\n";
		cout<<"Enter choice:";
	
		cin>>choice;
		switch(choice)
			{
			case 1://创建表 
				cout<<"请输入要创建的顺序表中元素个数:";
				cin>>i;
				cout<<endl;
				try
				{
					L.CreateList(i);
				}
				catch(char *err)
					{
					 cout<<err<<endl;
					 }
				break;
			case 2://元素插入
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
			case 3://元素删除 
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
			case 4://返回第i个元素值
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
			case 5:// 按值进行元素查询
				cout<<"请输入要查询的元素值:";
				cin>>e;//
				i=L.Locate(e);
				cout<<"查询元素"<<e<<"位于在表中的位置为:"<<i<<endl;
				cin.get(pause);
				system("pause");
				break;
			case 6://清空表
				L.Clear();
				cout<<"表已清空"<<endl;
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
			case 8://测表满
				i=L.Full();
				if(i) 
					cout<<"表满"<<endl;
				else
					cout<<"表未满"<<endl;
				cin.get(pause);
				system("pause");
				break;
			case 9://测表长 
				i=L.Length();
				cout<<"表长为:"<<i<<endl;
				cin.get(pause);
				system("pause");
				break;
			case 10://遍历显示表
				L.ListDisp();
				cout<<endl;
				cin.get(pause);
				system("pause");
				break;	
			case 11://退出
				cout<<"结束运行"<<endl;
                                break;
			default://非法选择
				cout<<"Invalid choice\n";
				break;
			}
	}while(choice!=11);
	return 0;
}//end of main function