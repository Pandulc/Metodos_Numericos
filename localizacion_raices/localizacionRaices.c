#include <stdio.h>
#include <math.h>

// PROTOTIPADO DE FUNCIONES

int menu();
double funcion(double x);
double funcionAux(double x);
void biseccion();
void regula_falsi();
void puntoFijo();
void newton_raphson();
void secante();

// DEFINICION DE f(x)

double funcion(double x){
    return exp(-x) - x;
}

double funcionAux(double x){
    return -exp(-x) - 1;
}

int main(int argc, char *argv[]){
    int option;
    do{
        option = menu();
        switch (option){
            case 0:
                break;
            case 1:
                biseccion();
                break;
            case 2:
                regula_falsi();
                break;
            case 3:
                puntoFijo();
                break;
            case 4:
                newton_raphson();
                break;
            case 5:
                secante();
                break;
            default:
                printf("La opcion ingresada no es valida. Porfavor ingrese una opcion valida\n");
                break;
        }

    } while (option != 0);
}

int menu(){
    int op = 0;
    printf("\n---------------------------------------------------------\n---------------------------------------------------------\n");
    printf("Seleccione el metodo a utilizar: \n1- Biseccion \n2- Regula-falsi \n3- Iteracion de punto fijo \n4- Newton-Raphson \n5- Secante \n0- Finalizar programa\n");
    printf("---------------------------------------------------------\n---------------------------------------------------------\n");
    scanf("%d", &op);
    return op;
}

void biseccion(){
    double a, b, cn, cv, tolerancia, e;
    int iteracion = 0;
    printf("Recuerde haber definido previamente la funcion al inicio del codigo\nIngrese el limite inferior del intervalo\n");
    scanf("%lf", &a);
    printf("Ingrese el limite superior del intervalo\n");
    scanf("%lf", &b);
    printf("Ingrese la cantidad de cifras decimales de error\n");
    scanf("%lf", &tolerancia);
    tolerancia = pow(10, -tolerancia);
    if (funcion(a) * funcion(b) < 0){
        do{
            if (iteracion == 0){
                cn = (a + b) / 2;
                cv = a;
                e = fabs(cn - cv);
            }
            else{
                if (funcion(a) * funcion(cn) < 0){
                    b = cn;
                    cv = cn;
                    cn = (a + b) / 2;
                    e = fabs(cn - cv);
                }
                else if (funcion(b) * funcion(cn) < 0){
                    a = cn;
                    cv = cn;
                    cn = (a + b) / 2;
                    e = fabs(cn - cv);
                }
                else{
                    break;
                }
            }
            iteracion++;
        } while (e > tolerancia);
    }
    printf("\nResultados:\n");
    printf("El valor de la raiz es %lf con un error de %lf\n", cn, e);
    printf("La funcion en dicho punto vale %lf\n",funcion(cn));
    printf("El problema fue resuelto en %d iteraciones\n", iteracion);
}

void regula_falsi(){
    double a, b, cn, cv, tolerancia, e;
    int iteracion = 0;
    printf("Recuerde haber definido previamente la funcion al inicio del codigo\nIngrese el limite inferior del intervalo\n");
    scanf("%lf", &a);
    printf("Ingrese el limite superior del intervalo\n");
    scanf("%lf", &b);
    printf("Ingrese la cantidad de cifras decimales de error\n");
    scanf("%lf", &tolerancia);
    tolerancia = pow(10, -tolerancia);
    if (funcion(a) * funcion(b) < 0){
        do{
            if (iteracion == 0){
                cn = (funcion(b) * a - funcion(a) * b) / (funcion(b) - funcion(a));
                cv = a;
                e = fabs(cn - cv);
            }
            else{
                if (funcion(a) * funcion(cn) < 0){
                    b = cn;
                    cv = cn;
                    cn = (funcion(b) * a - funcion(a) * b) / (funcion(b) - funcion(a));
                    e = fabs(cn - cv);
                }
                else if (funcion(b) * funcion(cn) < 0){
                    a = cn;
                    cv = cn;
                    cn = (funcion(b) * a - funcion(a) * b) / (funcion(b) - funcion(a));
                    e = fabs(cn - cv);
                }
                else{
                    break;
                }
            }
            iteracion++;
        } while (e > tolerancia);
    }
    printf("\nResultados:\n");
    printf("El valor de la raiz es %lf con un error de %lf\n", cn, e);
    printf("La funcion en dicho punto vale %lf\n",funcion(cn));
    printf("El problema fue resuelto en %d iteraciones\n", iteracion);
}

void puntoFijo(){
    double cn, cv, tolerancia, e;
    int iteracion = 0;
    printf("Recuerde haber definido previamente la funcion y la funcion auxiliar al inicio del codigo\nIngrese el valor de partida (X0)\n");
    scanf("%lf", &cv);
    printf("Ingrese la cantidad de cifras decimales de error\n");
    scanf("%lf", &tolerancia);
    tolerancia = pow(10, -tolerancia);
    do{
        double lim = (funcionAux(cv + (0.01)) - funcionAux(cv)) / (0.01);
        if (fabs(lim) >= 1){
            printf("El metodo diverge (|g'(x)|>1)");
            break;
        }
        cn = funcionAux(cv);
        e = fabs(cn - cv);
        cv = cn;
        iteracion++;

    } while (e > tolerancia);

    printf("\nResultados:\n");
    printf("El valor de la raiz es %lf con un error de %lf\n", cn, e);
    printf("La funcion en dicho punto vale %lf\n",funcion(cn));
    printf("El problema fue resuelto en %d iteraciones\n", iteracion);
}

void newton_raphson(){
    double cn, cv, tolerancia, e;
    int iteracion = 0;
    printf("Recuerde haber definido previamente la funcion y su derivada al inicio del codigo\nIngrese el valor de partida (X0)\n");
    scanf("%lf", &cv);
    printf("Ingrese la cantidad de cifras decimales de error\n");
    scanf("%lf", &tolerancia);
    tolerancia = pow(10, -tolerancia);
    do{
        if (fabs(funcionAux(cv)) < (0.001)){
            printf("El metodo diverge (|f'(x)| cercano a 0)");
            break;
        }
        cn = cv - (funcion(cv) / funcionAux(cv));
        e = fabs(cn - cv);
        cv = cn;
        iteracion++;

    } while (e > tolerancia || iteracion >= 5000);

    printf("\nResultados:\n");
    printf("El valor de la raiz es %lf con un error de %lf\n", cn, e);
    printf("La funcion en dicho punto vale %lf\n",funcion(cn));
    printf("El problema fue resuelto en %d iteraciones\n", iteracion);
}

void secante(){
    double cn, cv, cvv, tolerancia, e;
    int iteracion = 0;
    printf("Recuerde haber definido previamente la funcion y su derivada al inicio del codigo\nIngrese el valor de partida (cv)\n");
    scanf("%lf", &cv);
    printf("Ingrese el valor para Xi-1 (cvv)\n");
    scanf("%lf", &cvv);
    printf("Ingrese la cantidad de cifras decimales de error\n");
    scanf("%lf", &tolerancia);
    tolerancia = pow(10, -tolerancia);
    do{
        double aprox = (funcion(cvv) - funcion(cv)) / (cvv - cv);
        cn = cv - (funcion(cv) / aprox);
        e = fabs(cn - cv);
        cvv = cv;
        cv = cn;
        iteracion++;

    } while (e > tolerancia || iteracion >= 5000);

    printf("\nResultados:\n");
    printf("El valor de la raiz es %lf con un error de %lf\n", cn, e);
    printf("La funcion en dicho punto vale %lf\n",funcion(cn));
    printf("El problema fue resuelto en %d iteraciones\n", iteracion);
}

