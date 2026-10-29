
#include<stdio.h>
#include<stdlib.h>

// Structure representing a node in the doubly linked list
struct node{
    int data;               // Stores the data
    struct node *front;     // Points to the next node
    struct node *back;      // Points to the previous node
};

// Function declarations
void f_i(struct node **head,int x);  // Insert at front
void b_i(struct node **head,int x);  // Insert at back
int f_d(struct node **head);         // Delete from front
int b_d(struct node **head);         // Delete from back
void display(struct node *head);     // Display the linked list
int isfull(struct node *head);       // Checks whether list is non-empty

int main(){
    struct node *head;
    head=NULL;   // Initially, the linked list is empty

    int val,i,j=1;

    // Repeat the menu until the user chooses to exit
    while(j){
        printf("\n1: Insert from begining\n2: Insert from back\n3: Delete from front\n4: Delete from back\n5: Display\n6: Exit\n");
        printf("Enter the choice: ");
        scanf("%d",&val);

        switch(val){

            case 1:
                // Read data and insert a node at the beginning
                printf("\nEnter the data: ");
                scanf("%d",&i);
                f_i(&head,i);
                display(head);
                break;

            case 2:
                // Read data and insert a node at the end
                printf("\nEnter the data: ");
                scanf("%d",&i);
                b_i(&head,i);
                display(head);
                break;

            case 3:
                // Delete the first node only if the list is non-empty
                if(isfull(head)){
                    i = f_d(&head);
                    printf("\n%d is deleted from front\n",i);
                }
                display(head);
                break;

            case 4:
                // Delete the last node only if the list is non-empty
                if(isfull(head)){
                    i = b_d(&head);
                    printf("\n%d is deleted from back\n",i);
                }
                display(head);
                break;

            case 5:
                // Display all nodes in the linked list
                display(head);
                break;

            case 6:
                // Set j to 0 to terminate the menu loop
                j=0;
                break;

            default:
                // Handle choices that are not in the menu
                printf("\nInvalid choice\n");
        }
    }
    return 0;
}

// Insert a new node at the beginning
void f_i(struct node **head,int x){
    struct node *temp;

    // Allocate memory for the new node
    temp=(struct node*)malloc(sizeof(struct node));

    // Stop insertion if memory allocation fails
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    // Initialize the new node
    temp->data=x;
    temp->front=NULL;
    temp->back=NULL;

    if((*head)==NULL){
        // If the list is empty, the new node becomes the head
        (*head)=temp;
    }
    else{
        // Link the new node to the current first node
        temp->front=(*head);

        // Update the old first node's backward pointer
        (*head)->back=temp;

        // Update head to point to the new first node
        (*head)=temp;
    }
    return;
}

// Insert a new node at the end
void b_i(struct node **head,int x){
    struct node *temp,*ptr=(*head);

    // Allocate memory for the new node
    temp=(struct node*)malloc(sizeof(struct node));

    // Stop insertion if memory allocation fails
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    // Initialize the new node
    temp->data=x;
    temp->front=NULL;
    temp->back=NULL;

    if((*head)==NULL){
        // If the list is empty, the new node becomes the head
        (*head)=temp;
    }
    else{
        // Traverse until ptr reaches the last node
        while(ptr->front!=NULL)
            ptr=ptr->front;

        // Connect the last node to the new node
        ptr->front=temp;

        // Connect the new node back to the previous last node
        temp->back=ptr;
    }
    return;
}

// Delete the first node and return its data
int f_d(struct node **head){
    int i;
    struct node *cur=(*head);

    if(cur->front==NULL){
        // Special case: the list contains only one node
        i=cur->data;

        // Make the list empty
        (*head)=NULL;

        // Release the deleted node's memory
        free(cur);
        return i;
    }

    // Save the first node's data before deleting it
    i=cur->data;

    // Move head to the second node
    (*head)=(*head)->front;

    // Disconnect the old first node
    cur->front=NULL;

    // The new first node has no previous node
    (*head)->back=NULL;

    // Free the deleted node
    free(cur);

    return i;
}

// Delete the last node and return its data
int b_d(struct node **head){
    int i=-1;

    // cur traverses the list; prev tracks the previous node
    struct node *cur=(*head),*prev=NULL;

    if(cur->front==NULL){
        // Special case: the list contains only one node
        i=cur->data;

        // The list becomes empty
        (*head)=NULL;

        // Free the only node
        free(cur);
        return i;
    }

    // Traverse until cur reaches the last node
    while(cur->front!=NULL){
        prev=cur;
        cur=cur->front;
    }

    // Save the last node's data
    i=cur->data;

    // Make the previous node the new last node
    prev->front=NULL;

    // Disconnect the node being deleted
    cur->front=NULL;
    cur->back=NULL;

    // Release the deleted node's memory
    free(cur);

    return i;
}

// Display all nodes from the first node to the last node
void display(struct node *head){
    if(head==NULL){
        // Handle an empty linked list
        printf("\nThe Linked List is Empty\n");
    }
    else{
        printf("\n");

        // Print each node until the last node is reached
        while(head->front!=NULL){
            printf("%d->",head->data);

            // Move to the next node
            head=head->front;
        }

        // Print the last node without a trailing arrow
        printf("%d",head->data);
    }

    printf("\n");
    return;
}

// Return 1 if the list is non-empty; otherwise return 0
int isfull(struct node *head){
    if(head==NULL)
        return 0;
    else
        return 1;
}
