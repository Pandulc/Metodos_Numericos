#include <stdio.h>
#include <math.h>

double f(double x, double y) {
    return exp(-2*x)-2*y;
}

int main(int argc, char *argv[]) {

    int n;

    printf("Ingrese la cantidad de subintervalos (n) \n");
    scanf("%d", &n);

    double xf, x[n + 1], y[n + 1], y2[n + 1], y3[n + 1], Q[n + 1], yp, xp, h;

    printf("Ingrese el valor inicial (x0) \n");
    scanf("%lf", &x[0]);
    printf("Ingrese el valor final (xf) \n");
    scanf("%lf", &xf);
    printf("Ingrese el dato inicial (y0) \n");
    scanf("%lf", &y[0]);

    y2[0] = y3[0] = y[0];

    h = (xf - x[0]) / n;

    FILE *file;

    file = fopen("resultadosEuler.txt", "w");

    if (file == NULL) {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }


    for (int i = 0; i < n; ++i) {

        y[i + 1] = y[i] + h * f(x[i], y[i]);
        x[i + 1] = x[i] + h;

        fprintf(file, "%lf\t%E\n", x[i], y[i]);

    }

    fprintf(file, "%lf\t%E\n", x[n], y[n]);

}
