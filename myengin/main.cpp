#define GLEW_STATIC

#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);





int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "openglwindow", NULL, NULL);

	if (window == NULL) {
		std::cout << "open window fail" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	//init glew

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "init glew fail" << std::endl;
		glfwTerminate();
		return -1;
	}


	glViewport(0, 0, 800, 600);

	while (!glfwWindowShouldClose(window)) {


		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);







		glfwSwapBuffers(window);
		glfwPollEvents();
	}






	glfwTerminate();
	return 0;
}






void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}




void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}