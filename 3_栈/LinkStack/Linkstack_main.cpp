#include<iostream.h>//cout,cin
#include"process.h"//exit()
#include"stdio.h"//EOF,NULL
#include "LinkStack.h"
char pause;
 //主函数
int main()
{
	int e;
	LinkStack<int> s;
	system("cls");//执行系统命令cls，清屏
	int choice;
    do
	{//显示主菜单
		cout<<"1-元素入栈\n";
		cout<<"2-元素出栈\n";
		cout<<"3-取栈顶元素\n";
		cout<<"4-置栈空\n";
        cout<<"5-测栈空\n";
		cout<<"6-输出栈元素\n";
		cout<<"7-退出\n";
		cout<<"Enter choice:";
		
		cin>>choice;
		switch(choice)
			{
			case 1://入栈
				cout<<"请输入插入元素的值:";
				cin>>e;//
				cout<<endl;
				s.Push(e);
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
	    case 7://退出
		    cout<<"结束运行，Bye-Bye!"<<endl;
			break;
	    default:
		     cout<<"Invalid choice\n";
		break;
		}
	}while(choice!=7);
	return 0;
}//end of main function














