#include "common.hpp"

void init_glfw() {
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit(1);
    }
    glfwWindowHint(GLFW_SAMPLES, 8);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void init_glfw_window(t_env *env) {
    env->win.height = 768;
    env->win.width = 1024;
    env->win.window = glfwCreateWindow( env->win.width, env->win.height, "SCOP", NULL, NULL);
    if( env->win.window == NULL ){
        fprintf( stderr, "Failed to open GLFW window.\n" );
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(env->win.window);
    glfwSetInputMode(env->win.window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(env->win.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(env->win.window, mouse_callback);
    glfwSetScrollCallback(env->win.window, scroll_callback);
}

void init_glew() {
    glewExperimental=true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwTerminate();
        exit(1);
    }
}

void init(t_env *env) {
    srand(time(NULL));
    init_glfw();
    init_glfw_window(env);
    init_glew();
    env->ModelMatrix = create_mat4(1.0f);
    env->position = create_vec3( 5, 0, 0 );
    env->max = create_vec3( 0, 0, 0 );
    env->min = create_vec3( FLT_MIN, FLT_MIN, FLT_MIN );
    env->check.Poly = 0;
    env->check.isRotateX = false;
    env->check.isRotateY = true;
    env->check.isRotateZ = false;
    env->check.isEbo = false;
    env->check.isCyl = false;
    env->check.isTexture = 0;
    env->check.isColorGrey = false;
    env->speed_rotate = 0.02f;
    env->opt = 0;
    env->transition = 0.0f;
    env->PosMovX = 0.0f;
    env->PosMovY = 0.0f;
    env->PosMovZ = 0.0f;
}

void generate_texture(t_env *env)
{
    // GENERATE TEXTURE
    if (env->opt == 0) {
        env->uvs.clear();
        for (unsigned int i = 0; i < env->vertices.size(); i++) {
            env->uvs.push_back(create_vec2(0.0f, 0.0f));
            env->uvs.push_back(create_vec2(0.0f, 1.0f));
            env->uvs.push_back(create_vec2(1.0f, 1.0f));
            env->uvs.push_back(create_vec2(1.0f, 1.0f));
            env->uvs.push_back(create_vec2(1.0f, 0.0f));
            env->uvs.push_back(create_vec2(0.0f, 0.0f));
        }
    }
    glGenBuffers(1, &env->buf.uv);
    glBindBuffer(GL_ARRAY_BUFFER, env->buf.uv);
    glBufferData(GL_ARRAY_BUFFER, env->uvs.size() * sizeof(t_vec2), &env->uvs[0], GL_STATIC_DRAW);
}

void create_buffer(t_env *env)
{
    // GENERATE COLOR
    std::vector<GLfloat> g_color_buffer_data;
    for (unsigned int v = 0; v < env->vertices.size(); v++) {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        g_color_buffer_data.push_back(r);
        g_color_buffer_data.push_back(g);
        g_color_buffer_data.push_back(b);
        g_color_buffer_data.push_back(r);
        g_color_buffer_data.push_back(g);
        g_color_buffer_data.push_back(b);
        g_color_buffer_data.push_back(r);
        g_color_buffer_data.push_back(g);
        g_color_buffer_data.push_back(b);
    }

    glGenVertexArrays(1, &env->buf.vao);
    glBindVertexArray(env->buf.vao);

    glGenBuffers(1, &env->buf.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, env->buf.vbo);
    glBufferData(GL_ARRAY_BUFFER, env->vertices.size() * sizeof(t_vec3), &env->vertices[0] , GL_STATIC_DRAW);

    glGenBuffers(1, &env->buf.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->buf.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, env->indices.size() * sizeof(unsigned int), &env->indices[0] , GL_STATIC_DRAW);

    glGenBuffers(1, &env->buf.colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, env->buf.colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, g_color_buffer_data.size() * sizeof(GLfloat), &g_color_buffer_data[0], GL_STATIC_DRAW);

    generate_texture(env);
}
