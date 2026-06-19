#include "Utilidades.h"
#include <sstream>

namespace AlienBusters {

std::map<std::string, std::string> Utilidades::parsearCampos(const std::string& s) {
    std::map<std::string, std::string> campos;
    std::istringstream ss(s);
    std::string par;
    while (std::getline(ss, par, ',')) {
        std::size_t pos = par.find(':');
        if (pos != std::string::npos) {
            campos[par.substr(0, pos)] = par.substr(pos + 1);
        }
    }
    return campos;
}

float Utilidades::campoFloat(const std::map<std::string, std::string>& m, const std::string& chave, float padrao) {
    std::map<std::string, std::string>::const_iterator it = m.find(chave);
    if (it == m.end()) return padrao;
    float v = padrao;
    std::istringstream(it->second) >> v;
    return v;
}

int Utilidades::campoInt(const std::map<std::string, std::string>& m, const std::string& chave, int padrao) {
    std::map<std::string, std::string>::const_iterator it = m.find(chave);
    if (it == m.end()) return padrao;
    int v = padrao;
    std::istringstream(it->second) >> v;
    return v;
}

std::string Utilidades::campoStr(const std::map<std::string, std::string>& m, const std::string& chave, const std::string& padrao) {
    std::map<std::string, std::string>::const_iterator it = m.find(chave);
    if (it == m.end()) return padrao;
    return it->second;
}

}
