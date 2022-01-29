#include<iostream.h>
#include"stdio.h"//EOF,NULL
#include<string>
const int defaultSize = 128;
using namespace std;
#include"AString.h"

int main()
{
    cout<<"------------------------------------------------------------------------"<<endl;
    cout<<"请输入初始化对象的大小：";
    int len;
    cin>>len;
	char *str = new char[len+1];
    cout<<"\n请输入要初始化字符串(不能含有空格)：";
    cin>>str;
    AString string(len);
    string = str;
    int tag=0;
    while(1)
    {
        cout<<"1-删除操作\n"
            <<"2-插入操作\n"
            <<"3-连接操作\n"
            <<"4-截取字符串\n"
            <<"5-字符比较\n"
            <<"6-输出字符串对象\n"
            <<"7-清空字符对象(清空后可选择序号8来重新赋值)\n"
            <<"8-字符串对象赋值\n"
            <<"9-退出程序\n";
        cout<<"\n请输入要操作的方法的序号：";
        cin>>tag;
        switch(tag)
        {
        case 1:
			{int index,length;
                 cout<<"请输入要删除的起始位置：";
                 cin>>index;
                 cout<<"\n请输入要删除的长度：";
                 cin>>length;
                 string.Remove(index,length);
                 cout<<"\n删除后的字符串："<<endl;
                 string.Output();
                 break;}
        case 2:
			{int index;
                char *input = new char[defaultSize];
                cout<<"\n请输入要插入的字符串：";
                cin>>input;
               	//cout<<" 输入的串长为："<<strlen(input)<<endl;
				cout<<"\n请输入要插入的位置：";
                cin>>index;
                string.Insert(index,input);
                cout<<"\n插入字符串后的字符对象："<<endl;
                string.Output();
                delete[] input;
                break;}
        case 3:
			{char *value = new char[defaultSize+1];
                cout<<"\n请输入要连接的字符串：";
                cin>>value;
                AString astr = value;
                string+=astr;
                cout<<"\n连接字符串后的字符对象："<<endl;
                string.Output();
                delete[] value;
                break;}
		  case 4:
			  {int len,i;
               AString subs;
                cout<<"\n请输入要截取的字符串长度：";
                cin>>len;
               	cout<<"\n请输入开始截取的位置：";
                    cin>>i;
                 string.SubString(subs,i,len);
                cout<<"\n下面为截取后的字符串对象：";
                subs.Output();
                break;}
        case 5:
			{char *value = new char[128];
                cout<<"\n请输入要比较的字符串：";
                cin>>value;
                cout<<"\n字符串比较结果如下所示：";
                string.Output();
                if(string>value) cout<<">";
				if(string==value) cout<<"=";
				if(string<value) cout<<"<";
				cout<<value<<endl;
                break;}
        case 6:
                cout<<"\n当前字符串对象的值如下所示：";
                string.Output();
                break;
        case 7:
                string.Clear();
                cout<<"\n字符串对象已清空！\n";
                break;
        case 8:
			{char *str = new char[128];
                cout<<"\n请输入要赋值的字符串(不能有空格)：";
                cin>>str;
                string = str;
                cout<<"\n赋值后的字符串对象为：";
                string.Output();
                break;}
        case 9:
			cout<<"运行结束"<<endl;
			 return 0;
			 break;
		default:
			cout<<"选择非法，请重选!";
            break;
        }
    }
    
}