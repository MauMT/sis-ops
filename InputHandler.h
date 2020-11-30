

#include <fstream>

#include "ResponseAction.h"
class Processor;  // Include circular

// Tal vez incluir logica para leer el archivo de texto
class InputHandler {
    Processor *processor;  // Se necesita para validar el input
    std::ifstream *current_file;

   public:
    InputHandler(Processor *processor = nullptr);
    ~InputHandler();
    void loadFile(std::string filename);
    bool isReading();
    ResponseAction *readNextLine();
    ResponseAction *parse(std::string line);
    //función que borra todos los espacios vacíos antes de alguno de los caracteres de los comandos
    friend void lTrim(std::string &s);
    //función que elimina los espacios vacíos y el primer caracter del comando, deja a los valores enteros listos para ser leídos
    friend void firstCharDel(std::string &s);
    //función que borra todos los espacios vacíos después del último caracter alfanumérico de un comando
    friend void rTrim(std::string &s);
};
