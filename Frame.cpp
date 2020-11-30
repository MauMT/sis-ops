#include "Frame.h"

Frame::Frame() {
    free = true;
    page = nullptr;
}

Page* Frame::getPage() {
    return page;
}

int Frame::getProcessId() {
    return page->getProcessId();
}

int Frame::getAllocationTime() {
    return allocation_time;
}

bool Frame::isFree() {
    return free;
}

void Frame::setAllocationTime(int timestamp) {
    allocation_time = timestamp;
}

void Frame::setFree(bool free) {
    this->free = free;
    if (free && this->page) {
        this->page->setInMemory(false);
        setPage(nullptr);
    }
}

void Frame::setPage(Page* page) {
    this->page = page;
    page->setInMemory(true);
    setFree(false);
}
