# Priority Queues in C

Implementation of advanced **Priority Queue** data structures in C, with clean modular design and unit tests.  
Includes:
- **Priority Queue (PQueue)**: supports insertion, deletion of any node, and fast access to the maximum element.  
- **Double-Ended Priority Queue (DEPQ)**: supports both minimum and maximum operations.  
- **K-Priority Queue (KPQ – top-k)**: maintains the k largest elements while supporting efficient updates.

---

## Features & Complexities
- **PQueue**  
  - Insert / remove: O(log n)  
  - Access max: O(1)  

- **DEPQ**  
  - Insert / remove_min / remove_max: O(log n)  
  - Access min / max: O(1)  

- **KPQ (top-k)**  
  - Insert / remove_max: O(log n)  
  - Access max / k_th: O(1)  

✅ All data structures tested with unit tests.  
✅ No memory leaks (valgrind clean).  
✅ Continuous Integration with GitHub Actions (Ubuntu runner).

---

## Build & Run
```bash
# Build
make

# Run unit tests
make -C tests
