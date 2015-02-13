#ifndef _node_h
#define _node_h
#include <stdio.h>
#include <stdlib.h>

struct node{
	void *data; 
	struct Node *next;
};
typedef struct node Node;
#endif