#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <sys/time.h>
#include <omp.h>

#include "helper.hpp"

using namespace std;

double needleman_wunsch(string &A, string &B, int match_penalty, int mismatch_penalty, int gap_penalty,int tileSize) {

    int sequence1_size = A.size(), sequence2_size = B.size(),x=tileSize,y=tileSize;

    int **dp = new int *[sequence1_size + 1];
    for (int i = 0; i <= sequence1_size; i++)
        dp[i] = new int[sequence2_size + 1];

    double gflops = 6 * sequence1_size * sequence2_size;

    struct timeval t;
    start(&t);

    #pragma omp parallel for
    for (int i=0; i <= sequence1_size; i++) {
        dp[i][0]=i*gap_penalty;
    }

    #pragma omp parallel for
    for (int i=0; i <=sequence2_size; i++) {
        dp[0][i]=i*gap_penalty;
    }

    int horiTiles = sequence1_size/tileSize;
    int vertTiles = sequence2_size/tileSize;

    for (int diagNum=0; diagNum < min(horiTiles,vertTiles); diagNum++) {
        int startI = 1;
        int startJ = 1 + diagNum * tileSize;  
        for (int tile=0; tile <= diagNum; tile++) {
            for (int i=startI; i < startI+tileSize; i++) {
            for (int j=startJ; j < startJ+tileSize; j++) {
            int score = A[i-1] == B[j-1] ? match_penalty : mismatch_penalty;
            dp[i][j] = max(dp[i-1][j-1] + score, max(dp[i-1][j] + gap_penalty, dp[i][j-1] + gap_penalty));
    }
    }
    startI+=tileSize;
    startJ-=tileSize;
    }  
    }

    for (int diagNum=min(horiTiles,vertTiles)-1; diagNum>0; diagNum--) {
        int startI = 1 + (min(horiTiles,vertTiles)-diagNum)*tileSize;
        int startJ = 1 + (min(horiTiles,vertTiles)-1)*tileSize;
        for (int tile=0; tile < diagNum; tile++) {
             for (int i=startI; i < startI+tileSize; i++) {
            for (int j=startJ; j < startJ+tileSize; j++) {
            int score = A[i-1] == B[j-1] ? match_penalty : mismatch_penalty;
            dp[i][j] = max(dp[i-1][j-1] + score, max(dp[i-1][j] + gap_penalty, dp[i][j-1] + gap_penalty));
    }
    }
    startI+=tileSize;
    startJ-=tileSize;
    }
    }

    int totaDiagonals=min(horiTiles,vertTiles);

    if (sequence1_size > totaDiagonals*tileSize) {
        for (int i=1+totaDiagonals*tileSize; i <= sequence1_size; i++) {
            for (int j=1; j <= 1+totaDiagonals*tileSize; j++) {
                 int score = A[i-1] == B[j-1] ? match_penalty : mismatch_penalty;
                 dp[i][j] = max(dp[i-1][j-1] + score, max(dp[i-1][j] + gap_penalty, dp[i][j-1] + gap_penalty));
            }
        }
    }
    
     if (sequence2_size > totaDiagonals*tileSize) {
        for (int i=1; i <= sequence1_size; i++) {
            for (int j=1+totaDiagonals*tileSize; j <= sequence2_size; j++) {
                 int score = A[i-1] == B[j-1] ? match_penalty : mismatch_penalty;
                 dp[i][j] = max(dp[i-1][j-1] + score, max(dp[i-1][j] + gap_penalty, dp[i][j-1] + gap_penalty));
            }
        }
    }


    double time = end(&t);

    return time;
    // return gflops / (time * 1e9);
}

int main()
{

    ofstream fout("optimized_4_output.txt");
     

    for (int i = 1; i <= 1000; i++)
    {
        string A = generate_random_string(i), B = generate_random_string(i);
       

        int match_penalty = 1, mismatch_penalty = -1, gap_penalty = -2;

        double time = needleman_wunsch(A, B, match_penalty, mismatch_penalty, gap_penalty,4);

        fout << time << " " << i << " " << "\n";
    }
    fout.close();
}
