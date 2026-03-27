#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <string>

class Shader {
public:
    // This helper function reads a compiled shader file (.spv) from your disk
    static std::vector<char> ReadFile(const std::string& filename);

    // This creates a "Module" which Vulkan uses to execute the shader code
    static VkShaderModule CreateShaderModule(VkDevice device, const std::vector<char>& code);
};
