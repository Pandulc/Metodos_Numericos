#include <stdio.h>
#include <math.h>

#define MAXCOL 10
#define MAXROW 10

void readTxt (double [MAXROW][MAXCOL], double [MAXROW], int *, int *);
void printMatrix (double [MAXROW][MAXCOL], double [MAXROW], int, int);
void triangulation (double [MAXROW][MAXCOL], double [MAXROW], int, int);
void retrosustitucion (double [MAXROW][MAXCOL], double [MAXROW], double [MAXROW], int, int);
void pivot (double [MAXROW][MAXCOL], int, int, int);

int main(int argc, char *argv[]){
    double matrix[MAXROW][MAXCOL];
    double b[MAXROW];
    double x[MAXROW];
    int rows = 0;
    int columns = 0;
    readTxt(matrix, b, &rows, &columns);
    printMatrix(matrix, b, rows, columns);
    triangulation(matrix, b, rows, columns);
    retrosustitucion(matrix, b, x, rows, columns);
}

void readTxt(double m[MAXROW][MAXCOL], double b[MAXROW], int * rows, int * columns){
    FILE *readPtr;
    int j,i,n;
    float k;
    readPtr = fopen("data.txt", "r");
    fscanf(readPtr,"%d",&n);
    *rows = n;
    *columns = n;
    for (i=0; i<*rows; i++){
        for (j=0; j<*columns; j++){
            fscanf(readPtr,"%f",&k);
            m[i][j] = k;
        }
        fscanf(readPtr,"%f",&k);
        b[i] = k;
    }
    fclose(readPtr);
}

void printMatrix (double m[MAXROW][MAXCOL], double b[MAXROW], int rows, int columns){
    double diagonal = 1;
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<columns;j++)
        {
            printf("%lf ",m[i][j]);
        }
        printf("%lf",b[i]);
        diagonal = diagonal * m[i][i];
        printf("\n");
    }
    printf("Diagonal: %lf\n", diagonal);
}

void triangulation (double m[MAXROW][MAXCOL], double b[MAXROW], int rows, int columns){
    for (int i = 0; i < rows-1; ++i) {
        pivot(m, rows, columns, i);
        for (int j = i+1; j < rows; ++j) {
            double factor = -m[j][i]/m[i][i];
            for (int k = 0; k < columns; ++k) {
                m[j][k] = m[i][k] * factor + m[j][k];
            }
            b[j] = b[i] * factor + b[j];
        }
    }
    printMatrix(m, b, rows, columns);
}

void pivot (double m[MAXROW][MAXCOL], int rows, int columns, int i){
    double tolerance = pow(10, -3);
    if(fabs(m[i][i])<tolerance){
        for (int j = i+1; j < rows; ++j) {
            if(fabs(m[j][i])>fabs(m[i][i])){
                for (int k = j; k < columns; ++k) {
                    double swap = m[i][k];
                    m[i][k] = m[j][k];
                    m[j][k] = swap;
                }
            }
        }
    }
}

void retrosustitucion (double m[MAXROW][MAXCOL], double b[MAXROW], double x[MAXROW], int rows, int columns){
    double value = 0;
    value = b[rows-1]/m[rows-1][columns-1];
    x[rows-1] = value;
    for (int i = rows-2; i >= 0; --i) {
        double sum = 0;
        for (int j = i+1; j < columns; ++j) {
            sum = sum + m[i][j] * x[j];
        }
        value = (b[i] - sum) / m[i][i];
        x[i] = value;
    }
    printf("Conjunto solucion: \n");
    for (int i = 0; i < rows; ++i) {
        printf("x%d = %lf\n",i,x[i]);
    }
}

