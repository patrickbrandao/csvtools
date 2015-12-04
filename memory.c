
#include "memory.h"

// Tratar erro de alocacao, exibir tipo de alocacao e finalizar programa
static void zerror (const char *fname, int type, size_t size){
	fprintf (stderr, "%s : can't allocate memory for '%d' size %d\n", fname, type, (int) size);
	exit (1);
}

// Alocacao normal de memoria
void *zmalloc (int type, size_t size){
	void *memory;
	memory = malloc (size);
	if (memory == NULL) zerror ("malloc", type, size);
	return memory;
}

// Alocacao de memoria com preenchimento de zeros
void *zcalloc (int type, size_t size){
	void *memory;
	memory = calloc (1, size);
	if (memory == NULL) zerror ("calloc", type, size);
	return memory;
}

// Realocazao de memoria
void *zrealloc (int type, void *ptr, size_t size){
	void *memory;
	memory = realloc (ptr, size);
	if (memory == NULL) zerror ("realloc", type, size);
	return memory;
}

// Liberar memoria
void zfree (int type, void *ptr){
	if(ptr) free (ptr);
}
void sfree (void *ptr){
	if(ptr!=NULL) free (ptr);
}

// Duplicar string com alocacao
char *zxstrdup (int type, char *str){
	void *dup = NULL;
	int len = strlen(str);
	
	if(len){
		dup = zcalloc(type, len+1);
		memcpy (dup, str, len);
	}
	return dup;
}

// Duplicar string
char *zstrdup (int type, char *str){
	void *dup;
	dup = strdup (str);
	if (dup == NULL) zerror ("strdup", type, strlen (str));
	return dup;
}

// alocar memoria, preenche-la com zeros e copiar string
void *zscalloc (int type, size_t size, void *ptr){
	void *memory;
	int len = 0;
	memory = calloc (1, size);
	if (memory == NULL) zerror ("scalloc", type, size);
	if(ptr){
		len = strlen(ptr);
		if(len+1 > size) len = size-1;
		memcpy(memory, ptr, size);
	}
	return memory;
}



