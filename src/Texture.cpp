#include "Texture.hpp"

#include <spdlog/spdlog.h>

Texture::Texture()
{

}

Texture::~Texture()
{
    delete(this->buffer);
}

void Texture::SetBuffer(GLuint width, GLuint height, const unsigned char* buffer)
{
    const std::lock_guard<std::mutex> guard(mutex);
    this->width = width;
    this->height = height;
    delete(this->buffer);
    this->buffer = buffer;
}

void Texture::LoadBuffer()
{
    const std::lock_guard<std::mutex> guard(mutex);
    if (buffer == nullptr) return;
    glDeleteTextures(1, &textureID);
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Set texture clamping method
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D,    // Type of texture
                 0,                // Pyramid level (for mip-mapping) - 0 is the top level
                 GL_RGB,           // Internal colour format to convert to
                 width,         // Image width  i.e. 640 for Kinect in standard mode
                 height,         // Image height i.e. 480 for Kinect in standard mode
                 0,                // Border width in pixels (can either be 1 or 0)
                 GL_BGRA,           // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
                 GL_UNSIGNED_BYTE, // Image data type
                 this->buffer);       // The actual image data itself

    glGenerateMipmap(GL_TEXTURE_2D);
}
