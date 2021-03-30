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
    printf("[----- [김동원] [2020039023] -----]\n");

    int row, col;
    srand(time(NULL)); //시간에 의한 난수 발생

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col); //행렬 a 발생
    int** matrix_b = create_matrix(row, col); //행렬 b 발생
    int** matrix_a_t = create_matrix(col, row); //행렬 a의 transpose 발생

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
            fill_data(matrix_a, row, col); //행과 열의 개수만큼 생성만 되어있던 행렬의 데이터를 임의의 값들로 채워줌
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
                free_matrix(matrix_b, row, col); //덧, 뺄셈 등의 메모리는 함수가 끝날 때 해제해주었음
                break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        } //여러 기능이 있는 메뉴

    } while (command != 'q' && command != 'Q'); //q를 눌러 종료하기 전까지 반복

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



    int** matrix = (int**)malloc(sizeof(int*) * row); //행렬의 행과 열을 입력 값에 따라 동적메모리 할당
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

    for (int i = 0; i < row; i++) { //오른쪽으로 3칸 정렬하여 행렬의 값들을 사각형 형태로 표현
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

    for (int i = 0; i < row; i++) //메모리 할당을 해제
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

    int random; //만들어진 행렬에 임의의 난수를 할당해줌
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

    int** addition_matrix = create_matrix(row, col); //덧셈 값을 저장해줄 행렬을 생성
    for (int i = 0; i < row; i++) { //행렬 a와 행렬 b의 값을 더한 값들을 addition_matrix 행렬에 저장
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

    int** subtraction_matrix = create_matrix(row, col); //뺄셈 값을 저장해줄 행렬을 생성
    for (int i = 0; i < row; i++) { //행렬 a와 행렬 b의 값을 뺀 값들을 subtraction_matrix 행렬에 저장
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

    for (int i = 0; i < row; i++) { //행렬의 값들을 행과 열을 바꿔서 matrix_t 행렬에 저장
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

    int** multiply_matrix = create_matrix(row, row); //곱셈 값을 저장해줄 행렬을 생성, 전치행렬과 원행렬의 곱은 row*row형태의 정사각형 모양이므로 row값을 인자로 받아옴
    for (int i = 0; i < row; i++) { //행렬 a의 값과 행렬 b의 값들을 행렬 곱연하여 나온 값들을 multiply_matrix 행렬에 저장
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

