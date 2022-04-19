#include "common.hpp"

double	degree_to_radian(double degree)
{
	return (degree * ((static_cast<float>(PI)) / 180.0));
}

float	my_dot(const t_vec3 &a, const t_vec3 &b)
{
	return (a.x*b.x + a.y*b.y + a.z*b.z);
}

void    translate(t_mat4 *mat, float x, float y, float z)
{
    mat->m[3][0] = x;
    mat->m[3][1] = y;
    mat->m[3][2] = z;
}
