#include "../include/textura.hpp"

namespace spc{
    
        void textura::loadTexture(const char *filename){
            unsigned char *image = (SOIL_load_image(filename, &width, &height, &channels, SOIL_LOAD_RGB));
            if (image == 0)
            {
                std::cerr << "Erro ao carregar a textura: " << filename << std::endl;
            }
            setImage(image);
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            glGenerateMipmap(GL_TEXTURE_2D);
            SOIL_free_image_data(image);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
}