#include "header.h"
#include <pthread.h>

// Used to pass (i, j) to thread execution routine.
typedef struct{
    int a, b;
} Point;

// Routine to compute_element (point(i,j)) for a given thread and store the result in Matrix out.
void* compute_element(void *point){
    Point* p = (Point*) point;
    int i = p->a, j = p->b;
    int sum = 0;
    int m = a->m;
    for(int k = 0 ; k < m; k++){
        sum += a->data[i][k] * b->data[k][j];
    }
    out->data[i][j] = sum;
    pthread_exit(point);
}

// Calling this method will multiply the external Matrix a and Matrix b and store the result in Matrix out
// by calculating each element with a separate thread.
void compute_element_with_thread(){
    int n = a->n;
    int m = b->m;
    pthread_t threads[n*m];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            Point* p = malloc(sizeof(Point));
            p->a = i;
            p->b = j;
            if(pthread_create(&threads[i * m + j], NULL, compute_element, (void *)p)){
                perror("Cannot create thread!");
                exit(-1);
            };
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            void* ptr;
            pthread_join(threads[i * m + j], (void **) &ptr);
            Point* p = (Point *) ptr;
            free(p);
        }
    }
}

// Routine to compute_row (row) for a given thread and store the result in Matrix out.
void* compute_row(void* row){
    int i = (int) row;
    int m = a->m;
    for(int j = 0; j < b->m; j++){
        int sum = 0;
        for(int k = 0; k < m; k++){
            sum += a->data[i][k]  * b->data[k][j];
        }
        out->data[i][j] = sum;
    }
}

// Calling this method will multiply the external Matrix a and Matrix b and store the result in Matrix out
// by calculating each row with a separate thread.
void compute_row_with_thread(){
    int n = a->n;
    int m = b->m;
    pthread_t threads[n];
    for(int i = 0; i < n; i++){
        if(pthread_create(&threads[i], NULL, compute_row, (void *) i)){
            perror("Cannot create thread!");
            exit(-1);
        }
    }
    for(int i = 0; i < n; i++){
        pthread_join(threads[i], NULL);
    }
}