/* ANDREI Gabriel - 313CB */
/**-- main.c --  prelucreaza arbori trie --*/
#include "tarb.h"

typedef struct structura_carte
{
	char* Titlu;
	char* Autor;
	int Rating, Numar_Pagini;
	
}Carte;

Carte* ConstruiesteCarte(char* titlu, char* autor, int rating, int nr_pag)
{
	//construieste structura 'Carte' si o returneaza
	Carte* aux = (Carte*)calloc(1, sizeof(Carte));

	aux->Autor = (char*)calloc(strlen(autor) + 1, 1);
	aux->Titlu = (char*)calloc(strlen(titlu) + 1, 1);

	aux->Rating = rating;
	aux->Numar_Pagini = nr_pag;
	strcpy(aux->Autor, autor);
	strcpy(aux->Titlu, titlu);

	return aux;
}
void auxiliar_Search_Book(TArb r, char* name, FILE* f2)
{
	//  Aceasta functie auxiliara va fi folosita pentru cautarea 
	//  cartilor in arborele de autori dupa prefixul dat
	char** output;
	output = (char**)calloc(4, sizeof(char*));

	/* output[0] , output[1] , output[2] :
	vor retine cele 3 elemente in ordine lexicografica

	output[3] va fi folosit pentru construirea  	
	*/

	int i = 0;
	for(; i <= 3; i++)
	{
		output[i] = (char*)calloc(52, sizeof(char));
		output[i][0] = '\0';
	}
	searchBook_AC(r, name, output);

	//Gestionarea output-ului
	if(output[0][0] == '\0')
		fprintf(f2, "Nicio carte gasita.\n");
	else
	{
		for(i = 0; i<3; i++)
			if(output[i][0] != '\0')
				fprintf(f2, "%s\n", output[i]);
	}

	for(i = 0; i<4; i++)
		free(output[i]);
	free(output);
}
int auxiliar_Search_Arb(TArb r, char* name, FILE *f2)
{
	//asemanator cu functia auxiliar_Search_Book
	char** output;
	int ok = 1;

	output = (char**)calloc(4, sizeof(char*));
	int i = 0;
	for(; i <= 3; i++)
	{
		output[i] = (char*)calloc(42, sizeof(char));
		output[i][0] = '\0';
	}
	search_AC(r, name, output, 0);

	if(output[0][0] == '\0')
		ok = 0;
	else
	{
		for(i = 0; i<3; i++)
			if(output[i][0] != '\0')
				fprintf(f2, "%s\n", output[i]);
	}
	for(i = 0; i<4; i++)
		free(output[i]);
	free(output);

	return ok;
}
int main (int argc, char *argv[])
{
	TArb T1;
	T1 = InitArb();

	FILE *f1, *f2;
	f1 = fopen(argv[1], "rt");
	f2 = fopen(argv[2], "wt");
	char * line = NULL;
	size_t len = 0;

	while (getline(&line, &len, f1) != -1)
	{
		if (line[strlen(line) - 1] == '\n')
		{
			line[strlen(line) - 1] = '\0';
		}
		
		char * comand = strtok(line, " ");
		if(strcmp(comand, "add_book") == 0)//ADD_BOOK
		{
			char * titlu = strtok(NULL, ":");//titlu
			char * autor = strtok(NULL, ":");//autor

			char * aux = strtok(NULL, ":");
			int rating = (int)atoi(aux);//Rating

			aux = strtok(NULL, ":");
			int numar_pag = (int)atoi(aux);//Numar pagini

			Carte* aux_carte = ConstruiesteCarte(titlu, autor, rating, numar_pag);

			TArb T2 = search(T1, autor);

			if(T2 == NULL)
			{
				T2 = InitArb();
				insert(T2, titlu, aux_carte);
				insert(T1, autor, T2);
			}
			else
			{
				insert(T2, titlu, aux_carte);
			}

			continue;
		}
		if(strcmp(comand, "search_book") == 0)//SEARCH_BOOK
		{
			char * titlu = strtok(NULL, ":");
			char *p = strchr(titlu, '~');

			if(p == NULL)
			{
				Carte* aux = SearchBook(T1, titlu);
				if(aux == NULL)
					fprintf(f2, "Cartea %s nu exista in recomandarile tale.\n", titlu);
				else
					fprintf(f2, "Informatii recomandare: %s, %s, %d, %d\n", aux->Titlu, aux->Autor, aux->Rating, aux->Numar_Pagini);

			}
			else//AutoComplete
			{
				*p = '\0';
				auxiliar_Search_Book(T1, titlu, f2);
			}
			continue;
		}
		if(strcmp(comand, "list_author") == 0)//LIST AUTHOR
		{
			char * autor = strtok(NULL, ":");
			char *p = strchr(autor, '~');

			if(p == NULL)
			{
				TArb T2 = search(T1, autor);
				if(T2 == NULL)
					fprintf(f2, "Autorul %s nu face parte din recomandarile tale.\n", autor);
				else
				{
					AfiArb(T2, f2);
				}
			}
			else//AutoComplete
			{
				*p = '\0';
				int ok = auxiliar_Search_Arb(T1, autor, f2);
				if(ok == 0)
					fprintf(f2, "Niciun autor gasit.\n");

			}
			continue;
		}
		if(strcmp(comand, "search_by_author") == 0) //SEARCH_BY_AUTHOR
		{
			char * autor = strtok(NULL, ":");
			char* p = strchr(autor, '~');
			if(p == NULL)
			{
				char * titlu = strtok(NULL, ":");
				p = strchr(titlu, '~');

				if(p == NULL)
				{
					TArb T2 = search(T1, autor);
					if(T2 == NULL)
						fprintf(f2, "Autorul %s nu face parte din recomandarile tale.\n", autor);
					else
					{
						Carte* aux = search(T2, titlu);
						fprintf(f2, "Informatii recomandare: %s, %s, %d, %d\n", aux->Titlu, aux->Autor, aux->Rating, aux->Numar_Pagini);
					}
				}
				else//Auto Complete dupa titlu
				{
					*p = '\0';
					TArb T2 = search(T1, autor);
					if(T2 == NULL)
						fprintf(f2, "Autorul %s nu face parte din recomandarile tale.\n", autor);
					else
						auxiliar_Search_Arb(T1, titlu, f2);
				}
			}
			else//Auto Complete dupa autor
			{
				*p = '\0';
				int ok = auxiliar_Search_Arb(T1, autor, f2);
				if(ok == 0)
					fprintf(f2, "Niciun autor gasit.\n");
			}
			continue;
		}
		
		printf("Nu exista comanda %s\n", comand);
	}

	fclose(f1);
	fclose(f2);

	return 0;
}
