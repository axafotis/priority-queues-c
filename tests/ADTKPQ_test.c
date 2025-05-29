
////////////////////////////////////////////////////////////
//
// Unit tests για τον ADT k-Priority Queue (KPQ)
//
////////////////////////////////////////////////////////////

#include "acutest.h"


#include "ADTKPQ.h"


// Βοηθητικές συναρτήσεις
int compare_ints(Pointer a, Pointer b) {
	return *(int*)a - *(int*)b;
}

int* create_int(int value) {
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}



// θέτει τα στοιχεία του πίνακα array  σε τυχαία σειρά
void shuffle(int* array[], int size) {
	for (int i = 0; i < size; i++) {
		int new_pos = i + rand() / (RAND_MAX / (size - i) + 1);
		int* temp = array[new_pos];
		array[new_pos] = array[i];
		array[i] = temp;
	}
}

// Test για την kpq_create
void test_create(void) {
	KPQ kpq = kpq_create(compare_ints, 3, NULL);      // Δημιουργούμε KPQ με k=3 και χωρίς destroy
	//kpq_set_destroy_value(kpq, NULL);                 // Εξασφαλίζουμε ότι δεν κάνει free τίποτα

	TEST_ASSERT(kpq != NULL);                         // Η δομή πρέπει να έχει δημιουργηθεί επιτυχώς
	TEST_ASSERT(kpq_size(kpq) == 0);                  // Αρχικά είναι άδεια

	kpq_destroy(kpq);                                 // Καταστροφή χωρίς leaks
}

void test_insert(void) {
    int k = 10;                                                    // Ορίζουμε πόσα top-k στοιχεία θα κρατάμε
    KPQ kpq = kpq_create(compare_ints, k, free);                   // Δημιουργούμε KPQ με destroy = free, για σωστό καθαρισμό

    int N = 100;                                                   // Συνολικός αριθμός στοιχείων για εισαγωγή
    int** array = malloc(N * sizeof(*array));                      // Δεσμεύουμε πίνακα από δείκτες σε int

    for (int i = 0; i < N; i++) {
        array[i] = create_int(i);                                  // Δημιουργούμε νέο int με malloc και τιμή i
        kpq_insert(kpq, array[i]);                                 // Το εισάγουμε στην ουρά

        TEST_ASSERT(kpq_size(kpq) == i + 1);                       // Ελέγχουμε ότι το μέγεθος αυξάνεται σωστά

        TEST_ASSERT(kpq_max(kpq) == array[i]);                     // Εισάγουμε σε αύξουσα σειρά, άρα το τελευταίο είναι και το μέγιστο

        if (i >= k - 1)
            TEST_ASSERT(kpq_k_th(kpq) == array[i - k + 1]);        // Ελέγχουμε ότι το k-οστό μέγιστο είναι σωστό
    }

    kpq_destroy(kpq);                                              // Καταστρέφουμε την KPQ — κάνει free όλα τα int*
    free(array);                                                   // Ελευθερώνουμε τον πίνακα δεικτών (όχι τα περιεχόμενα, έχουν ήδη διαγραφεί)
}

void test_remove_max(void) {   
    
    KPQ kpq = kpq_create(compare_ints, 5, free);   // Δημιουργία KPQ με destroy = free

    int N = 10;
    int** array = malloc(N * sizeof(*array));      // Πίνακας από δυναμικά δεσμευμένους δείκτες

    for (int i = 0; i < N; i++)
        array[i] = create_int(i);                  // Τιμές 0 έως N-1

    shuffle(array, N);                             // Τυχαία σειρά εισαγωγής

    for (int i = 0; i < N; i++)
        kpq_insert(kpq, array[i]);                 // Εισαγωγή στοιχείων στην KPQ

    // Αφαιρούμε ένα-ένα το μέγιστο, ελέγχοντας τιμές και μέγεθος
    for (int i = N - 1; i >= 0; i--) {
         int* value = (int*)kpq_max(kpq);           // Παίρνουμε το μέγιστο στοιχείο
        TEST_ASSERT(*value == i);                  // Πρέπει να είναι το i (αφού ήταν όλα 0..N-1)
        kpq_remove_max(kpq);                       // Αφαιρούμε το μέγιστο
        TEST_ASSERT(kpq_size(kpq) == i);           // Ελέγχουμε μέγεθος
 }

    kpq_destroy(kpq);  // Καταστροφή της ουράς
    free(array);       // Αποδέσμευση του πίνακα δεικτών


}    





// Δήλωση των tests που θα τρέξουν
TEST_LIST = {
	{ "kpq_create", test_create },
    { "kpq_insert", test_insert },
    { "test remove_max", test_remove_max},
	{ NULL, NULL }
};
