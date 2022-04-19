#include "common.hpp"

void GetInputs(t_env *env, Shader shader)
{
	static double lastTime = glfwGetTime();
	static double lastTimeInput = glfwGetTime();
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	float cooldown = float(currentTime - lastTimeInput);

	if (glfwGetKey( env->win.window, GLFW_KEY_UP ) == GLFW_PRESS)
		env->cam.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey( env->win.window, GLFW_KEY_DOWN ) == GLFW_PRESS)
		env->cam.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey( env->win.window, GLFW_KEY_RIGHT ) == GLFW_PRESS)
		env->cam.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey( env->win.window, GLFW_KEY_LEFT ) == GLFW_PRESS)
		env->cam.ProcessKeyboard(LEFT, deltaTime);
	
	if (glfwGetKey( env->win.window, GLFW_KEY_W ) == GLFW_PRESS)
		env->PosMovY += 0.03f;
	if (glfwGetKey( env->win.window, GLFW_KEY_S ) == GLFW_PRESS)
		env->PosMovY -= 0.03f;
	if (glfwGetKey( env->win.window, GLFW_KEY_D ) == GLFW_PRESS)
		env->PosMovX += 0.03f;
	if (glfwGetKey( env->win.window, GLFW_KEY_A ) == GLFW_PRESS)
		env->PosMovX -= 0.03f;
	if (glfwGetKey( env->win.window, GLFW_KEY_Q ) == GLFW_PRESS)
		env->PosMovZ -= 0.03f;
	if (glfwGetKey( env->win.window, GLFW_KEY_E ) == GLFW_PRESS)
		env->PosMovZ += 0.03f;

	if (glfwGetKey( env->win.window, GLFW_KEY_P ) == GLFW_PRESS && cooldown >= 0.2f) {
		env->check.Poly++;
		if (env->check.Poly > 2)
			env->check.Poly = 0;
		if (env->check.Poly == 2)
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		else if (env->check.Poly == 1)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else if (env->check.Poly == 0)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (glfwGetKey( env->win.window, GLFW_KEY_O ) == GLFW_PRESS && cooldown >= 0.2f) {
		env->check.isEbo = !env->check.isEbo;
		if (env->check.isEbo) {
			glBindBuffer(GL_ARRAY_BUFFER, env->buf.vbo);
        	glBufferData(GL_ARRAY_BUFFER, env->indexed_vertices.size() * sizeof(t_vec3), &env->indexed_vertices[0], GL_STATIC_DRAW);
		} else {
			glBindBuffer(GL_ARRAY_BUFFER, env->buf.vbo);
            glBufferData(GL_ARRAY_BUFFER, env->vertices.size() * sizeof(t_vec3), &env->vertices[0], GL_STATIC_DRAW);
		}
	}

	if (glfwGetKey( env->win.window, GLFW_KEY_R ) == GLFW_PRESS && cooldown >= 0.2f) {
		env->ModelMatrix = create_mat4(1.0f);
		env->PosMovX = env->PosMovY = env->PosMovZ = 0.0f;
		env->check.isRotateX = false;
		env->check.isRotateY = true;
		env->check.isRotateZ = false;
	}
	if (glfwGetKey( env->win.window, GLFW_KEY_X ) == GLFW_PRESS && cooldown >= 0.2f)
		env->check.isRotateX = !env->check.isRotateX;
	if (glfwGetKey( env->win.window, GLFW_KEY_C ) == GLFW_PRESS && cooldown >= 0.2f)
		env->check.isRotateY = !env->check.isRotateY;
	if (glfwGetKey( env->win.window, GLFW_KEY_V ) == GLFW_PRESS && cooldown >= 0.2f)
		env->check.isRotateZ = !env->check.isRotateZ;
	if (glfwGetKey( env->win.window, GLFW_KEY_T ) == GLFW_PRESS && cooldown >= 0.2f) {
		if (env->check.isTexture == 1) env->check.isTexture = 2;
		else if (env->check.isTexture == 2) env->check.isTexture = 1;
		else if (env->check.isTexture == 0) env->check.isTexture = 1;
		glUniform1i(glGetUniformLocation(shader.getID(), "isTex"), env->check.isTexture);
		env->transition = 0.0f;
		glUniform1f(glGetUniformLocation(shader.getID(), "transition"), env->transition);
	}
	if (glfwGetKey( env->win.window, GLFW_KEY_G ) == GLFW_PRESS && cooldown >= 0.2f) {
		env->check.isColorGrey = !env->check.isColorGrey;
		shader.setBool("isColorGrey", env->check.isColorGrey);
	}
	if (glfwGetKey( env->win.window, GLFW_KEY_F ) == GLFW_PRESS && cooldown >= 0.2f)
		env->speed_rotate = -env->speed_rotate;
	if (glfwGetKey( env->win.window, GLFW_KEY_1 ) == GLFW_PRESS && cooldown >= 0.2f) {
		env->check.isCyl = !env->check.isCyl;
		shader.setBool("isCyl", env->check.isCyl);
	}
	
	if (glfwGetKey( env->win.window, GLFW_KEY_P ) == GLFW_PRESS ||
	glfwGetKey( env->win.window, GLFW_KEY_O ) == GLFW_PRESS ||
	glfwGetKey( env->win.window, GLFW_KEY_X ) == GLFW_PRESS ||
	glfwGetKey( env->win.window, GLFW_KEY_C ) == GLFW_PRESS ||
	glfwGetKey( env->win.window, GLFW_KEY_V ) == GLFW_PRESS ||
	glfwGetKey( env->win.window, GLFW_KEY_T ) == GLFW_PRESS ||
	glfwGetKey( env->win.window, GLFW_KEY_F ) == GLFW_PRESS ||
	glfwGetKey( env->win.window, GLFW_KEY_R ) == GLFW_PRESS ||
	glfwGetKey( env->win.window, GLFW_KEY_1 ) == GLFW_PRESS ||
	glfwGetKey( env->win.window, GLFW_KEY_G ) == GLFW_PRESS)
		lastTimeInput = currentTime;

	lastTime = currentTime;
}
