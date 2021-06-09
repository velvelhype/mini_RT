#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdarg.h>
#include <stdio.h>
#include "raytracing.h"

int raytrace(const scene_t* scene, const ray_t *eye_ray, colorf_t *out_col)
{
  if ()
  {
    colorf_t col = {0,0,0};

    for()
    {

    }
  }
  /* 実装せよ */
}/* int raytrace(const scene_t* scene, const ray_t *eye_ray, colorf_t *out_col) */

int intersection_test(const shape_t *shape, const ray_t* ray, 
                      intersection_point_t* out_intp)
{
  if ( shape->type == ST_SPHERE )
    {
      const sphere_t *sph = &shape->data.sphere;
      vector_t pe_pc;
      float A,B,C,D;
      float t;
      
      pe_pc.x = ray->start.x - sph->center.x;
      pe_pc.y = ray->start.y - sph->center.y;
      pe_pc.z = ray->start.z - sph->center.z;

      A = dot(&ray->direction, &ray->direction);
      B = 2 * dot(&ray->direction, &pe_pc);
      C = dot(&pe_pc, &pe_pc) - SQR(sph->radius);

      D = SQR(B) - 4*A*C;

      t = -1.0f;
      if ( D == 0 )
        {
          t = -B / (2*A);
        }
      else if ( D > 0 )
        {
          float t1 = (-B + sqrt(D))/(2*A);
          float t2 = (-B - sqrt(D))/(2*A);

          if ( t1 > 0 ) t = t1;
          if ( t2 > 0 && t2 < t ) t = t2;
        }

      if ( t > 0 )
        {
          if ( out_intp )
            {
              out_intp->distance = t;
              
              out_intp->position.x = ray->start.x + t * ray->direction.x;
              out_intp->position.y = ray->start.y + t * ray->direction.y;
              out_intp->position.z = ray->start.z + t * ray->direction.z;

              out_intp->normal.x = out_intp->position.x - sph->center.x;
              out_intp->normal.y = out_intp->position.y - sph->center.y;
              out_intp->normal.z = out_intp->position.z - sph->center.z;
              normalize(&out_intp->normal);
            }

          return 1;
        }
      else
        {
          return 0;
        }
    }
  else if ( shape->type == ST_PLANE )
    {
      const plane_t *pln = &shape->data.plane;
      float dn_dot = dot(&ray->direction, &pln->normal);

      if ( dn_dot != 0 )
        {
          vector_t s_p;
          float t;
          
          s_p.x = ray->start.x - pln->position.x;
          s_p.y = ray->start.y - pln->position.y;
          s_p.z = ray->start.z - pln->position.z;

          t = -dot(&s_p, &pln->normal) / dn_dot;

          if ( t > 0 )
            {
              if ( out_intp )
                {
                  out_intp->distance = t;

                  out_intp->position.x = ray->start.x + t * ray->direction.x;
                  out_intp->position.y = ray->start.y + t * ray->direction.y;
                  out_intp->position.z = ray->start.z + t * ray->direction.z;

                  out_intp->normal = pln->normal;
                }

              return 1;
            }
          else
            {
              return 0;
            }
        }
    }
  return 0;
}/* int intersection_test(const shape_t *shape, const ray_t* ray,  */

int get_nearest_shape(const scene_t* scene, const ray_t *ray, float max_dist, int exit_once_found,
                      shape_t **out_shape, intersection_point_t *out_intp)
{
  size_t i;
  shape_t *nearest_shape = NULL;
  intersection_point_t nearest_intp;
  nearest_intp.distance = max_dist;

  for(i = 0; i < scene->num_shapes; ++i)
    {
      int res;
      intersection_point_t intp;
      
      res = intersection_test(&scene->shapes[i], ray, &intp);

      if ( res && intp.distance < nearest_intp.distance )
        {
          nearest_shape = &scene->shapes[i];
          nearest_intp = intp;
          if ( exit_once_found ) break;
        }
    }/* for */

  if ( nearest_shape )
    {
      if ( out_shape )
        *out_shape = nearest_shape;
      if ( out_intp )
        *out_intp = nearest_intp;
      
      return 1;
    }
  else
    {
      return 0;
    }
}


void init_shape(shape_t* shape, shape_type st, ...)
{
  va_list args;
  va_start(args, st);

  shape->type = st;
  if ( st == ST_SPHERE )
    {
      sphere_t* sph = &shape->data.sphere;
      
      sph->center.x = va_arg(args, double);
      sph->center.y = va_arg(args, double);
      sph->center.z = va_arg(args, double);
      sph->radius   = va_arg(args, double);
    }
  else if ( st == ST_PLANE )
    {
      plane_t* plane = &shape->data.plane;
      
      plane->position.x = va_arg(args, double);
      plane->position.y = va_arg(args, double);
      plane->position.z = va_arg(args, double);

      plane->normal.x = va_arg(args, double);
      plane->normal.y = va_arg(args, double);
      plane->normal.z = va_arg(args, double);
    }
  else
    {
      fprintf(stderr, "init_shape : unknown shape type.\n");
      abort();
    }
  
  va_end(args);
}

void init_material(material_t* mat,
		   float ambR, float ambG, float ambB,
		   float difR, float difG, float difB,
		   float speR, float speG, float speB,
		   float shns)
{
  SET_COLOR(mat->ambient_ref,  ambR, ambG, ambB);
  SET_COLOR(mat->diffuse_ref,  difR, difG, difB);
  SET_COLOR(mat->specular_ref, speR, speG, speB);
  mat->shininess = shns;
}

void init_light(light_t* light, light_type lt,
		float vx, float vy, float vz,
		float illR, float illG, float illB)
{
  light->type = lt;
  SET_VECTOR(light->vector, vx, vy, vz);
  SET_COLOR(light->illuminance, illR, illG, illB);
}
