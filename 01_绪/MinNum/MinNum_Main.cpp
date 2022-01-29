#include<iostream.h>//cout,cin

void ArrayCreat(int * &A,int n)
{//创建一个整型数组
	A=new int[n];
	cout<<"依次输入"<<n<<"个元素值："<<endl;
	for(int i=0;i<n;i++)
		cin>>A[i];
}//ArrayCreat


int MinNum(int A[],int n)
{
	int min;//存放最小数
	min=A[0];
	for(int i=1;i<n;i++)
	{
		if(A[i]<min) min=A[i];
	}
	return min;
}
void ArrayDisp(int A[],int n)
{//数组元素输出
	for(int i=0;i<n;i++)
		cout<<A[i]<<'\t';
	cout<<endl;
}
void main()
{//
	int n;//元素个数
	int *A;
	cout<<"输入要创建的数组元素个数：";
	cin>>n;
	ArrayCreat(A,n);//调用创建函数，创建数组
	cout<<"已创建的数组为："<<endl;
	ArrayDisp(A,n);//调用显示函数，浏览数组
	cout<<"该数组的最小元素为："<<MinNum(A,n)<<endl;
}
