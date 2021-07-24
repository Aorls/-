#include<bits/stdc++.h>

typedef char ElemType;


typedef struct node
{
	ElemType data;  //结点数据域 
	int ltag, rtag;  // 增加的线索标记 
	struct node *lchild; //左孩子或线索指针 
	struct node *rchild;  //右孩子或线索指针 
}TBTNode;  


TBTNode *pre; //全局变量 

void CreateBiTree(TBTNode *&T)//根据输入的字符串，创建二叉树。
{
	char e;
	scanf("%c",&e);
	if(e=='#'){
		T=NULL;
	}else{
		T=new TBTNode ();
		if(!T)exit(-1);	
		T->data=e;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return ;  
}

void Thread(TBTNode * &p) //对二叉树p进行中序线索化 
{
	if(p != NULL)
	{
		Thread(p->lchild); //左子树线索化 
		if(p->lchild == NULL)  //左孩子不存在，进行前驱结点线索化 
		{
			p->lchild = pre;//建立当前结点的前驱结点线索 
			p->ltag = 1;
		}
		else				//p结点的左子树已线索化 
			p->ltag = 0; 
		if(pre->rchild == NULL) //对pre的后继结点线索化 
		{
			pre->rchild = p;  //建立前驱结点的后继结点线索 
			pre->rtag = 1;
		}
		else
			pre->rtag = 0;
		pre = p;
		Thread(p->rchild);  //右子树线索化 
	}
}

TBTNode *CreateThread(TBTNode *b)  //中序线索化二叉树 
{
	TBTNode *root;
	root = (TBTNode *)malloc(sizeof(TBTNode));  //创建头结点 
	root->ltag = 0;
	root->rtag = 1;
	root->rchild = b;
	if(b == NULL)  //空二叉树 
		root->lchild = root;
	else
	{
		root->lchild = b;
		pre = root;  //pre是结点p的前驱结点，供加线索用 
		Thread(b);  //中序遍历线索化二叉树 
		pre->rchild = root;  //最后处理，加入指向头结点的线索 
		pre->rtag = 1;
		root->rchild = pre; //头结点右线索化 
	}
	return root;
}

void ThlnOrder(TBTNode *tb)  //tb指向中序线索二叉树的头结点 
{
	TBTNode *p = tb->lchild;  //p指向根结点 
	while(p != tb)
	{
		while(p->ltag == 0)     //找开始结点 
			p = p->lchild;
		printf("%c ", p->data);   //访问开始结点 
		while(p->rtag == 1 && p->rchild != tb)
		{
			p = p->rchild;
			printf("%c ", p->data);
		}
		p = p->rchild;
	}
}

int main()
{
	TBTNode *p;
	CreateBiTree(p);
	p = CreateThread(p);
	ThlnOrder(p);
	
	return 0;
}
