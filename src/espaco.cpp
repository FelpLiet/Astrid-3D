#include "../include/espaco.hpp"

namespace spc
{
    planeta::planeta(glm::vec3 newPosition, glm::vec3 newSize)
    {
        position = newPosition;
        size = newSize;

    }

    planeta::~planeta()
    {
        delete text;
    }

    void planeta::draw()
    {
        glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glScalef(size.x, size.y, size.z);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, text->getTexture());

        // Enable automatic texture coordinate generation
        GLfloat sgen_params[] = {1.0f, 0.0f, 0.0f, 0.0f};
        GLfloat tgen_params[] = {0.0f, 1.0f, 0.0f, 0.0f};
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        glTexGenfv(GL_S, GL_OBJECT_PLANE, sgen_params);
        glTexGenfv(GL_T, GL_OBJECT_PLANE, tgen_params);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);

        // Draw the sphere
        GLUquadric *quad = gluNewQuadric();
        gluQuadricTexture(quad, GL_TRUE);
        gluSphere(quad, 1.0, 36, 18);
        gluDeleteQuadric(quad);

        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }

    void planeta::loadTexture(const char *filename)
    {
        text = new textura(filename);
    }
}