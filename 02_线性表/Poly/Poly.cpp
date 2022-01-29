#include<iostream.h>//cout,cin
#include"process.h"//exit()
#define Max 20
typedef struct 
{ 
	float coef;
	int exp;
}PolyArray[Max];

struct PolyNode
{
   float coef;
   int exp;
   PolyNode *next;
};

class Poly
{
private:
	PolyNode *head;
public:
	Poly();//构造函数，建立空多项式
	~Poly();//析构函数，释放多项式
	void Create(PolyArray a,int n);//键盘输入，创建多项式链表
	void Disp();//多项式显示
	void Sort();//有序表排序
	void Add (Poly LB);//多项式加
    //void Substract(PolyNode * hbQ);//多项式减
    //void Multiply(PolyNode * hb);//多项式乘
};

Poly::Poly()
{ //创建一空多项式
	head=new PolyNode;
	head->next=NULL;
}

Poly::~Poly()
{//释放多项式所占空间
	PolyNode *p;
	while(head!=NULL)
	{//从头结点开始，依次释放结点
		p=head;
		head=head->next;
	    delete p;
	}
	head=NULL;//头结点指向空
}

void Poly::Disp ()
{
	PolyNode *p;
	p=head->next;
	while(p!=NULL)
	{
		cout<<p->coef <<"x^"<<p->exp<<'\t' ;
		p=p->next ;
	}
	cout<<endl;
}

void Poly::Create (PolyArray a,int n)
{//由多项式数组创建多项式链表
	PolyNode *s,*r;
	int i;
	r=head;
	for(i=0;i<n;i++)
	{
		s=new PolyNode;
		s->coef =a[i].coef;
		s->exp =a[i].exp;
		s->next =NULL;
		r->next =s;
		r=s;
	}
}

void Poly::Sort()
{
	PolyNode *p,*q,*r;
	p=head->next ;
	if(p!=NULL)
	{
		r=p->next ;//r指向p的后继结点
		p->next =NULL;//构造只有一个结点的有序表
		p=r;
		while(p!=NULL)
		{
			r=p->next;
			q=head;
			while(q->next!=NULL && q->next ->exp < p->exp )
				q=q->next ;//在有序表中插入*p的前驱结点*q
			p->next =q->next ;//*p插入到*q之后
			q->next =p;
			p=r;
		}
	}
}

void Poly::Add(Poly LB)
{ 
	float sum;
	PolyNode *pa,*pb,*qa,*qb;
    pa=head;
	qa=pa->next;
    pb=LB.head ;
	qb=pb->next;
	while (qa!=NULL && qb!=NULL )
   {
	   if (qa->exp < qb->exp ) 
	   {//
		   pa=qa;qa=qa->next;   }
	   else if ( qa->exp > qb->exp )
	   { //
		   pb->next =qb->next; 
		   qb->next=qa; 
		   pa->next=qb; 
		   pa=qb;
		   qb=pb->next; 
	   }
	   else
	   {//
		   sum=qa->coef+qb->coef;
		   if (sum==0 )  
		   {//
			   pa->next=qa->next;
			   delete qa;
			   qa=pa->next;
			   pb->next=qb->next;
			   delete qb;
			   qb=pb->next;
			   }
            else 
			{
                qa->coef=sum;
                pa=qa; qa=qa->next;
                pb->next=qb->next;
                delete qb;
                qb=pb->next;
             }
          }
   }//while
   if(qb!=NULL) 
     qa->next=qb;//
}//Add

void main()
{
	Poly LA,LB;
	PolyArray a={{7.0,0},{3.0,1},{9.0,8},{5.0,16}};
	PolyArray b={{8.0,1},{22,7},{-9.0,8}};
	LA.Create (a,4);
	LB.Create (b,3);
	cout<<"原多项式A为：";
	LA.Disp ();
	cout<<"原多项式B为：";
	LB.Disp ();
	LA.Sort ();
	LB.Sort ();
	cout<<"有序多项式A为：";
	LA.Disp ();
	cout<<"有序多项式B为：";
	LB.Disp();
	LA.Add (LB);
	cout<<"和多项式为：";
	LA.Disp ();
}
