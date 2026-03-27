#pragma once // This "Header Guard" prevents the file from being included twice, 
             // which would cause a "Redefinition Error" and crash the compiler.

// 1. Include necessary tools for the "Blueprint"
#include <vulkan/vulkan.h> // The core Vulkan API
#include <string>          // For handling text (like the Window Title)

// Forward declarations: We tell the compiler these exist so we don't have to 
// include their massive files here. This makes compiling much faster.
struct GLFWwindow; 

class Application {
public:
    // The "Constructor": This runs the very moment you write "Application app;" in main.cpp
    Application();

    // The "Destructor": This runs automatically when the game closes.
    // This is where we safely "kill" Vulkan and the Window to prevent memory leaks.
    ~Application();

    // The main entry point for the game logic.
    void Run();

private:
    // 2. Internal Setup Steps (The "Private" Kitchen)
    // We mark these 'private' so other parts of the code can't accidentally 
    // mess with the engine's guts.
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();

    // 3. Member Variables (The "Ingredients")
    // In C++, we often prefix private variables with 'm_' (meaning 'Member')
    // so we know exactly which variables belong to the class.
    
    GLFWwindow* m_Window = nullptr; // A pointer to our OS window (Windows/Linux/Mac)
    
    // The "Heart" of Vulkan: The Instance
    // This is the connection between our 'Hatchet' code and the Graphics Driver.
    VkInstance m_Instance;

    // Window Settings
    const uint32_t m_Width = 1280;
    const uint32_t m_Height = 720;
    const std::string m_WindowTitle = "Hatchet - Survival Horror";
};
