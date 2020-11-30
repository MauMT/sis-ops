#pragma once

#include <fstream>

#include "ResponseAction.h"
class Processor;  // Include circular

/**
 * Maneja la entrada para el procesador. Incluye la carga y lectura de un archivo de texto, además 
 * de la interpretación de los comandos a objetos (ResponseAction) que pueden ser usados por el procesador.
 */
class InputHandler {
    Processor *processor;

   public:
    InputHandler(Processor *processor = nullptr);
    ~InputHandler();

    /**
     * Interpreta una línea de texto como un comando válido (ResponseAction).
     * 
     * @param line linea a interpretar.
     * @return ResponseAction correspondiente al string.
     */
    ResponseAction *parse(std::string line);

    // TODO: usar formato JavaDoc (/**)
    //función que borra todos los espacios vacíos antes de alguno de los caracteres de los comandos
    friend void lTrim(std::string &s);
    //función que elimina los espacios vacío y el primer caracter del comando, deja a los valores enteros listos para ser leídos
    friend void firstCharDel(std::string &s);
    //función que borra todos los espacios vacíos después del último caracter alfanumérico de un comando
    friend void rTrim(std::string &s);
};
