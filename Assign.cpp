#include <glad/glad.h>
#include <GLFW/glfw3.h>

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 700;

unsigned vao;
unsigned int shader_program;

const char* vertex_shader_source =
                "#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"layout (location = 1) in vec3 color;\n"
		"out vec3 vertexColor;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = vec4(position, 1.0);\n"
		"    vertexColor = color;\n"
		"}\n";

const char* fragment_shader_source =
		"#version 330 core\n"
		"out vec4 fragColor;\n"
		"in vec3 vertexColor;\n"
		"void main()\n"
		"{\n"
		"     fragColor = vec4(vertexColor, 1.0f);\n"
		"}\n";

void setup_shader() 
{
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void setup_data() 
{
	float vertices[] = {
	  // For visualization: each row is a vertex.
	  // Each vertex has position [x, y, z] and color [r, g, b]
	  -0.5f, -0.5f, 0.0f, 1.0, 0.0, 0.0,   // red color for this vertex
	   0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0,   // green color
	   0.0f,  0.5f, 0.0f, 0.0, 0.0, 1.0    // blue color for our top vertex
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

int main(void)
{
        GLFWwindow* window;

        if ( ! glfwInit() )
        {
            return -1;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "A simple Coloured Triangle", NULL, 0);

        if ( ! window )
        {
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(window);

        if ( ! gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) )
        {
            glfwTerminate();
            return -1;
        }

        setup_shader();
        setup_data();

        while ( ! glfwWindowShouldClose(window) )
        {
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(shader_program);
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);

            glfwPollEvents();
        }

        glfwTerminate();

        return 0;
}
