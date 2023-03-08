#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void computeLPSArray(char *pat, int M, int *lps) {
    lps[0] = -1;
    int i = 1;
    int j = 0; 
    while (i < M) {
        if (pat[j] == pat[i]) {
            lps[i] = lps[j];
            i++;
            j++;
        }
        else {// (pat[j] != pat[i])
            lps[i] = j;
            j = lps[j];
            while (j >= 0 && pat[j] != pat[i]) {
                j = lps[j];
            }
            i++;
            j++;
        }
    }
    lps[i] = j;
}

void KMPSearch(char *pat, char *txt) {
    int M = strlen(pat);
    int N = strlen(txt);

    //create lps[] that will hold the longest prefix suffix values for pattern
    int *lps = (int *)malloc(sizeof(int) * (M + 1));

    //Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0; //index for txt[]
    int j = 0; //index for pat[]
    
    //at this point i may be incremented while i < N && txt[i] != pat[0] - for performance 
    while (i < N) {
        if (pat[j] == txt[i]) {
            i++;
            j++;
            if (j == M) {
                printf("Found pattern at index %d \n", i-j);
                j = lps[j];
            }
        }
        else {//if (pat[j] != txt[i]) //mismatch after j matches
        //Pattern shift
            j = lps[j];
            if (j < 0) {
                i++;
                j++;
            //at this point i may be incremented while i < N && txt[i] != pat[0] - for performance 
            }
        }
    }
    free(lps); //to avoid memory leak
}

int main() {
    char *txt = "atcgagatcgatcgatagcgagatatagcgatatagcgat";
    char *pat = "atc";
    KMPSearch(pat, txt);
    return 0;
}
