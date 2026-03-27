#pragma once

// 1. Core Headers
#include <vulkan/vulkan.h> // The main Vulkan API
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>    // GLFW for windowing, configured to work with Vulkan

// 2. Standard Library Headers
#include <string>          // For the window title
#include <vector>          // For storing lists of images and buffers
#include <optional>        // For handling "maybe" values like GPU queue indices

// 3. Helper Structure: This identifies which "Command Lines" (Queues) the GPU has.
struct QueueFamilyIndices {
    // std::optional means this might be empty if the GPU doesn't support graphics.
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily; // The queue that can actually "show" images to a window

    // A helper to check if we found everything we need.
    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

class Application {
public:
    // Constructor: Sets up initial null values
    Application();

    // Destructor: Cleans up all GPU memory
    ~Application();

    // The main entry point called by main.cpp
    void Run();

private:
    // --- CORE STAGES ---
    void initWindow();    // Opens the OS window
    void initVulkan();    // Powers on the GPU and links it to the window
    void createSwapChain(); // Sets up the "Frame Buffer" system
    void createImageViews(); // Tells Vulkan how to interpret the Swap Chain images
    void mainLoop();      // Runs every frame (Update & Render)
    void cleanup();       // Shuts down everything in reverse order

    // --- HELPER FUNCTIONS ---
    // These help us pick the best hardware for "Hatchet"
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    // --- MEMBER VARIABLES (The Engine's "Guts") ---
    
    // Window variables
    GLFWwindow* m_Window = nullptr;
    const uint32_t m_Width = 1280;
    const uint32_t m_Height = 720;
    const std::string m_WindowTitle = "Hatchet - Survival Horror";

    // Vulkan Instance & Surface (The "Table" and the "Canvas")
    VkInstance m_Instance = VK_NULL_HANDLE;
    VkSurfaceKHR m_Surface = VK_NULL_HANDLE;

    // Physical & Logical Devices (The "Hard Drive" and the "Power Switch")
    VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
    VkDevice m_Device = VK_NULL_HANDLE;

    // Queues (The "Command Lines")
    VkQueue m_GraphicsQueue = VK_NULL_HANDLE;
    VkQueue m_PresentQueue = VK_NULL_HANDLE;

    // Swap Chain (The "Double Buffer" system)
    // This is a list of images that cycle through: [Showing] -> [Drawing] -> [Wait]
    VkSwapchainKHR m_SwapChain = VK_NULL_HANDLE;
    std::vector<VkImage> m_SwapChainImages; // The actual handles to the image memory
    VkFormat m_SwapChainImageFormat;        // e.g., B8G8R8A8_SRGB (Standard color format)
    VkExtent2D m_SwapChainExtent;           // The resolution (width/height) of the images

    // Image Views (The "Lenses")
    // A VkImage is just raw data. An ImageView tells Vulkan: "Treat this as a 2D Color Texture."
    std::vector<VkImageView> m_SwapChainImageViews;
};
