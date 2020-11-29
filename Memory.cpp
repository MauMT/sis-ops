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
        page->setFrameNumber(frame_number);
        free_frames--;
    }

    // TODO: Validar fuera de funcion o arrojar error
}

int Memory::getFreeFrameIndex() {
    for (int i = 0; i < frames.size(); i++) {
        if (frames[i].isFree()) {
            return i;
        }
    }

    return -1;
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
