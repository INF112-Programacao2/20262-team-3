#ifndef JOGO_ENGINE_H
#define JOGO_ENGINE_H

#include <vector>
#include <string>
#include "GerenciadorLog.h"

class MapaGrid;
class Jogador;
class Monstro;

class JogoEngine {
private:
    MapaGrid* mapa;
    Jogador* jogador;
    std::vector<Monstro*> monstros;
    GerenciadorLog log;
    bool jogoEmAndamento;

    void processarComandoJogador(const std::string& comando);

public:
    JogoEngine(MapaGrid* mapaInicial, Jogador* jogadorInicial, 
               const std::vector<Monstro*>& monstrosIniciais, 
               const std::string& caminhoLog = "relatorio_partida.txt");
    
    ~JogoEngine();

    void iniciarModoInterativo();
    void iniciarModoHeadless(const std::string& caminhoComandos);
    void atualizarTurno();
    bool verificarFimDeJogo();
};

#endif