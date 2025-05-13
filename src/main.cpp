#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#define DBG(x) std::cout << __FILE__ << ":" << __LINE__ << " " << x << std::endl;

constexpr int WIDTH = 640;
constexpr int HEIGHT = 480;

GLFWwindow* window;

void resize_callback(GLFWwindow* window, int width, int height);
int init();
void cleanup();
void imgui_begin();
void imgui_end();

int main() {
	if (init() != 0) {
		return -1;
	}

	float bg_color[4] = {0.1, 0.4, 0.2, 1.0};
    glClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);

	double fps = 0.f;
	float last_time = glfwGetTime();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {

		double time = glfwGetTime();
		fps = fps * 0.9 + 0.1 / (time - last_time);
		last_time = time;

		
        glClear(GL_COLOR_BUFFER_BIT);

		imgui_begin();

		ImGui::ColorPicker4("Choose bgcolor:", bg_color);
		glClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);

		ImGui::Text("fps: %.2f", fps);
			
		imgui_end();

        glfwSwapBuffers(window);


        glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
    }
	
	cleanup();
	return 0;
}

void imgui_begin() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void imgui_end() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void resize_callback(GLFWwindow* window, int width, int height) {
	// glViewport(0, 0, width, height);
	// DBG("window resized to " << width << "x" << height);
}

int init() {
    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "Game", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

	glfwSetFramebufferSizeCallback(window, resize_callback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        DBG("failed to initialize glad");
        return -1;
    }

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

    DBG("vendor: " << glGetString(GL_VENDOR) << 
		"\nversion: " << glGetString(GL_VERSION) << 
		"\nshader: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << 
		"\nrenderer: " << glGetString(GL_RENDERER) << 
		"\nimgui: " << IMGUI_VERSION <<
		"\nglfw: " << glfwGetVersionString());

	glViewport(0, 0, WIDTH, HEIGHT);

	return 0;
}

void cleanup() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}
