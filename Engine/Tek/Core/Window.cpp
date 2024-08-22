#include "Application.hpp"
#include "Window.hpp"

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    std::shared_ptr<EditorCamera> camera = EditorCamera::GetInstance();
    camera->ProcessShiftKey(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, Application::deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, Application::deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, Application::deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, Application::deltaTime);
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera->ProcessKeyboard(UP, Application::deltaTime);
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera->ProcessKeyboard(DOWN, Application::deltaTime);
    if(glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS){
        if(reloadedShaders)
            return;
        SceneManager::GetActiveScene()->renderManager->HotReloadShaders();
        reloadedShaders = true;
    }
    else{
        reloadedShaders = false;
    }

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        if(buttonPressed)
            return;
        glfwSetInputMode(window, GLFW_CURSOR, mouseLocked ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
        mouseLocked = !mouseLocked;
        firstMouse = true;
        buttonPressed = true;
    }
    else{
        buttonPressed = false;
    }

}

void Window::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (!win->mouseLocked)
        return;

    auto xpos = static_cast<float>(xposIn);
    auto ypos = static_cast<float>(yposIn);

    if (win->firstMouse) {
        win->lastX = xpos;
        win->lastY = ypos;
        win->firstMouse = false;
    }

    float xoffset = xpos - win->lastX;
    float yoffset = win->lastY - ypos; // reversed since y-coordinates go from bottom to top

    win->lastX = xpos;
    win->lastY = ypos;

    EditorCamera::GetInstance()->ProcessMouseMovement(xoffset, yoffset);
}

void Window::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    EditorCamera::GetInstance()->ProcessMouseScroll(static_cast<float>(yoffset));
}

void Window::debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                          const void *userParam) {
    // Handle the debug message (e.g., log it, display it, etc.)
    if (id == 131185 || id == 131204) // Filter out annoying Nvidia message of: Buffer you made will use VRAM because you told us that you want it to allocate VRAM.
        return;

    printf("OpenGL Debug Message (id: %d): %s\n", id, message);
}

Window::Window(int width, int height, const char* title) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    m_Window = glfwCreateWindow(width, height, "TekEngine", NULL, NULL);

    if (m_Window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glfwSetWindowUserPointer(m_Window, this);

    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_STENCIL_TEST);

    glEnable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugMessageCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(m_Window, Window::mouse_callback);

    glfwSetScrollCallback(m_Window, scroll_callback);
}

Window::~Window() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(m_Window);
}

void Window::PollEvents() {
    processInput(m_Window);
}

void Window::SwapBuffers() const {
    glfwSwapBuffers(m_Window);
}
