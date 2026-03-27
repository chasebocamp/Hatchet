#include <iostream>   // Allows us to print messages to the console (Input/Output Stream)
#include <stdexcept>  // Provides standard "exception" tools to handle crashes gracefully
#include <cstdlib>    // Provides EXIT_SUCCESS and EXIT_FAILURE macros

// This is a "Forward Declaration." We haven't written the Application class yet, 
// but we're telling the compiler "Trust me, it's coming."
#include "core/Application.hpp" 

int main() {
    // 1. Create an instance of our Application. 
    // In C++, "Application app;" allocates memory for our game engine object.
    Application app;

    // 2. The "Try-Catch" Block: This is crucial for stability.
    // Vulkan is strict. If an old graphics card can't handle a shader, 
    // it will "throw" an error. We "catch" it here so the game closes 
    // with a helpful message instead of just vanishing.
    try {
        // This is the heartbeat of your game. 
        // We go inside this function and stay there until the boy dies or the game is closed.
        app.Run();
    } 
    catch (const std::exception& e) {
        // 'std::cerr' is the "Character Error" stream. It's like 'cout' but for bad news.
        // 'e.what()' extracts the specific reason why the engine crashed.
        std::cerr << "CRITICAL ENGINE ERROR: " << e.what() << std::endl;
        
        // Return 1 to tell the Windows/Linux OS that the program crashed.
        return EXIT_FAILURE; 
    }

    // 3. If we made it here, the game closed perfectly.
    // Return 0 to tell the OS everything went fine.
    return EXIT_SUCCESS;
}
