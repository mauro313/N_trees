#ifndef NTREE_NODE_H_INCLUDED
#define NTREE_NODE_H_INCLUDED
#include "singly_linked_list_node.h"
#include "queue.h"
#define t_elem_1 int

typedef struct _ntn{
  t_elem_1 value;
  sll_node_t* sons;
}ntree_node_t;

ntree_node_t* ntree_node_new(t_elem_1 element);

void ntree_node_free(ntree_node_t** node);

t_elem_1 ntree_node_get_value(ntree_node_t* node);

sll_node_t* ntree_node_get_sonsList(ntree_node_t* node);

sll_node_t** ntree_node_get_sonsListReference(ntree_node_t* node);

void ntree_node_insert_son(ntree_node_t* node,ntree_node_t* newNode);

void ntree_node_amplitude_print(ntree_node_t* root,void (*printElement)(t_elem_1));

void ntree_node_depth_print(ntree_node_t* root,void (*printElement)(t_elem_1));

ntree_node_t* ntree_node_find_node(ntree_node_t* root,ntree_node_t* node);

ntree_node_t* ntree_node_find_value(ntree_node_t* root,t_elem_1 value,int (*compare)(t_elem_1,t_elem_1));

ntree_node_t** ntree_node_find_node_reference(ntree_node_t** root,ntree_node_t* node);

ntree_node_t** ntree_node_find_value_reference(ntree_node_t** root,t_elem_1 value,int (*compare)(t_elem_1,t_elem_1));

ntree_node_t* ntree_node_remove_node(ntree_node_t* root,ntree_node_t* nodeToRemove);

ntree_node_t* ntree_node_remove_value(ntree_node_t* root,t_elem_1 element,int(*compare)(t_elem_1,t_elem_1));

ntree_node_t* ntree_node_deleteRoot(ntree_node_t** root);

#include "ntree_node.c"
#endif //NTREE_NODE_H_INCLUDED