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

bool Frame::isFree() {
    return free;
}

void Frame::setFree(bool free = true) {
    this->free = free;
    if (free) setPage(nullptr);
}

void Frame::setPage(Page* page) {
    this->page = page;
    setFree(false);
}
