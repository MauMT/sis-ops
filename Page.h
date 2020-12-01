#pragma once

/**
 * Modelo de la página de un proceso.
 */
class Page {
    bool in_memory;
    int frame_number;  //era real_address_start
    int page_number;   // era virtual_address_start
    int swap_address; //indice del vector de swaparea
    int process_id;
    int last_use;

   public:
    Page(int process_id, int page_number);  // virtual_address_start se calcula con page_number

    /**
     * @return si la página está en memoria o no
     */
    bool isInMemory();

    /**
     * @return el valor del último uso de la página
     */
    int getLastUse();

    /**
     * @return el process id del proceso en la página
     */
    int getProcessId();

    /**
     * @return el valor del inicio de la dirección vitual
     */
    int getVirtualAddressStart();

    /**
     * @return el valor de page_number
     */
    int getPageNumber();

    /**
     * @return el inicio de la dirección real (frame_number)
     */
    int getFrameNumber();

    /**
     * Modifica el valor de si la página está en memoria.
     * 
     * @param in_memory booleano del nuevo estado en memoria.
     */
    void setInMemory(bool in_memory);

    /**
     * Modifica el tiempo en el que se usó la página por última vez.
     * 
     *  @param timestamp el nuevo tiempo de último uso.
     */
    void setLastUse(int timestamp);

    /**
     * Modifica el nuevo inicio de la dirección real (frame_number)
     * @param frame_numer el inicio de la dirección real
     */
    void setFrameNumber(int fram_number);

    /**
     * Modifica el process id
     * @param process_id el nuevo process id
     */
    void setProcessId(int process_id);

    /**
     * Regresa si la pagina contiene la direccion virtual virtual_address del
     * proceso
     * 
     * @param virtual_address direccion virtual a buscar.
     * @return si la direccion virtual esta en la pagina.
     */
    bool holdsVirtualAddress(int virtual_address);

    /**
     * Asigna el numero de marco de pagina en el area de swap.
     * @param swap_address el nuevo swap address.
     */
    void setSwapAddress(int swap_address);

    /**
     * Regresa numero de marco de pagina en el area de swap.
     * @return el numero de marco de pagina en el area de swap.
     */
    int getSwapAddress();
    static const int page_size = 16;
};
