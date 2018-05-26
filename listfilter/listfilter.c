
#include <stdbool.h>
#include <stdlib.h>

typedef struct node_t* Node; 
struct node_t {
	int n; 
	Node next;
};

typedef bool (*CondFun) (int number);

typedef enum listStatus_t {
	LIST_OK, 
	LIST_BAD_ARGUMENT, 
	LIST_MEMORY_ERROR
} ListStatus;

Node listFilter (Node node, CondFun condition, ListStatus *status);
Node coolElements (Node *node, int size, ListStatus *status);
bool checkCoolness2(int a);
bool checkCoolness3(int a);
Node collate(Node first_node, Node second_node);
Node nodeCopy (Node old_node, ListStatus* status);
bool checkCoolness1(int a);
void destroyList (Node node);

//creates a new list from the items of a given list selecting only
//the items satisfying a given condition
Node listFilter (Node node, CondFun condition, ListStatus *status) {
	if (node == NULL) {
		//we receive and return an empty list, this is not an error
		if (status != NULL) {
			*status = LIST_OK;
		}
		return NULL;
	}
	if (condition == NULL) {
		if (status != NULL) {
			*status = LIST_BAD_ARGUMENT;
		}
		return NULL;
	}
	Node given_node = node;

	while (given_node != NULL && condition(given_node->n) == false) {
		given_node = given_node->next;
	}

	if (given_node == NULL) {
		//no items in the list match the condition, an empty list is returned
		if (status != NULL) {
			*status = LIST_OK;
		}
		return NULL;
	}

	Node first_node = nodeCopy(given_node, status);
	Node my_node = first_node;
	if (*status != LIST_OK) {
		//memory allocation error
		return NULL;
	}
	Node current_node = given_node->next;
	while (current_node != NULL) {
		if (condition(current_node->n) == true) {
			Node new_node = nodeCopy(current_node, status);
			if (*status != LIST_OK) {
				//memory allocation failure
				destroyList(my_node);
				return NULL;
			}
			my_node->next = new_node;
			my_node = new_node;
		}
		current_node = current_node->next;
	}
	return first_node;
}

//given an array of lists of integers and a size of the array,
//returns a new list of integers that contains the integers that are
//equally divisible by (number of the list modulo 3) + 1
Node coolElements (Node *node, int size, ListStatus *status) {
	Node initial_node = NULL;
	for (int i = size-1; i >= 0; i--) {
		Node given_node = node[i];
		int magic_number = i%3 + 1;
		Node current_node;
		if (magic_number == 2) {
			current_node = listFilter(given_node, checkCoolness2, status);
		} else if (magic_number == 3) {
			current_node = listFilter(given_node, checkCoolness3, status);
		} else {
			current_node = listFilter(given_node, checkCoolness1, status);
		}
		if (status != NULL && *status != LIST_OK) {
			destroyList(initial_node);
			return NULL;
		}
		initial_node = collate(current_node, initial_node);
	}
	return initial_node;
}

//condition functions checking if n divides the number a when:
//n equals 1
bool checkCoolness1(int number) {
	return true;
}
//n equals 2
bool checkCoolness2(int number) {
	if (number%2==0) {
		return true;
	} else {
		return false;
	}
}
//n equals 3
bool checkCoolness3(int number) {
	if (number%3==0) {
		return true;
	} else {
		return false;
	}
}

//attaches the second_list to the first_list as tail
Node collate(Node first_node, Node second_node) {
	//no errors are possible, both arguments may be null (empty lists)
	if (first_node == NULL) {
		return second_node;
	}
	Node node = first_node;
	Node initial_node = first_node;
	while (node->next != NULL) {
		node = node->next;
	}
	node->next = second_node;
	return initial_node;
}

//creates a new node that contains the same int as a given node,
//the pointer to the next node is NULL
Node nodeCopy (Node old_node, ListStatus *status) {
	if (old_node == NULL) {
		if (status != NULL) {
			*status = LIST_BAD_ARGUMENT;
		}
		return NULL;
	}
	Node new_node = malloc(sizeof(Node));
	if (new_node == NULL) {
		if (status != NULL) {
			*status = LIST_MEMORY_ERROR;
		}
		return NULL;
	}
	new_node->n = old_node->n;
	new_node->next = NULL;
	if (status != NULL) {
		*status = LIST_OK;
	}
	return new_node;
}