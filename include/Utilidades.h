#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <map>
#include <string>

namespace AlienBusters {

class Utilidades {
public:
    static std::map<std::string, std::string> parsearCampos(const std::string& s);
    static float campoFloat(const std::map<std::string, std::string>& m, const std::string& chave, float padrao = 0.f);
    static int campoInt(const std::map<std::string, std::string>& m, const std::string& chave, int padrao = 0);
    static std::string campoStr(const std::map<std::string, std::string>& m, const std::string& chave, const std::string& padrao = "");
};

}

#endif
