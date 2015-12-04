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

	csv_remove_id planilha1.csv 5
	Retorna: (nada na tela)
	Arquivo csv atualizado:
		1;Patolino da Silva;17/02/1983;Programador;status=1,id=123;Ola voce
		2;Humberto Rodrigues;17/02/1983;Programador;status=1,id=123;Ola brasil
		3;Javali Real;17/02/1983;Programador;status=1,id=123;Ola pessoal
		4;Pr. Arnaldo:17/02/1983;Programador;status=1,id=123;Ola polo norte
		6;Patrick Luis:17/02/1983;Programador;status=1,id=123;Ola mundo

	Gera arquivo backup: nome-do-arquivo.csv + . + ano + mes + dia + hora + minuto + segundo
		Exemplo: NOMEARQUIVO.csv.20151014050001


*/

int help_std(){
	printf("\n");
	printf("csv_remove_id\n");
	printf("Remove um registro do arquivo CSV baseado no ID (valor da primeira coluna)\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: csv_remove_id (arquivo csv) (id)\n");
	printf("\n");
	return 1;
}

int main(int argc, char **argv){
	 if( argc < 3 || argc > 3) return help_std();

	char *line = NULL;

	 char *file = argv[1];
	 char *buffer[1024];
	 bzero(buffer, sizeof buffer);

	 ssize_t readbytes = 0;
	 size_t readlen = 1000;

	 // ids a serem procurados
	 int id = 0;

	 // contadores
	register int i, j;


	// ler id
	id = atoi(argv[2]);
	if(!id){ fprintf(stderr, "Informe o ID do registro que deseja remover\n", file); return 1; }

	 // testar acesso ao arquivo
	if(access(file, R_OK)!=0){ fprintf(stderr, "Incapaz de acessar arquivo '%s'\n", file); return 2; }

	// gerar nome de arquivos
	char *newfile; // arquivo temporario com nova versao
	char *oldfile; // nome do arquivo atual para renomear

	// abrir arquivo original
   CSV_READ = fopen(file, "r");
	if (CSV_READ == NULL){ fprintf(stderr, "Incapaz de abrir arquivo [r] '%s'\n", file); return 3; }

	// 1 - procurar id no arquivo
	int regfound = 0;
	while ((readbytes = getline(&line, &readlen, CSV_READ)) != -1){
		char *found;
		int xid;
		int idfound = 0;
		int colcount = 0;

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
		// o ID existe, podemos iniciar a reescrita para remove-lo
		if(id==xid){ regfound = 1; break; }
	}

	// nao achou? entao tudo bem, consideraremos que o registro nao existe mais
	if(!regfound){ fclose(CSV_READ); return 0; }

	// ACHOU

	// gerar nome dos novos arquivos
	// nova copia sem o id
	j = asprintf(&newfile, "%s.new", file);
	if(!j){
		fprintf(stderr, "Incapaz de alocar memoria para newfile\n");
		return 5;
	}

	// copia do arquivo original, sempre preserva-lo para depuracao
	j = asprintf(&oldfile, "%s.%s", file, get_datetime());
	if(!j){
		fprintf(stderr, "Incapaz de alocar memoria para oldfile\n");
		return 6;
	}

	// se nao der pra abrir novo arquivo, nem adianta
 	CSV_WRITE = fopen(newfile, "w");
	if (CSV_WRITE == NULL){
		fclose(CSV_READ);
		fprintf(stderr, "Incapaz de abrir newfile[%s] para escrita\n", newfile);
		return 7;
	}

	// Criar copia de sombra (backup do arquivo original)
	csv_copy_file(file, oldfile);

	// Percorrer novamente, gerando 
	// rebubinar o arquivo
	rewind(CSV_READ);

	while ((readbytes = getline(&line, &readlen, CSV_READ)) != -1){
		char *found;
		int xid;
		size_t wc=0;

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
		// o ID existe, deveremos ignora-lo para exclui-lo do novo arquivo
		if(id==xid) continue;

		// voltar separador para o lugar
		*found = CSV_SEPARATOR;

		// gravar no novo arquivo
		wc = fwrite (line , sizeof(char), readbytes, CSV_WRITE);

		// falha de escrita
		if(wc != readbytes){
			fclose(CSV_READ); fclose(CSV_WRITE);
			return 9;
		}
	}

	// Tudo certo, renomear novo arquivo para ficar com o nome do arquivo oficial
	fclose(CSV_READ); fclose(CSV_WRITE);
	csv_copy_file(newfile, file);

	//printf("Gravar novo arquivo em ..........: %s\n", newfile);
	//printf("Copia oculta ....................: %s\n", oldfile);

	// tudo certo
	return 0;

}








































