#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>
#include "Entidade.h"

// Heroi controlado pelo usuario. Herda de Entidade.
//Valores (vida, ataque, defesa) provisorios 
class Jogador : public Entidade {
private:
    // Bonus vindos de itens equipados (integrante 3 define/atualiza).
    int bonusAtaque;
    int bonusDefesa;

    // Contadores para o relatorio final (metricas do integrante 1).
    int danoCausado;
    int danoSofrido;
    int inimigosDerrotados;

public:
    static constexpr int VIDA_PADRAO = 100;
    static constexpr int ATAQUE_PADRAO = 15;
    static constexpr int DEFESA_PADRAO = 5;

    Jogador(const std::string& nome, Mapa* mapa, int x, int y, int z,
            int vida = VIDA_PADRAO, int ataque = ATAQUE_PADRAO,
            int defesa = DEFESA_PADRAO);

    // Ataque base + bonus de itens
    int calcularAtaque() const override;
    int calcularDefesa() const override;

    // Ataca o alvo e retorna o dano realmente causado
    int atacar(Entidade& alvo) override;

    // Igual ao da Entidade, mas tambem contabiliza o dano sofrido
    int receberDano(int danoBruto) override;

    // Usados pelo Inventario ao equipar/desequipar itens (bonus >= 0)
    void definirBonusAtaque(int bonus);
    void definirBonusDefesa(int bonus);
    int getBonusAtaque() const;
    int getBonusDefesa() const;

    // Metricas para o relatorio final
    int getDanoCausado() const;
    int getDanoSofrido() const;
    int getInimigosDerrotados() const;
};

#endif