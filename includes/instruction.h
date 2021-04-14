//function prototypes
void parse_mac_ops(gsl_matrix* data, gsl_matrix* weight, int* array);
int gen_mac_instructions(int* operand_array, int* instructions,int count);
int  calc_mac_operations(gsl_matrix* data, gsl_matrix* weight);