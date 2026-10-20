# --- CONFIGURACOES DO COMPILADOR ---
# Define o compilador padrao do C++ a ser usado
CXX = g++

# Opcoes de compilacao
CXXFLAGS = -Wall -Wextra -std=c++17


# --- ARQUIVOS DO PROJETO ---
# Nome do arquivo executavel final que o jogo vai gerar
TARGET = jogo_rpg

# Encontra automaticamente todos os arquivos .cpp na pasta do projeto
SRCS = $(wildcard *.cpp)

# Cria uma lista de arquivos "objeto" (.o) baseada nos arquivos .cpp
OBJS = $(SRCS:.cpp=.o)


# --- REGRA PRINCIPAL (GERAR O JOGO) ---
# O que o computador faz quando voce digita apenas 'make' no terminal
all: $(TARGET)

# Junta todos os arquivos compilados (.o) para criar o executavel final
$(TARGET): $(OBJS)
  $(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)


# --- REGRA DE COMPILACAO INDIVIDUAL ---
# Como transformar cada arquivo de texto (.cpp) em um arquivo de maquina (.o)
%.o: %.cpp
  $(CXX) $(CXXFLAGS) -c $< -o $@


# --- REGRA DE LIMPEZA ---
# O que o computador faz quando voce digita 'make clean' no terminal
# Serve para apagar as compilacoes antigas e comecar do zero
clean:
  rm -f $(OBJS) $(TARGET)
