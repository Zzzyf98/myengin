#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"Shader.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

float vertics[] = {
	0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,1.0f, // 右上角
	0.5f, -0.5f, 0.0f,0.0f, 1.0f, 0.0f, 1.0f,0.0f, // 右下角
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,0.0f,0.0f,// 左下角
	-0.5f, 0.5f, 0.0f ,0.0f, 0.0f, 1.0f ,0.0f,1.0f, // 左上角
};

unsigned int indices[] = { // 注意索引从0开始! 
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};





int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//------------------------------------------
	//create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "openglwindow", NULL, NULL);

	if (window == NULL) {
		std::cout << "open window fail" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//------------------------------------------
	//init glew
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "init glew fail" << std::endl;
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 800, 600);

	Shader* myShader = new Shader("vertexSourceCode.txt", "fragmentSourceCode.txt");

	//------------------------------------------

	



	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); //1 是 缓冲ID
	glGenBuffers(1, &EBO);


	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //GL_ARRAY_BUFFER是唯一的
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertics), vertics, GL_STATIC_DRAW);//VBO内容：全是数据顶点
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //VAO内容：告诉你几个为一组
	glEnableVertexAttribArray(0);//激活location = 0 号位置
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);//激活location = 1 号位置
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);//激活location = 2 号位置


	unsigned int texture0;
	unsigned int texture1;

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	glGenTextures(1, &texture0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);



	
	unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	glGenTextures(1, &texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data2);










	







	while (!glfwWindowShouldClose(window)) {


		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		myShader->use();
		glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);
		glUniform1i(glGetUniformLocation(myShader->ID, "ourFace"), 1);



		//float timeValue = glfwGetTime();
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(myShader->ID, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);//4维数字



		glBindVertexArray(VAO);// seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);



		glfwSwapBuffers(window);
		glfwPollEvents();
	}





	//------------------------------------------
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