#include "Memory.h"

#include <iostream>
#include <vector>

#include "Clock.h"

using namespace std;

Memory::Memory(int size) {
    this->size = size / Page::page_size;
    free_frames = this->size;
    frames = vector<Frame>(this->size);
}

std::vector<Frame>& Memory::getFrames() {
    return frames;
}

void Memory::setPageToFrame(int frame_number, Page* page) {
    if (frames[frame_number].isFree()) {
        frames[frame_number].setPage(page);
        frames[frame_number].setAllocationTime(Clock::time);

        page->setLastUse(Clock::time);
        page->setFrameNumber(frame_number);
        page->setInMemory(true);
        free_frames--;
    }
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
}

int Memory::getFreeFrames() {
    return free_frames;
}
