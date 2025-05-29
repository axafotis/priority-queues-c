#include <stdlib.h>             // Για malloc
#include <assert.h>             // Για assert

#include "ADTKPQ.h"             // Header του KPQ
#include "ADTDEPQ.h"            // Χρήση DEPQ από την Άσκηση 2
#include "ADTPriorityQueue.h"   // Χρήση PQ για τα υπόλοιπα στοιχεία


// Δομή της KPQ που κρατάει 2 ουρές και έναν ακέραιο k
struct kpq {
    DEPQ top_k;               // DEPQ που περιέχει τα k μεγαλύτερα στοιχεία
    PriorityQueue rest;       // PQ που περιέχει τα υπόλοιπα στοιχεία
    int k;                    // Πλήθος στοιχείων που κρατάμε στο DEPQ (τα μεγαλύτερα)
    DestroyFunc destroy_value;
};

// Συνάρτηση δημιουργίας KPQ
KPQ kpq_create(CompareFunc compare, int k, DestroyFunc destroy_value) {
    assert(k > 0);  // Απαιτείται k > 0 για να έχει νόημα η δομή

    KPQ kpq = malloc(sizeof(*kpq));                      // Δέσμευση μνήμης για τη δομή KPQ
    kpq->top_k = depq_create(compare, NULL);    // Δημιουργία DEPQ για τα top-k
    kpq->rest = pqueue_create(compare, NULL, NULL);  // Δεν δίνουμε destroy_value γιατί όταν αφαιρείται ο κόμβος από το rest, το value ΔΕΝ πρέπει να καταστραφεί — θα μεταφερθεί στο top_k (DEPQ)
    kpq->k = k;   
    kpq->destroy_value =  destroy_value;          
    
    

    return kpq;  // Επιστροφή της νέας KPQ
}

int kpq_size(KPQ kpq) {
    return  depq_size(kpq->top_k) + pqueue_size(kpq->rest);  // Άθροισμα στοιχείων και από τις δύο ουρές
}

Pointer kpq_max(KPQ kpq) {
    return depq_max(kpq->top_k);  // Το μέγιστο στοιχείο βρίσκεται στο DEPQ
}

Pointer kpq_k_th(KPQ kpq) {
    return depq_min(kpq->top_k);  // Το μικρότερο από τα top-k είναι το k-οστό μεγαλύτερο
}

void kpq_insert(KPQ kpq, Pointer value) {
    

    depq_insert(kpq->top_k, value);                 // Εισάγουμε την τιμή προσωρινά στα top-k (DEPQ)

    if (depq_size(kpq->top_k) > kpq->k) {           // Αν το πλήθος στοιχείων στο top_k ξεπερνάει το k
        Pointer min = depq_min(kpq->top_k);         // Παίρνουμε το μικρότερο στοιχείο από το top_k
       
        depq_remove_min(kpq->top_k);                // Το αφαιρούμε από το top_k
        pqueue_insert(kpq->rest, min);              // Και το προσθέτουμε στα υπόλοιπα (rest)
    }

}

void kpq_remove_max(KPQ kpq) {  

    Pointer max = depq_max(kpq->top_k); 

    depq_remove_max(kpq->top_k);

    if (kpq->destroy_value != NULL)           //  Αν έχει δώσει destroy ο χρήστης
        kpq->destroy_value(max);              //    κάνε destroy στο value

    if (pqueue_size(kpq->rest) > 0) {                     // Αν υπάρχει στοιχείο στο rest

        Pointer max = pqueue_max(kpq->rest);              // Παίρνουμε το μέγιστο από το rest
        
        
        pqueue_remove(kpq->rest, pqueue_max_node(kpq->rest));  // Το αφαιρούμε από το rest
        depq_insert(kpq->top_k, max);                     // Και το προσθέτουμε πίσω στο top_k

    }


}

DestroyFunc kpq_set_destroy_value(KPQ kpq, DestroyFunc destroy_value) {
       
    DestroyFunc old = kpq->destroy_value;     // Κρατάμε την προηγούμενη
    kpq->destroy_value = destroy_value;       // Θέτουμε τη νέα
    return old;

}

void kpq_destroy(KPQ kpq) {

    // Όσο υπάρχουν στοιχεία, τα αφαιρούμε και κάνουμε εμείς destroy (π.χ. free)
    while (kpq_size(kpq) > 0) {
        
        void* value = kpq_max(kpq);          // Παίρνουμε το μέγιστο

        //-- εδω ουσιαστικα κανω το ιδιο που κανω και στη kpq_remove_max απλα χωρις το destroy value
        depq_remove_max(kpq->top_k);

        if (pqueue_size(kpq->rest) > 0) {                     // Αν υπάρχει στοιχείο στο rest
            
            Pointer max = pqueue_max(kpq->rest);              // Παίρνουμε το μέγιστο από το rest
            pqueue_remove(kpq->rest, pqueue_max_node(kpq->rest));  // Το αφαιρούμε από το rest
            depq_insert(kpq->top_k, max);                     // Και το προσθέτουμε πίσω στο top_k

        }
        
        if (kpq->destroy_value != NULL) {    // Αν ο χρήστης έδωσε destroy
            kpq->destroy_value(value);
        }  
    }

    // Τώρα μπορούμε με ασφάλεια να καταστρέψουμε τις δομές
    depq_destroy(kpq->top_k);
    pqueue_destroy(kpq->rest);
    free(kpq);  // Τέλος, αποδεσμεύουμε το ίδιο το struct

}

     
   









