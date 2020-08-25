#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
	char *data;
	struct node *pNext;
}mynode;

mynode *build_a_node(char *data)
{
	mynode *p = (mynode*)malloc(sizeof(mynode));
	if(NULL == p)
	{
		printf("memory allocation Error.\n");
		return NULL;
	}
	memset(p,0,sizeof(mynode));
	p->data = data;
	p->pNext = NULL; 
	return p;
};
void insert_head(mynode *linked_head,mynode *new )
{
	mynode *p = linked_head;
	printf("p = %p,linked_head = %p",p,linked_head);	
	linked_head = new;
	linked_head->pNext = p;
}


 void display(mynode *head)
 {
 	mynode *p;
 	p = head;
 	printf("\nChain is:");
 	while(p->pNext!=NULL)
	{	
		printf("%s   ",p->data);
 		p=p->pNext;
	}
		printf("%s   \n",p->data);
  }

struct node *insert(struct node *head)
{
 struct node *r,*p;
 int i,j;
 char *str = (char *)malloc(sizeof(char *));
 p = head;
 r = (struct node*)malloc(sizeof(struct node));
 printf("请输入你要插入的位置:\n");
 scanf("%d",&i);
 printf("请输入你要插入的字符：\n");
 scanf("%s",str);
 r->data = str;
 for(j=1;j<i;j++)                    //将指针移动到要插入新结点的位置
  p = p->pNext;
 r->pNext = p->pNext;
 p->pNext = r;
 return(head);
}


int main(void)
{
	char *s ="second";
	
	mynode *pHeader;
	pHeader = build_a_node("head");
	mynode * p2 = build_a_node(s);
	pHeader->pNext = p2;
	
	insert_head(pHeader,build_a_node(s));
	insert_head(pHeader,build_a_node("tail1"));
	insert_head(pHeader,build_a_node("tail2"));
	insert_head(pHeader,build_a_node("tail3"));
	display(pHeader);

	mynode *p =pHeader;
	printf("p = %p,pHeader = %p",p,pHeader);	
	printf("pnext = %p,pHeadernext = %p",p->pNext,pHeader->pNext);	
	display(pHeader);
	return 0;
}




