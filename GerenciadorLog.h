#ifndef GERENCIADOR_LOG_H
#define GERENCIADOR_LOG_H

#include <string>
#include <vector>

class GerenciadorLog {
private:
    std::string arquivoSaida;
    std::vector<std::string> historicoEventos;
    
    // Contadores para as métricas do relatório final
    int turnosJogados;
    int danoCausado;
    int danoSofrido;
    int monstrosDerrotados;
    int itensColetados;

public:
    GerenciadorLog(const std::string& caminhoSaida);
    
    void registrarEvento(const std::string& evento);
    void gerarRelatorioFinal();
    
    // Métodos auxiliares para atualizar métricas durante a partida
    void incrementarTurnos();
    void adicionarDanoCausado(int dano);
    void adicionarDanoSofrido(int dano);
    void incrementarMonstrosDerrotados();
    void incrementarItensColetados();
};

#endif