# Κάνοντας compile το <foo>_test.c με μια υλοποίηση <foo>.c του
# συγκεκριμένου τύπου, παράγουμε ένα tets για την υλοποίηση αυτή.


# Υλοποιήσεις μέσω ADT Set: ADTPriorityQueue
# Χρειαζόμαστε και υλοποιήσεις για τα ADTSet και ADTVector
#
UsingADTSet_ADTPriorityQueue_test_OBJS = ADTPriorityQueue_test.o $(MODULES)/UsingADTSet/ADTPriorityQueue.o $(MODULES)/UsingAVL/ADTSet.o $(MODULES)/UsingDynamicArray/ADTVector.o
# Υλοποίηση DEPQ μέσω ADT Set
UsingADTSet_ADTDEPQ_test_OBJS = ADTDEPQ_test.o $(MODULES)/UsingADTSet/ADTDEPQ.o $(MODULES)/UsingAVL/ADTSet.o $(MODULES)/UsingDynamicArray/ADTVector.o

UsingADTDEPQ_ADTKPQ_test_OBJS = ADTKPQ_test.o $(MODULES)/UsingADTDEPQ/ADTKPQ.o $(MODULES)/UsingADTSet/ADTPriorityQueue.o $(MODULES)/UsingADTSet/ADTDEPQ.o $(MODULES)/UsingAVL/ADTSet.o $(MODULES)/UsingDynamicArray/ADTVector.o

all: UsingADTSet_ADTPriorityQueue_test UsingADTSet_ADTDEPQ_test UsingADTDEPQ_ADTKPQ_test


# Ο βασικός κορμός του Makefile
include ../common.mk

# Εκτέλεση όλων των tests με valgrind
valgrind: valgrind-UsingADTDEPQ_ADTKPQ_test valgrind-UsingADTSet_ADTDEPQ_test valgrind-UsingADTSet_ADTPriorityQueue_test

valgrind-%:
	valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all ./$(*) --time
