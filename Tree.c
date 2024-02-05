#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * A Tree structure based on the Cory Althoff's Self-Taught
 * Computer Scientist Book
 * @author Pasindu Ravimal
 * @date 02/03/2024
 * @version 1.0.0
*/
typedef int TreeData, NodeData;
typedef struct _node Node;

typedef struct _node{
    NodeData* data;
    Node* leftChild;
    Node* rightChild;
    int count;
} Node;

typedef struct{
    Node* root;
    int height;
}Tree;

/* Prototypes:
Tree* createTree();
int getHeight(Tree* pTree);
void insert(Node* pNode);
Node* getLeftChild(Node* pNode);
Node* getRightChild(Node* pNode);

Node* createNode(NodeData* pData);
NodeData* getData(Node* pNode);
void setData(Node* pNode, NodeData* pData); //

void insertLeft(Node* pNode);
void insertRight(Node* pNode);

insertNodeUsingComparator
*/

/**
 * Creates a new instance of a Tree structure.
 * 
 * @return A pointer to the root of the new Tree.
*/
Tree* createTree(){
    Tree* temp = (Tree*) calloc(1, sizeof(Tree));
    temp->height = 0;
    temp->root = NULL;
    return temp;
}

/**
 * Gets the height of the Tree.
 * 
 * @return The height of the Tree.
*/
int getHeight(Tree* pTree){
    return pTree->height;
}

/**
 * Creates a new Node structure using given data. The Tree stores not the
 * given data but a new instance of the data.
 * 
 * @param pData A pointer to the data to be stored.
 * @return A pointer to the new Node.
*/
Node* createNode(NodeData* pData){
    Node* temp = (Node*) calloc(1, sizeof(Node));
    NodeData* data = (NodeData*) calloc(1, sizeof(NodeData));
    *data = *pData;
    temp->data = data;
    temp->leftChild = NULL;
    temp->rightChild = NULL;
    temp->count = 1;
    return temp;
}

/**
 * Gets a pointer to the left child of the Node.
 * 
 * @param pNode The root Node.
 * @return A pointer to the left child.
*/
Node* getLeftChild(Node* pNode){
    return pNode->leftChild;
}

/**
 * Gets a pointer to the right child of the Node.
 * 
 * @param pNode The root Node.
 * @return A pointer to the right child.
*/
Node* getRightChild(Node* pNode){
    return pNode->rightChild;
}

/**
 * Sets the left child of the Node.
 * 
 * @param pNode The Node to be set as the Left child.
 * @param pRoot The root Node to set the child.
*/
void setLeftChild(Node* pNode, Node* pRoot){
    pRoot->leftChild = pNode;
}

/**
 * Sets the right child of the Node.
 * 
 * @param pNode The Node to be set as the Right child.
 * @param pRoot The root Node to set the child.
*/
void setRightChild(Node* pNode, Node* pRoot){
    pRoot->rightChild = pNode;
}

/**
 * Sets the root of the Tree to the given Node.
 * 
 * @param pNode The Node to be set as the root.
 * @param pTree The Tree to set the root.
*/
void setRoot(Node* pNode, Tree* pTree){
    pTree->root = pNode;
}

/**
 * Insert data to the Tree using following conditions,
 * - If data > parent, inserts to right
 * - If data < parent, inserts to left
 * - If data = parent, increase the count
 * 
 * @note This method inserts another copy of the data. So, the function
 * does not change the data in any means.
 * 
 * @param pData A pointer to the data to be added to the Tree.
 * @param pTree A pointer to the Tree which the data to be added.
*/
void insert(TreeData* pData, Tree* pTree){
    Node* temp = createNode(pData);

    Node* root = pTree->root;

    if(root == NULL){
        setRoot(temp, pTree);
        return;
    }
    
    while (true){
        if (*(root->data) > *pData){
            if (getLeftChild(root) != NULL)
                root = getLeftChild(root);
            else{
                setLeftChild(temp, root);
                return;
            }
        } else if (*(root->data) < *pData){
            if (getRightChild(root) != NULL)
                root = getRightChild(root);
            else{
                setRightChild(temp, root);
                return;
            }
        } else {
            root->count++;
            return;
        }
    }
}

int main(){
    Tree* tree = createTree();
    int values[] = {5,3,6,6,4};
    for (int i = 0; i < 5; i++)
    {
        insert(&(values[i]), tree);
    }
    
    return 0;
}
