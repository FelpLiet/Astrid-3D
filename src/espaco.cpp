#include "../include/espaco.hpp"

namespace spc
{
    void espaco::draw()
    {
        glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glScalef(size.x, size.y, size.z);
        drawSphere(raio, nStacks, nSectors, texture, pontos, texCoords);
        glPopMatrix();
    }

    void sol::draw()
    {  
        glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glScalef(size.x, size.y, size.z);
        drawSphere(raio, nStacks, nSectors, texture, pontos, texCoords);
        glPopMatrix();
    }

    void planeta::draw()
    {
        glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LIGHTING_BIT | GL_TEXTURE_BIT);
        glPushMatrix();
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT1);
        GLfloat light_position[] = {10.0, 10.0, 10.0, 1.0};
        GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};
        GLfloat light_diffuse[] = {1.5f, 1.5f, 1.5f, 1.0f}; 
        GLfloat light_specular[] = {2.0f, 2.0f, 2.0f, 1.0f};
        GLfloat att_constant = 0.2;
        GLfloat att_linear = 0.0;
        GLfloat att_quadratic = 0.0;
        GLfloat spot_direction[] = {0.0, 0.0, 0.0};
        GLfloat spot_exponent = 0.0;
        GLfloat spot_cutoff = 180.0;

        glLightfv(GL_LIGHT1, GL_POSITION, light_position);
        glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, att_constant);
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, att_linear);
        glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, att_quadratic);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spot_exponent);
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot_cutoff);
        
        glTranslatef(position.x, position.y, position.z);
        glScalef(size.x, size.y, size.z);
        glRotatef(rotation, 0.0f, 1.0f, 0.0f);
        drawSphere(raio, nStacks, nSectors, texture, pontos, texCoords);
        glPopMatrix();
        glPopAttrib();
    }
}