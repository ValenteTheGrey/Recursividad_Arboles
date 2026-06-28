#include "libArboles.h"

#define TODO_OK 0
#define ERR_MEM 1
#define DUPLICADO 2

///Ejemplos de recursividad
double factorial(unsigned n)
{
    if(n==0)
        return 1;

    return n * factorial(n-1);
}

int mcd (int m, int n)
{
    if(m%n == 0)
        return n;
    return mcd(n,m%n);
}

void imp_cad1(char* cad)
{
    if(!*cad)
        return;
    printf("%s\n",cad);
    imp_cad1(cad+1);
    printf("%s\n",cad); //Para algo que esta retrocediendo se utiliza despues de la llamada recursiva

}

int cmpInt(const void* a, const void* b)
{
    return *((int*)a) - *((int*)b);
}

void impInt(void* numImp, void* argInutil)
{
    int num = *(int*)numImp;
    printf("%d, ", num);
}

void iniciar_arbol(tArbol* pa)
{
    *pa = NULL;
}

int insertar_arbol(tArbol* pa,void* pd, size_t tam, int (*cmp)(const void*, const void*))
{
    tNodoa * nue;
    while(*pa)
    {
        int rc = cmp(pd, (*pa)->info);
        if(rc<0)
            pa = &(*pa)->izq;
        else if(rc>0)
            pa = &(*pa)->der;
        else
            return DUPLICADO;
    }
    if((nue=(tNodoa *) malloc(sizeof(tNodoa))) == NULL ||
       (nue->info = malloc(tam)) == NULL)
    {
        free(nue);
        return ERR_MEM;
    }
    memcpy(nue->info, pd, tam),
    nue->tam_info = tam;
    nue->izq = nue->der = NULL;
    *pa = nue;
    return TODO_OK;
}


//Recorrer en orden -> Izq - Raiz - Der
void rec_en_orden(tArbol *pa, void (*accion)(void* info, void* params), void* params)
{
    if(!*pa)
        return;
    rec_en_orden(&(*pa)->izq, accion, params);
    accion((*pa)->info, params);
    rec_en_orden(&(*pa)->der, accion, params);
}

//Recorrer en preorden -> Raiz - Izq - Der -> Esto sirve para ingestar info construyendo el arbol tal cual lo tenia, con el mismo balanceo
//Se deberia mover solo la accion

//Recorrer en postorden -> Izq - Der - Raiz -> Si hago de atras hacia adelante me queda el mismo arbol armado
//Se deberia mover solo la accion

//Vaciar arbol

//Contar cant nodos de un arbol
unsigned cantNodosArbolBin(tArbol* pa)
{
    if(!*pa)
        return 0;

    return 1 + cantNodosArbolBin(&(*pa)->izq) + cantNodosArbolBin(&(*pa)->der);
}

//Altura del Árbol Binario
unsigned alturaArbolBin(tArbol* pa)
{
    if(*pa)
        return 0;

    unsigned hi = alturaArbolBin(&(*pa)->izq);
    unsigned hd = alturaArbolBin(&(*pa)->der);

    return (hi > hd ? hi : hd) + 1;

    // o directamente hacer el return con una macro
    //return MAX(alturaArbolBin(&(*p)->izq), alturaArbolBin(&(*p)->der)) + 1;
}

//Cantidad de nodos hasta nivel
unsigned cantNodosHastaNivel(tArbol* pa, unsigned n)
{
    if(!*pa)
        return 0;

    if(n == 0)
        return 1;
    
    return (cantNodosHastaNivel(&(*pa)->izq, n - 1) + cantNodosHastaNivel(&(*pa)->izq, n - 1) + 1);
}

//Eliminar todas las hojas

//Probar guardar el arbol en un archivo y luego volver a crearlo a partir del mismo
