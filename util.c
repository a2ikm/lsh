#include "lsh.h"

Vector *vec_new(void)
{
  Vector *v = malloc(sizeof(Vector));
  v->capacity = 16;
  v->data = malloc(sizeof(void *) * v->capacity);
  v->len = 0;
  return v;
}

void vec_free(Vector *v)
{
  free(v->data);
  free(v);
}

void vec_push(Vector *v, void *e)
{
  if (v->len == v->capacity) {
    v->capacity *= 2;
    v->data = realloc(v->data, sizeof(void *) * v->capacity);
  }
  v->data[v->len++] = e;
}

void *vec_pop(Vector *v)
{
  return v->data[--v->len];
}
