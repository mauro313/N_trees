#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ntree_node.h"

ntree_node_t* ntree_fourChildCreation(void);
void printElem(t_elem_1 value);
int compare(t_elem_1 value1,t_elem_1 value2);


int main(void){
  srand(time(NULL));
  // cration of n_tree of 16 nodes.
  ntree_node_t* nTree = ntree_fourChildCreation();

  //print the n_tree in amplitude.
  ntree_node_amplitude_print(nTree,printElem);
  printf("\n\n");
 
  //delete the root. 
  ntree_node_t* exRoot = ntree_node_deleteRoot(&nTree);

  //print the new tree in amplitude
  ntree_node_amplitude_print(nTree,printElem);

  printf("\n\n");

  //print the tree in depth.
  ntree_node_depth_print(exRoot,printElem); 
   
  //free the memory of the exRoot
  ntree_node_free(&exRoot);
  
  return 0;    
}

/**
 * @brief creation of a 16 nodes n_trees
 * 
 * @return ntree_node_t* 
 */
ntree_node_t* ntree_fourChildCreation(void){
  ntree_node_t* root = ntree_node_new(rand()%50);
  for(int i=0;i<4;i++){
    ntree_node_t* auxiliar = ntree_node_new(rand()%50);
    for(int j=0;j<4;j++){
      ntree_node_t* auxiliar_1 = ntree_node_new(rand()%50);
      ntree_node_insert_son(auxiliar,auxiliar_1);  
    }
    ntree_node_insert_son(root,auxiliar);  
  }        
  return root;
}

/**
 * @brief auxiliar procedure to print an element.
 * 
 * @param value 
 */
void printElem(t_elem_1 value){
  printf(" %d ",value);    
}

/**
 * @brief auxiliar function to compare elements.
 * 
 * @param value1 
 * @param value2 
 * @return int 
 */
int compare(t_elem_1 value1,t_elem_1 value2){
  if(value1 == value2){
    return 0;  
  }
  return ((value1>value2)? 1:-1);
}





