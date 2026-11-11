#ifndef GUERREIRO_H
#define GUERREIRO_H

#include <string>
#include "Monstro.h"

// Inimigo corpo a corpo: muita vida e defesa, alcance curto.
// Os valores padrao sao provisorios: o grupo ainda nao os definiu.
class Guerreiro : public Monstro {
public:
    static constexpr int VIDA_PADRAO = 40;
    static constexpr int ATAQUE_PADRAO = 12;
    static constexpr int DEFESA_PADRAO = 4;
    static constexpr int ALCANCE_GUERREIRO = 1;

    Guerreiro(const std::string& nome, Mapa* mapa, int x, int y, int z,
              int vida = VIDA_PADRAO, int ataque = ATAQUE_PADRAO,
              int defesa = DEFESA_PADRAO);

    std::string tipo() const override;
};

#endif