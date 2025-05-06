///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT Priority Queue μέσω του ADT Set
//
///////////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>

#include "ADTPriorityQueue.h"
#include "ADTSet.h"			// Η υλοποίηση του PriorityQueue χρησιμοποιεί Set


// Ενα PriorityQueue είναι pointer σε αυτό το struct
struct priority_queue {
	Set set;		// το Set στο οποίο αποθηκεύουμε τα στοιχεία
	// ...
};



// Συναρτήσεις του ADTPriorityQueue ////////////////////////////////////////////////////////

PriorityQueue pqueue_create(CompareFunc compare, DestroyFunc destroy_value, Vector values) {
	// Προς υλοποίηση...

	return NULL;
}

int pqueue_size(PriorityQueue pqueue) {
	return 0;
}

Pointer pqueue_max(PriorityQueue pqueue) {
	return NULL;
}

PriorityQueueNode pqueue_max_node(PriorityQueue pqueue) {
	return NULL;
}

PriorityQueueNode pqueue_insert(PriorityQueue pqueue, Pointer value) {
	return NULL;
}

void pqueue_remove(PriorityQueue pqueue, PriorityQueueNode) {

}

Pointer pqueue_node_value(PriorityQueue pqueue, PriorityQueueNode node) {
	return NULL;
}

DestroyFunc pqueue_set_destroy_value(PriorityQueue pqueue, DestroyFunc destroy_value) {
	return NULL;
}

void pqueue_destroy(PriorityQueue pqueue) {

}
