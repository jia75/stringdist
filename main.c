#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "algorithms.c"

void setupWordlist(char ***deposit, char *filename) {
    (*deposit) = malloc(10000*sizeof(char *));
    int i = 0;

    FILE *words = fopen(filename, "r");
    
    char buffer;

    char *curstring = malloc(128*sizeof(char));
    
    while ((buffer = fgetc(words)) != EOF) {
        if (buffer != '\n') {
            sprintf(curstring, "%s%c", curstring, buffer);
        } else {
            (*deposit)[i] = malloc((strlen(curstring) + 1) * sizeof(char));
            strcpy((*deposit)[i], curstring);
            ++i;
            strcpy(curstring, "");
        }
    }

    free(curstring);

    fprintf(stderr, "Found %d records.\n", i);
}

int makeCorrection(char *from, char **to, int alg) {
    if (alg == 0) {
        int mindist = 999999999, choice;
        int dist;
        for (int i = 0; i<10000; ++i) {
            dist = levenshteinDistance(from, to[i]);
            if (dist < mindist) {
                mindist = dist;
                choice = i;
            }
        }

        return choice;
    }
    if (alg == 1) {
        int mindist = 999999999, choice;
        int dist;
        for (int i = 0; i<10000; ++i) {
            dist = characterLink(from, to[i], 1);
            if (dist < mindist) {
                mindist = dist;
                choice = i;
            }
        }

        return choice;
    }
    if (alg == 2) {
        int mindist = 999999999, choice;
        int dist;
        for (int i = 0; i<10000; ++i) {
            dist = characterLink(from, to[i], 2);
            if (dist < mindist) {
                mindist = dist;
                choice = i;
            }
        }

        return choice;
    }
}

int testCompatibility(char **from, char **to, int alg1, int alg2) {
    int count = 0;
    int res1, res2;
    for (int i = 0; i < 10000; ++i) {
        res1 = makeCorrection(from[i], to, alg1);
        res2 = makeCorrection(from[i], to, alg2);
        if (res1 == res2) ++count;
        // fprintf(stdout, "%s --> %s, %s\n", from[i], to[res1], to[res2]);
    }
    return count;
}

int main() {
    fprintf(stdout, "Test\n");
    char **wordlist;
    char **errlist;
    char **nudgelist;

    
    setupWordlist(&wordlist, "words.txt");
    setupWordlist(&errlist, "random-normal-100-1.5-10k.txt");
    setupWordlist(&nudgelist, "random-edit-2-1.5.txt");
    
    for (int i = 0;i < 10000; ++i) {
        // fprintf(stdout, "%s\n", wordlist[i]);
    }
    fprintf(stdout, "From r100 to w. Comp %d and %d. Result %d\n", 0, 1, 
        testCompatibility(errlist, wordlist, 0, 1));
    fprintf(stdout, "From r100 to w. Comp %d and %d. Result %d\n", 0, 2, 
        testCompatibility(errlist, wordlist, 0, 2));
    fprintf(stdout, "From r100 to w. Comp %d and %d. Result %d\n", 1, 2, 
        testCompatibility(errlist, wordlist, 1, 2));
    
    /* fprintf(stdout, "From er to w. Comp %d and %d. Result %d\n", 0, 1, 
        testCompatibility(nudgelist, wordlist, 0, 1));
    fprintf(stdout, "From er to w. Comp %d and %d. Result %d\n", 0, 2, 
        testCompatibility(nudgelist, wordlist, 0, 2));
    fprintf(stdout, "From er to w. Comp %d and %d. Result %d\n", 1, 2, 
        testCompatibility(nudgelist, wordlist, 1, 2)); */
    
    return 0;
}