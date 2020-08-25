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
	char *temp;
        new->pNext = linked_head->pNext;
	linked_head->pNext = new;
	temp = linked_head->data;
	linked_head->data = new->data;
	new->data = temp;	
}

void insert_tail(mynode *head,mynode *new)
{
	mynode *p;
	p = head;
	while(p->pNext!=NULL) p = p->pNext;
	p->pNext = new;
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
	insert_head(pHeader,build_a_node(s));
	insert_head(pHeader,build_a_node("thrid"));
	insert_head(pHeader,build_a_node("fourth"));
	insert_head(pHeader,build_a_node("fifth"));
	insert_head(pHeader,build_a_node("sixth"));
	insert_tail(pHeader,build_a_node("tail1"));
	insert_tail(pHeader,build_a_node("tail2"));
	insert_tail(pHeader,build_a_node("tail3"));
	display(pHeader);
//	insert(pHeader);
	pHeader->pNext =NULL;
	display(pHeader);
	return 0;
}




