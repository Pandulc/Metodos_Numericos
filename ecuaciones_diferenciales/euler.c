#include <stdio.h>
#include <math.h>

double f(double x, double y) {
    return -2 * x * y;
}

double fder(double x, double y) {
    return -2 * y;
}


int main(int argc, char *argv[]) {

    double x0, xf, y0, x, y, e, h;
    int n;


    printf("Ingrese el valor inicial (x0) \n");
    scanf("%lf", &x0);
    printf("Ingrese el valor final (xf) \n");
    scanf("%lf", &xf);
    printf("Ingrese el dato inicial (y0) \n");
    scanf("%lf", &y0);
    printf("Ingrese la cantidad de subintervalos (n) \n");
    scanf("%d", &n);

    h = (xf - x0) / n;

    FILE *file;

    file = fopen("derivadas.txt", "w");

    if (file == NULL) {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }


    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            y = y0 + h * f(x0, y0);
            x = x0 + h;
            e = pow(h, 2) * fder(x0, y0) / 2;
        } else {
            e = pow(h, 2) * fder(x, y) / 2;
            y = y + h * f(x, y);
            x = x + h;
        }
        fprintf(file, "%lf\t%lf\t%lf\n", x, y, e);

    }

}
