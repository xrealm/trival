//
// Created by Mao on 25/7/18.
//

#include "rgba_frame.h"

RGBAImageFrame::RGBAImageFrame() {
    pixels = NULL;
}

RGBAImageFrame::~RGBAImageFrame() {
    if (pixels != NULL) {
        delete[] pixels;
        pixels = NULL;
    }
}
