/*
 * Implementação da classe Settings.
 *
 * Autor: Edson Alves
 * Data: 20/05/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/settings.h"

#include <fstream>

using namespace std;

typedef enum {NONE, COMMENT, SECTION, NAME, VALUE} State;

string
ltrim(const string& s)
{
    int pos;
    
    for (pos = 0; s[pos] == ' '; ++pos) {}
    
    return s.substr(pos);
}

Settings *
Settings::from_file(const string& path) throw (Exception)
{
    Settings *settings = new Settings();

    ifstream inifile(path);

    if (not inifile)
    {
        return settings;
    }

    State state = NONE;
    char c;
    ostringstream os;
    string section = "", name, value;
    
    while (not inifile.eof())
    {
        c = inifile.get();

        switch (state)
        {
        case NONE:
            if (c == ';')
            {
                state = COMMENT;
            }
            else if (c == '[')
            {
                state = SECTION;
            }
            else if (isalpha(c) && section != "")
            {
                state = NAME;
                os << c;
            }

            break;

        case COMMENT:
            if (c == '\n')
            {
                state = NONE;
            }
            
            break;

        case SECTION:
            if (c == '\n')
            {
                throw Exception("Invalid syntax!");
            }
            
            if (c != ']')
            {
                os << c;
            }
            else
            {
                section = os.str();
                os.str("");
                state = NONE;
            }
            
            break;

        case NAME:
            if (c == '\n')
            {
                throw Exception("Missing value!");
            }
            
            if (isalnum(c) || c == '_')
            {
                os << c;
            }
            else if (c == '=')
            {
                if (section == "")
                {
                    throw Exception("Missing section!");
                }
                
                name = os.str();
                os.str("");
                state = VALUE;
            }

            break;

        case VALUE:
            if (c != '\n')
            {
                os << c;
            }
            else
            {
                value = os.str();
                settings->write<string>(section, name, value);
                os.str("");
                state = NONE;
            }

            break;
        }
    }
    
    if (state == VALUE)
    {
        settings->write<string>(section, name, value);
    }

    return settings;
}

void
Settings::save(const string& path) throw (Exception)
{
    ofstream outfile(path);

    if (not outfile)
    {
        throw Exception("Settings::save(): Couldn't open file " + path);
    }

    for (auto it : m_sections)
    {
        outfile << endl << "[" << it.first << "]" << endl << endl;

        for (auto p : it.second)
        {
            outfile << p.first << "=" << p.second << endl;
        }
    }

    outfile.close();
}

map< string, map<string, string> >
Settings::sections() const
{
    return m_sections;
}
