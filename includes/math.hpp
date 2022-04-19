#pragma once

typedef struct s_vec3 {
    float   x;
    float   y;
    float   z;
}              t_vec3;

typedef struct s_vec2 {
    float   x;
    float   y;
}              t_vec2;

typedef struct s_mat4 {
    float   m[4][4];
}              t_mat4;

// mat
t_mat4  create_mat4(float isPos);
t_mat4  mat4_mul(t_mat4 *a, t_mat4 *b);

// vec
t_vec3 create_vec3(double x, double y, double z);
t_vec3 my_normalize(const t_vec3 &v);
t_vec3 my_cross(const t_vec3 &x, const t_vec3 &y);
t_vec3 vec3_add(const t_vec3 &a, const t_vec3 &b);
t_vec3 vec3_mul(const t_vec3 &a, float b);
t_vec3 vec3_sub(const t_vec3 &a, const t_vec3 &b);
t_vec2 create_vec2(double x, double y);
