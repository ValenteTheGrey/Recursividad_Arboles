#ifndef LIBARBOLES_H_INCLUDED
#define LIBARBOLES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Arboles
typedef struct sNodoa
{
    void* info;
    size_t tam_info;
    struct sNodoa *izq, *der;
}tNodoa;

typedef tNodoa* tArbol;


double factorial(unsigned n);
int mcd (int m, int n);
void imp_cad1(char* cad);
int cmpInt(const void* a, const void* b);
void impInt(void* numImp, void* argInutil);
void iniciar_arbol(tArbol* pa);
int insertar_arbol(tArbol* pa, void* pd, size_t tam, int (*cmp)(const void*, const void*));
void rec_en_orden(tArbol *pa, void (*accion)(void*, void*), void* params);


#endif // LIBARBOLES_H_INCLUDED
