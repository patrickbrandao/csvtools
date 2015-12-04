#ifndef _MEMORY_H
#define _MEMORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <stdarg.h>

// Tipos de alocacoes para acompanhamento de depuracao
#define MTYPE_CSV_CONTENT 		1
#define MTYPE_CSV_LINE	 		2
#define MTYPE_CSV_REGLIST 		3

// Defines para captura de alocacao de memoria
#define XMALLOC(mtype, size)       zmalloc ((mtype), (size))
#define XCALLOC(mtype, size)       zcalloc ((mtype), (size))
#define XREALLOC(mtype, ptr, size) zrealloc ((mtype), (ptr), (size))
#define XFREE(mtype, ptr)          zfree ((mtype), (ptr))
#define XSTRDUP(mtype, str)        zstrdup ((mtype), (str))
#define XZSTRDUP(mtype, str)        zxstrdup ((mtype), (str))
#define XSCALLOC(mtype, size, dup)  zscalloc ((mtype), (size), (dup))
#define SFREE(ptr)          sfree ((ptr));ptr=0

// Funcoes principais de gerenciamento de memoria
void *zmalloc (int type, size_t size);
void *zcalloc (int type, size_t size);
void *zrealloc (int type, void *ptr, size_t size);
void  zfree (int type, void *ptr);
void  sfree (void *ptr);
char *zstrdup (int type, char *str);
void *zscalloc (int type, size_t size, void *ptr);

#endif /* _MEMORY_H */




