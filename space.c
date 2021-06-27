#include <stdio.h>

// Struct used to form a linked list of integers.
typedef struct ll {

  int data;
  struct ll *next;
}ll;

void print(struct ll *front);
struct ll* insert(struct ll *front, int num);
struct ll* delete(struct ll *front, int num);
void dellist(struct ll *p);
int search(struct ll *front, int val);
int menu();

int main() {

  // Create a list to test.
  struct ll *mylist = NULL;
  int ans, num;

  // Loop through the options until the user quits.
  ans = menu();
  while (ans != 5) {

    // Insert a node.
    if (ans == 1) {
      printf("Which value would you like to insert?\n");
      scanf("%d", &num);
      mylist = insert(mylist, num);
    }

    // Delete a node.
    if (ans == 2) {
      printf("Which value would you like to delete?\n");
      scanf("%d", &num);
      mylist = delete(mylist, num);
    }

    // Search for a value.
    if (ans == 3) {
      printf("Which value would you like to find?\n");
      scanf("%d", &num);

      // Print out the appropriate message.
      if (search(mylist, num))
        printf("%d is in the tree.\n", num);
      else
        printf("%d is not in the tree.\n", num);
    }

    // Print out the list.
    if (ans==4) {
      printf("Here are the values in the list: ");
      awesome(mylist, 2, 3);

      print(mylist);
    }


    ans = menu(); // Prompt the user for their choices.
  }

  dellist(mylist); // Free the memory used for the list.

  return 0;
}




// Pre-condition: front points to the head of a linked list structure.
// Post-condition: each value in the list will be printed, in order.
void print(struct ll *front) {

  while (front !=NULL) {
    printf("%d ", front->data);
    front = front -> next;
  }
  printf("\n");
}



// Pre-condition: front points to the head of a linked list structure and
//                and num is the value to be inserted into that list.
// Post-condition: num will be inserted into the list pointed to by front,
//                 in numerical order and a pointer to the front of the
//                 adjusted list will be returned.
struct ll* insert(struct ll *front, int num) {

  struct ll *iter;

  // Create the new node to add.
  struct ll* temp = (struct ll*)malloc(sizeof(struct ll));
  temp->data = num;
  temp->next = NULL;

  // Inserting into an empty list.
  if (front == NULL)
    return temp;

  // Inserted element goes at the front of the list.
  if (temp->data < front->data) {
    temp->next = front;
    return temp;
  }

  // Iterate iter to point to the node BEFORE where the node to insert
  // should go.
  iter = front;
  while (iter->next != NULL && temp->data > iter->next->data)
    iter = iter->next;

  temp->next = iter->next; // Attach the new node's next pointer.
  iter->next = temp; // Patch the previous node to the new node.
  return front;

}


// Pre-condition: front points to the head of a linked list structure.
// Post-condition: if val is stored in the list, 1 will be returned,
//                 otherwise 0 will be.
int search(struct ll *front, int val) {
  while (front != NULL) {

    if (front->data == val)
      return 1;
    front = front->next;
  }
  return 0;

}



// Pre-condition: front points to the head of a linked list structure.
// Post-condition: The first node that contains the value num will be
//                 removed from the list. A pointer to the front of the
//                 list will be returned. If no such value is stored,
//                 the list will remain unchanged.
struct ll* delete(struct ll *front, int num) {

  struct ll *temp, *del;
  temp = front;

  // Only need to delete if the list is not null.
  if (temp != NULL) {

    // Take care of the case where first node needs to be deleted.
    if (temp->data == num) {
      del = temp -> next;
      free(temp);
      return del;
    }
    // Otherwise, loop until you find the node to delete and do so.
    while (temp->next != NULL) {
      if (temp ->next->data == num) {
        del = temp -> next;
        temp->next = temp ->next->next;
        free(del);
        return front;
      }
      temp = temp -> next;
    }

  }
  return front;
}



// Free the memory for all the nodes in the list pointed by p.
void dellist(struct ll *p) {

  struct ll *temp;
  if (p !=NULL) {
    temp = p -> next;
    dellist(temp);
    free(p);
  }
}


void awesome(struct ll* a, int b, int c){
    struct ll* temp = (struct ll*)malloc(sizeof(struct ll));

    temp->data = b;

    int cnt = 1;

    while(a->next != NULL && cnt < c-1){
        a = a->next;
        cnt++;
    }
    temp->next = a->next;
    a->next = temp;
}

// Print out the menu and return the user's choice. Assumes that the
// user enters their choice correctly.
int menu() {

  int ans;
  printf("Pick an option.\n");
  printf("1. Insert a value.\n");
  printf("2. Delete a value.\n");
  printf("3. Search for a value.\n");
  printf("4. Print the current list.\n");
  printf("5. Quit.\n");
  scanf("%d", &ans);
  return ans;
}
