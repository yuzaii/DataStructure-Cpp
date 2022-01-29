//串模式匹配的类定义FindSub.cpp
#include<iomanip.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<string>
const maxsize=30;

int IndexBF(char s[],char t[],int pos)
{int i,j,m,n;
   i=pos-1;j=0;
   m=strlen(s);
   n=strlen(t);
 while(i<m && j<n)
  {if(s[i]==t[j])
    {++i;++j;}
   else {i=i-j+1;j=0;}
  }
 if(j>=n) 
	 return i-n+1;
 else  
	 return -1;
}

void GetNext(char t[],int next[])
{// 求模式串T的next函数值并存入数组next
	int j=0,k=-1;
	int n=strlen(t);
	next[j]=-1;
	while(j<n)
		{
		 if(k==-1||t[j]==t[k])
			 {j++;k++;next[j]=k;}
		 else k=next[k];
		 }
}

int IndexKMP(char s[],char t[],int next[],int pos)
{// 利用模式串T的next函数求T在主串S中第pos个字符之后的位置的KMP算法。
   // 其中,T非空,1≤pos≤StrLength(S)
	int i,j,n;
	i=pos-1;j=0;
	int m=strlen(s);
	//s[m]='\0';
	n=strlen(t);
	//t[n]='\0';
	while(i<m && j<n)
	   if(j==-1||s[i]==t[j])
		{i++;j++;}// 继续比较后继字符
	   else j=next[j];// 模式串向右移动
	if(j>=n) return i-n+1;// 匹配成功
	return -1;
}

//串模式匹配的测试
void main()
{   char s[maxsize]="aaabaaaabaa",t[maxsize]="aaaab";
    int index,*next;
    int choice,j,pos=0;
	int m,n;
	m=strlen(s);
	n=strlen(t);
	next=new int[n];
    GetNext(t,next); 
	do
	{//显示主菜单
		cout<<"1-BF匹配\n";
		cout<<"2-KMP匹配\n";
		cout<<"3-查看Next[]\n";
		cout<<"4-显示串\n";
		cout<<"6-退出\n";
		cout<<"Enter choice:";
		cin>>choice;
		switch(choice)
			{
			case 1://BF匹配
			   cout<<"输入匹配起始位置:";
			   cin>>pos;
		   	   if(pos<=m-n+1)
			  {
			      cout<<"主串为:"<<s<<'\t'<<"子串为:"<<t<<endl;
				   cout<<"BF的结果:"<<endl;
        	     index=IndexBF(s,t,pos);
                 if(index!=-1)
					 cout<<"模式串t在主串s中的位置从第"<<index<<"个字符开始"<<endl;
			     else cout<<"主串s中不含模式串t"<<endl;
			   }
			  else
			  { cout<<"位置非法，无法匹配!"<<endl; }
		       break;
	      case 2://KMP算法
		   	  cout<<"输入匹配起始位置:";
		      cin>>pos; 
			  if(pos<=m-n+1)
			  {
			      cout<<"主串为:"<<s<<'\t'<<"子串为:"<<t<<endl;
				  cout<<"KMP匹配结果:"<<endl;
                  index=IndexKMP(s,t,next,pos);
                  if(index!=-1)
					  cout<<"模式串在主串的位置从第"<<index<<"个字符开始"<<endl;
			      else
					cout<<"主串s中不含模式串t"<<endl;
			  }
			  else
			  { cout<<"位置非法，无法匹配!"<<endl; }
		       break;
	      case 3://显示NEXT
	           cout<<"子串为："<<t<<endl;
			  for(j=0;j<n;j++)
					{
					cout<<"next["<<j<<"]="<<next[j]<<'\t';
					if((j+1)%5==0) cout<<endl;
					}
			  cout<<endl;
			   break;
		  case 4: //显示串
      		  cout<<"主串为："<<s;
			  cout<<"子串为: "<<t;
		      cout<<endl;
		      break;
	    case 6://退出
		     cout<<"结束运行!"<<endl;  
			 break;
	    default:
		     cout<<"Invalid choice\n";
		     break;
		}
	}while(choice!=6);
}


