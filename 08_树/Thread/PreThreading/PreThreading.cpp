//--------------------------------------------------------------------------------
#include "Base.cpp"
template <class T>
class CPreThreading:public CThr<T>
{
	bool IsThreaded;
	public:
		CPreThreading(){IsThreaded=false;}
		void Pre_ThreadBiTree();							//生成先序线索二叉树
		void Pre_Thread(BiThrNode<T>*p,BiThrNode<T>**h);	//先序线索
		void Pre_TraThrBiTree();							//遍历先序线索二叉树
		void ShowPreTree();									//显示线索化后的信息
};
template <class T>
void CPreThreading<T>::Pre_ThreadBiTree()
{									//生成先序线索二叉链表
	BiThrNode<T>*bt,*q=NULL;
	bt=BT;							//根结点
	Pre_Thread(bt,&q);
}
//--------------------------------------------------------------------------------
template <class T>
void CPreThreading<T>::Pre_TraThrBiTree()
{
	if(IsThreaded==false){cout<<"请先线索化！"<<endl;return;}
	cout<<"\n--------------------------------------------------"<<endl;
	cout<<"遍历先序线索二叉树得：";
	BiThrNode<T>*p;
	if(BT==NULL) return ;			//二叉链表为空
	cout<<BT->data<<' ';			//输出根结点的值
	p=BT->lchild;					//沿左子树
	if(p==NULL) p=BT->rchild;		//左子树为空则沿右子树
	while(p!=NULL)
	{
		cout<<p->data<<' ';			//输出当前结点的值
		while(p->lflag==0)			//沿左链访问直到左标志非0
		{
			p=p->lchild;
			cout<<p->data<<' ';
		}
		p=p->rchild;
	}
	cout<<"\n--------------------------------------------------"<<endl;

}
//--------------------------------------------------------------------------------
template <class T>
void CPreThreading<T>::Pre_Thread(BiThrNode<T>*bt,BiThrNode<T>**h)
{
	BiThrNode<T>*p,*q;				//定义两个结点指针变量
	if(bt!=NULL)					//bt指向的结点不空
	{
		p=bt->lchild ;
		q=bt->rchild ;
									//若当前访问的结点的左指针为空，则将上次访问的结点赋给左指针域，并置标志域
		if((*h!=NULL)&&(p==NULL))
		{
			bt->lchild= *h;
			bt->lflag= 1;
		}
									//若上次访问的结点的右指针为空
									//则将访问过的结点指针赋给当前结点的右指针域，并置标志域为1
		if((*h!=NULL)&&((*h)->rchild==NULL))
		{
			(*h)->rchild=bt;
			(*h)->rflag=1;
		}
		*h=bt;						//记下当前访问的结点
		Pre_Thread(p,h);			//访问左子树
		Pre_Thread(q,h);			//访问右子树
	}
	IsThreaded=true;
}
//--------------------------------------------------------------------------------
template <class T>
void CPreThreading<T>::ShowPreTree()
{
	if(IsThreaded==false){cout<<"请先线索化！"<<endl;return;}
	cout<<"\n--------------------------------------------------"<<endl;
	cout<<"下面显示的是先序线索化以后的结果："<<endl;
	BiThrNode<T>*p;
	if(BT==NULL) return ;				//二叉链表为空。
	if(BT->lflag==1)					//如果标志域为1，输出它的前驱。
		cout<<"值为："<<BT->data<<"结点的前驱是："<<BT->lchild->data<<endl;
	if(BT->rflag==1)					//如果标志域为1，输出它的后继。
		cout<<"值为："<<BT->data<<"结点的后继是："<<BT->rchild->data<<endl;
	p=BT->lchild;						//沿左子树。
	if(p==NULL) p=BT->rchild;			//左子树为空则沿右子树。
	while(p!=NULL)
	{
		if(p->lflag==1)					//如果标志域为1，输出它的前驱。
			cout<<"值为："<<p->data<<"结点的前驱是："<<p->lchild->data<<endl;
		if(p->rflag==1)					//如果标志域为1，输出它的后继。
			cout<<"值为："<<p->data<<"结点的后继是："<<p->rchild->data<<endl;
		while(p->lflag==0)				//沿左链访问直到左标志非0
		{
			p=p->lchild;
			if(p->lflag==1)				//如果标志域为1，输出它的前驱。
				cout<<"值为："<<p->data<<"结点的前驱是："<<p->lchild->data<<endl;
			if(p->rflag==1)				//如果标志域为1，输出它的后继。
				cout<<"值为："<<p->data<<"结点的后继是："<<p->rchild->data<<endl;
		}
		p=p->rchild;
	}
	cout<<"--------------------------------------------------"<<endl;

}
//--------------------------------------------------------------------------------
void main()
{
	int opr;//操作变量
	CPreThreading<int> Tr;//创建一个 int 模板类型的对象
	do{
		system("cls");
		cout<<"----------菜   单---------------"<<endl;
		cout<<"--* 1：创建二叉树               *--"<<endl;
		cout<<"--* 2：先序线索化二叉树         *--"<<endl;
		cout<<"--* 3：先序线索化二叉树先序遍历 *--"<<endl;
		cout<<"--* 4：显示先序线索信息         *--"<<endl;
		cout<<"--* 5：退出操作                 *--"<<endl;
		cout<<"--------------------------------"<<endl;
		cout<<"请选择操作  [ ]";
		cout<<"\b\b";
		
		cin>>opr;
		switch(opr)
		{
		case 1:
			if(Tr.GetRoot()) Tr.DeleteNode();	//释放之前创建的对象的所有结点空间
			Tr.CreateBiTree(-1);				//创建二叉树
			system("pause");
			break;
		case 2:
			Tr.Pre_ThreadBiTree();				//先序线索化二叉树
			cout<<"线索化完成！"<<endl;
			system("pause");
			break;
		case 3:
			Tr.Pre_TraThrBiTree();				//先序遍历二叉树
			system("pause");
			break;
		case 4:
			Tr.ShowPreTree();					//显示线索化之后的标志域信息
			system("pause");
			break;
		case 5:
			cout<<"结束运行，Bye-Bye!"<<endl;
			break;
		default:
			cout<<"选择不合理，请重选!"<<endl;
			break;
		}
	}while(opr!=5);
}
