#include <stdio.h>
#include <math.h>

#define MAXCOL 10
#define MAXROW 10

int menu();

void readTxt(double [MAXROW][MAXCOL], double [MAXROW], int *, int *);

void printMatrix(double [MAXROW][MAXCOL], double [MAXROW], int, int);

void jacobi(double[MAXROW][MAXCOL], double[MAXROW], int, int);

void gauss_seidel(double[MAXROW][MAXCOL], double[MAXROW], int, int);

void relajacion(double[MAXROW][MAXCOL], double[MAXROW], int, int);

int main(int argc, char *argv[]) {
    printf("Recuerde haber definido previamente el tamanio de la matriz\n");
    double matrix[MAXROW][MAXCOL];
    double b[MAXROW];
    int rows = 0;
    int columns = 0;
    readTxt(matrix, b, &rows, &columns);
    printMatrix(matrix, b, rows, columns);

    int option;
    do {
        option = menu();
        switch (option) {
            case 0:
                break;
            case 1:
                jacobi(matrix, b, rows, columns);
                break;
            case 2:
                gauss_seidel(matrix, b, rows, columns);
                break;
            case 3:
                relajacion(matrix, b, rows, columns);
                break;
            default:
                printf("La opcion ingresada no es valida. Ingrese una opcion valida porfavor");

        }
    } while (option != 0);
}

int menu() {
    int op = 0;
    printf("\n---------------------------------------------------------\n---------------------------------------------------------\n");
    printf("Seleccione el metodo a utilizar: \n1- Jacobi \n2- Gauss-Seidel \n3- Relajacion \n0- Finalizar programa\n");
    printf("---------------------------------------------------------\n---------------------------------------------------------\n");
    scanf("%d", &op);
    return op;
}

void readTxt(double m[MAXROW][MAXCOL], double b[MAXROW], int *rows, int *columns) {
    FILE *readPtr;
    int j, i, n;
    float k;
    readPtr = fopen("data.txt", "r");
    fscanf(readPtr, "%d", &n);
    *rows = n;
    *columns = n;
    for (i = 0; i < *rows; i++) {
        for (j = 0; j < *columns; j++) {
            fscanf(readPtr, "%f", &k);
            m[i][j] = k;
        }
        fscanf(readPtr, "%f", &k);
        b[i] = k;
    }
    fclose(readPtr);
}

void printMatrix(double m[MAXROW][MAXCOL], double b[MAXROW], int rows, int columns) {
    printf("---------------MATRIZ AMPLIADA---------------\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%lf ", m[i][j]);
        }
        printf("%lf", b[i]);
        printf("\n");
    }
    printf("---------------------------------------------\n");

}

void jacobi(double m[MAXROW][MAXCOL], double b[MAXROW], int rows, int columns) {

    double xv[MAXROW] = {0, 0, 0, 0, 0};
    double xn[MAXROW] = {0, 0, 0, 0, 0};
    double tolerance = pow(10, -3);
    double error;
    int iterations = 0;

    //Diagonalmente dominante
    for (int i = 0; i < rows; i++) {
        double sum = 0;
        for (int j = 0; j < columns; j++) {
            if (i != j) {
                sum = sum + fabs(m[i][j]);
            }
        }
        if (fabs(m[i][i]) <= sum) {
            printf("La matriz no es diagonalmente dominante\n");
        }
    }

    do {
        error = 0;
        iterations++;
        for (int i = 0; i < rows; ++i) {
            double sum = 0;
            for (int j = 0; j < columns; ++j) {
                if (i != j) {
                    sum = sum + m[i][j] * xv[j];
                }
            }
            xn[i] = (b[i] - sum) / m[i][i];
            error = error + pow((xn[i] - xv[i]), 2);
            xv[i] = xn[i];
        }

        error = sqrt(error);

        if (iterations == 9999) {
            printf("Numero maximo de iteraciones alcanzado\n");
        }

    } while (error > tolerance && iterations < 10000);

    printf("Conjunto solucion: \n");
    for (int i = 0; i < rows; ++i) {
        printf("x%d = %lf\n", i + 1, xn[i]);
    }
    printf("Error: %lf\nIteraciones: %d", error, iterations);
}

void gauss_seidel(double m[MAXROW][MAXCOL], double b[MAXROW], int rows, int columns) {
    double xv[MAXROW] = {0, 0, 0, 0, 0};
    double xn[MAXROW] = {0, 0, 0, 0, 0};
    double tolerance = pow(10, -3);
    double error = 0;
    int iterations = 0;

    //Diagonalmente dominante
    for (int i = 0; i < rows; i++) {
        double sum = 0;
        for (int j = 0; j < columns; j++) {
            if (i != j) {
                sum = sum + fabs(m[i][j]);
            }
        }
        if (fabs(m[i][i]) <= sum) {
            printf("La matriz no es diagonalmente dominante\n");
        }
    }

    do {
        error = 0;
        iterations++;
        for (int i = 0; i < rows; ++i) {
            double sum = 0;
            for (int j = 0; j < columns; ++j) {
                if (i != j) {
                    sum = sum + m[i][j] * xv[j];
                }
            }
            xn[i] = (b[i] - sum) / m[i][i];
            error = error + pow((xn[i] - xv[i]), 2);
            xv[i] = xn[i];
        }

        //Metodo largo y complicado//
        
        /*if(i==0){
            double sum = 0;
            
            for (int j = 0; j < columns; ++j) {
                if (j != i) {
                    sum = sum + m[i][j] * xv[j];
                }
            }
            xn[i] = (b[i] - sum) / m[i][i];
            error = error + pow((xn[i] - xv[i]), 2);
            xv[i] = xn[i];
        }
        else if(i==rows-1){
            double sum = 0;
            
            for (int j = 0; j < columns; ++j) {
                if (j != i) {
                    sum = sum + m[i][j] * xn[j];
                }
            }
            xn[i] = (b[i] - sum) / m[i][i];
            error = error + pow((xn[i] - xv[i]), 2);
            xv[i] = xn[i];
        }
        else{
            double sum = 0;
            for (int j = 0; j < i-1; ++j) {
                sum = sum + m[i][j]*xn[j];
            }
            for (int j = i+1; j < columns; ++j) {
                sum = sum + m[i][j]*xv[j];
            }
            xn[i] = (b[i] - sum) / m[i][i];
            error = error + pow((xn[i] - xv[i]), 2);
            xv[i] = xn[i];
        }
        
    }
    */
        error = sqrt(error);

        if (iterations == 9999) {
            printf("Numero maximo de iteraciones alcanzado\n");
        }

    } while (error > tolerance && iterations < 10000);

    printf("Conjunto solucion: \n");
    for (int i = 0; i < rows; ++i) {
        printf("x%d = %lf\n", i + 1, xn[i]);
    }
    printf("Error: %lf\nIteraciones: %d", error, iterations);
}

void relajacion(double m[MAXROW][MAXCOL], double b[MAXROW], int rows, int columns) {
    double xv[MAXROW] = {0, 0, 0, 0, 0};
    double xn[MAXROW] = {0, 0, 0, 0, 0};
    double tolerance = pow(10, -3);
    double error = 0;
    int iterations = 0;
    double cte = 0;

    printf("Ingrese el coeficiente de relajacion\n");
    scanf("%lf", &cte);

    //Diagonalmente dominante
    for (int i = 0; i < rows; i++) {
        double sum = 0;
        for (int j = 0; j < columns; j++) {
            if (i != j) {
                sum = sum + fabs(m[i][j]);
            }
        }
        if (fabs(m[i][i]) <= sum) {
            printf("La matriz no es diagonalmente dominante\n");
        }
    }

    do {
        error = 0;
        iterations++;
        for (int i = 0; i < rows; ++i) {
            double sum = 0;
            for (int j = 0; j < columns; ++j) {
                if (i != j) {
                    sum = sum + m[i][j] * xv[j];
                }
            }
            xn[i] = (b[i] - sum) / m[i][i];
            error = error + pow((xn[i] - xv[i]), 2);
            xn[i] = cte * xn[i] + (1-cte)*xv[i];
            xv[i] = xn[i];
        }

        error = sqrt(error);

        if (iterations == 9999) {
            printf("Numero maximo de iteraciones alcanzado\n");
        }

    } while (error > tolerance && iterations < 10000);

    printf("Conjunto solucion: \n");
    for (int i = 0; i < rows; ++i) {
        printf("x%d = %lf\n", i + 1, xn[i]);
    }
    printf("Error: %lf\nIteraciones: %d", error, iterations);
}