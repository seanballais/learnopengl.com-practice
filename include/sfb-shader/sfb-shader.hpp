#ifndef SFB_SHADER_HPP
#define SFB_SHADER_HPP

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace SFB {
    class Shader
    {
    public:
        unsigned int id; // Shader program ID

        // Reads and builds the vertex and fragment shaders.
        Shader(const GLchar* vertexShaderPath, const GLchar* fragShaderPath);

        // Use/activate the shader.
        void use();

        // Utility uniform functions.
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
    }
}

#endif
