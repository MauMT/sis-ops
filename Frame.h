#include "Page.h"

class Frame {
    bool free;
    int allocation_time;
    Page *page;

   public:
    Frame();


    /**
     * 
     * @return el tiempo en el que se asignó una página al frame.
     */ 
    int getAllocationTime();

    /**
     * 
     * @return apuntador a la pagina del frame.
     */
    Page *getPage();

    /**
     * 
     * @return el Id del proceso que aloja el frame.
     */
    int getProcessId();

    /**
     * 
     * @return si el frame esta libre (no tiene asignado un proceso).
     */
    bool isFree();

    /**
     * Asigna el tiempo en el que se asignó una página al frame.
     * 
     * @param timestamp el tiempo de asignación.
     */ 
    void setAllocationTime(int timestamp);

    /**
     * Asigna la pagina de un proceso al frame
     * 
     * @param page pagina del proceso
     */
    void setPage(Page *page);

    /**
     * Libera el frame de la pagina;
     * 
     *
     */
    void setFree(bool free = true);
};
