#ifndef CHEFE_H
#define CHEFE_H

#include <string>
#include "Monstro.h"

// Inimigo mais forte da fase. Tem duas acoes alem do ataque comum:
//  - ataque forte: a cada 3o ataque, o dano bruto e dobrado;
//  - postura defensiva (defender()): dobra a defesa ate o proximo ataque.
// Quem decide QUANDO alternar entre atacar e defender e o bot (integrante 3).
// Os valores padrao sao provisorios: o grupo ainda nao os definiu.
class Chefe : public Monstro {
private:
    int ataquesRealizados;
    bool posturaDefensiva;

public:
    static constexpr int VIDA_PADRAO = 150;
    static constexpr int ATAQUE_PADRAO = 20;
    static constexpr int DEFESA_PADRAO = 8;
    static constexpr int ALCANCE_CHEFE = 2;
    static constexpr int ATAQUES_ATE_FORTE = 3;       // 3o ataque e forte
    static constexpr int MULTIPLICADOR_FORTE = 2;     // dano bruto x2
    static constexpr int MULTIPLICADOR_DEFESA = 2;    // defesa x2 na postura

    Chefe(const std::string& nome, Mapa* mapa, int x, int y, int z,
          int vida = VIDA_PADRAO, int ataque = ATAQUE_PADRAO,
          int defesa = DEFESA_PADRAO);

    std::string tipo() const override;

    // Defesa dobrada enquanto estiver em postura defensiva
    int calcularDefesa() const override;

    // Ataque comum ou forte (a cada 3o ataque). Encerra a postura defensiva.
    int atacar(Entidade& alvo) override;

    // Entra em postura defensiva ate o proximo ataque
    void defender() override;

    bool emPosturaDefensiva() const;
    bool proximoAtaqueEForte() const;   // util para o bot e para o log
    int getAtaquesRealizados() const;
};

#endif