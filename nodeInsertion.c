#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {

  char name[30];
  int info;

  struct node *next;
}node;



//functions
node *insertatfrontinlist(struct node *l, struct node node1);
node *insertatbackinlist(struct node *l, struct node node1);
void printlis(struct node *l);




int main (void) {

    int i;
    node nodeA, *head;
    head=NULL;


    for(i=0;i<4;i++){

        scanf( "%s", &nodeA.name);


        head= insertatbackinlist(head, nodeA);
        }

        printlis(head);
}



//node insertions

//front insert
node *insertatfrontinlist(node *l, node node1){

    node *temp;
    temp= (node*)malloc(sizeof(node));

    strcpy(temp->name,node1.name);

    temp->next = l;
    return (temp);
}





//back insert
node *insertatbackinlist(node *l, node node1){

    node *temp, *temp2, *temp3;
    temp= (node*) malloc(sizeof(struct node));

    strcpy(temp->name,node1.name);

    temp->next = NULL;

    temp2 = l;

    if (l==NULL){
        l=temp;
    }

    else{
        while (temp2 != NULL){

            temp3= temp2;
            temp2 = temp2->next;
        }
    temp3->next = temp;
    }
    return (l);
}




//between insert
node *sortedInsert(node *head, int item){

	node *temp = (node*)malloc(sizeof(node));

	temp->info = item;
	temp->next = NULL;

	if(head == NULL || head->info >= item){

		//inserts in the beginning
		temp-> next = head;
		head = temp;

	}else{

		node *t = head;

		while(t->next != NULL && t->next->info < item){

			t = t->next;

			temp->next = t->next;

			t->next = temp;
		}
	}
    return head;
}






//node deletions

//front delete




//back delete

//between delete






void printlis(struct node *l){

    if (l==NULL){
        printf("Empty\n");
    }

    while (l != NULL){
        printf("Name=%s \n", l->name);
        l= l->next;
    }
}
