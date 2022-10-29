#include <stdio.h>
#include <math.h>


int menu();

void heun();

void middlePoint();

double f(double x, double y) {
    return -2 * x * y;
}

double fder(double x, double y) {
    return -2 * y;
}

int main(int argc, char *argv[]) {
    int option;

    do {
        option = menu();
        switch (option) {
            case 0:
                break;
            case 1:
                heun();
                break;
            case 2:
                middlePoint();
                break;
            case 3:

                break;
            case 4:

                break;
            default:
                printf("La opcion ingresada no es valida. Porfavor ingrese una opcion valida\n");
                break;
        }
    } while (option != 0);

    return 0;

}

int menu() {
    int op = 0;
    printf("\n---------------------------------------------------------\n---------------------------------------------------------\n");
    printf("Seleccione el metodo a utilizar: \n1- Heun \n2- Punto Medio \n0- Finalizar programa\n");
    printf("---------------------------------------------------------\n---------------------------------------------------------\n");
    scanf("%d", &op);
    return op;
}

void heun() {
    double xf, y0, xn, xv, y, e, yt, h;
    int n;


    printf("Ingrese el valor inicial (x0) \n");
    scanf("%lf", &xv);
    printf("Ingrese el valor final (xf) \n");
    scanf("%lf", &xf);
    printf("Ingrese el dato inicial (y0) \n");
    scanf("%lf", &y0);
    printf("Ingrese la cantidad de subintervalos (n) \n");
    scanf("%d", &n);

    h = (xf - xv) / n;

    FILE *file;

    file = fopen("derivadas.txt", "w");

    if (file == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }


    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            yt = y0 + h * f(xv, y0);
            xn = xv + h;
            e = pow(h, 2) * fder(xv, y0) / 2;
            y = y0 + h * (f(xv, y0) + f(xn, yt)) / 2;
            xv = xn;

        } else {
            yt = y + h * f(xv, y);
            e = pow(h, 2) * fder(xv, y) / 2;
            xn = xv + h;
            y = y + h * (f(xv, y) + f(xn, yt)) / 2;
            xv = xn;
        }
        fprintf(file, "%lf\t%lf\t%lf\n", xn, y, e);
    }

}

void middlePoint() {
    double xf, y0, xm, xv, y, e, ym, h;
    int n;


    printf("Ingrese el valor inicial (x0) \n");
    scanf("%lf", &xv);
    printf("Ingrese el valor final (xf) \n");
    scanf("%lf", &xf);
    printf("Ingrese el dato inicial (y0) \n");
    scanf("%lf", &y0);
    printf("Ingrese la cantidad de subintervalos (n) \n");
    scanf("%d", &n);

    h = (xf - xv) / n;

    FILE *file;

    file = fopen("derivadas.txt", "w");

    if (file == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }


    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            ym = y0 + f(xv, y0) * h / 2;
            xm = xv + h / 2;
            e = pow(h, 2) * fder(xv, y0) / 2;
            y = y0 + h * f(xm, ym);
            xv = xv + h;

        } else {
            ym = y + f(xv, y) * h / 2;
            xm = xv + h / 2;
            e = pow(h, 2) * fder(xv, y) / 2;
            y = y + h * f(xm, ym);
            xv = xv + h;
        }
        fprintf(file, "%lf\t%lf\t%lf\n", xv, y, e);
    }

}

