#include <stdio.h>
#include <math.h>

#define MAXROW 7
#define MAXCOL 2

void readTxt(double [MAXROW][MAXCOL],  int *);


int main(int argc, char *argv[]) {
    double nodes[MAXROW][MAXCOL];
    int rows;
    readTxt(nodes, &rows);
    double a, b, x;
    int n;
    double derivative = 0;

    FILE *file;

    file = fopen("derivadas.txt", "w");

    if (file == NULL) {
        printf("No se pudo abrir el archivo\n");
        return -1;
    }

    double h = (b - a) / n;

   for (int i = 0; i < 3; ++i) {

        derivative = (-2 * nodes[i+5][1] + 11 * nodes[i+4][1] - 24 * nodes[i+3][1] + 26 * nodes[i+2][1] - 14 * nodes[i+1][1] +
                      3 * nodes[i][1]) / (pow(h, 4));
        fprintf(file, "%lf\t%lf\n", nodes[i][0], derivative);
    }

    for (int i = 3; i < n - 2; ++i) {
        x = a + i * h;
        derivative =
                (nodes[i+3][1] + 12 * nodes[i+2][1] - 39 * nodes[i+1][1] + 56 * nodes[i][1] - 39 * nodes[i-1][1] + 12 * nodes[i-2][1] -
                        nodes[i-3][1]) / (6 * pow(h, 4));;
        fprintf(file, "%lf\t%lf\n", x, derivative);
    }

    for (int i = n - 2; i < n + 1; ++i) {
        x = a + i * h;
        derivative = (3 * nodes[i][1] - 14 * nodes[i-1][1] + 26 * nodes[i-2][1] - 24 * nodes[i-3][1] + 11 * nodes[i-4][1] -
                      2 * nodes[i-5][1]) / (pow(h, 4));;
        fprintf(file, "%lf\t%lf\n", x, derivative);
    }
}

void readTxt(double m[MAXROW][MAXCOL], int *rows) {
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