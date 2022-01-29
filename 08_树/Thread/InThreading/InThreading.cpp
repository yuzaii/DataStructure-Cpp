#include "Base.cpp"
//--------------------------------------------------------------------------------
//线索二叉链表类
template <class T>
class InThreading:public CThr<T>
{
	bool IsThreaded;								//记录是否被线索化
	public:
		InThreading(){IsThreaded=false;};
	void In_ThreadBiTree();							//生成中序线索二叉树
	void In_Thread(BiThrNode<T>*p,BiThrNode<T>**h);	//中序线索
	void In_TraThrBiTree();							//遍历中序线索二叉树
	void ShowPostTree();
};
//------------------------------------------------------------------------------
template <class T>
void InThreading<T>::In_ThreadBiTree()
{//生成中序线索二叉链表
	BiThrNode<T>*p,*q=NULL;
	p=BT;
	In_Thread(p,&q);
}
//--------------------------------------------------------------------------------
template <class T>
void InThreading<T>::In_Thread(BiThrNode<T>*p,BiThrNode<T>**h)
{
	if(p)//p指向的结点不空
	{
		
		In_Thread(p->lchild,h);//访问左子树
		 //若上次访问的结点的右指针为空，则将当前访问到的结点指针赋给其有指针，并置右标志域为1
		if((*h!=NULL)&&((*h)->rchild==NULL))
		{
			(*h)->rchild=p;//h即是刚被访问过的结点指针，p是当前被访问的结点指针
			(*h)->rflag=1;
		}
		//若当前访问的结点的左指针为空，则将上次访问的指针赋给当前结点的左指针域，并置左标志位1
		if(p->lchild==NULL)
		{
			p->lchild=(*h);
			p->lflag=1;
		}
		*h=p;
		In_Thread(p->rchild,h);//访问右子树
	}
	IsThreaded=true;
}
//--------------------------------------------------------------------------------
template <class T>
void InThreading<T>::In_TraThrBiTree()
{//遍历中序线索二叉树
	if(IsThreaded==false){cout<<"请先线索化！"<<endl;return;}
	cout<<"\n--------------------------------------------------"<<endl;
	cout<<"遍历中序线索二叉树得：";
	BiThrNode<T> *p;
	if(BT==NULL) return ;			//二叉链表为空
	p=BT;							//根结点
	while(p->lflag==0) p=p->lchild;	//沿左链找到叶子结点
	cout<<p->data<<' ';				//输出中序序列中的第一个结点值
	while(p->rchild!=NULL)
	{
		if(p->rflag==1) p=p->rchild;
		else
		{							//沿右子树的左链扫描
			p=p->rchild;
			while((p->lflag==0)&&(p->lchild!=NULL)) p=p->lchild;
		}
		cout<<p->data<<' ';			//输出中序序列结点值
	}
	cout<<endl;
	cout<<"--------------------------------------------------"<<endl;
}
//--------------------------------------------------------------------------------
template <class T>
void InThreading<T>::ShowPostTree()
{
	if(IsThreaded==false){cout<<"请先线索化！"<<endl;return;}
	cout<<"\n--------------------------------------------------"<<endl;
	cout<<"中序线索化二叉树之后:\n";
	BiThrNode<T> *p;
	if(BT==NULL) return ;			//二叉链表为空
	p=BT;							//根结点
	while(p->lflag==0) p=p->lchild;	//沿左链找到叶子结点

	if(p->lflag==1&&p->lchild)				//如果标志域为1，输出它的前驱。
		cout<<"值为："<<p->data<<"结点的前驱是："<<p->lchild->data<<endl;
	if(p->rflag==1&&p->rchild)				//如果标志域为1，输出它的后继。
		cout<<"值为："<<p->data<<"结点的后继是："<<p->rchild->data<<endl;
	while(p->rchild!=NULL)
	{
		if(p->rflag==1) p=p->rchild;
		else
		{							//沿右子树的左链扫描
			p=p->rchild;
			while((p->lflag==0)&&(p->lchild!=NULL)) p=p->lchild;
		}
		if(p->lflag==1&&p->lchild)					//如果标志域为1，输出它的前驱。
			cout<<"值为："<<p->data<<"结点的前驱是："<<p->lchild->data<<endl;
		if(p->rflag==1&&p->rchild)					//如果标志域为1，输出它的后继。
			cout<<"值为："<<p->data<<"结点的后继是："<<p->rchild->data<<endl;
	}
	cout<<"--------------------------------------------------"<<endl;
}
//void TestFunc()
void main()
{int opr;							//操作变量
		InThreading<int> Tr;		//创建一个 int 模板类型的对象
	do{
		system("cls");
		cout<<"--------菜   单---------------*"<<endl;
		cout<<"* 1：创建二叉链表树         *"<<endl;
		cout<<"* 2：中序线索化二叉树       *"<<endl;
		cout<<"* 3：遍历中序线索化二叉树   *"<<endl;
		cout<<"* 4：显示中序线索化的二叉树 *"<<endl;
		cout<<"* 5：退出操作               *"<<endl;
		cout<<"-----------------------------"<<endl;
		cout<<"请选择操作  [ ]";
		cout<<"\b\b";
		
		cin>>opr;
		switch(opr)
		{
		case 1:
			if(Tr.GetRoot()) Tr.DeleteNode();//释放之前创建的对象的所有结点空间
			Tr.CreateBiTree(-1);
			system("pause");
			break;
		case 2:
			Tr.In_ThreadBiTree();
			cout<<"线索化完成！"<<endl;
			system("pause");
			break;
		case 3:
			Tr.In_TraThrBiTree();
			system("pause");
			break;
		case 4:
			Tr.ShowPostTree();
			system("pause");
			break;
		case 5:
			cout<<"运行结束，Bye-Bye!"<<endl;
			break;
		default:
			break;

		}
	}while(opr!=5);
}

//1 3 6 -1 -1 2 -1 -1 8 4 -1 -1 -1
