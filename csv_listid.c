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

	csv_listid planilha1.csv

	Retorna:
		1
		2
		3
		4
		5
		6

*/

int help_std(){
	printf("\n");
	printf("csv_listid\n");
	printf("Obtem os ids (primeiro numero de cada linha) do arquivo CSV\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: csv_listid (arquivo csv)\n");
	printf("\n");
	return 1;
}

int main(int argc, char **argv){
	 if(argc<2||argc>2) return help_std();

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
	register int i, j;

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

		printf("%d\n", id);
	}

	fclose(CSV_READ);

}



































