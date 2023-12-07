#include <stdio.h>

struct Node{
    int data;
    struct Node* next;
};

struct Node head;

int main(){
    head.data = 0;
    head.next = NULL;

    struct Node temp = {1, NULL};

    head.next = &temp;

    struct Node temp2 = {2,NULL};

    temp.next = &temp2;

    for(int i = 0; i < 2; i++){
        struct Node temp3 = {i, NULL};

        struct Node* current = &head;

        while(current->next != NULL){
            current = current->next;
        }

        current->next = &temp3;
    }

}