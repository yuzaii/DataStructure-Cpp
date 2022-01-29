#include<iostream.h>//cout,cin
#include"process.h"//exit()
#include"stdio.h"//EOF,NULL

typedef struct MNode
{ 
	int i,j;//行号，列号
	int e;//非零元
	MNode *next;// 指向同行下一个结点
}MNode,*MLink;

typedef struct
{
	int mu,nu,tu;// 行数、列数、非零元个数
	MLink *rops;// 存放各行链表的头指针
}LMatrix;

int cmp(int a,int b)
{//列号比较
	if(a<b) return -1;
	else if(a=b) return 0;
	else return 1;
}

void NodeCopy(MNode * &s,MNode * x)
{//结点拷贝
	s->e=x->e;s->i=x->i;s->j=x->j;
}

void AddNode(MNode * &lp,MNode * &lq,MNode *s)
{
	MNode *p;
	p=new MNode;
	NodeCopy(p,s);
	p->next=NULL;
	if(lp==NULL)//首元结点
	{
		lp=p;
		lq=p;
	}
	else//非首元结点
	{
		 lq->next =p;
		 lq=p;
	 }
}//

 
 LMatrix MAdd(LMatrix ma,LMatrix mb)
{
	LMatrix mc;
	MNode *pa,*pb,*pc;//分别指向被加数、加数、和矩阵行向量首元结点
	MNode *s;//
	int i,sum;
	int m,n;//行数，列数
	int flag=1;
	m=ma.mu ;
	n=ma.nu ;
	mc.mu=m;mc.nu=n;mc.tu=0;mc.rops=NULL;
	if(mc.rops) delete [] mc.rops;
	mc.rops=new MLink [m];
	for(i=0;i<m;i++)
		mc.rops[i]=NULL;//C行指针向量初始化
	for(i=0;i<m;i++)
	{
		pa=ma.rops[i];
	    pb=mb.rops[i];
		pc=mc.rops[i];
		while(pa && pb)//被加矩阵、加矩阵行链不空
		{
			flag=1;
			switch(cmp(pa->j,pb->j))//列数比较
				{
				case -1:
					s=new MNode;//
					NodeCopy(s,pa);
					s->next=NULL;
					pa=pa->next;
					break;
		        case 0:
					sum=pa->e+pb->e;
					if(sum==0)  flag=0;
					else
					{
						s=new MNode;
						NodeCopy(s,pa);
						s->e=sum;
					    s->next=NULL;
					}
					pa=pa->next;pb=pb->next;//pa,pb后移
			        break;
		        case 1:
					s=new MNode;
                    NodeCopy(s,pb);//复制pb所指结点
					pb=pb->next;//pb后移
					s->next=NULL;
					break;
			}//switch
			if(flag)//有新结点生成
			{
				mc.tu++;
				AddNode(mc.rops [i],pc,s);
			}
		}//while
		if(pa)//pa不空，复制pa剩余链到和矩阵中
		{
			while(pa)
			{
				NodeCopy(s,pa);pa=pa->next;
				AddNode(mc.rops [i],pc,s);
			}//while
		}//if(pa)
		if(pb)        //pb不空，复制pb剩余链到和矩阵中
		{
			while(pb)
			{
				NodeCopy(s,pb);pb=pb->next ;
				AddNode(mc.rops [i],pc,s);
			}//while
		}//if(pb)
	}//for
	return mc;
}//MAdd

void MDisp(LMatrix a)
{
	MNode *p;
	int i,j,c=0;
	for(i=0;i<a.mu;i++)
	{
		p=a.rops[i];
		for(j=0;j<a.nu;j++)
		{
			if(p==NULL)
				cout<<'\t'<<c;
			else if (j<p->j)
				cout<<'\t'<<c;
			else
			{
				cout<<'\t'<<p->e;
				p=p->next;
			}
		}//for
		cout<<endl;
	}//for
}//MatrixDisp

LMatrix MCreate(int d[][3],int m,int n,int k)
{//由三元组的二维数组生成行向量稀疏存储矩阵
	LMatrix M={m,n,k,NULL};
	int i,r1,r2;
	MNode *s,*p;//工作指针
	if(M.rops) delete [] M.rops;
	M.rops=new MLink[m];
	for(i=0;i<m;i++)
		M.rops[i]=NULL;
	r1=m;
	p=M.rops[r1];//
	for(i=0;i<k;i++)//扫描非零元数组
	{
		s=new MNode;
		s->i=d[i][0];
		s->j=d[i][1];
		s->e=d[i][2];
		r2=s->i;//非零元所在行
		if(r2!=r1) //创建链表第1个结点
		{
			M.rops[r2]=s;
			s->next=NULL;
			p=s;
			r1=r2;
		}
		else//创建链表非首元结点
		{
			s->next=p->next;
			p->next =s;
			p=s;
		}
	}//for
	return M;
}//MCreate
		

void main()
{
	//MNode *p;
	LMatrix ma,mb,mc;
	int m=4,n=6;//行数，列数
	int da[5][3]={{0,1,3},{1,1,2},{1,3,5},{3,0,9},{3,5,1}};
	int db[4][3]={{0,2,7},{1,1,6},{1,3,-5},{2,1,4}};
	ma=MCreate(da,4,6,5);
	cout<<"ma="<<endl;
	MDisp(ma);
	mb=MCreate(db,4,6,4);
	cout<<"mb="<<endl;
	MDisp(mb);
	mc=MAdd(ma,mb);
	cout<<"mc=ma+mb="<<endl;
	MDisp(mc);
}