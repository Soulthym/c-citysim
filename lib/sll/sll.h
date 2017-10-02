#ifndef _SLL_H_
#define	_SLL_H_
#define DEBUG 0
#include <stdlib.h>
#include <stdio.h>


typedef struct slln_ {
	size_t type;
	void* data;
	void (*del)(void*);
	void (*print)(void*);
	struct slln_ *nxt;
}slln;

typedef struct{
	size_t size;
	slln *head;
	slln *tail;
	slln *curr;
}sll;

struct sll {
    sll* (*new) (void);
	slln* (*append) (sll*, slln*);
	slln* (*prepend) (sll*, slln*);
	slln* (*insert) (sll*, slln*, slln*);
	slln* (*get) (sll*, int);
	sll* (*empty) (sll*);
	void (*del) (sll*);
	void (*print) (sll*);
	void (*delhead) (sll*);
};
extern const struct sll SLL;

struct slln {
	slln* (*new) (size_t type, void *data, void (*del)(void*), void (*print)(void*));
};
extern const struct slln SLLN;
#endif
