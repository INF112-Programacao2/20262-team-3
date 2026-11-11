#ifndef COMBATE_H
#define COMBATE_H

#include "Entidade.h"

struct ResultadoAtaque {
    int danoCausado;
    int vidaRestanteAlvo;
    bool alvoDerrotado;
    bool inimigoDerrotado;
};

class Combate {
public:
    // Executa o ataque polimorfico e informa o resultado para a partida.
    static ResultadoAtaque executarAtaque(Entidade& atacante, Entidade& alvo);
};

#endif
