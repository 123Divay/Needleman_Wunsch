# Needleman_Wunsch Algorithm
# Introduction :-
Needleman-Wunsch algorithm is an algorithm that is used in bioinformatics to align DNA or protein sequences. It involves the use of dynamic programming to compare biological sequences. The Needleman-Wunsch algorithm is used to find the optimal global alignment, and essentially divides a larger problem into a series of smaller problems to find this optimal alignment.
# Task :-
We attempt to make improvements upon the baseline performance of the algorithm by parallelizing it and optimizing it to achieve the peak performance possible.
# Performance Evaluation Framework :-
The main performance metrics were Execution Time and Throughput.
# Optimization Techniques used :-
## 1. Exploiting Cache Locality
   Accessing data row-wise gave better results than accessing colum-wise. This difference is intuitive since 2D matrices are stored in row-major form.
## 2. Compiler Optimizations
   We tested the code by adding various compiler flags and on various compilers (both ICC and GCC). The differences have been given in the images files.
## 3. Parallelization along Anti Diagonal
   By analyzing the dependency graph in states of the dynamic programming problem, we concluded that traversing along anti-diagonals would reduce the number of dependencies at each step, thus enabling higher 
   parallelization.
## 4. Tiling using Submatrices
   Although the anti-diagonal optimization allows higher parallelism, it doesn't let us exploit cache locality. Thus, we used the Tiling Technique. iling is a technique wherein the original DP matrix is divided 
   into square submatrices. We then fill each submatrix with the corresponding values just like we do for the normal matrix, using row traversal. We proceed in this manner, filling all the submatrices and filling 
   the leftover cells using brute force, iterating through all of them and filling them based on the values of the previous cells. It allows us to make use of both parallelism, and cache locality.
