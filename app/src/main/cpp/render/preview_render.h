//
// Created by Mao on 30/7/18.
//

#ifndef GL3BOOK_PREVIEW_RENDER_H
#define GL3BOOK_PREVIEW_RENDER_H

#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include "../util.h"
#include "../shader.h"
#include "pic_texture.h"

static const char VERTEX_SHADER[] = {
        "#version 300 es\n"
        "layout(location = 0) in vec4 vPosition;\n"
        "layout(location = 1) in vec2 vTexCoord;\n"
        "out vec2 texCoord;\n"
        "void main() {\n"
        "    gl_Position = vPosition;\n"
        "    texCoord = vTexCoord;"
        "}"
};
static const char FRAG_SHADER[] = {
        "#version 300 es \n"
        "precision mediump float;\n"
        "#define BackgroundColor vec4(0.957, 0.925, 0.773, 1.0);\n"
        "#define BlueColor vec4(0.384, 0.667, 0.655, 1.0);\n"
        "in vec2 texCoord;\n"
        "out vec4 fragColor;\n"

        "vec4 balloon(vec2 pos, vec2 start, vec2 end, float radius, vec4 color) {"
        "       vec2 linePos = pos;\n"
        "       "
        "       vec4 c = vec4(1.0,0.0,0.0,1.0);\n"
        "       "
        "       return c;\n"
        "}"

        "void main() {\n"
        "    float width = texCoord.x/texCoord.y; \n"
        "    float end = -0.1;"
//        "    vec4 c = balloon(texCoord, vec2(width * 0.5, 0.9), vec2(width * 0.5, end), 0.013, BlueColor);\n"
//        "    fragColor.rgb = mix(fragColor.rgb, c.rgb, c.a);\n"
        "    fragColor = vec4(width, 0.0, 0.0, 1.0);\n"
        "}"
};


const GLfloat vertices[] = {
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, - 0.5f, 0.0f
};

const float texCoords[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
};

class PreviewRender {
protected:
    int width;
    int height;

    Shader *shader;
    PicTexture *picTexture;

public:
    PreviewRender();

    virtual ~PreviewRender();

    virtual bool init(int width, int height, PicTexture *picTexture);

    virtual void render();

    virtual void dealloc();

    void resetRenderSize(int left, int top, int width, int height);

};

#endif //GL3BOOK_PREVIEW_RENDER_H
