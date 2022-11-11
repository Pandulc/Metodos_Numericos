#include <stdio.h>
#include <math.h>

double f(double x, double y) {
    return (4*x*y)/(1+ pow(x,2));
}

int main(int argc, char *argv[]) {

    int n;

    printf("Ingrese la cantidad de subintervalos (n) \n");
    scanf("%d", &n);

    double xf, x[n + 1], y[n + 1], h;

    printf("Ingrese el valor inicial (x0) \n");
    scanf("%lf", &x[0]);
    printf("Ingrese el valor final (xf) \n");
    scanf("%lf", &xf);
    printf("Ingrese el dato inicial (y0) \n");
    scanf("%lf", &y[0]);

    h = (xf - x[0]) / n;

    FILE *file;

    file = fopen("resultadosEuler.txt", "w");

    if (file == NULL) {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    //Metodo Parcial

    for (int i = 0; i < n; ++i) {

        if (i == 0) {
            y[i + 1] = y[i] + h * f(x[i], y[i]);
            x[i + 1] = x[i] + h;
        } else {
            y[i + 1] = y[i] + h * (2 * f(x[i], y[i]) - f(x[i - 1], y[i - 1]));
            x[i + 1] = x[i] + h;
        }

        fprintf(file, "%lf\t%.12lf\n", x[i], y[i]);

    }

    /*for (int i = 0; i < n; ++i) {

        y[i + 1] = y[i] + h * f(x[i], y[i]);
        x[i + 1] = x[i] + h;

        fprintf(file, "%lf\t%E\n", x[i], y[i]);

    }*/

    fprintf(file, "%lf\t%.12lf\n", x[n], y[n]);

}
