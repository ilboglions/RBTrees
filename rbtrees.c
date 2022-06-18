#include <stdio.h>
#include <stdlib.h>
#define RED 0
#define BLACK 1 


typedef struct rbnode_s{

    int key;
    int8_t color;
    struct rbnode_s * left;
    struct rbnode_s * right;
    struct rbnode_s * p;
  
}rbnode;

rbnode * rbInsertFixup(rbnode *, rbnode *); 
rbnode * rbInsert( rbnode * , int );
rbnode * leftRotate (rbnode * , rbnode *);
rbnode * rightRotate (rbnode * , rbnode *);
rbnode * search(rbnode *, int);
void preOrderVisit ( rbnode *);
void postOrderVisit (rbnode *);
void inOrderVisit(rbnode *);



rbnode * rbInsert( rbnode * root, int x){

    rbnode * new;
    rbnode * curr;
    rbnode * prev;

    
    new = malloc(sizeof(rbnode));
    if(new != NULL){

        curr = root;
        prev=NULL;
        while(curr != NULL){
            prev=curr;
            if(x > curr->key){   
                curr = curr->right;
            }
            else {
                curr = curr->left;
            }
        }

        new->p = prev;
        new->color = RED;
        new->key = x;
        new->right = NULL;
        new->left = NULL;

        if(prev == NULL){
            root = new;
        }
        else if(new->key > prev->key){
            prev->right = new;
        }
        else{
            prev->left = new;
        }

        root = rbInsertFixup(root, new);  
    }
    else{
        printf("Error in memory allocation \n");
    }
    return root;
}

rbnode * rbInsertFixup(rbnode * root, rbnode * elem){

    rbnode * daddy;
    rbnode * uncle;

    if(elem == root){
        elem->color = BLACK;
    }
    else{
        daddy = elem->p;
        
        if(daddy->color == RED){
            if(daddy == daddy->p->left){
                uncle = daddy->p->right;
                if(uncle->color == RED){ //CASE 1
                    daddy->color = BLACK;
                    daddy->p->color = RED;
                    uncle->color = BLACK;
                    rbInsertFixup(root, daddy->p);
                }
                else{
                    if(elem == daddy->right){  //CASE 2
                        elem = daddy;
                        root = leftRotate(root, elem);
                        daddy = elem->p;
                    }
                    daddy->color = BLACK;  //CASE 3
                    daddy->p->color = RED;
                    root = rightRotate(root, daddy->p);
                }
            }
            else{
                uncle = daddy->p->left;
                if(uncle->color == RED){ //CASE 4
                    daddy->color = BLACK;
                    daddy->p->color = RED;
                    uncle->color = BLACK;
                    rbInsertFixup(root, daddy->p);
                }
                else{
                    if(elem == daddy->left){  //CASE 5
                        elem = daddy;
                        root = rightRotate(root, elem);
                        daddy = elem->p;
                    }
                    daddy->color = BLACK;  //CASE 6
                    daddy->p->color = RED;
                    root = leftRotate(root, daddy->p);
                }
            }
        }
    }


} 


rbnode * leftRotate (rbnode * root, rbnode * elem){
    rbnode * tmp;
    tmp = elem->right;
    if(tmp != NULL){
        elem->right = tmp->left;
        tmp->left = elem;
        if(elem->p == NULL){
            root = tmp;
        }
        else if(elem->p->right == elem){
            elem->p->right=tmp;
        }
        else {
        elem->p->left=tmp; 
        }
        tmp->p = elem->p;
        elem->p = tmp;
    }
    return root;
}
rbnode * rightRotate (rbnode * root, rbnode * elem){
    rbnode * tmp;
    tmp = elem->left;
    if(tmp != NULL){
        elem->left = tmp ->right;
        tmp ->right = elem;
        if(elem->p == NULL){
            root = tmp;
        }
        else if(elem->p->right == elem){
            elem->p->right=tmp;
        }
        else {
        elem->p->left=tmp; 
        }
        tmp->p = elem->p;
        elem->p = tmp;
    }
    return root;
}
rbnode * search(rbnode * root, int value){

    if(root == NULL)
        return NULL;
    
    if( root->key == value){
        return root;
    }
    if( root->key > value){
        return search(root->left, value);
    }
        return search(root->right, value);        
}



void preOrderVisit ( rbnode * root){
    if(root != NULL){
        printf("%d ", root->key);
        preOrderVisit(root->left);
        preOrderVisit(root->right);
    }
    return;
}
void postOrderVisit (rbnode * root){
    if(root != NULL){
        postOrderVisit(root->left);
        postOrderVisit(root->right);
        printf("%d ", root->key);   
    }
    return;
}
void inOrderVisit(rbnode * root){
    if(root != NULL){
        inOrderVisit(root->left);
        printf("%d ", root->key);  
        inOrderVisit(root->right);        
    }
    return;
}