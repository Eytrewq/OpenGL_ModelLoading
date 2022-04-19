#include "common.hpp"

t_vec3 create_vec3(double x, double y, double z)
{
    t_vec3 vec;

    vec.x = x;
    vec.y = y;
    vec.z = z;

    return(vec);
}

t_vec2 create_vec2(double x, double y)
{
    t_vec2 vec;

    vec.x = x;
    vec.y = y;

    return(vec);
}

t_vec3 my_normalize(const t_vec3 &v)
{
   float length_of_v = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
   return create_vec3(v.x / length_of_v, v.y / length_of_v, v.z / length_of_v);
}

t_vec3 vec3_sub(const t_vec3 &a, const t_vec3 &b)
{
    return (create_vec3(a.x-b.x,
    a.y-b.y,
    a.z-b.z));
}

t_vec3 vec3_add(const t_vec3 &a, const t_vec3 &b)
{
    return (create_vec3(a.x+b.x,
    a.y+b.y,
    a.z+b.z));
}

t_vec3 vec3_mul(const t_vec3 &a, float b)
{
    return (create_vec3(a.x*b,
    a.y*b,
    a.z*b));
}

t_vec3 my_cross(const t_vec3 &a, const t_vec3 &b)
{
    return (create_vec3(a.y*b.z - b.y*a.z,
    a.z*b.x - b.z*a.x,
    a.x*b.y - b.x*a.y));
}
