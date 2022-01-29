#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "LinkQueue.h"
using namespace std;
#include "CTree.h"
int main()
{
	CTree<char> PT; 
	CTree<char> c;
	int op;
	do
	{
		cout<<"\t-----主菜单------"<<endl;
		cout<<"\t0 - 退出 "<<endl;
		cout<<"\t1 - 创建树 "<<endl;
		cout<<"\t2 - 清空一棵树 "<<endl;
		cout<<"\t3 - 判断树是否为空 "<<endl;
		cout<<"\t4 - 返回树的深度 "<<endl;
		cout<<"\t5 - 返回树根值 "<<endl;
		cout<<"\t6 - 根据序号，返回结点值 "<<endl;
		cout<<"\t7 - 修改结点值 "<<endl;
		cout<<"\t8 - 返回双亲结点的值 "<<endl;
		cout<<"\t9 - 返回最左边的孩子值 "<<endl;
		cout<<"\t10 - 返回右兄弟的值  "<<endl;
		cout<<"\t11 - 输出树   "<<endl;
		cout<<"\t12 - 插入操作  "<<endl;
		cout<<"\t13 - 删除操作  "<<endl;
		cout<<"\t14 - 遍历树  "<<endl;
		cout<<"\t请选择操作：[ ]";
		cout<<"\b\b";
		cin>>op;
		switch(op)
		{
		case 0:
			cout<<"结束运行，Bye-Bye!"<<endl;
			break;
		case 1://创建一棵树
			PT.CreateTree('#');
			break;
		case 2://清空一棵树
			PT.ClearTree();
			system("pause");
			break;
		case 3://判断树是否为空
			cout<<(PT.IsEmpty()==true?"树为空":"树不为空")<<endl;
			system("pause");
			break;
		case 4://树的深度
			cout<<"树的深度为："<<PT.TreeDepth()<<endl;
			system("pause");
			break;
		case 5://求树根的结点
			if(PT.Root()==0)cout<<"树为空！"<<endl;
			else cout<<"树根结点的值为："<<PT.Root()<<endl;
			system("pause");
			break;
		case 6://根据结点的序号,返回结点值
			cout<<"请输入结点的序号：";
			int index;
			cin>>index;
			if(PT.Value(index)!=0)
			{
				cout<<"序号为"<<index<<"的结点值为"<<PT.Value(index)<<endl;
			}
			else
			{
				cout<<"操作失败，输入的序号有误！"<<endl;
			}
			system("pause");
			break;
		case 7://修改结点值
			char cur_e;
			cout<<"请输入要改变的结点值：";
			cin>>cur_e;
			char value;
			cout<<"请输入改变后的值";
			cin>>value;
			if(PT.Assign(cur_e,value)==true)cout<<"操作成功！"<<endl;
			else cout<<"操作失败！"<<endl;
			system("pause");
			break;
		case 8://双亲结点
			char cur_e2;
			cout<<"请输入结点的值：";
			cin>>cur_e2;
			if(PT.parent(cur_e2)==0)
			{
				cout<<"该结点不存在或此结点是根结点！"<<endl;
			}
			else
			{
				cout<<"该结点的双亲结点是："<<PT.parent(cur_e2)<<endl;
			}
			system("pause");
			break;
		case 9://返回给定结点的最左孩子
			char cur_e3;
			cout<<"请输入结点的值：";
			cin>>cur_e3;
			if(PT.LeftChild(cur_e3))
			{
				cout<<"结点 "<<cur_e3<<" 的最左孩子结点为："<<PT.LeftChild(cur_e3)<<endl;
			}
			else
			{
				cout<<"该结点是叶子结点，或该结点不存在！"<<endl;
			}
			system("pause");
			break;
		case 10://返回给定结点右兄弟结点值
			char cur_e4;
			cout<<"请输入结点的值：";
			cin>>cur_e4;
			if(PT.RightSibling(cur_e4))
			{
				cout<<"该结点的右兄弟结点值为："<<PT.RightSibling(cur_e4)<<endl;
			}
			else
			{
				cout<<"该结点不存在，或该结点没有右兄弟！"<<endl;
			}
			system("pause");
			break;
		case 11:
			PT.Print();
			system("pause");
			break;
		case 12:
			
			c.CreateTree('#');
			cout<<"将树c插入到当前树中：输入插入位置双亲结点值以及插入位置";
			int insertPos;
			char p;
			cin>>p>>insertPos;

			PT.InsertChild(p,insertPos,c.GetTree());
			break;
		case 13:
			char par;
			cout<<"请输入要删除结点双亲结点值：";
			cin>>par;
			cout<<"请输入删除的子树序列：";
			int pos;
			cin>>pos;
			PT.DeleteChild(par,pos);
			break;
		case 14://层次遍历二叉树
			PT.TraverseTree();
			system("pause");
			break;
		default:
			break;
		}
	}while(op!=0);
	return 0;
}