//
// Created by Mao on 25/7/18.
//

#ifndef GL3BOOK_RGBA_FRAME_H
#define GL3BOOK_RGBA_FRAME_H

#include <cstdint>

class RGBAImageFrame {
public:
    float position;
    float duration;
    uint8_t *pixels;
    int width;
    int height;

    RGBAImageFrame();

    virtual ~RGBAImageFrame();
};

#endif //GL3BOOK_RGBA_FRAME_H
