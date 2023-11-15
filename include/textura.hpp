#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <SOIL/SOIL.h>


namespace spc
{

    class textura
    {
    private:
        int width;
        int height;
        int channels;
        unsigned char *image;
        GLuint texture;

        void loadTexture(const char *filename);

    public:
        textura(const char *filename) {
            loadTexture(filename);
        }
        ~textura(){
            glDeleteTextures(1, &texture);
        }

        int getWidth() { return width; }
        int getHeight() { return height; }
        int getChannels() { return channels; }
        unsigned char *getImage() { return image; }
        GLuint getTexture() { return texture; }

        void setWidth(int newWidth) { width = newWidth; }
        void setHeight(int newHeight) { height = newHeight; }
        void setChannels(int newChannels) { channels = newChannels; }
        void setImage(unsigned char *newImage) { image = newImage; }
        void setTexture(GLuint newTexture) { texture = newTexture; }
    };

}