# Priority Queues in C

Implementation of advanced **Priority Queue** data structures in C, with clean modular design and unit tests.  
This project was developed as part of the **Data Structures & Programming Techniques** course (NKUA).

---

## Implemented Data Structures
- **Priority Queue (PQueue)**  
  - Insert / remove any node  
  - Fast access to maximum element  

- **Double-Ended Priority Queue (DEPQ)**  
  - Access both minimum and maximum  
  - Remove from either end  

- **K-Priority Queue (KPQ – top-k)**  
  - Maintains the k largest elements  
  - Efficient max / k-th element queries  

---

## Time Complexities
- **PQueue**: Insert/Remove O(log n), Max O(1)  
- **DEPQ**: Insert/Remove O(log n), Min/Max O(1)  
- **KPQ**: Insert/Remove O(log n), Max/k-th O(1)  

---

## Key Highlights
- ✅ Clean modular C code  
- ✅ Memory management checked (Valgrind clean)  
- ✅ Automated tests with `make`  
- ✅ Continuous Integration (GitHub Actions)  
- ✅ Hands-on experience with **C, algorithms, data structures, and Git**  
- ✅ Source code **commented in Greek** (per university requirements) but fully capable of producing **professional English documentation/comments**  

---

## Build & Run
```bash
# Build project
make

# Run unit tests
make -C tests
```

---
*Note: Source code is commented in Greek (per university requirements), but I am fully capable of producing professional English documentation/comments.*

