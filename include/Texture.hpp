#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
// #include <memory>
#include <mutex>

class Texture
{
public:
    GLuint textureID;
    GLuint width;
    GLuint height;

public:
    Texture();
    ~Texture();
    void LoadBuffer();
    void SetBuffer(GLuint width, GLuint height, const unsigned char* buffer);

private:
    std::mutex mutex;
    const unsigned char* buffer = nullptr;
};

#endif
