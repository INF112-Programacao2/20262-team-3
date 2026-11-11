#ifndef MAGO_H
#define MAGO_H

#include <string>
#include "Monstro.h"

// Inimigo de longa distancia: ataque alto, pouca vida e defesa.
// Sua magia atravessa parte da defesa do alvo.
// Os valores padrao sao provisorios: o grupo ainda nao os definiu.
class Mago : public Monstro {
public:
    static constexpr int VIDA_PADRAO = 25;
    static constexpr int ATAQUE_PADRAO = 18;
    static constexpr int DEFESA_PADRAO = 1;
    static constexpr int ALCANCE_MAGO = 3;

    Mago(const std::string& nome, Mapa* mapa, int x, int y, int z,
         int vida = VIDA_PADRAO, int ataque = ATAQUE_PADRAO,
         int defesa = DEFESA_PADRAO);

    std::string tipo() const override;

    // Ataque magico: ignora metade da defesa do alvo.
    int atacar(Entidade& alvo) override;
};

#endif