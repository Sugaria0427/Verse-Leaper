#include "Atlas.h"

Atlas::Atlas(const char* path, int size, SDL_RendererFlip initFlip ) :size(size),flipMode(initFlip) {
    char path_file[256];
    for (size_t i = 0; i < size; i++) {
        sprintf_s(path_file, path, i);
        this->frameList.push_back(new Image(path_file));
    }
}

Atlas::~Atlas() {
    for (Image* img : frameList) {
        delete img;
    }
    frameList.clear();
}
