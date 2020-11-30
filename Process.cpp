
#include "Process.h"

Process::Process() {}

Process::Process(int id, int bytes, int init_timestamp) {
    this->id = id;
    this->bytes = bytes;
    this->init_timestamp = init_timestamp;
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
    return end_timestamp - init_timestamp;
}