/**
 * Singly Linked List Header File
 * @author Pasindu Ravimal
 * @version 2.0
 * @date 12/11/2023
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define type int

typedef struct _Node ListNode;

typedef struct _Node{
    type* data;
    ListNode* next;
}ListNode;

typedef struct _List{
    ListNode* head;
    int nodeCount;
}SinglyLinkedList;

/**
 * Adds a node to the end of the Singly Linked List
 * 
 * Parameters:
 * SinglyLinkedList* list       The SinglyLinkedList to add the node.
 * type* data                   The data to add.
*/
void addTailNode(SinglyLinkedList* list, type* data){
    ListNode* temp;
    temp = (ListNode*) calloc(1, sizeof(ListNode));
    type* tempData = (type*) calloc(1, sizeof(type));

    *tempData = *data;

    temp->data = tempData;
    temp->next = NULL;

    if (list->head == NULL){
        list->head = temp;
        list->nodeCount = 1;
        return;
    }

    ListNode* current = list->head;
    int count = (list->nodeCount) - 1;

    for (int i = 0; i < count; i++){
        current = current->next;
    }

    current->next = temp;
    list->nodeCount += 1;
}

/**
 * Prints the SinglyLinkedList.
 * 
 * Parameters:
 * SinglyLinkedList* list       The list to be printed.
*/
void printList(SinglyLinkedList* list){
    if (list->head != NULL){

        ListNode* current = list->head;
        int count = list->nodeCount;

        for (int i = 0; i < count; i++){

            printf("Data = %d\n", *(current->data));

            current = current->next;
        }
    } else {
        printf("List is empty!");
    }
}

/**
 * Adds a node to the start of the Singly Linked List
 * 
 * Parameters:
 * SinglyLinkedList* list       The SinglyLinkedList to add the node.
 * type* data                   The data to add.
*/
void addNewHead(SinglyLinkedList* list, type* data){

    ListNode* temp;
    temp = (ListNode*) calloc(1, sizeof(ListNode));
    type* tempData = (type*) calloc(1, sizeof(type));

    *tempData = *data;

    temp->data = tempData;
    temp->next = list->head;

    list->head= temp;

}

/**
 * Gets the node count of a list.
 * 
 * Parameters:
 * SinglyLinkedList* list       The SinglyLinkedList to count nodes.
 * 
 * Returns:
 *      The node count of the list.
*/
int getNodeCount(SinglyLinkedList* list){

    return list->nodeCount;
}

void removeNode(SinglyLinkedList* list, type* data){
    ListNode* temp;
    temp = (ListNode*) calloc(1, sizeof(ListNode));

    if (list->head != NULL){
        ListNode* current = list->head;
        ListNode* previous = NULL;

        while (current->data != data){
            if(current->next != NULL){
                previous = current;
                current = current->next;
            } else {
                printf("Error: Cannot remove the node. Data not found!\n");
                return;
            }
        }

        if (previous == NULL){
           list->head = list->head->next;
           free(current);
           return; 
        }

        previous->next = current->next;
        free(current);

    } else {
       printf("Empty list!\n");
    }
}
