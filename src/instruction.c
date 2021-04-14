//standard includes
#include <stdio.h>
#include <gsl/gsl_linalg.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>

//custom includes
#include "../includes/instruction.h"

/*
*This function iterates through both matrices and extracts the MAC instruction parameters
*
*PARAMTERS
* data: The first multiplication matrix
* weight: The second multiplication matrix
* array: memory pointer where operands for the instructions are stored
*/
void parse_mac_ops(gsl_matrix* data, gsl_matrix* weight, int* array){

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
*generate the mac instructions and stores them in memory
*PARAMETERS
* operand_array: array holding the mac instruction operands, unused for now
* instructions: array to hold the actual mac instructions
* count: number of mac instructions to be performed
*/
int gen_mac_instructions(int* operand_array, int* instructions, int count){
	
	//space in memory for the instruction
	instructions = (int *)malloc((count * sizeof(int)) + 1);
	if (instructions == NULL){
			printf("error at calloc\r\n");
			return 1;
	}
		
	int c = 0;
	while(c < count){
		*(instructions + c) = 0;
		//checks if the last instruction is being generated...
		if(c == (count - 1)){//if so
			*(instructions + count) = 0 | (3 << 17) | (1 << 9) | c; //gives the final instruction the END opcode 
		}
		*(instructions + c) |= (2 << 17); //exe bits
		*(instructions + c) |= (2 << 9);  //sets the rd/wr bits of the instructions
		*(instructions + c) |= c;	    //row address UPDATE 
		c++;
	}
	
	return 0;
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