//////////////////////////////////////////////////////////////////
//
// Unit tests για τον ADT Priority Queue.
// Οποιαδήποτε υλοποίηση οφείλει να περνάει όλα τα tests.
//
//////////////////////////////////////////////////////////////////

#include "acutest.h"			// Απλή βιβλιοθήκη για unit testing

#include "ADTDEPQ.h"

// θέτει τα στοιχεία του πίνακα array  σε τυχαία σειρά
void shuffle(int* array[], int size) {
	for (int i = 0; i < size; i++) {
		int new_pos = i + rand() / (RAND_MAX / (size - i) + 1);
		int* temp = array[new_pos];
		array[new_pos] = array[i];
		array[i] = temp;
	}
}

// Επιστρέφει έναν ακέραιο σε νέα μνήμη με τιμή value
int* create_int(int value) {
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}

int compare_ints(Pointer a, Pointer b) {
	return *(int*)a - *(int*)b;
}

void test_create(void) {
    DEPQ depq = depq_create(compare_ints, NULL);
	depq_set_destroy_value(depq, NULL);

	TEST_ASSERT(depq != NULL);
	TEST_ASSERT(depq_size(depq) == 0);

	depq_destroy(depq);

	

}	

void test_insert(void) {
	DEPQ depq = depq_create(compare_ints, NULL);
	int N = 1000;
	int* array = malloc(N * sizeof(*array));					// Στο pqueue θα προσθέσουμε pointers προς τα στοιχεία αυτού του πίνακα
	

	// insert N στοιχεία
	for (int i = 0; i < N; i++) {
		array[i] = i;
		depq_insert( depq, &array[i] );
		TEST_ASSERT( depq_size(depq) == i+1 );			// Το size ενημερώθηκε;
		TEST_ASSERT( depq_max(depq) == &array[i] );	// Εισαγωγή σε αύξουσα σειρά, το στοιχείο που μόλις βάλαμε πρέπει να είναι στην κορυφή
        TEST_ASSERT( depq_min(depq) == &array[0] );     // min παραμένει σταθερό στο πρώτο στοιχείο
		
	}

	depq_destroy(depq);
	free(array);
	
}

void test_remove_max(void) {

	 DEPQ depq = depq_create(compare_ints, free);  // Δημιουργία ουράς DEPQ με σύγκριση ακεραίων και συνάρτηση καταστροφής

    int N = 10;  // Πλήθος στοιχείων προς εισαγωγή
    int** array = malloc(N * sizeof(*array));  // Δέσμευση μνήμης για πίνακα από δείκτες σε ακέραιους
    for (int i = 0; i < N; i++)                  // Δημιουργία τιμών 0–9
        array[i] = create_int(i);               // Κάθε θέση δείχνει σε δυναμικά δεσμευμένο int με τιμή i
    shuffle(array, N);                          // Ανακατεύουμε τον πίνακα για να προσθέσουμε σε τυχαία σειρά

    for (int i = 0; i < N; i++)                 
        depq_insert(depq, array[i]);            // Εισαγωγή των τιμών στην ουρά

    for (int i = N - 1; i >= 0; i--) {                              // Διαδοχική αφαίρεση του max από την ουρά
        int* value = depq_max(depq);                                // Παίρνουμε το μέγιστο στοιχείο
        TEST_ASSERT(*value == i);                                   // Ελέγχουμε ότι είναι το αναμενόμενο
        depq_remove_max(depq);                                      // Αφαιρούμε το μέγιστο στοιχείο από την ουρά
        TEST_ASSERT(depq_size(depq) == i);                          // Ελέγχουμε ότι το μέγεθος μειώθηκε σωστά
    }

    depq_destroy(depq);  // Καταστροφή της ουράς και αποδέσμευση μνήμης των τιμών (μέσω free)

    // Δοκιμή αφαίρεσης max από ουρά χωρίς destroy function
    depq = depq_create(compare_ints, NULL);        // Νέα ουρά χωρίς συνάρτηση καταστροφής
    depq_insert(depq, &N);                         // Εισαγωγή δείκτη προς τον ακέραιο N
    TEST_ASSERT(depq_max(depq) == &N);             // Βεβαιωνόμαστε ότι είναι το μόνο και μέγιστο στοιχείο
    depq_remove_max(depq);                         // Το αφαιρούμε
    depq_destroy(depq);                            // Καταστροφή ουράς
    free(array);                                   // Αποδέσμευση μνήμης πίνακα δεικτών

}

void test_remove_min(void) {

    DEPQ depq = depq_create(compare_ints, free);  // Δημιουργία ουράς DEPQ με συνάρτηση καταστροφής (free)

    int N = 10;  // Πλήθος στοιχείων
    int** array = malloc(N * sizeof(*array));  // Πίνακας από δείκτες σε ακέραιους
    for (int i = 0; i < N; i++)                 // Γέμισμα του πίνακα με τιμές 0–9
        array[i] = create_int(i);
    shuffle(array, N);                         // Ανακάτεμα για τυχαία εισαγωγή

    for (int i = 0; i < N; i++)                 
        depq_insert(depq, array[i]);           // Εισαγωγή στοιχείων στην ουρά

    for (int i = 0; i < N; i++) {                              // Διαδοχική αφαίρεση του ελάχιστου στοιχείου
        int* value = depq_min(depq);                          // Παίρνουμε το μικρότερο στοιχείο
        TEST_ASSERT(*value == i);                             // Ελέγχουμε ότι είναι το σωστό (εισάγαμε 0–9)
        depq_remove_min(depq);                                // Αφαιρούμε το min
        TEST_ASSERT(depq_size(depq) == N - i - 1);            // Ελέγχουμε ότι μειώθηκε σωστά το μέγεθος
    }

    depq_destroy(depq);  // Αποδέσμευση μνήμης και καταστροφή ουράς

    // Δοκιμή χωρίς destroy function
    depq = depq_create(compare_ints, NULL);     // Δημιουργία DEPQ χωρίς free
    depq_insert(depq, &N);                      // Προσθήκη δείκτη σε τοπική μεταβλητή
    TEST_ASSERT(depq_min(depq) == &N);          // Επιβεβαίωση τιμής
    depq_remove_min(depq);                      // Αφαίρεση του min
    depq_destroy(depq);                         // Καταστροφή ουράς
    free(array);                                // Αποδέσμευση πίνακα
    
}




// Λίστα με όλα τα tests προς εκτέλεση
TEST_LIST = {
	{ "depq_create", test_create },
	{ "depq_insert", test_insert },
	{ "depq_remove_max", test_remove_max },
	{ "depq_remove_min", test_remove_min },
    { NULL, NULL } // τερματίζουμε τη λίστα με NULL
};