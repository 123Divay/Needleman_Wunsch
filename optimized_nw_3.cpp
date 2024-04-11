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

double needleman_wunsch(string &A, string &B, int match_penalty, int mismatch_penalty, int gap_penalty) {

    int sequence1_size = A.size(), sequence2_size = B.size();

    int **dp = new int *[sequence1_size + 1];
    for (int i = 0; i <= sequence1_size; i++)
        dp[i] = new int[sequence2_size + 1];

    double gflops = 6 * sequence1_size * sequence2_size;

    struct timeval t;
    start(&t);

    #pragma omp parallel for 
    for (int i=0; i<=sequence1_size; i++) {
        dp[i][0] = i * gap_penalty;
    }
    
    #pragma omp parallel for
    for (int i=0; i<=sequence2_size; i++) {
        dp[0][i] = i * gap_penalty;
    }

    for (int z=1; z<=sequence2_size; z++) {
        int i,j=z;
        #pragma omp parallel for
        for(i=1;i<=sequence1_size && j>=1;i++){
            int score = A[i-1] == B[j-1] ? match_penalty : mismatch_penalty;
            dp[i][j] = max(dp[i-1][j-1] + score, max(dp[i-1][j] + gap_penalty, dp[i][j-1] + gap_penalty));
            j--;
        }
    }

    for (int z=2; z<=sequence1_size; z++) {
        int j,i=z;
        #pragma omp parallel for
        for(j=sequence2_size;i<=sequence1_size && j>=1;j--){
            int score = A[i-1] == B[j-1] ? match_penalty : mismatch_penalty;
            dp[i][j] = max(dp[i-1][j-1] + score, max(dp[i-1][j] + gap_penalty, dp[i][j-1] + gap_penalty));
            i++;
        }
    }


    double time = end(&t);

    return time;
    //return gflops / (time * 1e9);

}


int main() {

    ofstream fout("optimized_3_output.txt");

    for (int i=1; i<=1000; i++) {

        string A = generate_random_string(i), B = generate_random_string(i);

        int match_penalty = 1, mismatch_penalty = -1, gap_penalty = -2;

        double time = needleman_wunsch(A, B, match_penalty, mismatch_penalty, gap_penalty);

        fout << time << " " << i << " " << "\n";
    }
    fout.close();
}