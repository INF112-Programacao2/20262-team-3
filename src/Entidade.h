#ifndef ENTIDADE_H
#define ENTIDADE_H

#include <string>
#include "posicao.h"   //integrante 2(João)


 // Classe base de todos os personagens que lutam (Jogador e Monstro).
 
class Entidade {
protected:
    std::string nome;
    Posicao posicao;
    int vidaMaxima;
    int vida;
    int ataqueBase;
    int defesaBase;

public:
    // A Entidade e dona da sua Posicao (que nao pode ser copiada),
    // entao ela e construida aqui a partir de mapa, x, y, z.
    Entidade(const std::string& nome, Mapa* mapa, int x, int y, int z,
             int vida, int ataque, int defesa);
    virtual ~Entidade() = default;   // deleta via ponteiro da base

    // Dá para fazer mudanças depois como Jogador soma bônus de itens
    virtual int calcularAtaque() const;
    virtual int calcularDefesa() const;

    // Cada tipo ataca do seu jeito
    virtual int atacar(Entidade& alvo) = 0;

    // Aplica a defesa, atualiza a vida e retorna o dano realmente sofrido
    virtual int receberDano(int danoBruto);
    void curar(int quantidade);

    bool estaViva() const;

    const std::string& getNome() const;
    const Posicao& getPosicao() const;
    Posicao& getPosicao();   // para chamar movimentar() e definirMapa()
    int getVida() const;
    int getVidaMaxima() const;
};

#endif