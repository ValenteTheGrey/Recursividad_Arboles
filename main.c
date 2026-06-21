#include "libArboles.h"

int main()
{
    ///RECURSIVIDAD
    int num = 3;
    char cad1[] = "abcd";
    double r = factorial(num);
    printf("\nFactorial de %d -> Resultado: %2.0f\n", num, r);
    puts("\n");
    imp_cad1(cad1);


    ///ARBOLES
    //Estructura de datos jerarquica
    /*
    Compuesto por nodos, los nodos que no tienen hijos son los nodos "hoja"
    La cantidad de saltos de la raiz a un nodo hoja se le llama altura
    Tiene niveles, el nivel de la raiz es 0 y va subiendo
    Arboles binarios -> Cada nodo puede tener hasta 2 hijos (0,1 o 2), pero cada hijo tiene que estar diferenciado entre izquierdo o derecho
    Arboles binarios de busqueda -> Todos los nodos que son menores a la raiz estan a la izquierda, si son mayores a la derecha. Su aplicacion mas grande es como indice, es muy eficiente en la busqueda.
    La maxima cantidad de comparaciones que tengo que hacer es igual a la altura del arbol
    No admite duplicados ♥
    */

    t_arbol arbol;
    iniciar_arbol(&arbol);
    int vec[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};

    for(int i = 0; i < 9; i++){
        insertar_arbol(&arbol, &vec[i], sizeof(vec[i]), cmpInt);
    }

    puts("\n");
    rec_en_orden(&arbol, impInt, NULL);


    return 0;

}
