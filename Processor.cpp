#include "Processor.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "Clock.h"
using namespace std;

Processor::Processor() {
    memory = Memory(2048);
    swap_area = SwapArea();
    input_handler = InputHandler(this);
    swapper = new FIFOSwapper(&memory, &swap_area);
    swap_in_count = 0;
    swap_out_count = 0;
}

Processor::~Processor() {
    delete swapper;
}

template <class T>
T castResponse(ResponseAction* action) {
    return *(dynamic_cast<T*>(action));
}

void Processor::exec(string filename) {
    ifstream current_file(filename);
    string line;

    while (getline(current_file, line)) {
        ResponseAction* action = input_handler.parse(line);
        switch (action->type) {
            case ResponseActionType::AllocateProcessQuery: {
                // AllocateProcessQuery query = castResponse<AllocateProcessQuery>(action);
                // allocateProcess(query);

                cout << "ALLOCATE\n";
            } break;
            case ResponseActionType::AccessAddressQuery: {
                // AccessAddressQuery query = castResponse<AccessAddressQuery>(action);
                // accessAddress(query);

                cout << "ACCESS\n";
            } break;
            case ResponseActionType::DeallocateProcessQuery: {
                // DeallocateProcessQuery query = castResponse<DeallocateProcessQuery>(action);
                // deallocateProcess(query);

                cout << "DEALLOCATE\n";
            } break;
            case ResponseActionType::CommentQuery: {
                CommentQuery comment = castResponse<CommentQuery>(action);
                comment.print();

            } break;
            case ResponseActionType::FinishQuery:
                reinitialize();
                cout << "RESTART\n";
                break;
            case ResponseActionType::ExitQuery:
                exit();
                cout << "EXIT\n";
                break;
            case ResponseActionType::Error: {
                Error error = castResponse<Error>(action);
                error.print();
            } break;
            default:
                break;
        }

        delete action;
    }
}

void Processor::accessAddress(AccessAddressQuery query) {
    // Guardamos las variables del input aqui por conveniencia.
    int process_id = query.process_id;
    int virtual_address = query.virtual_address;
    int modify = query.modify;

    // Tenemos que desplegar el comando.
    cout << "Obtener la dirección real correspondiente a la dirección virtual " << virtual_address << " del proceso " << process_id << '\n';

    // Ubicamos el proceso.
    Process process = processes[process_id];

    // Obtenemos las paginas del proceso.
    std::vector<Page> pages = process.getPages();

    int process_page_number = -1;

    // Localizar donde esta la pagina con esa dirrecion del proceso.
    for (Page& page : pages) {
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
    Page& page = pages[process_page_number];

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
            Clock::time += 1 * 1000;
        }

        // Ya hay espacio, hacemos swap in.
        swapper->swapIn(&page);
        swap_in_count++;
        Clock::time += 1 * 1000;
    }

    page.setLastUse(Clock::time);
    Clock::time += 0.1 * 1000;

    // Obtenemos el offset y luego la direccion real.
    int offset = virtual_address - page.getVirtualAddressStart();
    int real_address = page.getFrameNumber() * 16 + offset;
    // Desplegamos el resultado.
    cout << "Dirección virtual: " << virtual_address << ". Dirección real: " << real_address << '\n';
}

void Processor::allocateProcess(AllocateProcessQuery query) {
    cout << "Asignar " << query.bytes << " bytes al proceso " << query.process_id << endl;

    // Se crea el nuevo proceso especificado
    Process new_process = Process(query.process_id, query.bytes, Clock::time);

    auto pages = new_process.getPages();

    // Guarda los numeros de frames usados para desplegarlos posteriormente
    vector<int> frames_used;
    for (auto& page : pages) {
        if (memory.getFreeFrames() <= 0) {
            swapper->swapOut();
            swap_out_count++;
            Clock::time += 1 * 1000;
        }
        int frame_number = memory.getFreeFrameIndex();
        frames_used.push_back(frame_number);
        memory.setPageToFrame(frame_number, &page);
        Clock::time += 1 * 1000;
    }

    sort(frames_used.begin(), frames_used.end());

    vector<string> ranges;
    int from = 0, to = 0;
    for (int i = 0; i < frames_used.size(); i++) {
        if (i != 0 && frames_used[i] != frames_used[i - 1]) {
            to = i - 1;
            if (to == from)
                ranges.push_back(to_string(frames_used[from]));
            else
                ranges.push_back(to_string(frames_used[from]) + '-' + to_string(frames_used[to]));
            from = i;
            to = i;
        }
    }

    cout << "Se asignaron los marcos de página ";
    for (int i = 0; i < ranges.size(); i++) {
        cout << ranges[i] << (i == ranges.size() - 1 ? " " : ", ");
    }
    cout << "al proceso " << query.process_id;
}

void Processor::deallocateProcess(DeallocateProcessQuery query) {
}

void Processor::reinitialize() {
}

void Processor::exit() {
}

void Processor::printStats() {
}