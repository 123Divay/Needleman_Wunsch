#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>

using namespace std;

void start(struct timeval *t) {
    gettimeofday(t,NULL);
}

double end(struct timeval *t) {
    struct timeval now;
    gettimeofday(&now,NULL);
    return (double)(now.tv_sec-t->tv_sec) + ((double)(now.tv_usec-t->tv_usec) / 1000000.);
}

string generate_random_string(int length) {

    srand(time(NULL));
    string alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ", result;
    for (int i=0; i<length; i++) {
        result+=alphabets[rand() % 26];
    }
    return result;
}