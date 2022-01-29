#include<iostream.h>//cout,cin
#include"process.h"//exit()
#include"stdio.h"//EOF,NULL

typedef struct MNode
{ 
	int i,j;//行号，列号
	int e;//非零元
}MNode;

typedef struct
{
	int mu,nu,tu;// 行数、列数、非零元个数
	MNode *data;// 三元组表
}SMatrix;

SMatrix MCreate(int d[][3],int m,int n,int k)
{//由三元组的二维数组生成行向量稀疏存储矩阵
	SMatrix M={m,n,k,NULL};
	if(k!=0) 
		M.data=new MNode[k];
	for(int i=0;i<k;i++)
	{
		M.data [i].i=d[i][0];
	    M.data [i].j=d[i][1];
		M.data [i].e=d[i][2];
	}
	return M;
}//


void MDisp(SMatrix a)
{
	MNode p;
	int i,j,k=0,c=0;
	p=a.data[k];
	for(i=0;i<a.mu;i++)
	{
		for(j=0;j<a.nu;j++)
		{
			if(k<a.tu && p.i ==i && p.j ==j)  
			{
				cout<<'\t'<<p.e;
				k++;
				if(k<a.tu ) p=a.data[k];
			}
			else
			{
				cout<<'\t'<<c;
			}
		}//for
		cout<<endl;
	}//for
}//MatrixDisp

SMatrix MMul(SMatrix ma,SMatrix mb)
{
	SMatrix mc;
	int m1,n1,k1,m2,n2,k2;
	int *num,*rpot,*ctemp;
	int i,j,k,r,t;
	int p,q;
	if(ma.nu!=mb.mu)
	{
		cout<<"A的行数不等于B的列数，两个矩阵不能相乘!"<<endl;
        exit(1);
	}
	m1=ma.mu ;n1=ma.nu ;k1=ma.tu ;
	m2=mb.mu ;n2=mb.nu ;k2=mb.tu ;
	mc.mu =m1;mc.nu =n2;
	r=m1*n2;
	mc.data=new MNode[r];
	num=new int[m2];
	for(i=0;i<m2;i++) num[i]=0;//各行非零元个数计数器初始化
	rpot=new int[m2+1];
	rpot[0]=0;
	for(i=0;i<k2;i++)
	{
		k=mb.data[i].i;
		num[k]++;//计算B阵各行非零元个数
	}
	for(i=1;i<=m2;i++)//计算机B阵各行首个非零元在三元组表中的位置
		rpot[i]=rpot[i-1]+num[i-1];
	ctemp=new int[n2];
	r=0;//C的非零元个数
	p=0;//A的三元组位置指针
	for(i=0;i<m1;i++)
	{
		for(j=0;j<n2;j++) ctemp[j]=0;//cij累加器初始化
		while(ma.data [p].i ==i)
		{
			k=ma.data [p].j ;
			if(k<m2)  t=rpot[k+1];//确定B中第k行的非零元在B的三元组表中的位置
			else t=mb.tu +1;
			for(q=rpot[k];q<t;q++)
			{
				j=mb.data [q].j;
				ctemp[j]+=ma.data [p].e *mb.data [q].e;
			}//for
			p++;
		}//while
		for(j=0;j<n2;j++)
		{
			if(ctemp[j]!=0)
			{
				r++;
				mc.data[r-1].i=i;
				mc.data[r-1].j=j;
				mc.data[r-1].e=ctemp[j];
			}//if
		}//for
	}
	mc.tu =r;
	return mc;
}//MMul

void main()
{
	SMatrix ma,mb,mc;
	int m1=3,n1=4,k1=4;//被乘矩阵行数，列数，非零元个数
	int m2=4,n2=2,k2=4;//乘数矩阵行数，列数，非零元个数
	int da[4][3]={{0,0,3},{0,3,7},{1,3,-1},{2,1,2}};//ma阵的非零元
	int db[4][3]={{0,1,1},{1,0,2},{2,0,3},{2,1,4}};//mb阵的非零元
	ma=MCreate(da,m1,n1,k1);//生成三元组顺序存储的ma阵
	cout<<"ma="<<endl;
	MDisp(ma);//显示ma阵
	mb=MCreate(db,m2,n2,k2);//生成三元组顺序存储的mb阵
	cout<<"mb="<<endl;
	MDisp(mb);//显示mb阵
	if(ma.nu !=mb.mu )
	{
		cout<<"A矩阵列数不等于B矩阵行数，不能相乘"<<endl;
		exit(1);
	}
	if(ma.tu ==0||mb.tu ==0)
	{
		cout<<"C为零阵"<<endl;
		exit(1);
	}
	mc=MMul(ma,mb);//mc为ma、mb的乘积
	cout<<"mc="<<endl;
	MDisp(mc);//输出积矩阵
}//main

