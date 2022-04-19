#include "common.hpp"
#include "camera.hpp"

t_env env;
float lastX = env.win.width / 2.0f;
float lastY = env.win.height / 2.0f;
bool firstMouse = true;

int main(int argc, char *argv[])
{
    if (argc != 2 && argc != 3)
        return (1);
    init(&env);
    if (argc == 3) {
        env.opt = atoi(argv[2]);
    }

	glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
    env.cam = Camera(create_vec3(0.0f, 0.0f, 8.0f));
    Shader shader("./shaders/VertexShader.glsl", "./shaders/FragmentShader.glsl");
    unsigned int programID = shader.getID();

    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	if(!loadOBJ(argv[1], &env))
        return (1);
	indexVBO(env.vertices, env.indices, env.indexed_vertices);

    create_buffer(&env);

    GLuint Texture = loadBMP_custom("./ressource/kitten.bmp");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    while (glfwGetKey(env.win.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(env.win.window) == 0 ) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

        if (env.transition != 1.0f) {
            env.transition = (env.transition < 1.0f) ? env.transition + 0.0025f * glfwGetTime() : 1.0f;
            glUniform1f(glGetUniformLocation(programID, "transition"), env.transition);
        }

		GetInputs(&env, shader);

        calcul_mvp(MatrixID, &env);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, env.buf.vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, env.buf.colorbuffer);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, env.buf.uv);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

        if (env.check.isEbo == true) {
		    glDrawElements(GL_TRIANGLES, env.indices.size(), GL_UNSIGNED_INT,(void*)0);
        } else {
            glDrawArrays(GL_TRIANGLES, 0, env.vertices.size());
        }

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        glfwSwapBuffers(env.win.window);
        glfwPollEvents();
    }

	glDeleteBuffers(1, &env.buf.vbo);
	glDeleteBuffers(1, &env.buf.colorbuffer);
	glDeleteBuffers(1, &env.buf.ebo);
    glDeleteTextures(1, &Texture);
    glDeleteVertexArrays(1, &env.buf.vao);
	glDeleteProgram(programID);
	glfwTerminate();

    return (0);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    (void)window, (void)xposIn, (void)yposIn;
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    env.cam.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    (void)window, (void)xoffset, (void)yoffset;
    env.cam.ProcessMouseScroll(static_cast<float>(yoffset));
}
