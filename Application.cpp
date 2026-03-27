#include "Application.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

// 1. The Constructor
Application::Application() 
    : m_Window(nullptr), m_Instance(VK_NULL_HANDLE) {
}

// 2. The Destructor
Application::~Application() {
    cleanup();
}

void Application::initWindow() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_Window = glfwCreateWindow(m_Width, m_Height, m_WindowTitle.c_str(), nullptr, nullptr);

    if (!m_Window) {
        throw std::runtime_error("Failed to create GLFW window");
    }
}

void Application::initVulkan() {
    // --- STEP A: Create the Instance ---
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hatchet";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "HatchetEngine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_1;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan instance!");
    }

    std::cout << "Vulkan Instance created." << std::endl;

    // --- STEP B: Pick a Physical Device (GPU) ---
    uint32_t deviceCount = 0;
    // Ask Vulkan how many GPUs are in this computer
    vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("Failed to find GPUs with Vulkan support!");
    }

    // Store all found GPUs in a C++ Vector (Dynamic Array)
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(m_Instance,
