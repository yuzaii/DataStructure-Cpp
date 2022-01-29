#include"BinaryTree.cpp"
#include"windows.h"
int main()
{
	int MainMenu=-1;
	BinaryTree<int> T;
	BinaryTree<int> t;
	while(MainMenu!=6)
	{
		system("cls");
		cout<<"--------------主菜单--------------"<<endl;
		cout<<"	1--创建二叉树(元素类型为整数) "<<endl;
		cout<<"	2--树形显示二叉树"<<endl;
		cout<<"	3--获取二叉树信息  >>【进入子菜单】"<<endl;
		cout<<"	4--对二叉树操作    >>【进入子菜单】"<<endl;
		cout<<"	5--遍历二叉树      >>【进入子菜单】"<<endl;
		cout<<"	6--退出"<<endl;
		cout<<"	----------------------------------"<<endl;
		cout<<"		请选择操作：[ ]";
		cout<<"\b\b";
		cin>>MainMenu;
		switch(MainMenu)
		{
		case 1:
			T.CreateBiTree(-1);
			break;
		case 2:
			cout<<"下面显示的是一棵左转了90度的树!"<<endl;
			T.DisplayBTreeShape(T.GetRoot());//第一个参数是根结点指针，第二个参数为默认的1 
			cout<<endl;
			system("pause");
			break;
		case 3:
			int op;
			//cin>>op;
			do
			{
				//system("cls");
				cout<<" ---3-获取二叉树信息---------"<<endl;
				cout<<"	0. 返回主菜单"<<endl;
				cout<<"	1. 获取树根结点值"<<endl;
				cout<<"	2. 判断树是否为空"<<endl;
				cout<<"	3. 求树的深度"<<endl;
				cout<<"	4. 双亲结点值"<<endl;
				cout<<"	5. 左孩子值"<<endl;
				cout<<"	6. 右孩子值"<<endl;
				cout<<"	7. 左兄弟值"<<endl;
				cout<<"	8. 右兄弟值"<<endl;
				cout<<"	9. 叶子结点的个数"<<endl;
				cout<<"	10.树形显示二叉树"<<endl;
				cout<<" ------------------------------"<<endl;
				cout<<"	请选择操作：[  ]";
				cout<<"\b\b\b";
				cin>>op;
				switch(op)
				{
				case 1:
					int root;
					if(T.RootValue(root)==true)
						cout<<"树根结点的值为："<<root<<endl;					
					else
						cout<<"二叉树为空"<<endl;
					system("pause");
					break;
				case 2:
					if(T.IsEmpty()==true)
						cout<<"二叉树为空！"<<endl;
					else 
						cout<<"二叉树不空！"<<endl;
					system("pause");
					break;
				case 3:
					cout<<"二叉树的深度为："<<T.BiTreeDepth()<<endl;
					system("pause");
					break;
				case 4:
					cout<<"请输入结点值：";
					int node1;
					cin>>node1;
					cout<<"该结点的双亲结点为："<<T.GetParent(node1)<<endl;
					system("pause");
					break;
				case 5:
					cout<<"请输入结点值：";
					int node2;
					cin>>node2;
					cout<<"该结点的左孩子结点值为："<<T.GetLeftChild(node2)<<endl;
					system("pause");
					break;
				case 6:
					cout<<"请输入结点值：";
					int node3;
					cin>>node3;
					cout<<"该结点的右孩子结点值为："<<T.GetRightChild(node3)<<endl;
					system("pause");
					break;
				case 7:
					cout<<"请输入结点值：";
					int node4;
					cin>>node4;
					cout<<"该结点的左兄弟结点值为："<<T.GetLeftSibling(node4)<<endl;
					system("pause");
					break;
				case 8:
					cout<<"请输入结点值：";
					int node5;
					cin>>node5;
					cout<<"该结点的右兄弟结点值为："<<T.GetRightSibling(node5)<<endl;
					
					system("pause");
					break;
				case 9:
					cout<<"二叉树的叶子结点个数为："<<T.LeafCount()<<endl;
					system("pause");
					break;
				case 10:
					cout<<"下面显示的是一棵左转了90度的二叉树!"<<endl;
					T.DisplayBTreeShape(T.GetRoot());//第一个参数是根结点指针，第二个参数为默认的1 
					cout<<endl;
					system("pause");
					break;
				default:
					break;
				}
			}while(op!=0);
			break;
		case 4:
			int op2;
			do
			{
				cout<<" ---------4 对二叉树进行操作----------"<<endl;
				cout<<"	0. 返回主菜单"<<endl;
				cout<<"	1. 销毁二叉树"<<endl;
				cout<<"	2. 给指定结点赋值"<<endl;
				cout<<"	3. 插入"<<endl;
				cout<<"	4. 删除"<<endl;
				cout<<"	5. 显示二叉树"<<endl;
				cout<<" ------------------------------------"<<endl;
				cout<<"	请选择操作：[ ]";
				cout<<"\b\b";
				cin>>op2;
				switch(op2)
				{
				case 0:
					break;
				case 1:
					T.ClearBiTree();
					cout<<"已经将二叉树销毁！"<<endl;
					system("pause");
					break;
				case 2:
					int ChangeValue;//要改变的结点值
					int NewValue;//修改之后的结点值
					cout<<"请输入要修改的结点值：";
					cin>>ChangeValue;
					cout<<"请输入修改之后的结点值："<<endl;
					cin>>NewValue;
					if(T.SearchNode(ChangeValue)) 
					{
						(T.SearchNode(ChangeValue))->data=NewValue;
						cout<<"修改成功！"<<endl;
					}
					else
					{
						cout<<"修改失败！"<<endl;
					}
					system("pause");
					break;
				case 3:
					cout<<"请创建一棵没有右子树的二叉树："<<endl;
					t.CreateBiTree(-1);
					cout<<"请输入要插入的二叉树的结点值"<<endl;
					int invalue;
					cin>>invalue;
					cout<<"请选择插入左子树（0）还是右子树（1）";
					int lr;
					cin>>lr;
					if(T.SearchNode(invalue)&&t.GetRoot()&&(t.GetRoot()->rchild)==NULL)
					{
						t.InsertChild(T.SearchNode(invalue),t.GetRoot(),lr);
						cout<<"操作成功！"<<endl;
						cout<<"操作以后的二叉树为："<<endl;
						t.PreTraBiTree();
					}
					else
					{
						cout<<"操作失败！"<<endl;
					}
					system("pause");
					break;
				case 4:
					cout<<"请输入结点的值，"<<endl;
					int mm;
					cin>>mm;
					cout<<"删除左结点请输入0，右结点输入1"<<endl;
					int tag;
					cin>>tag;
					if(T.SearchNode(mm))
					{
						T.DeleteChild(T.SearchNode(mm),tag);
						cout<<"操作成功！已删除指点的子树！"<<endl;
					}
					else
					{
						cout<<"操作失败！"<<endl;
					}
					T.PreTraBiTree();
					system("pause");
					break;
				case 5:
			        cout<<"下面显示的是一棵左转了90度的树!"<<endl;
			        T.DisplayBTreeShape(T.GetRoot());//第一个参数是根结点指针，第二个参数为默认的1 
		     	    cout<<endl;
			        system("pause");
			        break;
				default:
					break;
				}
			}while(op2!=0);
			break;
		case 5:
			int op3;
			do
			{
				//system("cls");
				cout<<" ---------5-遍历二叉树----------------------"<<endl;
				cout<<"	0. 返回主菜单"<<endl;
				cout<<"	1. 先序遍历二叉树（递归）"<<endl;
				cout<<"	2. 中序遍历二叉树（递归）"<<endl;
				cout<<"	3. 后序遍历二叉树（递归）"<<endl;
				cout<<"	4. 先序遍历二叉树（非递归）"<<endl;
				cout<<"	5. 中序遍历二叉树（非递归）"<<endl;
				cout<<"	6. 层次遍历"<<endl;
				cout<<" --------------------------------------------"<<endl;
				cout<<"		请选择操作：[ ]";
				cout<<"\b\b";
				cin>>op3;
				switch(op3)
					
				{
				case 1:
					T.PreTraBiTree();
					system("pause");
					break;
				case 2:
					T.InTraBiTree();
					system("pause");
					break;
				case 3:
					T.PostTraBiTree();
					system("pause");
					break;
				case 4:
					T.PreTraBiTree_N();
					system("pause");
					break;
				case 5:
					T.InTraBiTree_N();
					system("pause");
					break;
				case 6:
					T.LevelTraBiTree();
					system("pause");
					break;
				default:
					break;
				}
			}while(op3!=0);
			break;
		case 6:
			cout<<"程序运行结束，Bye-Bye!"<<endl;
			break;
		default:
			break;
}

	}
	return 0;
	
}
