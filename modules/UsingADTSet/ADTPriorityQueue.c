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
	
};



// Συναρτήσεις του ADTPriorityQueue ////////////////////////////////////////////////////////

PriorityQueue pqueue_create(CompareFunc compare, DestroyFunc destroy_value, Vector values) {
	

	PriorityQueue pqueue = malloc(sizeof(*pqueue)); // Δέσμευση μνήμης για τη δομή PriorityQueue
    if (pqueue == NULL)
        return NULL; // Έλεγχος αποτυχίας δεσμεύσης μνήμης

    pqueue->set = set_create(compare, destroy_value); // Δημιουργία του Set που θα αποθηκεύει τα στοιχεία με την κατάλληλη συνάρτηση σύγκρισης

	if (values != NULL) {
		for (int i = 0; i < vector_size(values); i++) {
		    Pointer value = vector_get_at(values, i);
		    set_insert(pqueue->set, value);  // φορτώνουμε το vector μέσα στο set
	    }
    }
	
	return pqueue; // Επιστροφή της ουράς προτεραιότητας

	
}

int pqueue_size(PriorityQueue pqueue) {

	return set_size(pqueue->set);
}

Pointer pqueue_max(PriorityQueue pqueue) {

	SetNode max_node = set_last(pqueue->set); // Παίρνουμε τον τελευταίο κόμβο του Set (μέγιστο στοιχείο)
    if (max_node == NULL)
        return NULL; // Αν δεν υπάρχει στοιχείο, επιστρέφουμε NULL

    return set_node_value(pqueue->set, max_node); // Επιστρέφουμε την τιμή του κόμβου
	
}

PriorityQueueNode pqueue_max_node(PriorityQueue pqueue) {

	SetNode max_node = set_last(pqueue->set);
	if(max_node == NULL)
	   return NULL;

	return (PriorityQueueNode)max_node;   

}

PriorityQueueNode pqueue_insert(PriorityQueue pqueue, Pointer value) {

	set_insert(pqueue->set, value);  //προσθετουμε την τιμη μεσα στο set
	PriorityQueueNode return_node = (PriorityQueueNode)set_find_node(pqueue->set, value); //Βρισκουμε τον κομβο που μολις προσθεσαμε
	return return_node; //επιστρεφουμε τον κομβο που προσθεσαμε

}

void pqueue_remove(PriorityQueue pqueue, PriorityQueueNode node) {

	Pointer val = set_node_value(pqueue->set, (SetNode)node);
	set_remove(pqueue->set, val);

}

Pointer pqueue_node_value(PriorityQueue pqueue, PriorityQueueNode node) {
	return (Pointer)set_node_value(pqueue->set, (SetNode)node);
}

DestroyFunc pqueue_set_destroy_value(PriorityQueue pqueue, DestroyFunc destroy_value) {
	return set_set_destroy_value(pqueue->set, destroy_value);   // Θέτουμε νέα συνάρτηση καταστροφής στο Set και επιστρέφουμε την παλιά
}

void pqueue_destroy(PriorityQueue pqueue) { 
	
	set_destroy(pqueue->set);    // Καταστρέφουμε το Set και τα περιεχόμενά του
    free(pqueue);                // Αποδεσμεύουμε τη μνήμη της ουράς προτεραιότητας

}



