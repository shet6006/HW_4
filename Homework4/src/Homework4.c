/*
 ============================================================================
 Name        : HW4.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

 /* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

    char command;
    printf("[----- [�赿��] [2020039023] -----]\n");

    int row, col;
    srand(time(NULL)); //�ð��� ���� ���� �߻�

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col); //��� a �߻�
    int** matrix_b = create_matrix(row, col); //��� b �߻�
    int** matrix_a_t = create_matrix(col, row); //��� a�� transpose �߻�

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) { return -1; }

    do {
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {
        case 'z': case 'Z':
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col); //��� ���� ������ŭ ������ �Ǿ��ִ� ����� �����͸� ������ ����� ä����
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
            case 'm': case 'M':
                printf("Multiply matrix_a with transposed matrix_a \n");
                transpose_matrix(matrix_a, matrix_a_t, col, row);
                multiply_matrix(matrix_a, matrix_a_t, row, col);
                break;
            case 'q': case 'Q':
                printf("Free all matrices..\n");
                free_matrix(matrix_a_t, col, row);
                free_matrix(matrix_a, row, col);
                free_matrix(matrix_b, row, col); //��, ���� ���� �޸𸮴� �Լ��� ���� �� �������־���
                break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        } //���� ����� �ִ� �޴�

    } while (command != 'q' && command != 'Q'); //q�� ���� �����ϱ� ������ �ݺ�

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    /* Check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col!\n");
        return 0;
    }



    int** matrix = (int**)malloc(sizeof(int*) * row); //����� ��� ���� �Է� ���� ���� �����޸� �Ҵ�
    for (int i = 0; i < row; i++)
        matrix[i] = (int*)malloc(sizeof(int) * col);
    /* Check post conditions */
    if (matrix == NULL) {
        printf("Memory Allocation Failed.\n");
        return 0;
    }
    return matrix;
}


/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    /* Check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col!\n");
        return;
    }

    for (int i = 0; i < row; i++) { //���������� 3ĭ �����Ͽ� ����� ������ �簢�� ���·� ǥ��
        for (int j = 0; j < col; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    /* Check post conditions */
    if (matrix == NULL) {
        printf("Memory Allocation Failed.\n");
        return;
    }
    return;
}

/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{   /* Check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col!\n");
        return -1;
    }

    for (int i = 0; i < row; i++) //�޸� �Ҵ��� ����
        free(matrix[i]);
    free(matrix);

    /* Check post conditions */
    if (matrix == NULL) {
        printf("Memory Allocation Failed.\n");
        return -1;
    }
    return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    /* Check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col!\n");
        return -1;
    }

    int random; //������� ��Ŀ� ������ ������ �Ҵ�����
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            random = rand() % 20;
            matrix[i][j] = random;
        }
    }

    /* Check post conditions */
    if (matrix== NULL) {
        printf("Memory Allocation Failed.\n");
        return -1;
    }
    return 1;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    /* Check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col!\n");
        return -1;
    }

    int** addition_matrix = create_matrix(row, col); //���� ���� �������� ����� ����
    for (int i = 0; i < row; i++) { //��� a�� ��� b�� ���� ���� ������ addition_matrix ��Ŀ� ����
        for (int j = 0; j < col; j++) {
            addition_matrix[i][j] = matrix_a[i][j] + matrix_b[i][j];
        }
    }
    /* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL) {
        printf("Memory Allocation Failed.\n");
        return -1;
    }

    print_matrix(addition_matrix, row, col);
    free_matrix(addition_matrix, row, col);
    return 1;
}
/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    /* Check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col!\n");
        return -1;
    }

    int** subtraction_matrix = create_matrix(row, col); //���� ���� �������� ����� ����
    for (int i = 0; i < row; i++) { //��� a�� ��� b�� ���� �� ������ subtraction_matrix ��Ŀ� ����
        for (int j = 0; j < col; j++) {
            subtraction_matrix[i][j] = matrix_a[i][j] - matrix_b[i][j];
        }
    }

    /* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL) {
        printf("Memory Allocation Failed.\n");
        return -1;
    }
    print_matrix(subtraction_matrix, row, col);
    free_matrix(subtraction_matrix, row, col);
    return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    /* Check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col!\n");
        return -1;
    }

    for (int i = 0; i < row; i++) { //����� ������ ��� ���� �ٲ㼭 matrix_t ��Ŀ� ����
        for (int j = 0; j < col; j++) {
            matrix_t[i][j] = matrix[j][i];
        }
    }
    /* Check post conditions */
    if (matrix == NULL || matrix_t == NULL) {
        printf("Memory Allocation Failed.\n");
        return -1;
    }

    return 1;
}


/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    /* Check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col!\n");
        return -1;
    }

    int** multiply_matrix = create_matrix(row, row); //���� ���� �������� ����� ����, ��ġ��İ� ������� ���� row*row������ ���簢�� ����̹Ƿ� row���� ���ڷ� �޾ƿ�
    for (int i = 0; i < row; i++) { //��� a�� ���� ��� b�� ������ ��� �����Ͽ� ���� ������ multiply_matrix ��Ŀ� ����
        for (int j = 0; j < row; j++) {
            int temp = 0;
            for (int k = 0; k < col; k++)
                temp += matrix_a[i][k] * matrix_t[k][j];
            multiply_matrix[i][j] = temp;
        }
    }

    /* Check post conditions */
    if (matrix_t == NULL || matrix_t == NULL) {
        printf("Memory Allocation Failed.\n");
        return -1;
    }
    print_matrix(multiply_matrix, row, row);
    free_matrix(multiply_matrix, row, row);
    return 1;
}

