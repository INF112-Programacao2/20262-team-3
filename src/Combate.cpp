#include "Combate.h"

#include "Monstro.h"

ResultadoAtaque Combate::executarAtaque(Entidade& atacante, Entidade& alvo) {
    const int danoCausado = atacante.atacar(alvo);
    const bool alvoDerrotado = !alvo.estaViva();
    const bool inimigoDerrotado =
        alvoDerrotado && dynamic_cast<const Monstro*>(&alvo) != nullptr;

    return {danoCausado, alvo.getVida(), alvoDerrotado, inimigoDerrotado};
}
