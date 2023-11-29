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
        drawSphere(raio, nStacks, nSectors, texture, pontos, texCoords);
        glPopMatrix();
    }

    void espaco::draw()
    {
        glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glScalef(size.x, size.y, size.z);
        drawSphere(raio, nStacks, nSectors, texture, pontos, texCoords);
        glPopMatrix();
    }
}