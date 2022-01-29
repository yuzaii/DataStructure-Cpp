#include<iostream.h>//cout,cin
#include"process.h"//exit()
#include"stdio.h"//EOF,NULL
#include"SqStack.h"
char pause;
 //主函数
int main()
{
	int e;
	SqStack<int> s(20);//建立容量为20、元素类型为整型的空栈
	system("cls");//执行系统命令cls，清屏
	int choice;
    do
	{//显示主菜单
		cout<<"1-元素入栈\n";
		cout<<"2-元素出栈\n";
		cout<<"3-取栈顶元素\n";
		cout<<"4-置栈空\n";
        cout<<"5-测栈空\n";
		cout<<"6-显示栈元素\n";
		cout<<"7-显示栈顶指针\n";
		cout<<"8-退出\n";
		cout<<"Enter choice:";
		cin>>choice;
		switch(choice)
			{
			case 1://入栈
				cout<<"请输入插入元素的值:";
				cin>>e;//
				cout<<endl;
				try
					{
					s.Push(e);
					}
				catch(char *err)
					{
					 cout<<err<<endl;
					 }
				cin.get(pause);
                system("pause");
				break;
	       case 2://出栈
		        try
					{
		             e=s.Pop ();
		             cout<<"出栈元素为："<<e<<endl;
					 }
	           catch(char *err)
				   {
		            cout<<err<<endl;
					}
		       cin.get(pause);
               system("pause");
		       break;
	      case 3://获取栈顶元素
		       try
				   {
				   e=s.GetTop ();
				   cout<<"栈顶元素为："<<e<<endl;
				   }
			   catch(char *err)
				   {
				    cout<<err<<endl;
					}
			   cin.get(pause);
			   system("pause");
			   break;
	      case 4://清空栈 
		       s.ClearStack();
		       cin.get(pause);
               system("pause");
		       break;
	     case 5://测栈空
		      if(s.StackEmpty())
				  cout<<"栈空"<<endl;
		      else
			      cout<<"栈不空"<<endl;
		      cin.get(pause);
              system("pause");
		      break;
	    case 6://遍历栈 
		     s.StackTranverse();
		     cin.get(pause);
             system("pause");
		     break;
		case 7://显示栈顶指针
			s.StackTop ();
			break;
		case 8://
			 cout<<"程序结束,Bye-Bye!"<<endl;
		    break;
	    default:
		     cout<<"Invalid choice\n";
		break;
		}
	cout<<endl;
	}while(choice!=8);
	return 0;
}














