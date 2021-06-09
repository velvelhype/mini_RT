#include "vector_utils.h"

#include <stdio.h>
#include <math.h>
#include <string.h>

vector_t add(const vector_t* a, const vector_t* b)
{
    vector_t ret;
    ret.x = a->x + b->x;
    ret.y = a->y + b->y;
    ret.z = a->z + b->z;
    return  ret;
}

vector_t sub(const vector_t* a, const vector_t* b)
{
    vector_t ret;
    ret.x = a->x - b->x;
    ret.y = a->y - b->y;
    ret.z = a->z - b->z;
    return  ret;
}

vector_t mult(const vector_t* a, float b)
{
    vector_t ret;
    ret.x = a->x * b;
    ret.y = a->y * b;
    ret.z = a->z * b;
    return  ret;
}

float dot(const vector_t* a, const vector_t* b)
{
  return a->x * b->x + a->y * b->y + a->z * b->z;
}

float squared_norm(const vector_t*v)
{
  return SQR(v->x) + SQR(v->y) + SQR(v->z);
}

float norm(const vector_t *v)
{
  return sqrt(squared_norm(v));
}

float normalize(vector_t* v)
{
  float vnorm = norm(v);
  v->x /= vnorm;
  v->y /= vnorm;
  v->z /= vnorm;
  return vnorm;
}

void cross(vector_t* o, const vector_t*a, const vector_t*b)
{
  o->x = a->y * b->z - a->z * b->y;
  o->y = a->z * b->x - a->x * b->z;
  o->z = a->x * b->y - a->y * b->x;
}

const char* vector_str(const vector_t*v)
{
  static char buf[1024];
  memset(buf, 0, sizeof(buf));
  sprintf((void*)buf, "(%f, %f, %f)", v->x, v->y, v->z);
  return buf;
}
