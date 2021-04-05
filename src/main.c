/*
*Author: Xavier Brooks
*Email: <xmb5563@rit.edu>
*Created: 4/3/21
*
*
*  First version of the CNN compiler that generate a basic matrix multiplication operation,
* predicts the number of mac operations, pairs the operands together in memory, and prints
* the operands in a neat table
*/

#include <stdio.h>
#include <gsl/gsl_linalg.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include "/includes/matrix.h"

//function prototypes
void print_mac_sequence(int* subarray, int mac_count);
void gen_mac_ins(gsl_matrix* data, gsl_matrix* weight, int* array);
int  calc_mac_operations(gsl_matrix* data, gsl_matrix* weight);

int main(int argc, char* argv[]){

	int cnt = 0;
	int* t_array;
	int x = 0;

	//creates the matrices
	gsl_matrix* matrix_t1;
	gsl_matrix* matrix_t2;
	matrix_t1 = gsl_matrix_calloc(3,5);
	matrix_t2 = gsl_matrix_calloc(5,4);

	//populate both matrices
	for(int i = 0; i < matrix_t1->size1; i++){
		for(int j = 0; j < matrix_t1->size2;j++){
			gsl_matrix_set(matrix_t1, i, j, x);
			x++;
		}
	}

	x = 0;
	for(int k = 0; k < matrix_t2->size1; k++){
		for(int l = 0; l < matrix_t2->size2; l++){
			gsl_matrix_set(matrix_t2, k, l, x);
			x++;
		}
	}


	/*DEBUG CODE to ensure both matrices are populated*/
	//DEBUG START ------------------------------------------------------------
	for(int a = 0; a < matrix_t1->size1; a++){
		for(int b = 0; b < matrix_t1->size2; b++){
			int c = gsl_matrix_get(matrix_t1, a, b);
			printf("%d ", c);
		}
		printf("\r\n");
	}

	printf("\r\n");
	for(int d = 0; d < matrix_t2->size1; d++){
		for(int e = 0; e < matrix_t2->size2; e++){
			int f = gsl_matrix_get(matrix_t2, d, e);
			printf("%d ", f);
		}
		printf("\r\n");
	}
	printf("\r\n");

	//DEBUG END----------------------------------------------------------------

	//calculate mac operations
	cnt = calc_mac_operations(matrix_t1, matrix_t2);
	printf("necessary number of MAC operationss is: %d\r\n\r\n", cnt);
	t_array = (int *)malloc(2*cnt*sizeof(int));

	//generates the operand pairs for mac operations
	gen_mac_ins(matrix_t1, matrix_t2, t_array);

	//print the operand pairs in table format
	print_mac_sequence(t_array, cnt);
	gsl_matrix_free(matrix_t1);
	gsl_matrix_free(matrix_t2);
	free(t_array);
	return 0;
}


/*
*This function neatly prints the MAC instruction operands required to multiply two matrices in a table format
*
*NOTES
* prints 8 instruction operands per line
* pads the final row if it can't be filled with operands
*
*PARAMETERS
* subarray: points to the integer operande of each mac operation in memory
* mac_count: total number of mac operations needed to multiply matrices - used to format operand table
*/
void print_mac_sequence(int* subarray, int mac_count){
	int padding = mac_count % 8;
	int num_lines = mac_count/8;
	int i = 0;

	//one line to be printed since less than eight instructions
	if(mac_count < 8){
		printf("line 1: ");

		while(i<(2*mac_count)){
			printf("[%d,%d], ", *(subarray + i), *(subarray + i + 1));
			i+=2;
		}

		//if the line isn't completely filled with instructions padd with 0's
		for(int i = 0; i < padding; i++){
			printf("[0,0] ");
		}
		printf("\r\n");
		return;
	}

	else{
		//for every line...
		for(int i = 0; i < num_lines; i++){

			//the temp pointer points to eight pairs of mac operands ata time
			int* temp = (subarray + (16*i));

			//print the line number...
			printf("line %d: ", (i + 1));

			//if the final line is hit and there are operand
			//locations to pad
			if((i == (num_lines-1)) && (padding != 0)){

				int k = 0;
				while(k < (16 - (2*padding))){
					printf("[%d,%d]", *(temp + k), *(temp + k + 1));
					k += 2;
				}

				printf("\r\n");
				return;
			}

			//j is used to index the operands of each instruction
			int j = 0;
			while(j < 16){
				printf("[%d,%d]", *(temp + j), *(temp + j + 1));
				j+=2;
			}
			printf("\r\n");
		}
		return;
	}
}

/*
*This function iterates through both matrices and extracts the MAC instruction parameters
*
*PARAMTERS
* data: The first multiplication matrix
* weight: The second multiplication matrix
* array: memory pointer where operands for the instructions are stored
*/
void gen_mac_ins(gsl_matrix* data, gsl_matrix* weight, int* array){

	int array_access = 0;

	//iterates through each element in each row of data matrix to be multiplied
	for(int i = 0; i < data->size1; i++){
		//iterates through each colum in the weight matrix
		for(int j = 0; j < weight->size2; j++){
			//selects the elemnt in the weight matrix to be multiplied
			for(int k = 0; k < weight->size1; k++){
				//these lines populates the array of operands
				*(array + array_access) = gsl_matrix_get(data, i, k);
				*(array + array_access + 1) = gsl_matrix_get(weight, k, j);
				array_access += 2;
			}
		}
	}
	return;
}

/*
*Simple function that calculates the necessary number of mac operations to successfully
* multiply two matrices
*
*NOTES
* when multiplying a [m x n] matrix with a [n x p] matrix
* num of mac instructions = m*n*p
*
*PARAMETERS
* data: first matrix
* weight:second matrix
* count: final number of mac operations needed
*/
int calc_mac_operations(gsl_matrix* data, gsl_matrix* weight){
	int count = (data->size1) * (data->size2) * (weight->size2);
	return count;
}
