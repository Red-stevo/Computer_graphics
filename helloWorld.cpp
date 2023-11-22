#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ostream>
#include <iostream>

int main()
{
	//Initializing the glfw
	glfwInit();
	//configuring the glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Creating the window
	GLFWwindow* steve = glfwCreateWindow(800,600,"Brenda Mukami", NULL, NULL);
	if(steve == NULL)
	{
		std::cout << "Failed to create the GLFW window " << std::endl;
		glfwTerminate();
		return -1;
	}

	//checking whether glad is setup
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
    	std::cout << "Failed to initialize GLAD" << std::endl;
    	return -1;
	}

	glViewport(0,0, 700,500);

	//Define the function to set the new window size when the window is resized.
	void framebuffer_size_callback(GLFWwindow* steve, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	//glfwSetFramebufferSizeCallBack(steve, framebuffer_size_callback);
	//render loop
	while(!glfwWindowShouldClose(steve))
	{
    	glfwSwapBuffers(steve);
    	glfwPollEvents();    
	}
	glfwTerminate();
	return 0;
}
