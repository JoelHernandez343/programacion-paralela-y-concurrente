#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define N 32
#define PRC_NUMBER 2

void child_process(int, int *);
void parent_process();
int * memoryAllocation();
void fillArray(int *);
void showArray(int *);
int searchHigher (int *);
int searchSmaller (int *);

int * data;

int main() {
    pid_t pid;
    register int np;

    printf("Example of process\n");

    data = memoryAllocation();
    fillArray(data);
    showArray(data);

    for (np = 0; np < PRC_NUMBER; ++np){
        pid = fork();
        if (pid == -1) {
            perror("Error creating process!\n");
            exit(EXIT_FAILURE);
        }
        if (!pid) {
            child_process(np, data);
        }
    }

    parent_process();

    free(data);

    return 0;
}

int * memoryAllocation() {
    int * mem = (int *)malloc(N * sizeof(int));

    if (!mem) {
        perror("Error allocating memory...\n");
        exit(EXIT_FAILURE);
    }

    return mem;
}

void fillArray(int * array) {
    register int i;

    for (i = 0; i < N; ++i){
        data[i] = rand() % 256;
    }
}

void showArray(int * array){
    register int i;

    for (i = 0; i < N; ++i){
        if (!(i % 16)) printf("\n");

        printf("%3d ", array[i]);
    }

    printf("\n");
}

void child_process(int np, int * data) {
    if (np == 0){
        exit(searchHigher(data));
    } else if (np == 1) {
        exit(searchSmaller(data));
    }
}

int searchHigher (int * data){
    int higher = data[0];
    register int i;

    for (i = 1; i < N; ++i){
        if (data[i] > higher)
            higher = data[i];
    }

    return higher;
}

int searchSmaller(int * data){
    int smaller = data[0];
    register int i;

    for (i = 1; i < N; ++i){
        if (data[i] < smaller)
            smaller = data[i];
    }

    return smaller;
}

void parent_process() {
    register int np;
    pid_t pid;
    int status;

    for (np = 0; np < PRC_NUMBER; ++np) {
        pid = wait(&status);

        printf("Child process w/ pid %d return %d\n", pid, status >> 8);
    }
}