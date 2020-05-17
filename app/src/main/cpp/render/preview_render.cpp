//
// Created by Mao on 30/7/18.
//

#include "preview_render.h"

PreviewRender::PreviewRender() {

}

PreviewRender::~PreviewRender() {
    if (shader != NULL) {
        delete shader;
    }
}

bool PreviewRender::init(int width, int height, PicTexture *picTexture) {
    shader = new Shader(VERTEX_SHADER, FRAG_SHADER);
    this->picTexture = picTexture;

    glBindAttribLocation(shader->program, 0, "vPosition");
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(0);


    glBindAttribLocation(shader->program, 1, "vTexCoord");
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(1);

    return true;
}

void PreviewRender::resetRenderSize(int left, int top, int width, int height) {
    this->width = width;
    this->height = height;
}

void PreviewRender::render() {
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);



    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    shader->Use();

    //bindTexutre
//    GLint uniformSampler = glGetUniformLocation(shader->program, "");
//    picTexture->bindTexture(uniformSampler);
//    shader->setInt(uniformSampler, )
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisable(GL_BLEND);
}

void PreviewRender::dealloc() {
    if (picTexture != NULL) {
        picTexture->dealloc();
    }
    if (shader != NULL) {
        delete shader;
        shader = NULL;
    }
}