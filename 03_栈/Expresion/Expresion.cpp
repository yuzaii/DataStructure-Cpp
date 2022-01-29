#include<iostream.h>//cout,cin
#include"process.h"//exit()
#include"stdio.h"//EOF,NULL
#include<string.h>
#include<stdlib.h> // atoi()
#include"SqStack.h"
char pause;

char Precede(char t1,char t2)  
 {//算符的优先级比较 
   char f;
   switch(t2)
   {
     case '+':
     case '-':if(t1=='('||t1=='=')
                f='<';
              else
                f='>';
              break;
     case '*':
     case '/':if(t1=='*'||t1=='/'||t1==')')
                f='>';
              else
                f='<';
              break;
     case '(':if(t1==')')
              {
                cout<<"ERROR1"<<endl;
                exit(0);
              }
              else
                f='<';
              break;
     case ')':switch(t1)
              {
                case '(':f='=';
                         break;
                case '=':cout<<"ERROR2"<<endl;
                         exit(0);
                default: f='>';
              }
              break;
     case '=':switch(t1)
              {
                case '=':f='=';
                         break;
                case '(':cout<<"ERROR2"<<endl;
                         exit(0);
                default: f='>';
              }
   }
   return f;
 }

 
int In(char c) 
 { // 判断c是否为运算符
   switch(c)
   {
     case'+':
     case'-':
     case'*':
     case'/':
     case'(':
     case')':
     case'=':return 1; 
     default:return 0;
   }
 }


float Operate(float a,char theta,float b) 
 {//实施一次运算
   float c;
   switch(theta)
   {
     case'+':c=a+b;
             break;
     case'-':c=a-b;
             break;
     case'*':c=a*b;
             break;
     case'/':c=a/b;
   }
   return c;
 }

float Val_Exp(char *exp) 
 { //中缀表达式求值。设OPTR和OPND分别为运算符栈和运算数栈
   SqStack<char> OP(20);
   SqStack<float>  OD(20);
   char theta;
   float a,b,d;
   char c,x; // 存放由键盘接收的字符
   char z[6]; // 存放符点数字符串
   int i;
   OP.Push('='); // =是表达式结束标志
   c=*exp++;
   x=OP.GetTop();
   while(c!='='||x!='=')
   {
     if(In(c)) // 是7种运算符之一
       switch(Precede(x,c))
       {
         case'<':OP.Push(c); // 栈顶元素优先权低
                 c=*exp++;
                 break;
         case'=':x=OP.Pop(); // 脱括号并接收下一字符
                 c=*exp++;
                 break;
         case'>':theta=OP.Pop(); // 退栈并将运算结果入栈
                 b=OD.Pop();
                 a=OD.Pop();
                 OD.Push(Operate(a,theta,b));
       }
     else if(c>='0'&&c<='9'||c=='.') // c是操作数
     {
       i=0;
       do
       {
         z[i]=c;
         i++;
         c=*exp++;
       }while(c>='0'&&c<='9'||c=='.');
       z[i]='\0';
       d=atof(z); // 将字符串数组转为符点型存于d
       OD.Push(d);
     }
     else // c是非法字符
     {
       cout<<"ERROR3"<<endl;;
       exit(0);
     }
     x=OP.GetTop();
   }
   d=OD.GetTop();
   return d;
 }

void CreatePostExp(char * exp,char * &postexp)
{//由中缀式求后缀式
	char c,x;
	int i=0;
	SqStack<char> OP(20);
	OP.Push('='); // =是表达式结束标志
	cout<<"exp:"<<exp<<endl;
	c=*exp++;
	while(c)
	{
		if((c>='0'&&c<='9')||c=='.')
		{
			postexp[i++]=c;
			c=*exp++;
		}
		if(In(c)) // 是7种运算符之一
		{
			postexp[i++]=' ';
     	    x=OP.GetTop();
			switch(Precede(x,c))
			{
				case'<':OP.Push(c); // 栈顶元素优先权低
                         c=*exp++;
                         break;
                 case'=':x=OP.Pop(); // 脱括号并接收下一字符
                         c=*exp++;
                         break;
                 case'>':postexp[i++]=OP.Pop(); // 运算符出栈输出
					     break;
			}
		}
		postexp[i]='\0';
	}//while
	cout<<"后缀表达式为:"<<postexp<<endl;
}

float Val_PostExp(char *postexp)
{//后缀表达式求值
	int i;
	char z[6];
	float v=0,d=0,a,b;
	char c;
	SqStack<float> OD(20);
	c=*postexp++;
	while(c!='\0')
	{
		if((c>='0'&&c<='9')||c=='.')//为操作数
		{
			i=0;
			do
			{
				z[i++]=c;
				c=*postexp++;
			}while(c>='0'&&c<='9'||c=='.');
			z[i]='\0';
			d=atof(z); // 将字符串数组转为符点型存于d
			OD.Push(d);
		}
		if(In(c))//c为运算符
		{
			b=OD.Pop ();
			a=OD.Pop ();
			OD.Push (Operate(a,c,b));
			c=*postexp++;
		}
		c=*postexp++;
	}
	v=OD.Pop ();
	return v;
}


 //主函数
void main()
{
	//int i;
	char exp[20]="(2.2+5)+4*(5-3.1)=";
	char *postexp;
	postexp=new char[20];
	*postexp='\0';
    //char c;
	float v1;
	system("cls");//执行系统命令cls，清屏
	int choice;
    do
	{//显示主菜单
		cout<<"1-创建表达式\n";
		cout<<"2-表达式求值\n";
		cout<<"3-求后缀表达式\n";
		cout<<"4-后缀表达式求值\n";
		cout<<"5-显示表达式\n";
		cout<<"6-退出\n";
		cout<<"Enter choice:";
		cin>>choice;
		switch(choice)
			{
			case 1://创建表达式
				cout<<"请输入表达式，以=结束"<<endl;
				cin>>exp;
				cin.get(pause);
				system("pause");
				break;
			case 2://表达式求值
				v1=Val_Exp(exp) ;
				cout<<exp;
				cout<<v1<<endl;
				cin.get(pause);
    			system("pause");
				break;
			case 3://求后缀表达式
				CreatePostExp(exp,postexp);
				cin.get(pause);
				system("pause");
				break;
			case 4://后缀表达式求值
				v1=Val_PostExp(postexp);
				cout<<postexp<<"="<<v1<<endl;
				cin.get(pause);
				system("pause");
				break;
			case 5:// 显示表达式
				cout<<endl;
				cout<<"已创建的表达式为：";
				cout<<exp<<endl;
				if(strlen(postexp))
				{
					cout<<"后缀表达式为：";
					cout<<postexp<<endl; }
				    cin.get(pause);
				    system("pause");
				break;
			case 6://退出
				cout<<"结束运行，Bye-Bye!"<<endl;
				break;
			default://
				cout<<"Invalid choice\n";
				break;
			}
	}while(choice!=6);
}//end main