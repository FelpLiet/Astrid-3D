#include "../include/shader.hpp"

GLuint loadAndCompileShader(GLenum shaderType, const std::string& filename)
{
    std::string shaderCode;
    std::ifstream shaderFile;

    // Ensure ifstream objects can throw exceptions
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // Open file
        shaderFile.open(filename);

        std::stringstream shaderStream;

        // Read file's buffer contents into stream
        shaderStream << shaderFile.rdbuf();

        // Close file handler
        shaderFile.close();

        // Convert stream into string
        shaderCode = shaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n" << e.what() << std::endl;
    }

    const char* shaderCodeCStr = shaderCode.c_str();

    // Create a shader object
    GLuint shader = glCreateShader(shaderType);

    // Attach the shader source to the shader object
    glShaderSource(shader, 1, &shaderCodeCStr, NULL);

    // Compile the shader
    glCompileShader(shader);

    // Check if compilation was successful
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}


void initShaders(GLuint &shaderProgram)
{
    GLuint vertexShader = loadAndCompileShader(GL_VERTEX_SHADER, "../shaders/vertexShader.glsl");
    GLuint fragmentShader = loadAndCompileShader(GL_FRAGMENT_SHADER, "../shaders/fragmentShader.glsl");

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Verifique se a vinculação foi bem-sucedida
    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}