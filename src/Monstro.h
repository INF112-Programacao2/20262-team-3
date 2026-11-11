#ifndef MONSTRO_H
#define MONSTRO_H

#include <string>
#include "Entidade.h"

// Classe base dos inimigos. Herda de Entidade e define o comportamento
// comum; cada tipo (Guerreiro, Mago, Chefe) sobrescreve o que for diferente.
// E abstrata: so da para criar um Monstro por meio de uma subclasse.
class Monstro : public Entidade {
private:
    int alcanceBase;   // distancia maxima (em celulas) do ataque

public:
    // Valores provisorios: o grupo ainda nao definiu os numeros.
    static constexpr int ALCANCE_PADRAO = 1;

    Monstro(const std::string& nome, Mapa* mapa, int x, int y, int z,
            int vida, int ataque, int defesa, int alcance = ALCANCE_PADRAO);

    // Nome do tipo do inimigo, para exibicao e log (ex.: "Guerreiro")
    virtual std::string tipo() const = 0;

    // Alcance do ataque. O bot consulta este valor para decidir entre
    // atacar e se aproximar. As subclasses podem sobrescrever.
    virtual int getAlcance() const;

    // Ataque padrao: causa o ataque calculado ao alvo e retorna o dano
    // realmente causado. As subclasses podem sobrescrever (ex.: Mago, Chefe).
    int atacar(Entidade& alvo) override;

    // Acao defensiva. Por padrao nao faz nada; tipos que sabem se defender
    // (ex.: Chefe) sobrescrevem. Assim o bot pode chamar defender() em
    // qualquer Monstro sem precisar conhecer o tipo.
    virtual void defender();
};

#endif