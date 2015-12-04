/*

	Funcoes CSV


*/

#include "headers.h"
#include "csvlib.h"

// Inicializar area de trabalho na memoria
void csvlib_init(){
	if(CSV_INIT) return;

	// Separador padrao
	//CSV_SEPARATOR = ';';

	CSV_INIT = 0;
}


// fazer parser do registro
char **csv_parse_line(const char *line, int *cols){
	// contadores
	register int i,j;

	// inicializar
	csvlib_init();

	// lista de retorno
	char **list = NULL;
	// numero de colunas
	int listcount = 0;

	// tamanho da linha
	int linelen;
	linelen = strlen(line);
	if(!linelen) return list;

	// gerar copia da linha para onde serao apontados os ponteiros
	// da lista
	char *newline = XSCALLOC(MTYPE_CSV_LINE, linelen + 1, line);

	// string de posicionamento de ponteiros,
	// numero de registros nao pode ser maior que numero de bytes do registro
	list = XCALLOC(MTYPE_CSV_REGLIST, linelen+2);

	// contar numero de campos
	int bread = 0;
	for(i=0; i < linelen; i++){
		char at = newline[i], nx = newline[i+1];

		// Primeiro campo
		if(!bread){
			// primeiro campo comecou com divisor
			if(at==';') newline[i] = 0;

			// colocar ponteiro do primeiro item no primeiro byte da string
			list[listcount++] = (newline);

			bread++;
			continue;
		}

		// pular 2 caracteres
		if(at=='\\' && nx ==';'){i++;bread+=2;continue;}

		// divisor
		if(at==';'){
			newline[i] = 0;

			// proximo e' um divisor tambem?
			// ?

			list[listcount++] = (newline)+i+1;
		}

		bread++;
	}

	// exportar numero de colunas
	*cols = listcount;


	return list;
}



// obter ano+mes+dia+hora+minuto+segundo
char *get_datetime(){
	time_t time_raw_format;
	struct tm * ptr_time;
	char buffer[50];
	bzero(buffer, sizeof buffer);

	time ( &time_raw_format );
	ptr_time = localtime ( &time_raw_format );
	if(strftime(buffer, 50, "%Y%m%d%H%M%S", ptr_time) == 0){
		// nao deu pra gerar, alocacao temporaria
		strcpy(buffer, "oldnotime");
	}
	return buffer;
}


// Copiar arquivo (cria novo arquivo)
int csv_copy_file(const char *src, const char *dst){
	FILE *src_fd = NULL;
	FILE *dst_fd = NULL;

	char ch;

	// abrir arquivo original
   src_fd = fopen(src, "r");
	if (src_fd == NULL) return -1;

	// abrir/criar arquivo destino
   dst_fd = fopen(dst, "w");
	if (dst_fd == NULL){ fclose(src_fd); return -2; }

	// byte a byte
	while( ( ch = fgetc(src_fd) ) != EOF ) fputc(ch, dst_fd);

	fclose(src_fd);
	fclose(dst_fd);

	return 0;

}




















