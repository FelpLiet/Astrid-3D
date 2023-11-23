#include "../include/espaco.hpp"

namespace spc
{

    planeta::~planeta()
    {
    }

    void planeta::draw()
    {
        glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glScalef(size.x, size.y, size.z);
        glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Enable automatic texture coordinate generation
        GLfloat sgen_params[] = {1.0f / size.x, 0, 0, 0};
        GLfloat tgen_params[] = {0, 1.0f / size.y, 0, 0};
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

    void espaco::draw()
    {
        GLfloat halfSize = size / 2.0f;

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture); // Bind the texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBegin(GL_QUADS);
        // Front Face
        // glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-halfSize, -halfSize, halfSize);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(halfSize, -halfSize, halfSize);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(halfSize, halfSize, halfSize);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-halfSize, halfSize, halfSize);

        // Back Face
        glNormal3f(0.0, 0.0, -1.0);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-halfSize, -halfSize, -halfSize);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-halfSize, halfSize, -halfSize);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(halfSize, halfSize, -halfSize);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(halfSize, -halfSize, -halfSize);

        // Top Face
        glNormal3f(0.0, 1.0, 0.0);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-halfSize, halfSize, -halfSize);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-halfSize, halfSize, halfSize);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(halfSize, halfSize, halfSize);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(halfSize, halfSize, -halfSize);

        // Bottom Face
        glNormal3f(0.0, -1.0, 0.0);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-halfSize, -halfSize, -halfSize);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(halfSize, -halfSize, -halfSize);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(halfSize, -halfSize, halfSize);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-halfSize, -halfSize, halfSize);

        // Right face
        glNormal3f(1.0, 0.0, 0.0);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(halfSize, -halfSize, -halfSize);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(halfSize, halfSize, -halfSize);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(halfSize, halfSize, halfSize);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(halfSize, -halfSize, halfSize);

        // Left Face
        glNormal3f(-1.0, 0.0, 0.0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-halfSize, -halfSize, -halfSize);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-halfSize, -halfSize, halfSize);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-halfSize, halfSize, halfSize);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-halfSize, halfSize, -halfSize);

        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
}