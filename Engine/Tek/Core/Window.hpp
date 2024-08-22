#ifndef WINDOW_HPP
#define WINDOW_HPP

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    bool ShouldClose() const;
    void PollEvents() ;
    void SwapBuffers() const;

private:
    GLFWwindow* m_Window;

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    void processInput(GLFWwindow *window);

    bool reloadedShaders;
    bool mouseLocked;

    static void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);

    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

    static void
    debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                         const void *userParam);


    bool firstMouse;
    bool buttonPressed;
    float lastX;
    float lastY;
};


#endif //WINDOW_HPP
