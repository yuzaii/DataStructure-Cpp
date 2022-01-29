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

void MatrixTrans(SMatrix A,SMatrix &B)
{//
	int col,k,p,q;
	int *num,*cpot;
	num= new int[B.nu];
	cpot=new int [B.nu];
	if(B.tu)// 非零元个数不为零，实施转置
	{
		for(col=0;col<A.tu ;++col)//A中每一列非零元个数初始化为0
			num[col]=0;
		for(k=0;k<A.tu ;++k)/求矩阵A中每一列非零元个数
			++num[A.data [k].j];
		cpot[0]=0;//A中第0列首个非零元在B中的下标
		for(col=1;col<=A.nu ;++col)// 求A中每一列首个非零元在B中的下标
			cpot[col]=cpot[col-1]+num[col-1];
		for(p=0;p<A.tu ;++p)//扫描A的三元组表
		{
			col=A.data [p].j ;//当前三元组列号
			q=cpot[col];//当前三元组在B中的下标
			B.data[q].i=A.data[p].j;
			B.data [q].j =A.data [p].i;
			B.data [q].e =A.data [p].e;
			++cpot[col];// 预置同一列下一个三元组在B中的下标
		}//for
	}//if
}//



void main()
{
	SMatrix ma,mb;
	int m1=4,n1=6,k1=6;//被乘矩阵行数，列数，非零元个数
	int da[6][3]={{0,2,11},{0,4,12},{1,3,22},{2,1,31},{2,3,32},{3,0,41}};//ma阵的非零元
	ma=MCreate(da,m1,n1,k1);//生成三元组顺序存储的ma阵
	cout<<"ma="<<endl;
	MDisp(ma);//显示ma阵
	mb.mu =ma.nu ;
	mb.nu=ma.mu ;
	mb.tu=ma.tu;
	mb.data=new MNode[ma.tu ];
	MatrixTrans(ma,mb);
	cout<<"mb="<<endl;
	MDisp(mb);
}//