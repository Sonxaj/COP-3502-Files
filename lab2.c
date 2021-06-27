#include <stdio.h>
#include <stdlib.h>

/*
    Lab 2, as per the zoom session. Slight differences with some print
    statements, but otherwise the same.
*/

// full of errors!


// stores one node of the linked list
typedef struct node{
    int data;
    struct node* next;
}node;

// stores our queue
typedef struct queue{
    struct node* front;
    struct node* back;
}queue;


// functions
void init(queue* qptr);

int enqueue(queue* qptr, int val);

int dequeue(queue* qptr);

int empty(queue* qptr);

int front(queue* qptr);

void displayQueue(queue* qptr);



int main(void){
    queue* myqptr = (queue*)malloc(sizeof(queue));
    init(myqptr);

    int choice, data;

    while(1){
        printf("\n\nChoose your option:\n\n");
        printf("Enter your choice:");
        scanf("%d", &choice);

        switch(choice){

            case 1:
                printf("\nEnter the data you want to enqueue: ");
                scanf("%d", &data);
                enqueue(myqptr, data);
                displayQueue(myqptr);
                break;

            case 2:
                data = dequeue(myqptr);
                if(data != -1){
                    printf("\n%d was deleted from the queue.\n", data);
                    displayQueue(myqptr);
                }else{
                    printf("Queue is empty!");
                }
                break;

            case 3:
                displayQueue(myqptr);
                break;

            case 4:
                exit(1);
                break;

            default:
                printf("Wrong choice! \n");
                break;
        }
    }
}

void init(queue* qptr){

    qptr->front = NULL;
    qptr->back = NULL;
}

int enqueue(queue* qptr, int val){

    node* temp = (node*)malloc(sizeof(node));

    if(temp != NULL){

        temp->data = val;
        temp->next = NULL;

        if(qptr->back != NULL){

            qptr->back->next = temp;
        }

        qptr->back = temp;

        if(qptr->front == NULL){
            qptr->front = temp;
        }

        return 1;

    }else{

        return 0;
    }
}

int dequeue(queue* qptr){

    node* temp;
    int retval;

    if(qptr->front == NULL){
        return -1;
    }

    retval = qptr->front->data;
    

    temp = qptr->front;

    qptr->front = qptr->front->next;

    if(qptr->front == NULL){
        qptr->back = NULL;
    }

    free(temp);

    return retval;
};

int empty(queue* qptr){

    return qptr->front == NULL;
};

int front(queue* qptr){

    if(qptr->front != NULL){

        return qptr->front->data;

    }else{
        return -1;
    }
}

void displayQueue(queue* qptr){
    node* t = qptr->front;

    while(t){
        printf("%d ", t->data);
        t=t->next;
    }
}
