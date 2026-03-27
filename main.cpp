#include "Application.hpp"
#include "Logger.hpp" // Our new logging system
#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main() {
    // 1. Initialize the Logger first so we can record the boot process
    Logger::Init();
    HT_INFO("Hatchet Engine version 0.1 starting up...");

    // 2. Create the Application object on the "Stack"
    // This calls the Constructor in Application.cpp
    Application app;

    try {
        // 3. Enter the engine's lifecycle
        app.Run();
    } 
    catch (const std::exception& e) {
        // 4. If any part of initVulkan() or the mainLoop() fails,
        // it "throws" to here. We log it and exit safely.
        HT_ERROR("FATAL ENGINE ERROR: {0}", e.what());
        return EXIT_FAILURE;
    }

    // 5. If Run() finishes normally (user closed the window),
    // the 'app' variable goes out of scope and its Destructor clears the GPU memory.
    HT_INFO("Hatchet Engine shut down safely.");
    
    return EXIT_SUCCESS;
}
