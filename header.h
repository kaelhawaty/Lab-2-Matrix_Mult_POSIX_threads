#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Matrix{
    int n, m;
    int** data;
};
typedef struct Matrix Matrix;

extern char* file_input_A;
extern char* file_input_B;
extern char* file_output;
extern Matrix* a; 
extern Matrix* b;
extern Matrix* out;
extern int computation_method;

Matrix* new_matrix(int n, int m);
Matrix* readMatrixFromFile(char* fileName);
void writeMatrixToFile(char* fileName, Matrix* mat);
void compute_element_with_thread();
void compute_row_with_thread();

