#include "cadastro.hpp"
//done
std::string Jogador::serializar() const {
        return _nome + "," + _apelido + "," + 
        std::to_string(Velha._vitorias) + "," + std::to_string(Velha._derrotas) + "," + 
        std::to_string(Lig4._vitorias) + "," + std::to_string(Lig4._derrotas) + "," + 
        std::to_string(Reversi._vitorias) + "," + std::to_string(Reversi._derrotas);
        //é possível adicionar novos jogos a partir daqui.
    }
//done
Jogador Jogador::deserializar(const std::string& linha) {

    std::vector<std::string> campos;
    size_t inicio = 0;
    size_t pos = 0;

    while ((pos = linha.find(',', inicio)) != std::string::npos) {
        campos.push_back(linha.substr(inicio, pos - inicio));
        inicio = pos + 1;
    }
    campos.push_back(linha.substr(inicio)); 

    if (campos.size() != 8) {
        throw std::invalid_argument("Formato inválido na string de entrada para deserialização.");
    }

    std::string nome = campos[0];
    std::string apelido = campos[1];
    int lig4Vitorias = std::stoi(campos[2]);
    int lig4Derrotas = std::stoi(campos[3]);
    int velhaVitorias = std::stoi(campos[4]);
    int velhaDerrotas = std::stoi(campos[5]);
    int reversiVitorias = std::stoi(campos[6]);
    int reversiDerrotas = std::stoi(campos[7]);

    return Jogador(nome, apelido, velhaVitorias, velhaDerrotas, lig4Vitorias, lig4Derrotas, reversiVitorias, reversiDerrotas);
}
//done
void Cadastro::adicionarJogador(const Jogador& alvo) { 
    _jogadores.push_back(std::unique_ptr<Jogador>(new Jogador(alvo)));
    std::cout << "Jogador " << alvo.getApelido() << " cadastrado com sucesso" << std::endl;
}

//done
void Cadastro::mostrarJogadores() const {
    if (_jogadores.empty()) {
        std::cout << "Nenhum jogador cadastrado." << std::endl;
        return;
    }
    
    for (const auto& jogador : _jogadores) {
            std::cout << jogador->getNome() << " " << jogador->getApelido() <<
                "LIG4 - V: " << jogador->getVitorias(jogador->getLig4()) <<
                " D: " << jogador->getDerrotas(jogador->getLig4()) <<
                "VELHA - V:" << jogador->getVitorias(jogador->getVelha()) <<
                " D: " << jogador->getDerrotas(jogador->getVelha()) <<
                "REVERSI - V: " << jogador->getVitorias(jogador->getReversi()) <<
                " D: " << jogador->getDerrotas(jogador->getReversi()) <<
                //possivel adicionar outros jogos aqui
                std::endl;
        }
}

//done
void Cadastro::import(const std::string& caminho) {
    //abre o arquivo para leitura
    std::ifstream arquivo(caminho);
    //verifica se o arquivo foi aberto com sucesso
    if (!arquivo.is_open()) {
        std::cerr << "erro ao abrir o arquivo: " << caminho << std::endl;
        return;
    }
    //limpa o vetor de jogadores para importar a lista atualizada
    _jogadores.clear();

    //importa todos os jogadores do arquivo .txt
    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (!linha.empty()) {
            _jogadores.push_back(std::unique_ptr<Jogador>(new Jogador(Jogador::deserializar(linha))));
        }
    }
    arquivo.close();
    std::cout << "jogadores importados com sucesso." << std::endl;
}

//done
//limpa o arquivo e salva
void Cadastro::save(const std::string& caminho) {
    //abre o arquivo para gravação
    std::ofstream arquivo(caminho);
    //verifica se o arquivo foi aberto com sucesso
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << caminho << std::endl;
        return;
    }
    //limpa o arquivo para atualização
    arquivo.clear();
    //itera entre os jogadores e grava-os no txt
    for (const auto& jogador : _jogadores) {
        arquivo << jogador->serializar() << "\n";
    }
    arquivo.close();
    std::cout << "jogadores salvos com sucesso" << std::endl;
}

//done
void Cadastro::removeJogador(const Jogador& alvo) {
    
    auto it = std::remove_if(_jogadores.begin(), _jogadores.end(),
        [&alvo](const std::unique_ptr<Jogador>& jogador) {
            return jogador->getApelido() == alvo.getApelido();
        }
    );

    if (it != _jogadores.end()) {
        _jogadores.erase(it, _jogadores.end()); 
        std::cout << "Jogador " << alvo.getApelido() << " removido com sucesso" << std::endl;
    } else {
        std::cout << "ERRO: jogador inexistente" << std::endl;
    }
}
//done
bool Cadastro::check(const Jogador& alvo) const {
        for (const auto& jogador : _jogadores) {
            if (jogador->getApelido() == alvo.getApelido()) {
                return true;
            }
        }
        return false;
    }

    

