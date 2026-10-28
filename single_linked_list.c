
#include<stdio.h>
#include<stdlib.h>

// Structure representing a node of the linked list
struct node{
    int data;              // Stores the data
    struct node *next;     // Points to the next node
};

// Function declarations
void f_i(struct node **head,int x);  // Insert at front
void b_i(struct node **head,int x);  // Insert at back
int f_d(struct node **head);         // Delete from front
int b_d(struct node **head);         // Delete from back
void display(struct node *head);     // Display the list
int isfull(struct node *head);       // Checks whether list is non-empty

int main(){
    struct node *head;
    head=NULL;  // Initially, the list is empty

    int val,i,j=1;

    // Continue displaying the menu until the user exits
    while(j){
        printf("\n1: Insert from begining\n2: Insert from back\n3: Delete from front\n4: Delete from back\n5: Display\n6: Exit\n");
        printf("Enter the choice: ");
        scanf("%d",&val);

        switch(val){

            case 1:
                // Read data and insert a new node at the beginning
                printf("Enter the data: ");
                scanf("%d",&i);
                f_i(&head,i);
                display(head);
                break;

            case 2:
                // Read data and insert a new node at the end
                printf("Enter the data: ");
                scanf("%d",&i);
                b_i(&head,i);
                display(head);
                break;

            case 3:
                // Delete the first node only if the list is non-empty
                if(isfull(head)){
                    i = f_d(&head);
                    printf("%d is deleted from front\n",i);
                }
                display(head);
                break;

            case 4:
                // Delete the last node only if the list is non-empty
                if(isfull(head)){
                    i = b_d(&head);
                    printf("%d is deleted from back\n",i);
                }
                display(head);
                break;

            case 5:
                // Print all the nodes
                display(head);
                break;

            default:
                // Stop the loop for any choice not handled above
                j=0;
                break;
        }
    }
}

// Insert a new node at the beginning
void f_i(struct node **head,int x){
    struct node *temp;

    // Allocate memory for the new node
    temp=(struct node*)malloc(sizeof(struct node));

    temp->data=x;       // Store the given value
    temp->next=NULL;    // Initially, the new node points to NULL

    if((*head)==NULL){
        // If the list is empty, the new node becomes the head
        (*head)=temp;
    }
    else{
        // Link the new node to the current first node
        temp->next=(*head);

        // Update head to point to the new first node
        (*head)=temp;
    }
    return;
}

// Insert a new node at the end
void b_i(struct node **head,int x){
    struct node *temp,*ptr=(*head);

    // Create and initialize the new node
    temp=(struct node*)malloc(sizeof(struct node));
    temp->data=x;
    temp->next=NULL;

    if((*head)==NULL){
        // If empty, the new node becomes the first node
        (*head)=temp;
    }
    else{
        // Traverse until ptr reaches the last node
        while(ptr->next!=NULL)
            ptr=ptr->next;

        // Connect the last node to the new node
        ptr->next=temp;
    }
    return;
}

// Delete the first node and return its data
int f_d(struct node **head){
    int i;

    // Keep a pointer to the first node
    struct node *cur=(*head);

    i=cur->data;              // Save its data before freeing it

    // Move head to the second node
    (*head)=(*head)->next;

    cur->next=NULL;           // Disconnect the old first node
    free(cur);                // Release its allocated memory

    return i;                 // Return the deleted value
}

// Delete the last node and return its data
int b_d(struct node **head){
    int i=-1;

    // cur traverses the list; prev tracks the previous node
    struct node *cur=(*head),*prev=NULL;

    if(cur->next==NULL){
        // Special case: the list contains only one node
        i=cur->data;

        (*head)=NULL;         // The list becomes empty
        free(cur);            // Free the only node

        return i;
    }

    // Find the last node and its previous node
    while(cur->next!=NULL){
        prev=cur;
        cur=cur->next;
    }

    i=cur->data;              // Save the last node's data

    // Make the previous node the new last node
    prev->next=NULL;

    free(cur);                // Free the deleted last node

    return i;
}

// Display every node from the head to the last node
void display(struct node *head){
    if(head==NULL){
        // An empty list has no nodes to display
        printf("The Linked List is Empty\n");
    }
    else{
        // Print nodes until the last node is reached
        while(head->next!=NULL){
            printf("%d->",head->data);
            head=head->next;  // Move to the next node
        }

        // Print the last node without an arrow afterward
        printf("%d",head->data);
    }
    return;
}

// Returns 1 if the list is non-empty, otherwise returns 0
int isfull(struct node *head){
    if(head==NULL)
        return 0;
    else
        return 1;
}
