#include "GerenciadorLog.h"
#include "Excecoes.h"
#include <iostream>
#include <fstream>

GerenciadorLog::GerenciadorLog(const std::string& caminhoSaida)
    : arquivoSaida(caminhoSaida),
      turnosJogados(0),
      danoCausado(0),
      danoSofrido(0),
      monstrosDerrotados(0),
      itensColetados(0) {
    // Limpa ou cria o arquivo de log logo no início para garantir que há permissão de escrita
    std::ofstream arquivo(arquivoSaida, std::ios::trunc);
    if (!arquivo.is_open()) {
        throw ArquivoNaoEncontradoException(arquivoSaida);
    }
    arquivo.close();
}

void GerenciadorLog::registrarEvento(const std::string& evento) {
    // Guarda o evento na lista em memória para compor o relatório depois
    historicoEventos.push_back(evento);

    // Exibe o evento no terminal (útil no modo interativo e para acompanhar a execução)
    std::cout << "[LOG] " << evento << std::endl;

    // Também já grava incrementalmente no arquivo de saída para não perder dados se o programa fechar
    std::ofstream arquivo(arquivoSaida, std::ios::app);
    if (!arquivo.is_open()) {
        throw ArquivoNaoEncontradoException(arquivoSaida);
    }
    arquivo << evento << "\n";
    arquivo.close();
}

void GerenciadorLog::gerarRelatorioFinal() {
    std::ofstream arquivo(arquivoSaida, std::ios::app);
    if (!arquivo.is_open()) {
        throw ArquivoNaoEncontradoException(arquivoSaida);
    }

    arquivo << "\n========================================\n";
    arquivo << "           RELATORIO FINAL              \n";
    arquivo << "========================================\n";
    arquivo << "Turnos jogados: " << turnosJogados << "\n";
    arquivo << "Dano causado: " << danoCausado << "\n";
    arquivo << "Dano sofrido: " << danoSofrido << "\n";
    arquivo << "Monstros derrotados: " << monstrosDerrotados << "\n";
    arquivo << "Itens coletados: " << itensColetados << "\n";
    arquivo << "Total de eventos registrados: " << historicoEventos.size() << "\n";
    arquivo << "========================================\n";

    arquivo.close();
    std::cout << "\nRelatorio final salvo com sucesso em: " << arquivoSaida << std::endl;
}

// --- Métodos auxiliares para atualização das métricas ---

void GerenciadorLog::incrementarTurnos() {
    turnosJogados++;
}

void GerenciadorLog::adicionarDanoCausado(int dano) {
    if (dano > 0) {
        danoCausado += dano;
    }
}

void GerenciadorLog::adicionarDanoSofrido(int dano) {
    if (dano > 0) {
        danoSofrido += dano;
    }
}

void GerenciadorLog::incrementarMonstrosDerrotados() {
    monstrosDerrotados++;
}

void GerenciadorLog::incrementarItensColetados() {
    itensColetados++;
}