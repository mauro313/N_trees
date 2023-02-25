#include <stdio.h>
#include <stdlib.h>
#include "ntree_node.h"

/**
 * @brief create a new n_tree node.
 * 
 * @param element 
 * @return ntree_node_t* 
 */
ntree_node_t* ntree_node_new(t_elem_1 element){
  ntree_node_t* newNode = (ntree_node_t*)malloc(sizeof(ntree_node_t));
  if(newNode == NULL){
    printf("\nmemory cannot be reserved for a ntree_node pointer\n");
    exit(EXIT_FAILURE);  
  }     
  newNode->value = element;
  newNode->sons = NULL;
  return newNode;
}

/**
 * @brief free the memory used in a n_tree node
 * 
 * @param node 
 */
void ntree_node_free(ntree_node_t** node){
  if(node!=NULL && *node!=NULL){
    (*node)->sons = NULL;
    free(*node);
    *node = NULL;      
  }        
}

/**
 * @brief getter for the value of a n_tree node.
 * 
 * @param node 
 * @return t_elem_1 
 */
t_elem_1 ntree_node_get_value(ntree_node_t* node){
  if(node == NULL){
    printf("\nntree_node pointer is NULL(1)\n");
    exit(EXIT_FAILURE);  
  }    
  return node->value;
}

/**
 * @brief getter for the list of the sons of a n_tree node.
 * 
 * @param node 
 * @return sll_node_t* 
 */
sll_node_t* ntree_node_get_sonsList(ntree_node_t* node){
  if(node == NULL){
    printf("\nntree_node pointer is NULL(2)\n");
    exit(EXIT_FAILURE);    
  }  
  return node->sons;
}

/**
 * @brief getter for the reference of the list of the sons of a n_tree node.
 * 
 * @param node 
 * @return sll_node_t** 
 */
sll_node_t** ntree_node_get_sonsListReference(ntree_node_t* node){
  if(node == NULL){
    printf("\nntree_node pointer is NULL(3)\n");
    exit(EXIT_FAILURE);  
  }  
  return &node->sons;
}

/**
 * @brief insert a new n_tree node as a son of the first argument n_tree node.
 * 
 * @param node 
 * @param newNode 
 */
void ntree_node_insert_son(ntree_node_t* node,ntree_node_t* newNode){
  sll_node_add_node_end_recursive(&(node)->sons,sll_node_new(newNode));
}

/**
 * @brief print a n_tree in amplitude.
 * 
 * @param root 
 * @param printElement 
 */
void ntree_node_amplitude_print(ntree_node_t* root,void (*printElement)(t_elem_1)){
  if(root == NULL){
    printf("\nntree_node pointer is NULL(4)\n");
    return; 
  }
  queue_t* queue = queue_new(1000);
  enqueue(queue,root);
  while(!queue_isempty(queue)){
    root = (ntree_node_t*)dequeue(queue);
    sll_node_t* sons = root->sons;
    while(sons != NULL){
      enqueue(queue,sons->value);
      sons = sons->next;    
    }  
    printElement(root->value);
  }
  printf("\n");
  queue_free(&queue);
}

/**
 * @brief print a ntree in amplitude.
 * 
 * @param root 
 * @param printElement 
 */
void ntree_node_depth_print(ntree_node_t* root,void (*printElement)(t_elem_1)){
  if(root == NULL){
    printf("\nntree_node pointer is NULL(5)\n");
    return; 
  }  
  printElement(root->value);
  sll_node_t* auxiliar = root->sons;
  while(auxiliar != NULL){
    ntree_node_depth_print(sll_node_get_value(auxiliar),printElement);
    auxiliar = sll_node_get_next(auxiliar);    
  }
}

/**
 * @brief search a node in a n_tree.
 * 
 * @param root 
 * @param node 
 * @return ntree_node_t* 
 */
ntree_node_t* ntree_node_find_node(ntree_node_t* root,ntree_node_t* node){
  if(root == NULL){
    printf("\nntree_node pointer is NULL(5)\n");
    exit(EXIT_FAILURE);  
  }
  if(node == NULL){
    return node;  
  }
  if(root == node){
    return root;  
  }
  sll_node_t* auxiliar = root->sons;
  ntree_node_t* findedNode = NULL;
  bool finded = false;
  while(!finded && auxiliar != NULL){
    findedNode = ntree_node_find_node(sll_node_get_value(auxiliar),node);
    if(findedNode != NULL){
      finded = true;  
    }
    auxiliar = sll_node_get_next(auxiliar);    
  }
  return findedNode;
}

/**
 * @brief search an element in a n_tree. 
 * 
 * @param root 
 * @param value 
 * @param compare 
 * @return ntree_node_t* 
 */
ntree_node_t* ntree_node_find_value(ntree_node_t* root,t_elem_1 value,int (*compare)(t_elem_1,t_elem_1)){
  if(root == NULL){
    printf("\nntree_node pointer is NULL(6)\n");
    exit(EXIT_FAILURE);  
  } 
  if(compare(root->value,value)==0){
    return root;  
  }
  sll_node_t* auxiliar = root->sons;
  ntree_node_t* findedNode = NULL;
  bool finded = false;
  while(!finded && auxiliar != NULL){
    findedNode = ntree_node_find_value(sll_node_get_value(auxiliar),value,compare);
    if(findedNode != NULL){
      finded = true;    
    }
    auxiliar = sll_node_get_next(auxiliar);    
  }
  return findedNode;
}

/**
 * @brief search a node in a n_tree. Return the reference of the node if exist.
 * 
 * @param root 
 * @param node 
 * @return ntree_node_t** 
 */
ntree_node_t** ntree_node_find_node_reference(ntree_node_t** root,ntree_node_t* node){
  if(root == NULL){
    printf("\nntree_node double pointer is NULL(1)\n");
    exit(EXIT_FAILURE);  
  }
  if(node == NULL){
    return NULL;  
  }
  if(*root == node){
    return root;  
  }
  sll_node_t* auxiliar = (*root)->sons;
  ntree_node_t** findedNodeReference = NULL;
  bool finded = false;
  while(!finded && auxiliar != NULL){
    ntree_node_t* auxToReference = sll_node_get_value(auxiliar);
    findedNodeReference = ntree_node_find_node_reference(&auxToReference,node);
    if(findedNodeReference != NULL){
      finded = true;  
    }
    auxiliar = sll_node_get_next(auxiliar);    
  }
  return findedNodeReference;
}

/**
 * @brief search an element in a n_tree. Return the reference of the node if exist.
 * 
 * @param root 
 * @param value 
 * @param compare 
 * @return ntree_node_t** 
 */
ntree_node_t** ntree_node_find_value_reference(ntree_node_t** root,t_elem_1 value,int (*compare)(t_elem_1,t_elem_1)){
  if(root == NULL){
    printf("\nntree_node double pointer is NULL(2)\n");
    exit(EXIT_FAILURE);  
  }
  if(compare((*root)->value,value)==0){
    return root;  
  }
  sll_node_t* auxiliar = (*root)->sons;
  ntree_node_t** findedNodeReference = NULL;
  bool finded = false;
  while(!finded && auxiliar != NULL){
    ntree_node_t* auxToReference = sll_node_get_value(auxiliar);
    findedNodeReference = ntree_node_find_value_reference(&auxToReference,value,compare);
    if(findedNodeReference != NULL){
      finded = true;  
    }
    auxiliar = sll_node_get_next(auxiliar);    
  }
  return findedNodeReference;
}

/**
 * @brief remove a node in a n_tree (the root is not included for deletion).
 * 
 * @param root 
 * @param nodeToRemove 
 * @return ntree_node_t* 
 */
ntree_node_t* ntree_node_remove_node(ntree_node_t* root,ntree_node_t* nodeToRemove){
  if(root == NULL){
    printf("\nntree_node pointer is NULL(8)\n");
    exit(EXIT_FAILURE);  
  }  
  if(root == nodeToRemove){
    return root;
  }
  sll_node_t** auxToRefereneceSons = &(root)->sons;
  ntree_node_t* toDelete = NULL;
  bool checkToContinue = false;
  while(!checkToContinue && (*auxToRefereneceSons)!=NULL){
    toDelete = ntree_node_remove_node(sll_node_get_value(*auxToRefereneceSons),nodeToRemove);
    if(toDelete != NULL){
      sll_node_t* aux = *auxToRefereneceSons;
      *auxToRefereneceSons = sll_node_get_next(aux);
      sll_node_set_value(&aux,NULL);
      sll_node_free(&aux);
      checkToContinue = true;
    } 
    else{
      auxToRefereneceSons = sll_node_get_next_referece(*auxToRefereneceSons);
    }
  }
  return toDelete;  
}

/**
 * @brief remove an element of a n_tree. Use of ntree_node_remove_node.
 * (The root is not included for deletion)
 * 
 * @param root 
 * @param element 
 * @param compare 
 * @return ntree_node_t* 
 */
ntree_node_t* ntree_node_remove_value(ntree_node_t* root,t_elem_1 element,int(*compare)(t_elem_1,t_elem_1)){
  if(root == NULL){
    printf("\nntree_node pointer is NULL(8)\n");
    exit(EXIT_FAILURE);  
  }  
  if(compare(root->value,element)==0){
    return root;
  }
  sll_node_t** auxToRefereneceSons = &(root)->sons;
  ntree_node_t* toDelete = NULL;
  bool checkToContinue = false;
  while(!checkToContinue && (*auxToRefereneceSons)!=NULL){
    toDelete = ntree_node_remove_value(sll_node_get_value(*auxToRefereneceSons),element,compare);
    if(toDelete != NULL){
      sll_node_t* aux = *auxToRefereneceSons;
      *auxToRefereneceSons = sll_node_get_next(aux);
      sll_node_set_value(&aux,NULL);
      sll_node_free(&aux);
      checkToContinue = true;
    } 
    else{
      auxToRefereneceSons = sll_node_get_next_referece(*auxToRefereneceSons);
    }
  }
  return toDelete;   
}

/**
 * @brief delete the root.
 * 
 * @param root 
 * @return ntree_node_t* 
 */
ntree_node_t* ntree_node_deleteRoot(ntree_node_t** root){
  if(root == NULL){
    printf("\nntree_node double pointer is NULL(3)\n");
    exit(EXIT_FAILURE);   
  }  
  if(*root == NULL){
    printf("\nntree_node doble pointer contain a NULL pointer\n");
    return NULL;
  }
  ntree_node_t* toDelete = NULL;
  if((*root)->sons != NULL){
    sll_node_t* aux = (*root)->sons;
    ntree_node_t* newRoot = sll_node_get_value(aux);
    sll_node_add_node_end_recursive(&(newRoot)->sons,sll_node_get_next(aux));
    sll_node_set_value(&aux,NULL);
    sll_node_free(&aux);
    toDelete = *root;
    (*root)->sons = NULL;
    *root = newRoot;     
  }
  return toDelete;
}

