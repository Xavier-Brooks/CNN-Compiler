#include <stdio.h>
#include <gsl/gsl_linalg.h>
#include <String.h>
#include <getopt.h>
#include <stdlib.h>
#include "/includes/matrix.h"

//file io defines
#define BUFF_SIZE

//function prototypes
void initMatrix(File *file);
int writeMatrix(FILE *file, gsl_matrix *data, gsl_matrix *weight);

struct matrices{
	gsl_matrix* d_matrix;
	gsl_matrix* w_matrix;
}

struct matrices m;

void init_matrix(FILE *file){
	char *buffer;
	char *token;
	int found_size_line = 0;
	int  nr = 0, nc = 0, nr2 = 0, nc2 = 0;
	int num_elem = 0;
	gsl_matrix* data_matrix, weight_matrix;

	buffer = (char *)malloc(BUFF_SIZE*sizeof(char));

	//iterates through file lines until first non-commented line is found
	while(fgets(buffer, BUFF_SIZE, file)){
		if(buffer[0] == '#'){
			continue;
		}
		else{
			found_size_line = 1;
			break;
		}
	}//end while


	//if the entirety of the input data file was commented then exit program
	if(!found_size_line){
		printf("all lines were commented\r\n");
		free(buffer);
		fclose(file);
		exit(1);
	}

	token = strok(buffer, " \r\t\n"); //gets the first number in the line holding the matrix sizes

	//this while loop extracts the size of both matrices
	while(token != NULL){
		if(!num_elem){
			nr = atoi(token);
		}
		else if(num_elem == 1){
			nc = atoi(token);
		}
		else if(num_elem == 2){
			nr2 = atoi(token);
		}
		else if(num_elem == 3){
			nc3 == atoi(token);
		}
		token = strok(NULL, "\r\t\n");
		num_elem++;
	}

	//checks if the size line has appropriate matrix rows number values
	if((nr < 1) || (nr2 < 1)){
		printf("ERROR: insufficient number of rows for one of the matrices!\r\n");
		free(buffer);
		fclose(file)
		exit(1);
	}

	//checks if the size line has appropriate matrix coloumn number values
	if((nc < 1) || (nc2 < 1)){
		printf("ERROR: insufficient number of cols for one or mor eof the matrices!\r\n");
		free(buffer);
		fclose(file);
		exit(2);
	}


	//assures that the number of rows in the weight matrices is equal to number of columns in data matrices
	if(nr2 != nc){
		printf{"ERROR: # of rows in weight matrix must be equivalent to # of cols in data matrix!\r\n"};
		free(buffer);
		fclose(file);
		exit(3);
	}

	//create the weight and data matrices with the appropriate size and initialize them to 0
	data_matrix = gsl_matrix_calloc(nr, nc);
	weight_matrix = gsl_matrix_calloc(nr2, nc2);
	free(buffer);

	//passes the initialized matrices to the global structure variable for other functions to access
	m.d_matrix = data_matrix;
	m.w_matrix = weight_matrix;
}

/*writes data and weights to their appropriate matrices
*file - pointer to the text file with our data
*data - pointer to the matrix strucure for the data
*weight - pointer to the weight data matrices
*/
int writeMatrix(FILE *file, gsl_matrix* data, gsl_matrix* weight){
	

}
