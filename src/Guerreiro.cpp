#include "Guerreiro.h"

Guerreiro::Guerreiro(const std::string& nome, Mapa* mapa, int x, int y, int z,
                     int vida, int ataque, int defesa)
    : Monstro(nome, mapa, x, y, z, vida, ataque, defesa, ALCANCE_GUERREIRO) {}

std::string Guerreiro::tipo() const { return "Guerreiro"; }