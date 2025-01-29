/**
 * @file cadastro.cpp 
 * @brief Declaração dos métodos das classes Jogador e Cadastro.
 */
#define DIVIDER "-------------------------------------------------------------------------------------------------------------\n"

#include "cadastro.hpp"
#include "cores.hpp"
#include <stdexcept>
#include <sstream>
#include <iomanip>


/**
 * @brief Serializa os dados do jogador em uma string formatada
 * @return String contendo os dados do jogador separados por vírgula
 * @throw std::runtime_error Se houver falha na serialização
 */
std::string Jogador::serializar() const {
    try {
        std::ostringstream oss;
        oss << _nome << "," << _apelido << "," 
            << Velha._vitorias << "," << Velha._derrotas << "," 
            << Lig4._vitorias << "," << Lig4._derrotas << "," 
            << Reversi._vitorias << "," << Reversi._derrotas;
        return oss.str();
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Erro na serialização do jogador: ") + e.what());
    }
}

/**
 * @brief Cria um objeto Jogador a partir de uma string serializada
 * @param linha String contendo os dados do jogador
 * @return Objeto Jogador construído com os dados da string
 * @throw std::invalid_argument Se a string tiver formato inválido
 * @throw std::runtime_error Se houver erro na conversão dos dados
 */
Jogador Jogador::deserializar(const std::string& linha) {
    if (linha.empty()) {
        //throw std::invalid_argument("String de entrada vazia para deserialização");
    }

    std::vector<std::string> campos;
    std::size_t inicio = 0;
    std::size_t pos = 0;

    try {
        while ((pos = linha.find(',', inicio)) != std::string::npos) {
            campos.push_back(linha.substr(inicio, pos - inicio));
            inicio = pos + 1;
        }
        campos.push_back(linha.substr(inicio));

        if (campos.size() != 8) {
            throw std::invalid_argument(
                std::string("Formato inválido na string de entrada: esperado 8 campos, encontrado ") + 
                std::to_string(campos.size()));
        }

        if (campos[0].empty() || campos[1].empty()) {
            throw std::invalid_argument("Nome ou apelido não podem estar vazios");
        }

        auto convertAndValidate = [&](const std::string& str, const std::string& field) -> int {
            try {
                int value = std::stoi(str);
                if (value < 0) {
                    throw std::invalid_argument(field + " não pode ser negativo");
                }
                return value;
            } catch (const std::exception& e) {
                throw std::runtime_error(field + ": " + e.what());
            }
        };

        int velhaVitorias = convertAndValidate(campos[2], "vitórias do jogo da velha");
        int velhaDerrotas = convertAndValidate(campos[3], "derrotas do jogo da velha");
        int lig4Vitorias = convertAndValidate(campos[4], "vitórias do Lig 4");
        int lig4Derrotas = convertAndValidate(campos[5], "derrotas do Lig 4");
        int reversiVitorias = convertAndValidate(campos[6], "vitórias do Reversi");
        int reversiDerrotas = convertAndValidate(campos[7], "derrotas do Reversi");

        return Jogador(campos[0], campos[1], 
                      velhaVitorias, velhaDerrotas,
                      lig4Vitorias, lig4Derrotas,
                      reversiVitorias, reversiDerrotas);

    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Erro na deserialização: ") + e.what());
    }
}

/**
 * @brief Adiciona um novo jogador ao cadastro
 * @param alvo Jogador a ser adicionado
 * @throw std::invalid_argument Se o jogador já estiver cadastrado
 * @throw std::runtime_error Se houver falha na alocação de memória
 */
void Cadastro::adicionarJogador(const Jogador& alvo) {
    if (check(alvo)) {
        throw std::invalid_argument(std::string("Jogador '") + alvo.getApelido() + "' já está cadastrado");
    }

    try {
        _jogadores.push_back(std::unique_ptr<Jogador>(new Jogador(alvo)));
        std::cout << "Jogador " << alvo.getApelido() << " cadastrado com sucesso" << std::endl;
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Erro ao adicionar jogador: ") + e.what());
    }
}

/**
 * @brief Exibe todos os jogadores cadastrados
 * @throw std::runtime_error Se houver erro ao acessar os dados dos jogadores
 */
void Cadastro::mostrarJogadores() const {
    try {
        if (_jogadores.empty()) {
            std::cout << "Nenhum jogador cadastrado." << std::endl;
            return;
        }

        // Cabeçalho da tabela
        std::cout << NEGRITO << DIVIDER
                  << std::left 
                  << std::setw(20) << "  Nome" 
                  << std::setw(15) << "Apelido" 
                  << std::setw(12) << "LIG4 (V/D)"
                  << std::setw(12) << "VELHA (V/D)"
                  << std::setw(12) << "REVERSI (V/D)"
                  << "\n" << DIVIDER << RESETAR;

        // Dados dos jogadores
        for (const auto& jogador : _jogadores) {
            if (!jogador) {
                throw std::runtime_error("Ponteiro inválido na lista de jogadores");
            }

            std::cout << std::left 
                      << std::setw(20) << ("  " + jogador->getNome())
                      << std::setw(15) << jogador->getApelido()
                      << AMARELO << std::setw(12) 
                      << (std::to_string(jogador->getVitorias(jogador->getLig4())) + "/" + std::to_string(jogador->getDerrotas(jogador->getLig4())))
                      << VERDE << std::setw(12) 
                      << (std::to_string(jogador->getVitorias(jogador->getVelha())) + "/" + std::to_string(jogador->getDerrotas(jogador->getVelha())))
                      << AZUL << std::setw(12) 
                      << (std::to_string(jogador->getVitorias(jogador->getReversi())) + "/" + std::to_string(jogador->getDerrotas(jogador->getReversi())))
                      << RESETAR << "\n";
        }

        std::cout << NEGRITO << DIVIDER << RESETAR;

    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Erro ao mostrar jogadores: ") + e.what());
    }
}


/**
 * @brief Importa dados de jogadores de um arquivo
 * @param caminho Caminho do arquivo a ser lido
 * @throw std::runtime_error Se houver erro na leitura do arquivo
 * @throw std::invalid_argument Se o arquivo estiver mal formatado
 */
void Cadastro::import(const std::string& caminho) {
    std::ifstream arquivo(caminho);
    if (!arquivo.is_open()) {
        //throw std::runtime_error(std::string("Não foi possível abrir o arquivo: ") + caminho);
    }

    try {
        _jogadores.clear();
        std::string linha;
        int lineNumber = 0;

        while (std::getline(arquivo, linha)) {
            ++lineNumber;
            if (!linha.empty()) {
                try {
                    _jogadores.push_back(
                        std::unique_ptr<Jogador>(new Jogador(Jogador::deserializar(linha)))
                    );
                } catch (const std::exception& e) {
                    throw std::invalid_argument(
                        std::string("Erro na linha ") + std::to_string(lineNumber) + ": " + e.what()
                    );
                }
            }
        }
        
        arquivo.close();
        std::cout << "Jogadores importados com sucesso." << std::endl;

    } catch (const std::exception& e) {
        arquivo.close();
        _jogadores.clear();
        throw std::runtime_error(std::string("Erro na importação: ") + e.what());
    }
}

/**
 * @brief Salva todos os jogadores em um arquivo
 * @param caminho Caminho do arquivo onde os dados serão salvos
 * @throw std::runtime_error Se houver erro na escrita do arquivo
 */
void Cadastro::save(const std::string& caminho) {
    std::ofstream arquivo(caminho);
    if (!arquivo.is_open()) {

        throw std::runtime_error(std::string("Não foi possível abrir o arquivo para escrita: ") + caminho);
    }

    try {
        for (const auto& jogador : _jogadores) {
            if (!jogador) {
                throw std::runtime_error("Ponteiro inválido encontrado na lista de jogadores");
            }
            arquivo << jogador->serializar() << "\n";
            if (arquivo.fail()) {
                throw std::runtime_error("Falha ao escrever no arquivo");
            }
        }

        arquivo.close();
        std::cout << "Jogadores salvos com sucesso" << std::endl;

    } catch (const std::exception& e) {
        arquivo.close();
        throw std::runtime_error(std::string("Erro ao salvar jogadores: ") + e.what());
    }
}

/**
 * @brief Remove um jogador do cadastro
 * @param alvo Jogador a ser removido
 * @throw std::invalid_argument Se o jogador não for encontrado
 * @throw std::runtime_error Se houver erro durante a remoção
 */
void Cadastro::removeJogador(const Jogador& alvo) {
    try {
        auto it = std::remove_if(_jogadores.begin(), _jogadores.end(),
            [&alvo](const std::unique_ptr<Jogador>& jogador) -> bool {
                return jogador && jogador->getApelido() == alvo.getApelido();
            }
        );

        if (it == _jogadores.end()) {
            throw std::invalid_argument(std::string("Jogador '") + alvo.getApelido() + "' não encontrado");
        }

        _jogadores.erase(it, _jogadores.end());
        std::cout << "Jogador " << alvo.getApelido() << " removido com sucesso" << std::endl;

    } catch (const std::invalid_argument& e) {
        throw;
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Erro ao remover jogador: ") + e.what());
    }
}

/**
 * @brief Verifica se um jogador está cadastrado
 * @param alvo Jogador a ser verificado
 * @return true se o jogador estiver cadastrado, false caso contrário
 * @throw std::runtime_error Se houver erro durante a verificação
 */
bool Cadastro::check(const Jogador& alvo) const {
    try {
        for (const auto& jogador : _jogadores) {
            if (!jogador) {
                throw std::runtime_error("Ponteiro inválido encontrado na lista de jogadores");
            }
            if (jogador->getApelido() == alvo.getApelido()) {
                return true;
            }
        }
        return false;
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Erro ao verificar jogador: ") + e.what());
    }
}