#include "common.hpp"

t_mat4  perspective(float fovy, float aspect, float near, float far)
{
    t_mat4 res = create_mat4(0.0f);

    float halfFovy = tanf(degree_to_radian(fovy) / 2.0f);

	res.m[0][0] = 1.0f / (aspect * halfFovy);
	res.m[1][1] = 1.0f / (halfFovy);
	res.m[2][2] = -(far + near) / (far - near);
	res.m[2][3] = -1.0;
	res.m[3][2] = -(2.0f * far * near) / (far - near);
	return (res);
}


t_mat4  lookAt(t_vec3  const & eye, t_vec3  const & center, t_vec3  const & up)
{
    t_vec3  cameraDirection = my_normalize(vec3_sub(center, eye));
    t_vec3  cameraUp = my_normalize(up);
    t_vec3  cameraRight = my_normalize(my_cross(cameraDirection, cameraUp));

    cameraUp = my_cross(cameraRight, cameraDirection);

    t_mat4 Result = create_mat4(1.0f);
    Result.m[0][0] = cameraRight.x;
    Result.m[1][0] = cameraRight.y;
    Result.m[2][0] = cameraRight.z;
    Result.m[0][1] = cameraUp.x;
    Result.m[1][1] = cameraUp.y;
    Result.m[2][1] = cameraUp.z;
    Result.m[0][2] =-cameraDirection.x;
    Result.m[1][2] =-cameraDirection.y;
    Result.m[2][2] =-cameraDirection.z;
    Result.m[3][0] =-my_dot(cameraRight, eye);
    Result.m[3][1] =-my_dot(cameraUp, eye);
    Result.m[3][2] = my_dot(cameraDirection, eye);
    return Result;
}

void    check_rotate(t_env *env, t_mat4 *model)
{
    if (env->check.isRotateX || env->check.isRotateY || env->check.isRotateZ) {
        t_mat4 x = rotate_x(env->speed_rotate * degree_to_radian(-45.0f) * env->check.isRotateX);
        t_mat4 y = rotate_y(env->speed_rotate * degree_to_radian(-45.0f) * env->check.isRotateY);
        t_mat4 z = rotate_z(env->speed_rotate * degree_to_radian(-45.0f) * env->check.isRotateZ);
        t_mat4 xy = mat4_mul(&y, &x);
        t_mat4 xyz = mat4_mul(&z, &xy);
        *model = mat4_mul(model, &xyz);
    }
}

t_mat4 rotate_x(float a)
{
    t_mat4 mat = create_mat4(1.0f);
    mat.m[1][1] = cos(a);
    mat.m[1][2] = -sin(a);
    mat.m[2][1] = sin(a);
    mat.m[2][2] = cos(a);
    return (mat);
}

t_mat4 rotate_y(float a)
{
    t_mat4 mat = create_mat4(1.0f);
    mat.m[0][0] = cos(a);
    mat.m[0][2] = sin(a);
    mat.m[2][0] = -sin(a);
    mat.m[2][2] = cos(a);
    return (mat);
}

t_mat4 rotate_z(float a)
{
    t_mat4 mat = create_mat4(1.0f);
    mat.m[0][0] = cos(a);
    mat.m[1][0] = -sin(a);
    mat.m[0][1] = sin(a);
    mat.m[1][1] = cos(a);
    return (mat);
}

void    calcul_mvp(GLuint MatrixID, t_env *env)
{
    t_mat4 ProjectionMatrix = perspective(env->cam.Fov, 4.0f / 3.0f, 0.1f, 100.0f);
    t_mat4 ViewMatrix = env->cam.GetViewMatrix();

    check_rotate(env, &env->ModelMatrix);
    translate(&env->ModelMatrix, env->PosMovX, env->PosMovY, env->PosMovZ);

    t_mat4 MV = mat4_mul(&env->ModelMatrix, &ViewMatrix);
    t_mat4 MVP =  mat4_mul(&MV, &ProjectionMatrix);

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP.m[0][0]);
}
