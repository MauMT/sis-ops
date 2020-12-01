
#include "Process.h"
#include <math.h>

Process::Process() {}

Process::Process(int id, int bytes, int init_timestamp) {
    this->id = id;
    this->bytes = bytes;
    this->init_timestamp = init_timestamp;
    page_faults = 0;
    is_active = true;

    for (int i = 0; i < ceil(bytes / Page::page_size); i++) {
        pages.push_back(Page(id, i));
    }
}

Page* Process::getPageByVirtualAddress(int virtual_address) {
    for (Page& page : pages) {
        // Encuentra y regresa la pagina si el virtual address esta en el rango correcto.
        if (page.holdsVirtualAddress(virtual_address)) {
            return &page;
        }
    }
    return nullptr;
}

std::vector<Page>& Process::getPages() {
    return pages;
}

bool Process::isActive() {
    return is_active;
}

void Process::setInactive() {
    is_active = false;
    end_timestamp = Clock::time;
}

int Process::getInitTimeStamp() {
    return init_timestamp;
}

int Process::getFinishTimeStamp() {
    return end_timestamp;
}

int Process::getSize() {
    return bytes;
}

int Process::getPageFaults() {
    return page_faults;
}

int Process::getTurnaround() {
    if (is_active) return Clock::time - init_timestamp;
    return end_timestamp - init_timestamp;
}

int Process::getProcessId() {
    return id;
}

void Process::incrementPageFaults() {
    page_faults++;
};