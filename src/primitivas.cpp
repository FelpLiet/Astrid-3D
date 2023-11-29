#include "../include/primitivas.hpp"
namespace spc
{
    void drawSphere(GLfloat raio, GLuint nStacks, GLuint nSectors, GLuint texture,
                    std::vector<std::vector<glm::vec3>> &pontos,
                    std::vector<std::vector<glm::vec2>> &texCoords)
    {
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D, texture);

        const GLfloat TWO_PI = 2 * M_PI;

        GLfloat deltaPhi = M_PI / nStacks;
        GLfloat deltaTheta = TWO_PI / nSectors;

        for (GLuint i = 0; i <= nStacks; i++)
        {
            GLfloat phi = -M_PI_2 + i * deltaPhi;
            GLfloat r = raio * cos(phi);
            GLfloat y = raio * sin(phi);

            std::vector<glm::vec3> pts;
            std::vector<glm::vec2> texs;

            for (GLuint j = 0; j <= nSectors; j++)
            {
                GLfloat theta = j * deltaTheta;
                GLfloat x = r * sin(theta);
                GLfloat z = r * cos(theta);

                GLfloat s = theta / TWO_PI;
                GLfloat t = phi / M_PI + 0.5;

                pts.push_back(glm::vec3(x, y, z));
                texs.push_back(glm::vec2(s, t));
            } // next j
            pontos.push_back(pts);
            texCoords.push_back(texs);
        } // next i
        ;
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        for (GLuint i = 0; i < nStacks; i++)
        {
            glBegin(GL_TRIANGLE_STRIP);

            for (GLuint j = 0; j <= nSectors; j++)
            {
                glTexCoord2fv(glm::value_ptr(texCoords[i][j]));
                glVertex3fv(glm::value_ptr(pontos[i][j]));

                glTexCoord2fv(glm::value_ptr(texCoords[i + 1][j]));
                glVertex3fv(glm::value_ptr(pontos[i + 1][j]));
            } // next j

            glEnd();
        } // next i
        glDisable(GL_TEXTURE_2D);
    }
}