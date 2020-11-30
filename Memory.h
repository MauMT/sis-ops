#include <vector>

#include "Frame.h"

class Memory {
    int size;
    int free_frames;
    std::vector<Frame> frames;

   public:
    Memory(int size = 2048);

    /**
     * Regresa una referencia a los frames de la memoria.
     * 
     * @return referencia al contenedor de frames.
     */
    std::vector<Frame>& getFrames();

    
    /**
     *  Regresa el primer número de marco de página que esta disponible.
     * 
     * @return índice del marco en el vector frames, o -1 si no se encontró.
     */
    int getFreeFrameIndex();

    /**
     * Asigna una pagina de un proceso a un frame.
     * 
     * @param frame_number numero del frame a modificar (indexado desde 0).
     * @param page apuntador a la pagina que se va a alocar.
     * @return copia del frame.
     */
    void setPageToFrame(int frame_number, Page* page);

    /**
     * Libera el frame numero frame_number.
     * 
     * @param frame_number numero del frame a liberar.
     */
    void freeFrame(int frame_number);

    /**
     * Regresa el numero de frames libres en memoria.
     * 
     * @return el numero de frames.
     */
    int getFreeFrames();

};