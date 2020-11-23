#include "header.h"

// Allocates a matrix of size n and m and returns a pointer to the allocated struct.
Matrix* new_matrix(int n, int m){
    Matrix* mat = malloc(sizeof(Matrix));
    mat->n = n;
    mat->m = m;
    mat->data = (int**) malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++){
        mat->data[i] = malloc(m * sizeof(int));
    }
    return mat;
}

// Reads and allocates a matrix from a file.
Matrix* readMatrixFromFile(char* fileName){
    FILE* file = fopen(fileName, "r");
    if(file == NULL){
        printf("Couldn't not open file %s\n", fileName);
        exit(-1);
    }
    int n, m;
    if(fscanf(file,"row=%d col=%d", &n, &m) != 2){
        printf("Couldn't read matrix size of file %s\n", fileName);
        exit(-1);
    }
    Matrix* mat = new_matrix(n, m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(fscanf(file,"%d", &mat->data[i][j]) != 1){
                printf("Couldn't read matrix at [%d, %d] of file %s\n", i, j, fileName);
                exit(-1);
            }
        }
    }
    return mat;
}

// Writes a matrix to file.
void writeMatrixToFile(char* fileName, Matrix* mat){
    FILE* file = fopen(fileName, "w");
    if(file == NULL){
        printf("Couldn't not open file %s\n", fileName);
        exit(-1);
    }
    int n = mat->n;
    int m = mat->m;
    fprintf(file, "row=%d col=%d\n", n, m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            fprintf(file, "%d ", mat->data[i][j]);
        }
        fprintf(file, "\n");
    }
}