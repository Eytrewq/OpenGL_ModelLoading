#include "common.hpp"

t_mat4  create_mat4(float homogene)
{
	t_mat4		mat;

	mat.m[0][0] = 1.0f;
	mat.m[0][1] = 0.0f;
	mat.m[0][2] = 0.0f;
	mat.m[0][3] = 0.0f;
	mat.m[1][0] = 0.0f;
	mat.m[1][1] = 1.0f;
	mat.m[1][2] = 0.0f;
	mat.m[1][3] = 0.0f;
	mat.m[2][0] = 0.0f;
	mat.m[2][1] = 0.0f;
	mat.m[2][2] = 1.0f;
	mat.m[2][3] = 0.0f;
	mat.m[3][0] = 0.0f;
	mat.m[3][1] = 0.0f;
	mat.m[3][2] = 0.0f;
	mat.m[3][3] = homogene;
	return (mat);
}

t_mat4  mat4_mul(t_mat4 *a, t_mat4 *b)
{
	t_mat4		res_mat;

	for (int j = 0; j < 4; j++)
        for (int i = 0; i < 4; i++)
			res_mat.m[j][i] =
			a->m[j][0] * b->m[0][i] +
			a->m[j][1] * b->m[1][i] +
			a->m[j][2] * b->m[2][i] +
			a->m[j][3] * b->m[3][i];
	return (res_mat);
}
