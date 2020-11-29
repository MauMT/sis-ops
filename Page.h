// TODO: documentar
class Page {
    static const int page_size = 16;
    bool in_memory;
    int frame_number;  //era real_address_start
    int page_number;   // era virtual_address_start
    int swap_address;
    int process_id;
    int last_use;

   public:
    Page(int process_id, int page_number);  // virtual_address_start se calcula con page_number

    bool isInMemory();
    int getLastUse();
    int getProcessId();
    int getVirtualAddressStart();
    int getFrameNumber();
    void setInMemory(bool);

    /**
     * Modifica el tiempo en el que se usó la página por última vez.
     * 
     *  @param timestamp el nuevo tiempo de último uso.
     */
    void setLastUse(int timestamp);
    void setFrameNumber(int);
    void setProcessId(int);

    /**
     * Regresa si la pagina contiene la direccion virtual virtual_address del
     * proceso
     * 
     * @param virtual_address direccion virtual a buscar.
     * @return si la direccion virtual esta en la pagina.
     */
    bool holdsVirtualAddress(int virtual_address);
};

Page::Page(int process_id, int page_number) {
    this->process_id = process_id;
    this->page_number = page_number;
}

bool Page::isInMemory() {
    return in_memory;
}

bool Page::holdsVirtualAddress(int virtual_address) {
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