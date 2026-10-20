#ifndef ENTIDADE_H
#define ENTIDADE_H

#include <string>
#include "Posicao.h"   //integrante 2(João)


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
    Entidade(const std::string& nome, const Posicao& posicao,
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
    void setPosicao(const Posicao& nova);
    int getVida() const;
    int getVidaMaxima() const;
};

#endif