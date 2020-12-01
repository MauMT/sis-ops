#include "Page.h"

#include <iostream>

using namespace std;
Page::Page(int process_id, int page_number) {
    this->process_id = process_id;
    this->page_number = page_number;
}

bool Page::isInMemory() {
    return in_memory;
}

bool Page::holdsVirtualAddress(int virtual_address) {
    //revisa que la virtual address esté en el rango de esta página
    return (virtual_address >= page_size * page_number && virtual_address < page_size * (page_number + 1));
}

int Page::getLastUse() {
    return last_use;
}

int Page::getProcessId() {
    return process_id;
}

void Page::setProcessId(int process_id) {
    this->process_id = process_id;
}

int Page::getVirtualAddressStart() {
    return page_number * page_size;
}

int Page::getPageNumber() {
    return page_number;
}

void Page::setLastUse(int timestamp) {
    this->last_use = timestamp;
}

int Page::getFrameNumber() {
    return frame_number;
}

void Page::setFrameNumber(int frame_number) {
    this->frame_number = frame_number;
}

void Page::setInMemory(bool in_memory) {
    this->in_memory = in_memory;
}

void Page::setSwapAddress(int swap_address) {
    this->swap_address = swap_address;
}

int Page::getSwapAddress() {
    return swap_address;
}