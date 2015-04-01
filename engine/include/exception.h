/*
 * Classe que representa uma exceção.
 *
 * Autor: Edson Alves
 * Data: 01/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

using std::string;

class Exception
{
public:
    Exception(const string& message)
        : m_message(message) {}

    string message() const { return m_message; }

private:
    string m_message;
};

#endif
