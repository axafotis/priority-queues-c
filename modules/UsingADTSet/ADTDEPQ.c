///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT DEPQ μέσω του ADT Set
//
///////////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>

#include "ADTDEPQ.h"
#include "ADTSet.h"			// Η υλοποίηση του PriorityQueue χρησιμοποιεί Set


// Ενα PriorityQueue είναι pointer σε αυτό το struct
struct depq {
    
    Set set;		// το Set στο οποίο αποθηκεύουμε τα στοιχεία

};



// Συναρτήσεις του ADTPriorityQueue ////////////////////////////////////////////////////////

// Δημιουργεί και επιστρέφει μια νέα ουρά προτεραιότητας, της οποίας τα στοιχεία συγκρίνονται με βάση τη συνάρτηση compare.
// Αν destroy_value != NULL, τότε καλείται destroy_value(value) κάθε φορά που αφαιρείται ένα στοιχείο.

DEPQ depq_create(CompareFunc compare, DestroyFunc destroy_value){

    DEPQ depq = malloc(sizeof(*depq));

    if(depq == NULL)
       return NULL;

    depq->set = set_create(compare, destroy_value);   

    return depq;


}


// Επιστρέφει τον αριθμό στοιχείων που περιέχει η ουρά depq

int depq_size(DEPQ depq){

    return set_size(depq->set);

}

// Επιστρέφει το μεγαλύτερο στοιχείο της ουράς (μη ορισμένο αποτέλεσμα αν η ουρά είναι κενή)

Pointer depq_max(DEPQ depq){

    return set_node_value( depq->set, set_last(depq->set) );

}

// Επιστρέφει το μικρότερο στοιχείο της ουράς (μη ορισμένο αποτέλεσμα αν η ουρά είναι κενή)

Pointer depq_min(DEPQ depq){
    
    return set_node_value( depq->set, set_first(depq->set) );
}

// Προσθέτει την τιμή value στην ουρά depq.

void depq_insert(DEPQ depq, Pointer value){

    set_insert(depq->set, value);

}

// Αφαιρεί την μεγαλύτερη τιμή της ουράς (μη ορισμένο αποτέλεσμα αν η ουρά είναι κενή)

void depq_remove_max(DEPQ depq){

    set_remove( depq->set, set_node_value(depq->set, set_last( depq->set ) ) );

}

// Αφαιρεί τη μικρότερο τιμή της ουράς (μη ορισμένο αποτέλεσμα αν η ουρά είναι κενή)

void depq_remove_min(DEPQ depq){

     set_remove(depq->set, set_node_value(depq->set, set_first( depq->set ) ) );
}

// Αλλάζει τη συνάρτηση που καλείται σε κάθε αφαίρεση/αντικατάσταση στοιχείου σε
// destroy_value. Επιστρέφει την προηγούμενη τιμή της συνάρτησης.

DestroyFunc depq_set_destroy_value(DEPQ depq, DestroyFunc destroy_value){
    return set_set_destroy_value(depq->set, destroy_value);  // Ενημερώνουμε την destroy συνάρτηση του Set
}

// Ελευθερώνει όλη τη μνήμη που δεσμεύει η ουρά depq.
// Οποιαδήποτε λειτουργία πάνω στη ουρά μετά το destroy είναι μη ορισμένη.

void depq_destroy(DEPQ depq){

    set_destroy(depq->set);  // Καταστρέφει όλα τα στοιχεία του Set
    free(depq);              // Αποδεσμεύουμε τη δομή depq

}







