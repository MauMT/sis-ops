
#include "Swapper.h"

using namespace std;

Swapper::Swapper(Memory* memory, SwapArea* swap_area) {
    this->memory = memory;
    this->swap_area = swap_area;
}

void Swapper::swapIn(Page* page) {
    swap_area->removePage(page);
    int frame_number = memory->getFreeFrameIndex();
    if (frame_number != -1) {
        memory->setPageToFrame(frame_number, page);
    }

    // TODO: error handling si no se encontró la página
}

FIFOSwapper::FIFOSwapper(Memory* memory, SwapArea* swap_area) : Swapper(memory, swap_area) {}

Page* FIFOSwapper::swapOut() {
    vector<Frame>& frames = memory->getFrames();
    int first_inserted_frame, first_inserted_time;

    // Itera por los frames de memoria para buscar la página que se insertó primero
    for (int i = 0; i < frames.size(); i++) {
        if (frames[i].isFree()) continue;
        int curr_alloc_time = frames[i].getAllocationTime();

        // Si no se ha registrado un frame o el frame entró a memoria antes que el frame registrado
        if (i == 0 || curr_alloc_time < first_inserted_time) {
            first_inserted_frame = i;
            first_inserted_time = curr_alloc_time;
        }
    }

    Page* swapped_page = frames[first_inserted_frame].getPage();
    memory->freeFrame(swapped_page->getFrameNumber());

    return swapped_page;
}

LRUSwapper::LRUSwapper(Memory* memory, SwapArea* swap_area) : Swapper(memory, swap_area) {}

Page* LRUSwapper::swapOut() {
    vector<Frame>& frames = memory->getFrames();
    int least_used_frame, least_used_time;

    // Itera por los frames de memoria para buscar la página que se usó
    for (int i = 0; i < frames.size(); i++) {
        if (frames[i].isFree()) continue;
        int curr_last_use = frames[i].getPage()->getLastUse();

        // Si no se ha registrado un frame o el frame se usó antes que el frame registrado
        if (i == 0 || curr_last_use < least_used_time) {
            least_used_frame = i;
            least_used_time = curr_last_use;
        }
    }

    Page* swapped_page = frames[least_used_frame].getPage();
    memory->freeFrame(swapped_page->getFrameNumber());

    return swapped_page;
}