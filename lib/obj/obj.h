#ifndef _OBJ_H_
#define	_OBJ_H_
#define DEBUG 0
#include <stdlib.h>
#include <stdio.h>

typedef struct obj{
  (void)(*print)(void);
  (void)(*del)(void);
  void* data;
}obj;

#endif
