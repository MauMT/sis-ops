// TODO: documentar
class Page {
    bool in_memory;
    int frame_number;  //era real_address_start
    int page_number;   // era virtual_address_start
    int swap_address;
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
     * 
     * Modifica el valor de si la página está en memoria
     */
    void setInMemory(bool);

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

    static const int page_size = 16;
};

Page::Page(int process_id, int page_number) {
    this->process_id = process_id;
    this->page_number = page_number;
}

bool Page::isInMemory() {
    return in_memory;
}

bool Page::holdsVirtualAddress(int virtual_address) {
    //revisa que la virtual address esté en el rango de esta página
    return (virtual_address >= page_size * page_number && virtual_address < page_size * (page_number + 1));
}

int Page::getLastUse() {
    return last_use;
}

int Page::getProcessId() {
    return process_id;
}

void Page::setProcessId(int process_id) {
    this->process_id = process_id;
}

int Page::getVirtualAddressStart() {
    return page_number*16;
}

int Page::getPageNumber(){
    return page_number;
}

void Page::setLastUse(int timestamp) {
    this->last_use = timestamp;
}

int Page::getFrameNumber() {
    return frame_number;
}

void Page::setFrameNumber(int frame_number) {
    this->frame_number = frame_number;
}

void Page::setInMemory(bool in_memory) {
    this->in_memory = in_memory;
}