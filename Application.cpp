#include "Application.hpp"
#include <iostream>
#include <stdexcept>

// 1. The Constructor: This runs first.
// We initialize our variables here using a "Member Initializer List" (the : part).
Application::Application() 
    : m_Window(nullptr), m_Instance(VK_NULL_HANDLE) {
    // We leave this empty for now because we call our init functions in Run()
}

// 2. The Destructor: This runs last.
// This is "Manual Memory Management." C++ won't clean up Vulkan for you; 
// you must do it yourself or the GPU memory will stay "leaked."
Application::~Application() {
    cleanup();
}

void Application::initWindow() {
    // Initialize the GLFW library
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    // Tell GLFW NOT to create an OpenGL context (since we are using Vulkan)
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    
    // Disable resizing for now to keep the "Stability" high
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Create the actual window
    m_Window = glfwCreateWindow(m_Width, m_Height, m_WindowTitle.c_str(), nullptr, nullptr);

    if (!m_Window) {
        throw std::runtime_error("Failed to create GLFW window");
    }
}

void Application::initVulkan() {
    // This is where we will eventually talk to the GPU.
    // For now, we'll just print a message to show the engine is starting.
    std::cout << "Initializing Vulkan for Hatchet..." << std::endl;
}

void Application::mainLoop() {
    // This loop runs until the user clicks the 'X' on the window.
    while (!glfwWindowShouldClose(m_Window)) {
        // Check for "Events" (like mouse clicks or keyboard presses)
        glfwPollEvents();
        
        // This is where the "Dread" happens! 
        // We will put our ECS Update and Rendering code here later.
    }
}

void Application::cleanup() {
    // Destroy the window
    if (m_Window) {
        glfwDestroyWindow(m_Window);
    }

    // Terminate GLFW
    glfwTerminate();
    
    std::cout << "Engine shut down safely." << std::endl;
}

void Application::Run() {
    // The sequence of life for the engine:
    initWindow();
    initVulkan();
    mainLoop();
    // Cleanup happens automatically via the Destructor when Run() finishes
}
