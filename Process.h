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

    void incrementPageFaults();

    /**
     * Regresa la pagina del proceso donde se encuentra su direccion virtual virtual_address.
     * 
     * @param virtual_address direccion virtual a buscar.
     * @return apuntador a la pagina del proceso donde se encuentra la direccion virtual.
     * nullptr si no se encontro.
     */
    Page* getPageByVirtualAddress(int virtual_address);
};