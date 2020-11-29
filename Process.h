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

    std::vector<Page>& getPages();

    bool isActive();

    int getInitTimeStamp();

    int getFinishTimeStamp();

    /**
     * Regresa el tamanio en bytes del proceso.
     * 
     * @return cantidad de bytes del proceso.
     */
    int getSize();

    int getPageFaults();

    int getTurnaround();

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
            return page;
        }
    }
    return nullptr;
}

std::vector<Page>& getPages(){
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