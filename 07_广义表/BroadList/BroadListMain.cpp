#include <iostream>      //引用输入输出流库函数的头文件
#include "BroadList.cpp"  //引用广义表的成员函数文件
#include <string> //引用string库函数的头文件  
using namespace std; //指出后续的所有的程序语句都在名字空间std内
char pause;

void main()
{
	GLists<char> *stulists,*stulistsHead,*stulistsTail;//*stulistsAdd;
	string str="(a,b,(a,b))";
	stulists = new GLists<char>(str);  //生成str表示的广义表
    cout<<"初始构建的广义表为："<<"\n";
	stulists->Prnt();
	system("cls");//执行系统命令cls，清屏
	int choice;
    do
	{//显示主菜单
		cout<<"1-创建广义表\n";
		cout<<"2-求表长\n";
		cout<<"3-求表深\n";
		cout<<"4-求表头\n";
		cout<<"5-求表尾\n";
		cout<<"6-显示表\n";
		cout<<"7-退出\n";
		cout<<"Enter choice:";
	
		cin>>choice;
		switch(choice)
			{
			case 1://创建广义表
				cout<<"输入广义表：";
				cin>>str;
				stulists = new GLists<char>(str); 
				cout<<"已创建的广义表为";
				stulists->Prnt();
			    cin.get(pause);
			    system("pause");
				break;
			case 2://求表长
                cout<<"\n"<<"广义表的长度为：";
	            cout<<stulists->Length();
			    cout<<endl;
				cin.get(pause);
			    system("pause");
				break;
			case 3://求表深
                cout<<"\n"<<"广义表的深度为：";
	            cout<<stulists->DepthGList();				
			    cout<<endl;
				cin.get(pause);
				system("pause");
				break;
			case 4://求表头
				stulistsHead = stulists->Head();
	            cout<<"\n"<<"广义表的头指针为：";
	            stulistsHead->Prnt();
				cin.get(pause);
				system("pause");
				break;
			case 5:// 求表尾
				stulistsTail = stulists->Tail();
	            cout<<"\n"<<"广义表的尾指针为：";
	            stulistsTail->Prnt();
				cin.get(pause);
				system("pause");
				break;
			case 6://显示广义表
				stulists->Prnt();
				cin.get(pause);
				system("pause");
				break;
			case 7://退出
				break;
			default://
				cout<<"Invalid choice\n";
				break;
			}
	}while(choice!=7);//
}






