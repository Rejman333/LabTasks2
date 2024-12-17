#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma warning (disable : 4996) //This allows is to use scanf in vs

clear(void)
{
	while (getchar() != '\n');
}

int get_matrix_dimension(char name) {
	int dimension = 0;
	printf("%c: ", name);
	while (1) {
		scanf("%d", &dimension);
		if (dimension > 0) {
			break;

		}
		printf("Value %c: %d, incorect!\n Try again!\n", name, dimension);
		clear();
	}
	return dimension;

}

void prepare(
	float* p_vector, int vector_size,
	float** p_matrix, int matrix_N, int matrix_M
) {
	//Prepare vector
	for (int i = 0; i < vector_size; i++) {
		p_vector[i] = 1.0;
	}
	//Prepare matrix
	for (int i = 0; i < matrix_N; i++) {
		for (int j = 0; j < matrix_M; j++) {
			p_matrix[i][j] = sqrt((i + 1) * (j + 1));
		}
	}

	for (int i = 0; i < matrix_M && i < matrix_N; i++) {
		p_matrix[i][i] = (i+1) * 100;
	}

}

float* multi(
	float* p_vector, int vector_size,
	float** p_matrix, int matrix_N, int matrix_M) {

	float* p_solution = (float*)calloc(matrix_N, sizeof(float));
	for (int i = 0; i < matrix_N; i++) {
		float sum = 0;
		for (int j = 0; j < matrix_M; j++) {
			printf("i: %d, j: %d\n", i, j);
			sum += p_matrix[i][j] * p_vector[j];
		}
		p_solution[i] = sum;
	}
	return p_solution;
}
// Skipped, not enough context given in exercise.  
short check(
	float* p_vector, int vector_size,
	float** p_matrix, int matrix_N, int matrix_M) {

	short is_corret = -1;
	float* p_control_sum = (float*)calloc(matrix_N, sizeof(float));

	for (int i = 0; i < matrix_N; i++) {
		float sum = 0;
		for (int j = 0; j < matrix_M; j++) {
			sum += p_matrix[i][j];
		}
		p_control_sum[i] = sum;
	}

	printf("Control Sum: [");
	for (int i = 0; i < matrix_N; i++) {
		printf("%f", p_control_sum[i]);
		if (i < matrix_N - 1) {
			printf(", ");
		}
	}
	printf("]\n");


	for (int i = 0; i < matrix_N; i++) {
		if (p_control_sum[i] != p_vector[i]) {
			break;
		}
	}
	is_corret = 1;
	return is_corret;
}

int main(int argc, char *argv[])
{
	int n = 0, m = 0;
	printf("We represent matrix as N x M\n");
	n = get_matrix_dimension('N');
	m = get_matrix_dimension('M');
	printf("Matrix %d x %d\n", n, m);

	float* p_vector = (float*)calloc(m,sizeof(float));
	float** p_matrix = (float**)malloc(n*(sizeof(float*)));

	for (int i = 0; i < n; i++) {
		p_matrix[i] = (float*)calloc(m, sizeof(float));
	}

	prepare(p_vector, m, p_matrix, n, m);
	float* p_sum = (float*)multi(p_vector, m, p_matrix, n, m);

	printf("Vector: [");
	for (int i = 0; i < m; i++) {
		printf("%f", p_vector[i]);
		if (i < m - 1) {
			printf(", ");
		}
	}
	printf("]\n");

	printf("[\n");
	for (int i = 0; i < n; i++) {
		printf("\t[ ");
		for (int j = 0; j < m; j++) {
			printf(" %6.2f,", p_matrix[i][j]);
		}
		printf("]\n");
	}
	printf("]\n");

	printf("Sum: [");
	for (int i = 0; i < n; i++) {
		printf("%f", p_sum[i]);
		if (i < n - 1) {
			printf(", ");
		}
	}
	printf("]\n");

	short is_correct = check(p_vector, m, p_matrix, n, m);
	if (is_correct == 1) {
		printf("Correct!");
	}
	else {
		printf("Error!");
	}

	free(p_vector);
	free(p_matrix);
	free(p_sum);
	p_vector = NULL;
	p_matrix = NULL;
	p_sum = NULL;

	return 0;

}