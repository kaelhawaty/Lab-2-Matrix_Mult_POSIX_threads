#include "header.h"
#include <sys/time.h>

// Defualt file names.
char* file_input_A = "a.txt";
char* file_input_B = "b.txt";
char* file_output = "c.out";

// Input matrices.
Matrix* a;
Matrix* b;
// Output matrix.
Matrix* out;

// Computation method: 0 each row, 1 each element with a separate thread.
int computation_method = 0;

bool isNumeric(const char *str)
{
    while(*str != '\0')
    {
        if(*str < '0' || *str > '9')
            return false;
        str++;
    }
    return true;
}

// Parses file names for Matrix A, Matrix B and Matrix out. Additionaly, reads computation method whether it is
// by each element or by each row (Default each row).
void parse(int num_args, char** args){
   if(num_args != 4 && num_args != 1 && num_args != 5){
       printf("Please follow format: ./matMultp Mat1 Mat2 MatOut\n");
       exit(-1);
   }
   // Check if computation method is supplied as an argument.
   if(num_args == 5 && isNumeric(args[4])){
       int num = atoi(args[4]);
       if(num != 0 && num != 1){
           printf("Method of computation must be either zero or one (row_wise (default), element_wise) respectively\n");
           exit(-1);
       }
       computation_method = num;
   }
   // Read file names.
   if(num_args >= 4){
       file_input_A = malloc(100 * sizeof(char));
       strcpy(file_input_A, args[1]);
       strcat(file_input_A, ".txt");

       file_input_B = malloc(100 * sizeof(char));
       strcpy(file_input_B, args[2]);
       strcat(file_input_B, ".txt");

       file_output = malloc(100 * sizeof(char));
       strcpy(file_output, args[3]);
       strcat(file_output, ".out");
   }
}


// Calls methods in correct ordering from parsing arguments - in format of
// ./multp a b c {0 or 1} where 0 or 1 is the execution method and it is optional -
// to reading matrices from files and calling the correct computation method then outputting it to
// file with time spent and num_thread used.
int main(int num_args, char** args)
{
    parse(num_args, args);
    a = readMatrixFromFile(file_input_A);
    b = readMatrixFromFile(file_input_B);
    if(a->m != b->n){
        printf("# of cols of Matrix A doesn't equal # of rows of Matrix B\n");
        exit(-1);
    }
    out = new_matrix(a->n, b->m);
    struct timeval stop, start;
    gettimeofday(&start, NULL); //start checking time
    int num_threads;
    if(computation_method == 0){
        compute_row_with_thread();
        num_threads = out->n;
    }else{
        compute_element_with_thread();
        num_threads = out->n * out->m;
    }
    writeMatrixToFile(file_output, out);
    gettimeofday(&stop, NULL); //end checking time
    printf("Threads used: %d\n", num_threads);
    printf("Microseconds taken: %lu\n", stop.tv_usec - start.tv_usec);


    return 0;
}