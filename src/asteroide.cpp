#include "../include/asteroide.hpp"

extern GLuint shaderProgram;

namespace spc
{
    void asteroide::draw()
{
    // Use the shader program
    glUseProgram(shaderProgram);

    glm::vec3 posicaoAjustada = position + 0.1f * direction;

    // Set the transformation matrix
    glm::mat4 model = glm::translate(glm::mat4(1.0f), posicaoAjustada);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

    // Set the light parameters
    glUniform3fv(glGetUniformLocation(shaderProgram, "light.position"), 1, glm::value_ptr(light_position));
    glUniform3fv(glGetUniformLocation(shaderProgram, "light.ambient"), 1, glm::value_ptr(light_ambient));
    glUniform3fv(glGetUniformLocation(shaderProgram, "light.diffuse"), 1, glm::value_ptr(light_diffuse));
    glUniform3fv(glGetUniformLocation(shaderProgram, "light.specular"), 1, glm::value_ptr(light_specular));

    // Draw the VAO
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);

    // Don't forget to reset the shader program
    glUseProgram(0);
}
    void asteroide::updatePointStatus()
    {
        auto currentTime = std::chrono::steady_clock::now();
        if (drawPoint && std::chrono::duration_cast<std::chrono::seconds>(currentTime - pointTimerStart).count() >= 1)
        {
            drawPoint = false;
        }
        position += direction * speed * deltaTime();
        // std::cout << position.x << " " << position.y << " " << position.z << std::endl;
    }

    bool asteroide::isAlive() const
    {
        return position.y > 0;
    }

    bool asteroide::isColliding(const glm::vec3 &position, float radius) const
    {
        return glm::distance(this->position, position) <= this->radius + radius;
    }

    void asteroide::updateVertexBuffer()
    {
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        std::vector<glm::vec3> vertexData = generateVertexData();
        vertexCount = vertexData.size();

        glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(glm::vec3), vertexData.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    std::vector<glm::vec3> asteroide::generateVertexData()
    {
        std::vector<glm::vec3> vertexData;

        // Define the number of segments and slices to create the sphere
        int segments = 16;
        int slices = 16;

        // Generate the vertices for the sphere
        for (int i = 0; i <= slices; ++i)
        {
            float v = i / static_cast<float>(slices);
            float phi = v * glm::pi<float>();

            for (int j = 0; j <= segments; ++j)
            {
                float u = j / static_cast<float>(segments);
                float theta = u * (glm::pi<float>() * 2);

                // Calculate the vertex position
                glm::vec3 vertex;
                vertex.x = std::cos(theta) * std::sin(phi);
                vertex.y = std::cos(phi);
                vertex.z = std::sin(theta) * std::sin(phi);

                vertexData.push_back(vertex * radius);
            }
        }

        return vertexData;
    }

    void verificaAsteroides(std::vector<spc::asteroide *> &asteroides)
    {
        for (auto it = asteroides.begin(); it != asteroides.end();)
        {
            it[0]->updatePointStatus();
            if (!it[0]->isAlive())
            {
                it = asteroides.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void drawAsteroides(std::vector<spc::asteroide *> &asteroides)
    {
        for (auto &asteroide : asteroides)
        {
            asteroide->draw();
        }
    }

    void gerarAsteroide(std::vector<spc::asteroide *> &asteroides)
    {
        // ramdom x position between -16 and 16
        float x = (float)(rand() % 32) - 16.0f;
        // random y position between 12 and 16
        float y = (float)(rand() % 4) + 12.0f;
        // random z position between 0 and 16
        float z = (float)(rand() % 16);
        glm::vec3 pontoPartida = glm::vec3(x, y, z);
        glm::vec3 pontoFinal = glm::vec3(10, 0, -10);
        glm::vec3 newDirection = glm::normalize(pontoFinal - pontoPartida);

        // glm::vec3 pontoPartida = glm::vec3(20, 10, 40);
        // glm::vec3 pontoFinal = glm::vec3(10, 0, -10);
        // glm::vec3 newDirection = glm::normalize(pontoFinal - pontoPartida);
        spc::asteroide *novoAsteroide = new spc::asteroide(pontoPartida, newDirection);
        asteroides.push_back(novoAsteroide);
    }
}