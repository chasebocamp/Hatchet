#include "Shader.hpp"
#include "Logger.hpp"
#include <fstream>

std::vector<char> Shader::ReadFile(const std::string& filename) {
    // 1. Open the file starting at the end (ate) and in binary mode
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        HT_ERROR("Failed to open shader file: {0}", filename);
        throw std::runtime_error("failed to open file!");
    }

    // 2. Because we started at the end, 'tellg' tells us the file size
    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    // 3. Move back to the beginning and read the whole thing into our buffer
    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    return buffer;
}

VkShaderModule Shader::CreateShaderModule(VkDevice device, const std::vector<char>& code) {
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    
    // Vulkan expects a pointer to 'uint32_t' but our buffer is 'char'
    // This 'reinterpret_cast' is a C++ way of saying "Trust me, treat this as a different type"
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create shader module!");
    }

    return shaderModule;
}
