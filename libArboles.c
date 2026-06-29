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

void iniciarArbol(tArbol* pa)
{
    *pa = NULL;
}

int insertarArbol(tArbol* pa,void* pd, size_t tam, int (*cmp)(const void*, const void*))
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
void recorrerEnOrdArbol(tArbol *pa, void (*accion)(void* info, void* params), void* params)
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
    if(!*pa)
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
    
    return (cantNodosHastaNivel(&(*pa)->izq, n - 1) + cantNodosHastaNivel(&(*pa)->der, n - 1) + 1);
}

//Se recorre 2 veces, uno para obtener la altura y otra para ver si cada nodo tiene dos hijos
unsigned esBalanceado(const tArbol* pa)
{
    unsigned h = alturaArbolBin(pa);

    return cantNodosHastaNivel(pa, h - 2) == pow(2, h - 1) - 1;

    //recordar que cantidad de nodos en Arbol Completo: 2^h - 1.
    //Balanceado: Completo hasta su altura h - 1.
}

unsigned esBalanceado2(const tArbol *p)
{
    return esCompletoHastaNivel(p, alturaArbolBin(...));

}


int esCompletoHastaNivel(const tArbol *p, int n)
{
    if(!*p)
        return 0;

    if(n == 0)
        return 1;

    return esCompletoHastaNivel(&(*p)->izq, n - 1) && esCompletoHastaNivel(&(*p)->der, n - 1);

}


tArbol* buscarNodo(tArbol* pa, const void* pd, int (*cmp)(const void*, const void*))
{
    tArbol* nodo;
    while(*pa)
    {
        int rc = cmp(pd, (*pa)->info);
        if(rc > 0)
            pa = &(*pa)->der;
        else if(rc < 0)
            pa = &(*pa)->izq;
        else if(rc == 0)
             return nodo = pa;
    }

    return NULL;         
}

//Para eliminar un nodo primero se busca en sus subarbol cual es el valor mas cercano y se lo reemplaza con el.
int eliminarElemArbol(tArbol* pa, void* pd, unsigned tam, int (*cmp)(const void*, const void*))
{
     if(!(pa = buscarNodo(pa, pd, cmp)))
         return 0;

    memcpy(pd, (*pa)->info, MINIMO(tam, (*pa)->tamInfo));

    return eliminarRaizArbol(pa);

}


int eliminarRaizArbol(tArbol* pa)
{
    tArbol* remp, elim;    //Son tNodoa**

    if(!*pa)
        return 0;

    free((*pa)->info);
    if(!(*pa)->izq && !(*pa)->der)
    {
        free(*pa);
        *pa = NULL;
        return 1;
    }

    remp = alturaArbolBin(&(*pa)->izq) > alturaArbolBin(&(*pa)->der) ? mayorNodoArbol(&(*pa)->izq) : menorNodoArbol(&(*pa)->der);

    elim = *remp;
    (*pa)->info = elim->info;
    (*pa)->tamInfo = elim->tamInfo;
    *remp = elim->izq ? elim->izq : elim->der;
    free(elim);

    return 1;
    
}

tArbol* mayorNodoArbol(tArbol* pa)
{
    while((*pa)->der)
        pa = &(*pa)->der;

    return pa;
}

tArbol* menorNodoArbol(tArbol* pa)
{
    while((*pa)->izq)
        pa = &(*pa)->izq;

    return pa;
}

//Eliminar todas las hojas

//Probar guardar el arbol en un archivo y luego volver a crearlo a partir del mismo

int cargarDesdeDatosOrd(tArbol* pa, void* ds, unsigned (*leer)(void**,void*,unsigned,void*), int li, int ls, void* params)
{
    int m = (li + ls) / 2;
    int r;

    if(li > ls)
        return TODO_OK;

    *pa = (tNodoa*)malloc(sizeof(tNodoa));

    if(!*pa || !((*pa)->tamInfo = leer(&(*pa)->info, ds, m, params)))
    {
        free(*pa);
        return SIN_MEM;
    }

    (*pa)->izq = (*pa)->der = NULL;

    if((r = cargarDesdeDatosOrd(&(*pa)->izq, ds, leer, li, m - 1, params)) != TODO_OK)
        return r;

    return cargarDesdeDatosOrd(&(*pa)->der, ds, leer, li, m + 1, params);
}


int cargarArchivoBinOrdenadoArbolBin(tArbol* pa, const char* path, unsigned tamInfo)
{
    int cantReg, r;
    FILE * pf;
    if(*pa)
        return SIN_INICIALIZAR;

    if(!(pf = fopen(path, "rb")))
        return ERROR_ARCH;

    fseek(pf, 0L, SEEK_END);
    cantReg = ftell(pf) / tamInfo;

    r = cargarDesdeDatosOrd(pa, pf, leerDesdeArchivoBin, 0, cantReg - 1, &tamInfo);

    fclose(pf);
    return r;
    
}

unsigned leerDesdeArchivoBin(void** d, void* pf, unsigned pos, void* params)
{
    unsigned tam = *((int*)params);
    *d = malloc(tam);
    if(!*d)
        return 0;

    fseek((FILE*)pf, pos*tam, SEEK_SET);
    return fread(*d, tam, 1, (FILE*)pf);
}
