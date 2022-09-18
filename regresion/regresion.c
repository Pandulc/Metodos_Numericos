#include <stdio.h>
#include <math.h>

#define MAXCOL 2
#define MAXCOLM 10
#define MAXROW 10

void readTxtI(double[MAXROW][MAXCOL], int *);

void printMatrixI(double[MAXROW][MAXCOL], int);

void buildMatrix(double [MAXROW][MAXCOL], double [MAXROW][MAXCOLM], double [MAXROW], int, int);

void triangulation(double [MAXROW][MAXCOLM], double [MAXROW], int, int);

void retrosustitucion(double [MAXROW][MAXCOLM], double [MAXROW], double [MAXROW], int, int);

void pivot(double [MAXROW][MAXCOLM], double [MAXROW], int, int, int);


void printMatrix(double [MAXROW][MAXCOLM], double [MAXROW], int, int);

int main(int argc, char *argv[]) {
    int rows, p;
    double nodes[MAXROW][MAXCOL];
    double m[MAXROW][MAXCOLM];
    double b[MAXROW];
    double x[MAXROW];

    printf("Ingrese el grado del polinomio\n");
    scanf("%d", &p);
    readTxtI(nodes, &rows);
    printMatrixI(nodes, rows);
    buildMatrix(nodes, m, b, rows, p);
    printf("----------- MATRIZ AMPLIADA -----------\n");
    printMatrix(m, b, p, p);
    printf("---------------------------------------\n");
    printf("----------- MATRIZ REDUCIDA -----------\n");
    triangulation(m, b, p, p);
    printf("---------------------------------------\n");
    retrosustitucion(m, b, x, p, p);
}

void readTxtI(double m[MAXROW][MAXCOL], int *rows) {
    FILE *readPtr;
    int j, i, n;
    float k;
    readPtr = fopen("data.txt", "r");
    fscanf(readPtr, "%d", &n);
    *rows = n;

    for (i = 0; i < *rows; i++) {
        for (j = 0; j < MAXCOL; j++) {
            fscanf(readPtr, "%f", &k);
            m[i][j] = k;
        }
    }
    fclose(readPtr);
}

void printMatrixI(double m[MAXROW][MAXCOL], int rows) {
    printf("------ NODOS ------\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < MAXCOL; j++) {
            printf(" %lf ", m[i][j]);
        }
        printf("\n");
    }
    printf("-------------------\n");
}

void printMatrix(double m[MAXROW][MAXCOLM], double b[MAXROW], int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%lf ", m[i][j]);
        }
        printf("%lf", b[i]);
        printf("\n");
    }
}

void buildMatrix(double n[MAXROW][MAXCOL], double m[MAXROW][MAXCOLM], double b[MAXROW], int rows, int p) {

    for (int i = 0; i < p; ++i) {
        double sumxy = 0;
        for (int j = 0; j < rows; ++j) {
            sumxy = sumxy + pow(n[j][0], i) * n[j][1];
        }
        b[i] = sumxy;
        for (int j = 0; j < p; ++j) {
            double sumx = 0;
            for (int k = 0; k < rows; ++k) {
                sumx = sumx + pow(n[k][0], i + j);
            }
            m[i][j] = sumx;
        }
    }
}

void triangulation(double m[MAXROW][MAXCOLM], double b[MAXROW], int rows, int columns) {
    for (int i = 0; i < rows - 1; ++i) {
        pivot(m, b, rows, columns, i);
        for (int j = i + 1; j < rows; ++j) {
            double factor = -m[j][i] / m[i][i];
            for (int k = 0; k < columns; ++k) {
                m[j][k] = m[i][k] * factor + m[j][k];
            }
            b[j] = b[i] * factor + b[j];
        }
    }
    printMatrix(m, b, rows, columns);
}

void pivot(double m[MAXROW][MAXCOLM], double b[MAXROW], int rows, int columns, int i) {
    double tolerance = pow(10, -3);
    if (fabs(m[i][i]) < tolerance) {
        for (int j = i + 1; j < rows; ++j) {
            if (fabs(m[j][i]) > fabs(m[i][i])) {
                for (int k = i; k < columns; ++k) {
                    double swap = m[i][k];
                    m[i][k] = m[j][k];
                    m[j][k] = swap;
                }
                double swap = b[i];
                b[i] = b[j];
                b[j] = swap;
            }
        }
    }
}

void retrosustitucion(double m[MAXROW][MAXCOLM], double b[MAXROW], double x[MAXROW], int rows, int columns) {
    double value;
    value = b[rows - 1] / m[rows - 1][columns - 1];
    x[rows - 1] = value;
    for (int i = rows - 2; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < columns; ++j) {
            sum = sum + m[i][j] * x[j];
        }
        value = (b[i] - sum) / m[i][i];
        x[i] = value;
    }
    printf("Conjunto solucion: \n");
    for (int i = 0; i < rows; ++i) {
        printf("x%d = %lf\n", i, x[i]);
    }
}
