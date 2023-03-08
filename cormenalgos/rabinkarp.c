#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>






void rabinkarp(char* T, char* P, int d, int q) {
    int n = strlen(T);
    int m = strlen(P);
    int h = (int)pow(d,m-1) % q;
    int p = 0;
    int t0 = 0;
    for(int i = 0; i < m; i++) {
        p = (d*p + P[i]) % q;
        t0 = (d*t0 + T[i]) % q;
    }
    for(int s = 0; s < n-m+1; s++) {
        if(p == t0) {
            char subT[m];
            strncpy(subT, T+s, m);
            if(strcmp(P,subT)==0) {
                printf("pattern occurs with shift %d\n", s);
            }
        }
        if(s < n-m) {
            t0 = (t0-h*T[s]) % q;
            t0 = (t0*d+T[s+m]) % q;
            t0 = (t0+q) % q;
        }
    }
}


int main() {
    char* T = "01233948248824812";
    char* P = "248";
    int d = 10;
    int q = 13;
    rabinkarp(T,P,d,q);
}