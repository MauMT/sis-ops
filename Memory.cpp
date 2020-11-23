#include "Memory.h"

#include <vector>

using namespace std;

Memory::Memory(int size) {
    this->size = size;
    free_frames = size;
    frames = vector<Frame>(size);
}

std::vector<Frame>& Memory::getFrames() {
    return frames;
}

void Memory::setPageToFrame(int frame_number, Page* page) {
    if (frames[frame_number].isFree()) {
        frames[frame_number].setPage(page);
        free_frames--;
    }

    // TODO: Validar fuera de funcion o arrojar error
}

void Memory::freeFrame(int frame_number) {
    if (!frames[frame_number].isFree()) {
        frames[frame_number].setFree();
        free_frames++;
    }

    // TODO: Validar fuera de funcion o arrojar error
}

int Memory::getFreeFrames() {
    return free_frames;
}
