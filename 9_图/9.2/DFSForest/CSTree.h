
#ifndef CSTREE
#define CSTREE
template <class T>
struct CSTree{
	//Ê÷µÄ¶þ²æÁ´±í´æ´¢
	T data;
	CSTree *firstchild; //º¢×Ó
	CSTree *nextsibling;//ÐÖµÜ
};
#endif