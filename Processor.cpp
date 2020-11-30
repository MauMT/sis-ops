#include "Processor.h"

Processor::Processor() {
    memory = Memory(2048);
    swap_area = SwapArea();
    input_handler = InputHandler(this);
    swapper = new FIFOSwapper(&memory, &swap_area);
    clock = 0;
    swap_in_count = 0;
    swap_out_count = 0;
}

Processor::~Processor() {
    delete swapper;
}

void Processor::accessAddress(AccessAddressQuery query) {
    // Guardamos las variables del input aqui por conveniencia.
    int process_id = query.process_id;
    int virtual_address = query.virtual_address;
    int modify = query.modify;

    // Tenemos que desplegar el comando.
    std::cout << "Obtener la dirección real correspondiente a la dirección virtual " << virtual_address << " del proceso " << process_id << '\n';

    // Ubicamos el proceso.
    Process process = processes[process_id];

    // Obtenemos las paginas del proceso.
    std::vector<Page> pages = process.getPages();

    int process_page_number = -1;

    // Localizar donde esta la pagina con esa dirrecion del proceso.
    for (Page page : pages) {
        if (page.holdsVirtualAddress(virtual_address)) {
            // Hemos encontrado la pagina que tiene la direccion virtual del proceso.
            process_page_number = page.getPageNumber();
            break;
        }
    }

    // Si process_page_number es -1, no encontró la direccion virtual del proceso.
    if (process_page_number == -1) {
        // Error
        return;
    }

    // Obtenemos la pagina con su numero de pagina del proceso.
    Page page = pages[process_page_number];

    // Tenemos que ver si esta en memoria.
    // Si no esta en memoria, tendremos que hacer swap in,
    // y un swap out en caso de que la memoria esté llena.
    if (!page.isInMemory()) {
        // No está en memoria.

        // Tenemos que ver si la memoria está llena antes de hacer el swap in.
        if (memory.getFreeFrames() <= 0) {
            // Memoria llena. Es necesario un swap out.
            swapper->swapOut();
            swap_out_count++;
        }

        // Ya hay espacio, hacemos swap in.
        swapper->swapIn(&page);
        swap_in_count++;
    }

    // Obtenemos el offset y luego la direccion real.
    int offset = virtual_address - page.getVirtualAddressStart();
    int real_address = page.getFrameNumber() * 16 + offset;
    // Desplegamos el resultado.
    std::cout << "Dirección virtual: " << virtual_address << ". Dirección real: " << real_address << '\n';
}

void Processor::allocateProcess(AllocateProcessQuery query) {
}

void Processor::deallocateProcess(DeallocateProcessQuery query) {
}

void Processor::reinitialize() {
}

void Processor::exit() {
}

void Processor::printStats() {
}