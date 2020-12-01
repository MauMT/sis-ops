#include "InputHandler.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void lTrim(std::string &s) {
    auto pos = s.find_first_not_of(' ');
    if (s.size() > 1)
        s = s.substr(pos);
}

void rTrim(std::string &s) {
    auto pos = s.find_last_not_of(' ');
    //lTrim(s);
    if (s.size() > 1)
        s = s.substr(0, pos + 1);
}

void firstCharDel(std::string &s) {
    if (s.size() > 1)
        s = s.substr(1);
    lTrim(s);
}

InputHandler::InputHandler(Processor *processor) {
    this->processor = processor;
}

InputHandler::~InputHandler() {
}

ResponseAction *InputHandler::parse(std::string line) {
    std::stringstream ss;
    lTrim(line);
    char commandSymbol = line[0];  //se extrae el primer caracter no vacío que representa al comando
    firstCharDel(line);

    int input_process_id;
    int input_n;  //Se trata de una solicitud de “n” bytes para cargar un proceso a la memoria.
    int input_direccion_virtual;
    bool input_m;  //Si “m” es 0, la dirección correspondiente sólo se lee; si es 1, también se modifica

    switch (commandSymbol) {
        case 'p':
        case 'P':  //allocate process command
            ss << line;
            ss >> input_n >> input_process_id;
            if (ss.fail())  //ss.fail() es una función de sstream que verifica que el type coincida con el de la declaración
            {
                return new Error("Entrada invalida para el comando P");
            }
            return new AllocateProcessQuery(input_process_id, input_n);
            break;

        case 'a':
        case 'A':  //access memory address command
            ss << line;
            ss >> input_direccion_virtual >> input_process_id >> input_m;
            if (ss.fail()) {
                return new Error("Entrada invalida para el comando A");
            }
            return new AccessAddressQuery(input_process_id, input_direccion_virtual, input_m);
            break;
        case 'l':
        case 'L':  //deallocate process command
            ss << line;
            ss >> input_process_id;
            if (ss.fail()) {
                return new Error("Entrada invalida para el comando L");
            }
            return new DeallocateProcessQuery(input_process_id);
            break;

        case 'c':
        case 'C':  //comment command
            return new CommentQuery(line);
            break;
        case 'f':
        case 'F':  //finish command sequence command
            return new FinishQuery();
        case 'e':
        case 'E':  //exit program command
            return new ExitQuery();
            break;

        default:
            return new Error("Comando desconocido");  //si el primer caracter no coincide con nada entonces no es un comando
            break;
    }
    return new Error("syntax error");  //return necesario para evitar warning
}