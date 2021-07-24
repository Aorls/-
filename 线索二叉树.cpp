#include<bits/stdc++.h>

typedef char ElemType;


typedef struct node
{
	ElemType data;  //��������� 
	int ltag, rtag;  // ���ӵ�������� 
	struct node *lchild; //���ӻ�����ָ�� 
	struct node *rchild;  //�Һ��ӻ�����ָ�� 
}TBTNode;  


TBTNode *pre; //ȫ�ֱ��� 

void CreateBiTree(TBTNode *&T)//����������ַ�����������������
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

void Thread(TBTNode * &p) //�Զ�����p�������������� 
{
	if(p != NULL)
	{
		Thread(p->lchild); //������������ 
		if(p->lchild == NULL)  //���Ӳ����ڣ�����ǰ����������� 
		{
			p->lchild = pre;//������ǰ����ǰ��������� 
			p->ltag = 1;
		}
		else				//p������������������ 
			p->ltag = 0; 
		if(pre->rchild == NULL) //��pre�ĺ�̽�������� 
		{
			pre->rchild = p;  //����ǰ�����ĺ�̽������ 
			pre->rtag = 1;
		}
		else
			pre->rtag = 0;
		pre = p;
		Thread(p->rchild);  //������������ 
	}
}

TBTNode *CreateThread(TBTNode *b)  //���������������� 
{
	TBTNode *root;
	root = (TBTNode *)malloc(sizeof(TBTNode));  //����ͷ��� 
	root->ltag = 0;
	root->rtag = 1;
	root->rchild = b;
	if(b == NULL)  //�ն����� 
		root->lchild = root;
	else
	{
		root->lchild = b;
		pre = root;  //pre�ǽ��p��ǰ����㣬���������� 
		Thread(b);  //������������������� 
		pre->rchild = root;  //���������ָ��ͷ�������� 
		pre->rtag = 1;
		root->rchild = pre; //ͷ����������� 
	}
	return root;
}

void ThlnOrder(TBTNode *tb)  //tbָ������������������ͷ��� 
{
	TBTNode *p = tb->lchild;  //pָ������ 
	while(p != tb)
	{
		while(p->ltag == 0)     //�ҿ�ʼ��� 
			p = p->lchild;
		printf("%c ", p->data);   //���ʿ�ʼ��� 
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
