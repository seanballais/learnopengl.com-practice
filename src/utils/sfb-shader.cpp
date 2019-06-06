SFB::Shader::Shader(const GLchar* vertexShaderPath, const GLchar* fragShaderPath)
{
    std::string vertexCode;
    std::string fragCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragShaderFile;

    // Ensure the ifstream objects can throw exceptions.
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertexShaderFile.open(vertexShaderPath);
        fragShaderFile.open(fragShaderFile);

        std::stringstream vertexShaderStream;
        std::stringstream fragShaderStream;
        
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragShaderStream << fragShaderStream.rdbuf();

        vertexShaderFile.close();
        fragShaderFile.close();

        vertexCode = vertexShaderStream.str();
        fragCode = fragShaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SFB::SHADER::FILE_NOT_SUCCESSFULLY_READ"
                  << std::endl;
    }

    const char* vertexShaderCode = vertexCode.c_str();
    const char* fragShaderCode = fragCode.c_str();

    unsigned int vertexShader;
    unsigned int fragShader;
    char infoLog[512];

    // Set up the vertex shader.
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);

    int vertexShaderCompileSuccess;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompileSuccess);
    if (!vertexShaderCompileSuccess) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SFB::SHADER::VERTEX_SHADER_COMPILATION_FAILED: " << infoLog << std::endl;
    }

    // Set up the fragment shader.
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragShader, 1, &fragShaderCode, NULL);
    glCompileShader(fragShader);

    int fragShaderCompileSuccess;
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &fragShaderCompileSuccess);
    if (!fragShaderCompileSuccess) {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cout << "ERROR::SFB::SHADER::FRAGMENT_SHADER_COMPILATION_FAILED: " << infoLog << std::endl;
    }

    // Set up the shader program.
    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragShader);

    glAttachShader(id, vertexShader);
    glAttachShader(id, fragShader);
    glLinkProgram(id);
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);

    int shaderProgLinkSuccess;
    glGetProgramiv(id, GL_LINK_STATUS, &shaderProgLinkSuccess);
    if (!shaderProgLinkSuccess) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SFB::SHADER::SHADER_PROGRAM_LINKING_FAILED: " << infoLog << std::endl;
    }
}

void SFB::Shader::use()
{
    glUseProgram(id);
}

void SFB::Shader::setBool(const std::string &name, bool value) const
{
    setInt(name, (int) value);
}

void SFB::Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void SFB::Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
