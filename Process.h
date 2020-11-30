#include <vector>

#include "Page.h"

class Process {
    int id;
    int bytes;
    std::vector<Page> pages;
    int init_timestamp;
    int end_timestamp;
    int page_faults;
    bool is_active;

   public:
    Process(int id, int bytes, int init_timestamp);

    /**
     * Regresa un vector de páginas en el que está el proceso
     * @return vector de páginas del proceso
     */
    std::vector<Page>& getPages();

    /**
     * DRegresa si un proceso esta o no activo
     * @return estado del proceso
     */
    bool isActive();

    /**
     * Regresa el valor del timestamp al inicio del proceso
     * @return timestamp al inicio del proceso 
     */
    int getInitTimeStamp();

    /**
     * Regresa el valor del timestamp al final del proceso
     * @return timestamp al final del proceso
     */
    int getFinishTimeStamp();

    /**
     * Regresa el tamanio en bytes del proceso.
     * 
     * @return cantidad de bytes del proceso.
     */
    int getSize();

    /**
     * Regresa el número de page faults del proceso
     * @return número de page faults
     */
    int getPageFaults();

    /**
     * Calcula el turnaround time del proceso
     * @return turnaround time
     */
    int getTurnaround();

    /**
     * Incrementa en 1 el número de page faults del proceso
     */
    void incrementPageFaults(){page_faults++;};

    /**
     * Regresa la pagina del proceso donde se encuentra su direccion virtual virtual_address.
     * 
     * @param virtual_address direccion virtual a buscar.
     * @return apuntador a la pagina del proceso donde se encuentra la direccion virtual.
     * nullptr si no se encontro.
     */
    Page *getPageByVirtualAddress(int virtual_address);
};

Process::Process(int id, int bytes, int init_timestamp){
    this->id=id;
    this->bytes=bytes;
    this->init_timestamp=init_timestamp;
}

Page *Process::getPageByVirtualAddress(int virtual_address){
    
     for (Page page : pages) {
        // Encuentra y regresa la pagina si el virtual address esta en el rango correcto.
        if (virtual_address >= page.getVirtualAddressStart() && virtual_address < page.getVirtualAddressStart() + 16) {
            return &page;
        }
    }
    return nullptr;
}

std::vector<Page>& Process::getPages(){
    return pages;
}

bool Process::isActive(){
    return is_active;
}

int Process::getInitTimeStamp(){
    return init_timestamp;
}

int Process::getFinishTimeStamp(){
    return end_timestamp;
}

int Process::getSize(){
    return bytes;
}

int Process::getPageFaults(){
    return page_faults;
}

int Process::getTurnaround(){
    return end_timestamp - init_timestamp;
}