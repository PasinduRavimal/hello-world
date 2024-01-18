#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * A concrete Singly Linked List structure based on Jeff Szuhay's
 * Learning C Programming book.
 * @author Pasindu Ravimal
 * @version 1.0
 * @date 01/17/2024
*/
typedef int ListData;
typedef struct _Node ListNode;

typedef struct _Node {
    ListNode* pNext;
    ListData* pData;
} ListNode;

typedef struct{
    ListNode* pFirstNode;
    ListNode* pLastNode;
    int nodeCount;
} LinkedList;

/* Prototypes:
LinkedList* createLinkedList();
bool isEmpty(LinkedList* pList);
int getSize(LinkedList* pList);
void setSize(LinkedList* pList, int size);
void insertNodetoFront(LinkedList* pList, ListNode* pNode);
void insertNodetoBack(LinkedList* pList, ListNode* pNode);
ListNode* removeNodeFromFront(LinkedList* pList);
ListNode* removeNodeFromBack(LinkedList* pList);
ListNode* getNode(LinkedList* pList, int pos);
ListNode* createNode(ListData* pData);
ListNode* getFirstNode(LinkedList* pList);
ListNode* getLastNode(LinkedList* pList);
ListData* getData(ListNode* pNode);
void setData(ListNode* pNode, ListData* pData);
void setFirstNode(LinkedList* pList, ListNode* Node);
void setLastNode(LinkedList* pList, ListNode* Node);
void deleteNode(ListNode* pNode);
void printList(LinkedList* pList, void (*printData)(ListData* pData), bool dataFlag);
void printNode(ListNode* pNode, void (*printData) (ListData* pData));
void OutofStorage(void);

ListNode* insertNodeAt(LinkedList* pList, ListNode* pNode);
ListNode* removeNodeAt(LinkedList* pList, ListNode* pNode);
void sortList(LinkedList* pList, eSortOrder order);
void concatenateList(LinkedList* pList1, LinkedList* pList2);
*/

/**
 * This function only prints a message to the stderr.
*/
void OutofStorage(void){
    fprintf(stderr, "### FATAL RUNTIME ERROR ###"
    "\n--- No Memory Available --- \n");
    exit(EXIT_FAILURE);
}

/**
 * Creates an instance of a LinkedList.
 * 
 * @return A pointer to the new LinkedList instance.
*/
LinkedList* createLinkedList(){
    LinkedList* pLL = (LinkedList*) calloc(1, sizeof(LinkedList));
    if (pLL == NULL)
        OutofStorage();
    return pLL;
}

/**
 * Gets the size of the given LinkedList.
 * 
 * @param pList A pointer to the LinkedList to get the size.
 * @return The size of the LinkedList.
*/
int getSize(LinkedList* pList){
    return pList->nodeCount;
}

/**
 * Sets the size of the given LinkedList.
 * 
 * @param pList A pointer to the LinkedList to get the size.
*/
void setSize(LinkedList* pList, int size){
    pList->nodeCount = size;
}

/**
 * Checks whether a given LinkedList is empty.
 * 
 * @param pList A pointer to the LinkedList to be checked empty.
 * @return true if the LinkedList is empty.
*/
bool isEmpty(LinkedList* pList){
    return (getSize(pList) == 0);
}

/**
 * Gets the first Node of the LinkedList.
 * 
 * @param pList A pointer to the LinkedList to get the first Node.
 * @return A pointer to the first Node.
*/
ListNode* getFirstNode(LinkedList* pList){
    return pList->pFirstNode;
}

/**
 * Gets the last Node of the LinkedList.
 * 
 * @param pList A pointer to the LinkedList to get the last Node.
 * @return A pointer to the last Node.
*/
ListNode* getLastNode(LinkedList* pList){
    return pList->pFirstNode;
}

/**
 * Sets the first Node of the LinkedList. This function
 * does not change the Node in any means.
 * 
 * @param pList A pointer to the LinkedList to set the first Node.
 * @param pNode A pointer to the Node to be set as the first Node.
*/
void setFirstNode(LinkedList* pList, ListNode* pNode){
    pList->pFirstNode = pNode;
}

/**
 * Sets the last Node of the LinkedList. This function
 * does not change the Node in any means.
 * 
 * @param pList A pointer to the LinkedList to set the last Node.
 * @param pNode A pointer to the Node to be set as the last Node.
*/
void setLastNode(LinkedList* pList, ListNode* pNode){
    pList->pLastNode = pNode;
}

/**
 * Insert a new Node to the Front of the LinkedList.
 * 
 * @param pList A pointer to the LinkedList to add the new Node.
 * @param pNode A pointer to the Node to be added.
*/
void insertNodetoFront(LinkedList* pList, ListNode* pNode){
    ListNode* pNext = getFirstNode(pList);
    setFirstNode(pList, pNode);
    pNode->pNext = pNext;
    pList->nodeCount++;
}

/**
 * Insert a new Node to the Back of the LinkedList. This function
 * is guaranteed to return in constant time.
 * 
 * @param pList A pointer to the LinkedList to add the new Node.
 * @param pNode A pointer to the Node to be added.
*/
void insertNodetoBack(LinkedList* pList, ListNode* pNode){
    if (isEmpty(pList)){
        setFirstNode(pList, pNode);
        setLastNode(pList, pNode);
    } else {
        getLastNode(pList)->pNext = pNode;
    }
    pList->nodeCount++;
}

/**
 * Removes the front Node from the LinkedList and returns it.
 * This does not deallocate the memory that is allocated for the
 * Node. Rather than deleting the Node, this function just unlinks
 * the Node from the LinkedList. In order to deallocate memory, use
 * the deleteCode function on the returned Node.
 * 
 * @param pList A pointer to the LinkedList to unlink the front Node from.
 * @return A pointer to the unlinked Node.
*/
ListNode* removeNodefromFront(LinkedList* pList){
    if (isEmpty(pList))
        return NULL;
    ListNode* pCurr = getFirstNode(pList);
    setFirstNode(pList, getFirstNode(pList)->pNext);
    pList->nodeCount--;
    return pCurr;
}

/**
 * Removes the last Node from the LinkedList and returns it.
 * This does not deallocate the memory that is allocated for the
 * Node. Rather than deleting the Node, this function just unlinks
 * the Node from the LinkedList. In order to deallocate memory, use
 * the deleteCode function on the returned Node.
 * 
 * @param pList A pointer to the LinkedList to unlink the last Node from.
 * @return A pointer to the unlinked Node.
*/
ListNode* removeNodefromBack(LinkedList* pList){
    if (isEmpty(pList)){
        return NULL;
    } else {
        ListNode* pCurr = getFirstNode(pList);
        ListNode* pPrev = NULL;

        while (pCurr->pNext != NULL){
            pPrev = pCurr;
            pCurr = pCurr->pNext;
        }

        pPrev->pNext = NULL;
        setLastNode(pList, pPrev);
        pList->nodeCount--;

        return pCurr;
    }
}

/**
 * Gets the Node at the given position.
 * 
 * @param pList A pointer to the LinkedList to get the Node from.
 * @param pos The position of the Node.
 * @return A ponter to the Node at the given position.
*/
ListNode* getNode(LinkedList* pList, int pos){
    ListNode* pCurr = getFirstNode(pList);

    if (isEmpty(pList)){
        return NULL;
    } else if (pos == 0){
        return pCurr;
    } else if (pos == getSize(pList)){
        return getLastNode(pList);
    } else {
        int i = 0;
        while (pCurr->pNext != NULL){
            if (i == pos)
                return pCurr;
            i++;
            pCurr = pCurr->pNext;
        }
        return pCurr;
    }
}

/**
 * Gets the data stored in the Node.
 * 
 * @param pNode A pointer to the Node containing data.
 * @return A pointer to the data contained.
*/
ListData* getData(ListNode* pNode){
    return pNode->pData;
}

/**
 * Sets the data stored in the Node.
 * 
 * @param pNode A pointer to the Node to store data.
 * @param pData A pointer to the data to be stored.
*/
void setData(ListNode* pNode, ListData* pData){
    pNode->pData = pData;
}

/**
 * Creates a new Node structure using the given data.
 * 
 * @param pData A pointer to the data to be stored in the Node.
 * @return A pointer to the created Node structure.
*/
ListNode* createNode(ListData* pData){
    ListNode* pNewNode = (ListNode*) calloc(1, sizeof(ListNode));

    if (pNewNode == NULL)
        OutofStorage();
    setData(pNewNode, pData);
    return pNewNode;
}

/**
 * Deallocate both the data stored in the Node and the Node itself.
 * 
 * @param pNode A pointer to the Node to be deallocated.
*/
void deleteNode(ListNode* pNode){
    free(getData(pNode));
    free(pNode);
}

/**
 * Prints the contents of the Node.
 * 
 * @param pNode A pointer to the Node to be printed.
 * @param printData The fuction to print the data.
*/
void printNode(ListNode* pNode, void (*printData)(ListData* pData)){
    printData(getData(pNode));
}

/**
 * Prints all the Nodes in the LinkedList and its contents to
 * the stdout if dataFlag is true or only the Nodes if it is false.
 * 
 * @param pList A pointer to the LinkedList to be printed.
 * @param printData The function to print the data.
 * @param dataFlag Whether data in the Node should printed.
*/
void printList(LinkedList* pList, void (*printData)(ListData* pData), bool dataFlag){
    fprintf(stdout, "List has %2d entries: [", getSize(pList));
    
    ListNode* pCurr = getFirstNode(pList);
    while((pCurr != NULL) && dataFlag){
        printNode(pCurr, printData);
        pCurr = pCurr->pNext;
    }

    fprintf(stdout, "]\n");
}

//----------------------------------------------------------
//---------Specific to Testing------------------------------

void printInt(int* i){
    printf("%2d ", *i);
}

ListData* CreateData(ListData d){
    ListData* pD = (ListData*) calloc(1, sizeof(ListData));
    if (pD == NULL)
        OutofStorage();
    *pD = d;
    return pD;
}

typedef enum{
    eFront = 0,
    eBack
} eWhere;

typedef enum{
    eLook = 0,
    eInsert,
    eDelete
} eAction;

int main(){
    LinkedList* pLL = createLinkedList();
    printf( "Input or operation          "
            "Current state of linked list \n"
            "=====================  "
            "===================================");
    printf("\nUsing input{1 2 3 4} ");
    printList(pLL, printInt, true);
    int data1[] = {1, 2, 3, 4};
    for (int i = 0; i < 4; i++){
        TestPrintOperation(pLL, eInsert, data1[i], eFront);
    }

    TestPrintOperation(pLL, eLook, 0, eFront);
    TestPrintOperation(pLL, eDelete, 0, eBack);

    printf( "\nUsing input{ 31 32 33 }  ");
    printList(pLL, printInt, true);
    int data2[] = {31, 32, 33};
    for (int i = 0; i < 3; i++){
        TestPrintOperation(pLL, eLook, 0, eBack);
    }
    TestPrintOperation(pLL, eLook, 0, eBack);

    int count = pLL->nodeCount;
    for(int i = 0; i < count; i++){
        TestPrintOperation(pLL, eDelete, 0, eFront);
    }
}

void TestPrintOperation(LinkedList* pLL, eAction action,
                        ListData data, eWhere where){
    switch(action){
        case eLook:
            data = TestExamineNode(pLL, where);
            printf("Get %s node, see [%2d]. ",
            where==eFront? "front" : "back", data);
            break;
        case eInsert:
            printf("Insert [%2d] to %s.     ", data,
                    where==eFront? "front" : "back");
            TestCreateNodeAndInsert(pLL, data, where);
            break;
        case eDelete:
            data = TestRemoveNodeAndFree(pLL, where);
            printf("Remove [%2d] from %s.   ", data,
                    where==eFront? "front" : "back");
            break;
        default:
            printf("::ERROR:: unknown action\n");
            break;
    }
    printList(pLL, printInt, true);
}

void TestCreateNodeAndInsert(LinkedList* pLL, ListData data, eWhere where){
    ListData* pData = CreateData(data);
    ListNode* pNode = createNode(pData);
    switch (where){
        case eFront:
            insertNodetoFront(pLL, pNode);
            break;
        case eBack:
            insertNodetoBack(pLL, pNode);
            break;
    }
}

ListData TestExamineNode(LinkedList* pLL, eWhere where){
    ListNode* pNode;

    switch (where){
        case eFront:
            pNode = getNode(pLL, 0);
            break;
        case eBack:
            pNode = getNode(pLL, getSize(pLL));
            break;
    }

    ListData data = *(getData(pNode));
    return data;
}

ListData TestRemoveNodeAndFree(LinkedList* pLL, eWhere where){
    ListNode* pNode;

    switch (where){
        case eFront:
            pNode = removeNodefromFront(pLL);
            break;
        case eBack:
            pNode = removeNodefromBack(pLL);
            break;
    }
    
    ListData data = *(getData(pNode));
    deleteNode(pNode);
    return data;
}