#ifndef EXCECOES_H
#define EXCECOES_H

#include <stdexcept>
#include <string>

// Herdando de std::runtime_error, ela já gerencia a mensagem de erro (what()) automaticamente
class ArquivoNaoEncontradoException : public std::runtime_error {
public:
    explicit ArquivoNaoEncontradoException(const std::string& caminho)
        : std::runtime_error("Erro: Arquivo nao encontrado ou sem permissao: " + caminho) {}
};

class ComandoInvalidoException : public std::runtime_error {
public:
    explicit ComandoInvalidoException(const std::string& comando)
        : std::runtime_error("Erro: Sintaxe de comando invalida: " + comando) {}
};

class ForaDosLimitesException : public std::runtime_error {
public:
    explicit ForaDosLimitesException(const std::string& detalhe)
        : std::runtime_error("Erro: Movimento fora dos limites do grid: " + detalhe) {}
};

#endif