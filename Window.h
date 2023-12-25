#pragma once
class Window
{
public:
    //Creates the window
    GLFWwindow* createWindow(int width, int height, const char* title);
    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    void events();
    void swap_buffers(GLFWwindow* window);
    // exits program if a window failed to create
    int check_creation(GLFWwindow* window);
    void clear_buffer(const glm::vec4 color);

    //glad
    void glad_init();
};

