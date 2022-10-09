/* ANDREI Gabriel - 313CB */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#ifndef ARBORE_BINAR
#define ARBORE_BINAR
#define ALPHABET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! "
#define ALPHABET_SIZE 70

typedef int TInfo;

typedef struct nod {
	void* info;
	struct nod *descendenti[ALPHABET_SIZE];
	
	short Frunza;   //este = 1 daca nodul este o frunza
} TNod, *TArb;


void AfiArb(TArb r, FILE*);//afisare cheia elementelor arborelui
TArb InitArb(void);///initializare arbore
void* search(TArb r, char *name);///cauta in arbore dupa cheia data
								///returneaza informatia stocata in frunza
void search_AC(TArb r, char* name, char* output[], int level);//cauta maxim 3 elemente cu
								//prefixul dat intr-un arbore

void insert(TArb r, char *name, void* info);//insereaza in arbore structura de date 
											//corespunzatoare si cheia

void* SearchBook(TArb r, char *name);///cauta cartea in arborele cu autori
void searchBook_AC(TArb r, char* name, char* output[]);
#endif

#ifndef _random_
#define _random_
#define random(n) (rand() % (n))
#define randomize() (srand((unsigned int)time(NULL)))
#endif
