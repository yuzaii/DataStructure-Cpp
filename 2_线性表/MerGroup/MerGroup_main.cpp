#include<iostream.h>//cout,cin
#include"process.h"//exit()
#include "LinkList.h"
typedef  int T;

void main()
{
	T e;
    LinkList<int> La,Lb;
	int la_len,lb_len;
	int i;
	cout<<"请输入要创建A集合中元素个数:";
	cin>>la_len;//将创建的链表中数据元素的个数
	cout<<endl;
	La.CreateList(la_len);
	cout<<"请输入要创建的B集合中元素个数:";
	cin>>lb_len;//将创建的链表中数据元素的个数
	cout<<endl;
	Lb.CreateList(lb_len);
	cout<<endl;
	cout<<"La:"<<"\t";
	La.ListDisplay();
	cout<<"Lb:"<<"\t";
	Lb.ListDisplay();
		for(i=1;i<=lb_len;i++)
	{
		try
		{
			e=Lb.GetElem(i);}
		catch(char *err)
					{
					 cout<<err<<endl;
					 }
		if(!La.Locate(e))
			try
				{
					La.Insert(++la_len,e);
				}
				catch(char *err)
					{
					 cout<<err<<endl;
					 }
			}//for
    cout<<"union:"<<"\t";
	La.ListDisplay();
	cout<<endl;
}//end main



	
	
