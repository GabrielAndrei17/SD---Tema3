/* ANDREI Gabriel - 313CB */
/*--- auxarb.c --- functii auxiliare pentru arbori */
#include "tarb.h"
#include <stdarg.h>
#include <time.h>


TArb InitArb(void)
{
    TArb nod = NULL;
  
    nod = (TArb)malloc(sizeof(TNod));
  
    if (nod)
    {
        int i;
  
        nod->Frunza = 0;
		nod->info = NULL;
  
        for (i = 0; i < ALPHABET_SIZE; i++)
            nod->descendenti[i] = NULL;
    }
  
    return nod;
}

int CharToIndex(char a)
{
	char *ptr = strchr(ALPHABET, a);
	return ptr - ALPHABET; 
}

char IndexToChar(int a)
{
	return ALPHABET[a];
}
void insert(TArb r, char *name, void* info)
{
    int level;
    int length = strlen(name);
    int index;
  
    TArb aux = r;
  
    for (level = 0; level < length; level++)
    {
        index = CharToIndex( name[level] );

        if (!aux->descendenti[index])
            aux->descendenti[index] = InitArb();
  
        aux = aux->descendenti[index];
    }
  
    // marcheaza ultimul nod ca frunza
    aux->Frunza = 1;
	aux->info = info;
}

void* search(TArb r, char *name)
{
    int level;
    int length = strlen(name);
    int index;
    TArb aux = r;
  
    for (level = 0; level < length; level++)
    {
        index = CharToIndex( name[level] );
  
        if (!aux->descendenti[index])
            return NULL;
  
        aux = aux->descendenti[index];
    }
  
    if(aux != NULL && aux->Frunza == 1)
		return aux->info;
	else
		return NULL;
}
void* SearchBook(TArb r, char *name)
{
	if(r->Frunza == 1)
		return search(r->info, name);

	int i = 0;
	for (; i < ALPHABET_SIZE; i++)
		if(r->descendenti[i] != NULL)
		{
			void* aux = SearchBook(r->descendenti[i], name);
			if(aux != NULL)
				return aux;
		}
	return NULL;
}
void AfisAux(TArb r, char* name, int len, FILE *f2)
{
	if(r->Frunza == 1)
	{
		name[len] = '\0';
		fprintf(f2, "%s\n", name);
	}
	
	int i = 0;
	for (; i < ALPHABET_SIZE; i++)
		if(r->descendenti[i] != NULL)
		{
			name[len] = IndexToChar(i);
			AfisAux(r->descendenti[i], name, len + 1, f2);
		}

}
void AfiArb(TArb r, FILE * f2)
{
	char* name = (char*) calloc(50, 1);

	AfisAux(r, name, 0, f2);

	free(name);
}
void insertI(char* output[])
{
	if(output[0][0] == '\0')
	{
		strcpy(output[0], output[3]);
		return;
	}
	else
		if(strcmp(output[3], output[0]) < 0)
		{
			strcpy(output[2], output[1]);
			strcpy(output[1], output[0]);
			strcpy(output[0], output[3]);
			return;
		}

	if(output[1][0] == '\0')
	{
		strcpy(output[1], output[3]);
		return;
	}
	else
		if(strcmp(output[3], output[1]) < 0)
		{
			strcpy(output[2], output[1]);
			strcpy(output[1], output[3]);
			return;
		}

	if(output[2][0] == '\0')
	{
		strcpy(output[2], output[3]);
		return;
	}
	else
		if(strcmp(output[3], output[2]) < 0)
		{
			strcpy(output[2], output[3]);
			return;
		}
}
void search_AC(TArb r, char* name, char* output[], int level)
{
	if(level < (int)strlen(name))//inca nu am parcurs tot prefixul
	{
		int index = CharToIndex(name[level]);
		if(r->descendenti[index] != NULL)//daca putem sa mergem mai departe(exista prefixul in arbore)
		{
			output[3][level] = name[level];
			output[3][level + 1] = '\0';
			search_AC(r->descendenti[index], name, output, level+1);
		}
		return;
	}
	if(r->Frunza == 1)
	{
		insertI(output);//daca este frunza retinem cheia
	}

	int i = 0;
	for (; i < ALPHABET_SIZE; i++)//incercam sa completam prefixul
		if(r->descendenti[i] != NULL)
		{
			output[3][level] = IndexToChar(i);
			output[3][level + 1] = '\0';
			search_AC(r->descendenti[i], name, output, level + 1);
		}	
}
void searchBook_AC(TArb r, char* name, char* output[])
{
	if(r->Frunza == 1)
	{
		search_AC(r->info, name, output, 0);
	}
	
	int i = 0;
	for (; i < ALPHABET_SIZE; i++)
		if(r->descendenti[i] != NULL)
		{
			searchBook_AC(r->descendenti[i], name, output);
		}
}