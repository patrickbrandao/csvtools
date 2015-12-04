/*

	Obter linha pelo ID de um arquivo CSV

*/

#include "headers.h"
#include "csvlib.h"

/*
Planilha CSC:

		1;Patolino da Silva;17/02/1983;Programador;status=1,id=123;Ola voce
		2;Humberto Rodrigues;17/02/1983;Programador;status=1,id=123;Ola brasil
		3;Javali Real;17/02/1983;Programador;status=1,id=123;Ola pessoal
		4;Pr. Arnaldo:17/02/1983;Programador;status=1,id=123;Ola polo norte
		5;Super Nani:17/02/1983;Programador;status=1,id=123;Ola siberia
		6;Patrick Luis:17/02/1983;Programador;status=1,id=123;Ola mundo

Exemplo:

	csv_getid planilha1.csv 6

	Retorna:
		6:Patrick Luis:17/02/1983;Programador;status=1,id=123;Ola mundo

*/

int help_std(){
	printf("\n");
	printf("csv_getid\n");
	printf("Obtem linha do arquivo CSV onde o primeiro campo tem o numero desejado\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: csv_getid (arquivo csv) (id) [id] [id] [...]\n");
	printf("\n");
	return 1;
}

int main(int argc, char **argv){
	 if(argc<3) return help_std();

	char *line = NULL;

	 char *file = argv[1];
	 char *buffer[1024];
	 bzero(buffer, sizeof buffer);

	 ssize_t readbytes = 0;
	 size_t readlen = 1000;

	 // ids a serem procurados
	 int idcount = 0;
	 int ids[1024];
	 bzero(ids, sizeof ids);

	 // contadores
	int i, j, max= argc - 2;

	 // coletar ids dos argumentos
	 if(max > 1024) max = 1024;
	 for(i=0;i < max;i++){
	 	char *ar = NULL;
	 	int nr = 0;

	 	ar = argv[i+2];
	 	nr = atoi(ar);

	 	//printf(" > ar=%s nr=%d\n", ar, nr);

	 	// usuario informou numero zerado ou que nao deu pra converter para int
	 	if(!nr) continue;

	 	// catalogar
	 	ids[idcount++] = nr;
	 }
	 if(!idcount){ fprintf(stderr, "Informe o ID do registro\n", file); return 4; }

	 // testar acesso ao arquivo
	if(access(file, R_OK)!=0){ fprintf(stderr, "Incapaz de acessar arquivo '%s'\n", file); return 2; }

	// abrir arquivo
   CSV_READ = fopen(file, "r");
	if (CSV_READ == NULL){ fprintf(stderr, "Incapaz de abrir arquivo '%s'\n", file); return 3; }

	while ((readbytes = getline(&line, &readlen, CSV_READ)) != -1) {
		char *found;
		int id;
		int idfound = 0;

		// comentario
		if(line[0]=='#') continue;

		// pegar primeiro campo da linha
		found = strchr (line, CSV_SEPARATOR);
		if(!found) continue;

		// finalizar string pra ficar mais facil pegar o id
		*found = 0;

		// obter numero
		id = atoi(line);
		if(!id) continue;

		// procurar
		for(j=0; j < idcount; j++){
			if(ids[j]==id){ idfound = 1; break; }
		}
		if(!idfound) continue;

		// voltar o separador
		*found = CSV_SEPARATOR;

		//printf("Retrieved line of length [%zu]: %s\n", readbytes, line);
		printf("%s", line);

	}
	fclose(CSV_READ);
}



































