#include "Processor.h"

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include "Clock.h"
using namespace std;

Processor::Processor() {
    memory = Memory(2048);
    swap_area = SwapArea();
    input_handler = InputHandler(this);
    // swapper = new FIFOSwapper(&memory, &swap_area);
    swapper = new LRUSwapper(&memory, &swap_area);
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
                AllocateProcessQuery query = castResponse<AllocateProcessQuery>(action);
                allocateProcess(query);
            } break;
            case ResponseActionType::AccessAddressQuery: {
                AccessAddressQuery query = castResponse<AccessAddressQuery>(action);
                accessAddress(query);
            } break;
            case ResponseActionType::DeallocateProcessQuery: {
                DeallocateProcessQuery query = castResponse<DeallocateProcessQuery>(action);
                deallocateProcess(query);
            } break;
            case ResponseActionType::CommentQuery: {
                CommentQuery comment = castResponse<CommentQuery>(action);
                comment.print();

            } break;
            case ResponseActionType::FinishQuery:
                reinitialize();
                break;
            case ResponseActionType::ExitQuery:

                printStats();
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
    cout << "Obtener la direccion real correspondiente a la direccion virtual " << virtual_address << " del proceso " << process_id << '\n';

    if (processes.find(process_id) == processes.end()) {
        // El proceso no existe en la lista de procesos
        cout << "ERROR: El proceso " << process_id << " no existe.\n\n";
        return;
    }

    // Ubicamos el proceso.
    Process& process = processes[process_id];

    if (!process.isActive()) {
        // Si ya no esta activo, nos salimos de la funcion para que no ocurran cosas extrañas.
        cout << "ERROR: El proceso " << process_id << " no esta activo.\n\n";
        return;
    }

    // Obtenemos las paginas del proceso.
    std::vector<Page>& pages = process.getPages();
    int process_page_number = -1;

    // Localizar donde esta la pagina con esa dirrecion del proceso.
    for (int i = 0; i < pages.size(); i++) {
        Page& page = pages[i];
        page.holdsVirtualAddress(virtual_address);
        if (page.holdsVirtualAddress(virtual_address)) {
            // Hemos encontrado la pagina que tiene la direccion virtual del proceso.
            process_page_number = page.getPageNumber();
            break;
        }
    }

    if (process_page_number == -1) {
        // Si process_page_number es -1, no encontró la direccion virtual del proceso.
        cout << "ERROR: El proceso no tiene una direccion " << virtual_address << ".\n\n";
        return;
    }

    // Obtenemos la pagina con su numero de pagina del proceso.
    Page& page = pages[process_page_number];

    // Tenemos que ver si esta en memoria.
    // Si no esta en memoria, tendremos que hacer swap in,
    // y un swap out en caso de que la memoria esté llena.
    if (!page.isInMemory()) {
        // No está en memoria.
        process.incrementPageFaults();
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

    if (modify) {
        cout << "Pagina " << page.getPageNumber() << " del proceso " << page.getProcessId() << " modificada.\n";
    }

    // Obtenemos el offset y luego la direccion real.
    int offset = virtual_address - page.getVirtualAddressStart();
    int real_address = page.getFrameNumber() * 16 + offset;

    // Desplegamos el resultado.
    cout << "Direccion virtual: " << virtual_address << ". Direccion real: " << real_address << "\n\n";
}

void Processor::allocateProcess(AllocateProcessQuery query) {
    int process_id = query.process_id;
    int bytes = query.bytes;

    cout << "Asignar " << bytes << " bytes al proceso " << process_id << endl;

    // Se crea el nuevo proceso especificado
    processes[process_id] = Process(process_id, bytes, Clock::time);
    Process& new_process = processes[process_id];

    vector<Page>& pages = new_process.getPages();
    // Guarda los numeros de frames usados para desplegarlos posteriormente
    vector<int> frames_used;
    for (Page& page : pages) {
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

    // Se construyen los rangos de marcos utilizados
    // Se ordena la lista de numeros de marco
    sort(frames_used.begin(), frames_used.end());
    vector<string> ranges;
    // Indicadores para el inicio y fin del rango que se este registrando
    int from = 0, to = 0;
    for (int i = 0; i < frames_used.size(); i++) {
        // Si no hay dos numeros de marcos continuos, se registra el ultimo rango y se inicializa uno nuevo
        if (i != 0 && frames_used[i] != frames_used[i - 1] + 1) {
            to = i - 1;
            // Si los limites del rango son iguales, solo se imprime un
            if (to == from)
                ranges.push_back(to_string(frames_used[from]));
            else
                ranges.push_back(to_string(frames_used[from]) + '-' + to_string(frames_used[to]));
            from = i;
            to = i;
        } else {
            to = i;
            if (i == frames_used.size() - 1) {
                if (to == from)
                    ranges.push_back(to_string(frames_used[from]));
                else
                    ranges.push_back(to_string(frames_used[from]) + '-' + to_string(frames_used[to]));
            }
        }
    }

    cout << "Se asignaron los marcos de pagina ";
    for (int i = 0; i < ranges.size(); i++) {
        cout << ranges[i] << (i == ranges.size() - 1 ? " " : ", ");
    }
    cout << "al proceso " << process_id << endl
         << endl;
}

void Processor::deallocateProcess(DeallocateProcessQuery query) {
    // Guardamos el id del proceso en esta variable
    int process_id = query.process_id;

    if (processes.find(process_id) == processes.end()) {
        // El proceso no existe en la lista de procesos
        cout << "ERROR: El proceso " << process_id << " no existe.\n\n";
        return;
    }

    // Obtenemos el proceso.
    Process& process_to_deallocate = processes[process_id];

    if (!process_to_deallocate.isActive()) {
        // Revisamos que el proceso esté activo para evitar errores.
        cout << "ERROR: El proceso " << process_id << " ya no esta activo.\n\n";
        return;
    }

    std::cout << "Liberar los marcos de pagina ocupados por el proceso " << process_id << '\n';

    // Obtenemos todas las paginas del proceso, ya sea que esten en memoria o en el area de swap.
    std::vector<Page>& pages = process_to_deallocate.getPages();

    Clock::time += 100 * pages.size();

    // Iteramos sobre las paginas del proceso.
    // Las eliminamos dependiendo si estan en memoria o en el area de swap.

    std::vector<bool> frames_deallocated(128, false);
    std::vector<bool> swaparea_pages_deallocated(256, false);

    for (Page& page : pages) {
        if (page.isInMemory()) {
            // Esta en memoria
            int frame_number = page.getFrameNumber();
            frames_deallocated[frame_number] = true;
            memory.freeFrame(frame_number);
        } else {
            // Esta en area de swap.
            int swap_address = page.getSwapAddress();
            swaparea_pages_deallocated[swap_address] = true;
            swap_area.removePage(&page);
        }

        Clock::time += 100;
    }

    std::vector<pair<int, int>> frames_ranges;
    for (int i = 0; i < 128; i++) {
        if (frames_deallocated[i]) {
            int start = i, end = i;
            for (int j = i + 1; j < 128; j++) {
                if (frames_deallocated[j]) {
                    end = j;
                } else {
                    break;
                }
            }
            frames_ranges.push_back({start, end});
            i = end + 1;
        }
    }

    std::vector<pair<int, int>> swaparea_pages_ranges;
    for (int i = 0; i < 256; i++) {
        if (swaparea_pages_deallocated[i]) {
            int start = i, end = i;
            for (int j = i + 1; j < 256; j++) {
                if (swaparea_pages_deallocated[j]) {
                    end = j;
                } else {
                    break;
                }
            }
            swaparea_pages_ranges.push_back({start, end});
            i = end + 1;
        }
    }

    // 'Desactivamos' el proceso.
    // Pero se queda en el contenedor de procesos para obtener estadisticas mas adelante.
    process_to_deallocate.setInactive();

    // Desplegar los frames de la memoria y paginas del area de swap que se liberaron.
    std::cout << "Se liberan los marcos de memoria real: ";
    for (int i = 0; i < frames_ranges.size(); i++) {
        pair<int, int> p = frames_ranges[i];
        if (p.first == p.second)
            std::cout << p.first;
        else
            std::cout << p.first << '-' << p.second;
        std::cout << (i == frames_ranges.size() - 2 ? " y " : (i == frames_ranges.size() - 1 ? "\n" : " "));
    }

    if (swaparea_pages_ranges.size() > 0) std::cout << "Se liberan los marcos ";
    for (int i = 0; i < swaparea_pages_ranges.size(); i++) {
        pair<int, int> p = swaparea_pages_ranges[i];
        if (p.first == p.second)
            std::cout << p.first;
        else
            std::cout << p.first << '-' << p.second;
        std::cout << (i == swaparea_pages_ranges.size() - 2 ? " y " : (i == swaparea_pages_ranges.size() - 1 ? " del area de swapping\n" : " "));
    }
    cout << endl;
}

void Processor::reinitialize() {
    printStats();
    delete swapper;
    memory = Memory(2048);
    swap_area = SwapArea();
    swapper = new FIFOSwapper(&memory, &swap_area);
    swap_in_count = 0;
    swap_out_count = 0;
}

void Processor::exit() {
    for (auto& process : processes) {
        process.second.setInactive();
    }
}

void Processor::printStats() {
    /*
    - turnaround time de cada proceso que se consideró, desde que se
    comienza a cargar un proceso (P) hasta que se terminan de liberar todas
    sus páginas (L). Puedes obtenerlo por medio de una diferencia de
    timestamps.
    - turnaround promedio.
    - número de page faults por proceso. Recuerda que un page fault ocurre
    únicamente cuando un marco de página necesario no se encuentra en
    memoria real. → En esta versión del manejador de memoria virtual, el
    comando P (cargar un proceso completo a memoria real) no produce page
    faults. Los habría si es necesario reemplazar páginas de memoria real para
    hacerle espacio al proecso. ←
    - número total de operaciones de swap-out y de swap-in que fueron
    necesarias por cualquier motivo 
    */

    double num_processes = 0.0;
    double average_turnaround;
    for (auto& process : processes) {
        cout << "Turnaround time del Proceso " << process.second.getProcessId() << ": " << process.second.getTurnaround() / 1000 << "s" << endl;
        num_processes++;
        average_turnaround += process.second.getTurnaround();
    }

    cout << "\nTurnaround promedio: " << (average_turnaround / num_processes) / 1000 << "s\n" << endl;

    for (auto& process : processes) {
        cout << "Page faults del Proceso " << process.second.getProcessId() << ": " << process.second.getPageFaults() << endl;
    }
    cout << "\nOperaciones de swap in: " << swap_in_count << endl;
    cout << "Operaciones de swap out: " << swap_out_count << endl;
    cout << endl;
}