#ifndef _CDLL_H_
#define	_CDLL_H_
#define DEBUG 0
#include <stdlib.h>
#include <stdio.h>

typedef struct cdlln {
	size_t type;
	void* data;
	void (*del)(void*);
	void (*print)(void*);
	struct cdlln *nxt;
	struct cdlln *prev;
}cdlln;

typedef struct {
	cdlln *curr;
	int size;
}cdll;

#endif
