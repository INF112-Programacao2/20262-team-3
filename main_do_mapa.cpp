#include <iostream>
#include "mapa.h"
#include "posicao.h"

int main() {
    // Criação dos mapas e configuração de obstáculos e passagens.
    Mapa floresta(1, "Whispering Woods");
    Mapa masmorra(2, "Dark Dungeon");

    floresta.adicionarObstaculo(15, 17, 15, 17);
    floresta.adicionarObstaculo(21, 21, 20, 20);
    floresta.adicionarPassagem(50, 50, 50, 50, &masmorra, 0, 0, 0);
    masmorra.adicionarPassagem(0, 0, 0, 0, &floresta, 0, 0, 0);

    Posicao entidade(&floresta, 0, 0, 0);
    Posicao goblin(&floresta, 6, 5, 0);

    // Demonstração de movimento livre, colisão e troca de mapa.
    std::cout << "Movendo para espaco aberto...\n";
    entidade.movimentar(5, 5, 0);

    std::cout << "\nTentando entrar na posicao de outra entidade...\n";
    entidade.movimentar(1, 0, 0);

    std::cout << "\nTentando reposicionar na posicao ocupada...\n";
    entidade.definirMapa(&floresta, 6, 5, 0);

    std::cout << "\nTentando passar na diagonal ao lado de um obstaculo...\n";
    entidade.definirMapa(&floresta, 20, 20, 0);
    entidade.movimentar(1, 1, 0);

    std::cout << "\nTentando atravessar um obstaculo...\n";
    entidade.definirMapa(&floresta, 14, 16, 0);
    entidade.movimentar(36, 0, 0);

    goblin.definirMapa(&masmorra, 0, 0, 0);
    std::cout << "\nTentando entrar na masmorra ocupada...\n";
    entidade.definirMapa(&floresta, 50, 50, 0);
    entidade.movimentar(0, 0, 0);

    Posicao::Dados pos = entidade.obterPosicao();
    std::cout << "Mapa final: " << pos.mapa->obterNome() << " em (" << pos.x << ", " << pos.y << ")\n";

    return 0;
}