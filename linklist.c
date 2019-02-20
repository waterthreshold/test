#include <stdlib.h>
#include <stdio.h>

typedef struct node{
	int val;
	struct node *next;
}node_t;

int print(node_t *n){
	int i=0;
	node_t *tmp=NULL;
	if (n==NULL)
		return i;
	tmp=n;
	while (tmp !=NULL){
		printf ("%d:%d\n",i++,tmp->val);
		tmp = tmp->next;
	}
	return i;
}

int remove_node(node_t **head,int n){
	int ret;
	node_t* t;
	if (head == NULL){
		printf ( "list is NULL\n");
		return ret;
	}
	t = *head;
	while (t->next != NULL ){
		if ((t->next)->val ==n ){
			printf ("find %d\n",n);
			node_t* tmp;
			tmp = t->next;
			t->next= (t->next)->next;
			free(tmp);
			break;
		}
		t = t->next;
	}
}

int insert (node_t **head,int n){
	int ret=0;
	node_t *tmp = (node_t *)malloc (sizeof (node_t));
	node_t* t;
	tmp->val=n;
	tmp->next=NULL;
	
	if (*head == NULL){
		printf (" list is NULL\n");
		*(head)= tmp;
		return ret;
	}
	t = (*head);
	while (t->next != NULL){
		t=t->next;
	}
	t->next=tmp;
	return ret;
}

void print_usage (){
	printf ("----------------------------\n");
	printf ("1.print length\n2.insert number\n3.remove number\n");
	printf ("----------------------------\n");
}

int main (){
	node_t *head=NULL;
	int len=0;
	int n,val=0;
	int ret=0;
	while (1){
		print_usage();
		scanf ("%d",&n);
		switch (n){
			case 1 :
				len = print (head);
				break;
			case 2 :
				printf ("insert value:");
				scanf ("%d",&val);
				ret =insert (&head,val);
				printf ("ret=%d\n",ret);
				break;
			case 3 :
				printf ("remove value:");
				scanf ("%d",&val);
				ret =remove_node (&head,val);
				break;
			default :
				print_usage();
				break;
		}
	}
	return EXIT_SUCCESS;
}