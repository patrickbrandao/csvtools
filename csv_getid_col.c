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

	csv_getid planilha1.csv 6 2
	Retorna:
		Patrick Luis

	csv_getid planilha1.csv 2 5
	Retorna:
		Ola brasil

*/

int help_std(){
	printf("\n");
	printf("csv_getid_col\n");
	printf("Obtem linha do arquivo CSV pelo id, em seguida retorna o valor da coluna\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: csv_getid_col (arquivo csv) (id) (col)\n");
	printf("\n");
	return 1;
}

int main(int argc, char **argv){
	 if( argc < 4 || argc > 4) return help_std();

	char *line = NULL;

	 char *file = argv[1];
	 char *buffer[1024];
	 bzero(buffer, sizeof buffer);

	 ssize_t readbytes = 0;
	 size_t readlen = 1000;

	 // ids a serem procurados
	 int id = 0;
	 int col = 0;

	 // contadores
	register int i, j;

	// ler id
	id = atoi(argv[2]);
	if(!id){ fprintf(stderr, "Informe o ID do registro\n", file); return 4; }
	// ler coluna
	col = atoi(argv[3]);
	if(!col){ fprintf(stderr, "Informe a coluna no registro\n", file); return 5; }

	 // testar acesso ao arquivo
	if(access(file, R_OK)!=0){ fprintf(stderr, "Incapaz de acessar arquivo '%s'\n", file); return 2; }

	// abrir arquivo
   CSV_READ = fopen(file, "r");
	if (CSV_READ == NULL){ fprintf(stderr, "Incapaz de abrir arquivo '%s'\n", file); return 3; }

	while ((readbytes = getline(&line, &readlen, CSV_READ)) != -1){
		char *found;
		int xid;
		int idfound = 0;
		int colcount = 0;
		char **reg;

		// comentario
		if(line[0]=='#') continue;

		// pegar primeiro campo da linha
		found = strchr (line, CSV_SEPARATOR);
		if(!found) continue;

		// finalizar string pra ficar mais facil pegar o id
		*found = 0;

		// obter numero
		xid = atoi(line);
		if(!xid) continue;

		// numero do registro diferente
		if(id!=xid) continue;

		// voltar o separador
		*found = CSV_SEPARATOR;

		// Temos a linha, obter a coluna
		reg = csv_parse_line(line, &colcount);

		// se o numero de colunas for menor que a coluna que eu quero,
		// nao tem como obter a coluna que eu quero
		if(col > colcount) continue;

		// imprimir coluna
		printf("%s\n", reg[col-1]);

		/*

		printf("Linha..............: %s", line);
		printf("Numero de colunas..: %d\n", colcount);

		for(j=0;j<colcount;j++){
			printf(" Coluna %d => %s\n", j+1, reg[j]);
		}
		*/

		// liberar memoria
		SFREE(reg[0]); // copia da linha
		// SFREE(reg);    // lista

		//printf("Retrieved line of length [%zu]: %s\n", readbytes, line);

	}
	fclose(CSV_READ);

}








































