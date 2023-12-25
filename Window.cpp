#include "engine.h"

void Window::events()
{
    glfwPollEvents();
}

void Window::swap_buffers(GLFWwindow* window)
{
    glfwSwapBuffers(window);
}
// ---------------------------------------------------------------------------------------------
void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void Window::glad_init()
{
    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        // Exit the program if GLAD initialization fails
        exit(EXIT_FAILURE);
    }
}

// Function to create a GLFW window and return the window pointer
GLFWwindow* Window::createWindow(int width, int height, const char* title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE /*GLFW_OPENGL_CORE_PROFILE*/);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title, NULL, NULL);

    if (window == NULL) {
        const char* error;
        glfwGetError(&error);
        std::cout << "Failed to create GLFW window" << error << std::endl;
    }
    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set the framebuffer size callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return window;
}

int Window::check_creation(GLFWwindow* window){
    if (!window) {
        // Exit the program if GLAD initialization fails
        exit(EXIT_FAILURE);
    }
    return 0;
}

//background
void Window::clear_buffer(const glm::vec4 color) {
    // Specify the color of the background
    glClearColor(color.x, color.y, color.z, color.w);
    // Clean the back buffer and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}