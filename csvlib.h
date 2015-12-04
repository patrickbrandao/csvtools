/*

	Definicoes CSV

*/
#include "headers.h"

#ifndef _CSV_H
#define _CSV_H

// caracter separador dos campos
char CSV_SEPARATOR = ';';
int CSV_INIT = 0;


// ponteiro de leitura
FILE *CSV_READ = NULL;
FILE *CSV_WRITE = NULL;

// Registro (linha) CSV
struct CSV_REG {
	int id;			// id do registro
	int cols;		// numero de colunas
	char **cindex;	// ponteiro da lista de valores
};
typedef struct CSV_REG CSV_REG;


// Planilha CSV indexada por ID
struct CSV {
	int count;			// numero de registros
	CSV_REG *rindex;	// ponteiro da lista de registros
};
typedef struct CSV CSV;



// funcoes
void csvlib_init();
char **csv_parse_line(const char *line, int *cols);

char *get_datetime();

int csv_copy_file(const char *from, const char *to);

// incluir fontes
#include "csvlib.c"
#include "memory.c"

#endif

