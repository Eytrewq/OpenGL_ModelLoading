#pragma once

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <cfloat>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "math.hpp"
#include "camera.hpp"

# define PI 3.1415926535897932384626

typedef struct s_window {
    GLFWwindow* window;
    size_t      height;
    size_t      width;
}              t_window;

typedef struct s_buffer {
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLuint colorbuffer;
    GLuint uv;
}              t_buffer;

typedef struct s_check {
    int Poly;
    bool isRotateX;
    bool isRotateY;
    bool isRotateZ;
    bool isEbo;
    int isTexture;
    bool isColorGrey;
    bool isCyl;
}              t_check;

typedef struct s_env {
    t_window                    win;
    t_buffer                    buf;
    t_mat4                      ModelMatrix;
    std::vector<t_vec3>         vertices;
    std::vector<t_vec2>         uvs;
    std::vector<t_vec3>         normals;
    std::vector<unsigned int>   indices;
    std::vector<t_vec3>         indexed_vertices;
    t_vec3                      position;
    t_vec3                      direction;
    t_vec3                      up;
    t_check                     check;
    t_vec3                      min;
    t_vec3                      max;
    Camera                      cam;
    float                       Fov;
    float                       speed_rotate;
    float                       transition;
    int                         opt;
    float                       PosMovX;
    float                       PosMovY;
    float                       PosMovZ;
}              t_env;

struct PackedVertex {
	t_vec3 position;
    bool operator<(const PackedVertex that) const {
		return memcmp((void*)this, (void*)&that, sizeof(PackedVertex)) > 0;
	};
};

// mat
t_mat4  create_mat4(float isPos);
t_mat4  mat4_mul(t_mat4 *a, t_mat4 *b);

// coordinate_systems
t_mat4  perspective(float fovy, float aspect, float near, float far);
t_mat4  lookAt(t_vec3  const & eye, t_vec3  const & center, t_vec3  const & up);
void    calcul_mvp(GLuint MatrixID, t_env *env);
void    check_rotate(t_env *env, t_mat4 *model);
void    rotate(t_mat4 *model, t_vec3 &center, float a);

// vec
t_vec3 create_vec3(double x, double y, double z);
t_vec3 my_normalize(const t_vec3 &v);
t_vec3 my_cross(const t_vec3 &x, const t_vec3 &y);
t_vec3 vec3_add(const t_vec3 &a, const t_vec3 &b);
t_vec3 vec3_mul(const t_vec3 &a, float b);
t_vec3 vec3_sub(const t_vec3 &a, const t_vec3 &b);
t_vec2 create_vec2(double x, double y);

// shader
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

// utils
double	degree_to_radian(double degree_angle);
float	my_dot(const t_vec3 &a, const t_vec3 &b);
void    translate(t_mat4 *mat, float x, float y, float z);
t_mat4    rotate_x(float a);
t_mat4    rotate_y(float a);
t_mat4    rotate_z(float a);

// init
void init_glfw();
void init_glfw_window(t_env *env);
void init_glew();
void create_buffer(t_env *env);
void init(t_env *env);
void generate_texture(t_env *env);

// control
void GetInputs(t_env *env, Shader shader);

// objloader
bool loadOBJ(const char * path, t_env *env);

// vboIndexer
bool getSimilarVertexIndex_fast(PackedVertex & packed, std::map<PackedVertex,unsigned int> & VertexToOutIndex, unsigned int & result);
void indexVBO(std::vector<t_vec3> & in_vertices,std::vector<unsigned int> & out_indices,std::vector<t_vec3> & out_vertices);

// main
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// texture
GLuint loadBMP_custom(const char * imagepath);
