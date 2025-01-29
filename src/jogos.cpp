/**
 * @file jogos.cpp
 * @brief Declaração dos métodos da classe JogosDeTabuleiro.
 */

#include "jogos.hpp"


JogosDeTabuleiro::JogosDeTabuleiro(int linhas, int colunas) : linhas_(linhas), colunas_(colunas){
        //Caso o vetor seja inicializado com sem parametros, entao ele sera iniciado com tamanho zero
        //Caso ele for aumentado, essas novas "casas" serao prenchidas com ' '.
    Tabuleiro_.resize(linhas, std::vector<int>(colunas, 0));
}

int JogosDeTabuleiro::getLinhas() const { return this->linhas_; };
int JogosDeTabuleiro::getColunas() const { return colunas_; };
std::vector<std::vector<int>> JogosDeTabuleiro::get_tabuleiro() const { return Tabuleiro_; };
char JogosDeTabuleiro::get_casa(int linha, int coluna) const {
    if (linha >= 0 && linha < linhas_ && coluna >= 0 && coluna < colunas_) {
        return Tabuleiro_[linha][coluna];
    }
    return 'F';
}

void JogosDeTabuleiro::setLinhasColunas(int linha, int coluna) { linhas_ = linha; colunas_ = coluna; };

// jogador 1 é X, jogador 2 é O
int Reversi::imprimir_vetor(int jogador) const {
    int casa;
    auto jogadas_validas = atualizar_jogadas_validas(jogador);

    // Imprime jogadas validas
    std::cout << "Jogadas validas: " << std::endl;
    for (int i = 0; i < getLinhas(); i++)
    {
        for (int j = 0; j < getColunas(); j++)
        {
            if (jogadas_validas[i][j])
            {
                std::cout << FUNDO_AMARELO << "|" << i+1 << ':' << j+1 << "|" << RESETAR << ' ';
            }
        }
    }
    std::cout << std::endl << std::endl;

    // Imprime tabuleiro
    for (int i = 0; i < this->getLinhas(); i++)
    {
        if (i == 0){
            std::cout << FUNDO_BRANCO << "| |";
            for (int k = 0; k < getColunas(); k++)
            {
                std::cout << "|" << k+1 << "|";
            }
        }
        std::cout << RESETAR << std::endl;
        for (int j = 0; j < this->getColunas(); j++)
        {
            if (j == 0)
            {
                std::cout << FUNDO_BRANCO << '|' << i+1 << '|' << RESETAR;
            }
            casa = this->get_casa(i, j);
            if(casa == 0)
            {
                if (jogadas_validas[i][j])
                {
                    std::cout << FUNDO_VERDE << "| |" << RESETAR; 
                }
                else
                {
                    std::cout << FUNDO_VERMELHO << "| |" << RESETAR; 
                }
            }
            else if (casa == 1)
            {
                std::cout << "|X|";
            }
            else
            {
                std::cout << FUNDO_BRANCO << "|O|" << RESETAR;
            }
        }
    }
    
    std::cout << std::endl;
    mostrar_pontuacao();
    return 0;
}


const std::vector<std::pair<int, int>> Reversi::direcoes = {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1},           {0, 1},
    {1, -1},  {1, 0},  {1, 1}
};

Reversi::Reversi(int linhas, int colunas) : JogosDeTabuleiro(linhas, colunas) {
    JogadasValidas_.resize(linhas, std::vector<bool>(colunas, false));
    
    // Configuração inicial padrão do Reversi
    // Coloca as 4 peças iniciais no centro do tabuleiro
    int meio_linha = linhas / 2;
    int meio_coluna = colunas / 2;
    
    Tabuleiro_[meio_linha-1][meio_coluna-1] = 2;   // O
    Tabuleiro_[meio_linha-1][meio_coluna] = 1;     // X
    Tabuleiro_[meio_linha][meio_coluna-1] = 1;     // X
    Tabuleiro_[meio_linha][meio_coluna] = 2;       // O
}

bool Reversi::verificar_direcao(int linha, int coluna, int dLinha, int dColuna, int jogador) const {
    int oponente = (jogador == 1) ? 2 : 1;
    int novaLinha = linha + dLinha;
    int novaColuna = coluna + dColuna;
    bool encontrou_oponente = false;
    
    // Corrected condition: Check if the first cell is the opponent's piece
    if (get_casa(novaLinha, novaColuna) != oponente) return false;
    
    while (novaLinha >= 0 && novaLinha < getLinhas() && 
           novaColuna >= 0 && novaColuna < getColunas()) {
        
        int casa_atual = get_casa(novaLinha, novaColuna);
        
        if (casa_atual == 0) return false; 
        if (casa_atual == oponente) {
            encontrou_oponente = true;
        }
        if (casa_atual == jogador) {
            return encontrou_oponente;
        }
        
        novaLinha += dLinha;
        novaColuna += dColuna;
    }
    
    return false;
}

bool Reversi::verificar_jogada(int linha, int coluna, int jogador) const {
    if (linha < 0 || linha >= getLinhas() || coluna < 0 || coluna >= getColunas()) {
        return false;
    }
    
    if (get_casa(linha, coluna) != 0) { //Verifica se tentou jogar em uma casa vazia
        return false;
    }
    
    for (const auto& dir : direcoes) { //verifica todas direcoes
        if (verificar_direcao(linha, coluna, dir.first, dir.second, jogador)) {
            return true;
        }
    }
    
    return false;
}

int Reversi::ler_jogada(int linha, int coluna, int jogador) {
    if (!verificar_jogada(linha, coluna, jogador)) { //verifica se a jogada é valida
        return 0;
    }
    
    Tabuleiro_[linha][coluna] = jogador;
    
    int oponente = (jogador == 1) ? 2 : 1;
    int pecas_capturadas = 0;
    
    for (const auto& dir : direcoes) {
        if (verificar_direcao(linha, coluna, dir.first, dir.second, jogador)) {
            int novaLinha = linha + dir.first;
            int novaColuna = coluna + dir.second;
            
            while (get_casa(novaLinha, novaColuna) == oponente) {
                Tabuleiro_[novaLinha][novaColuna] = jogador;
                pecas_capturadas++;
                novaLinha += dir.first;
                novaColuna += dir.second;
            }
        }
    }
    
    return pecas_capturadas;
}

std::vector<std::vector<bool>> Reversi::atualizar_jogadas_validas(int jogador) const {
    std::vector<std::vector<bool>> jogadas_validas(getLinhas(), 
                                                  std::vector<bool>(getColunas(), false));
    
    for (int i = 0; i < getLinhas(); i++) {
        for (int j = 0; j < getColunas(); j++) {
            jogadas_validas[i][j] = verificar_jogada(i, j, jogador);
        }
    }
    return jogadas_validas;
}

bool Reversi::testar_condicao_de_vitoria() const {
    std::vector<std::vector<bool>> jogadas_validas_1 = atualizar_jogadas_validas(1);
    std::vector<std::vector<bool>> jogadas_validas_2 = atualizar_jogadas_validas(2);

    bool ha_jogadas_1 = false;
    bool ha_jogadas_2 = false;

    for (const auto& linha : jogadas_validas_1) {
        for (bool jogada : linha) {
            if (jogada) ha_jogadas_1 = true;
        }
    }

    for (const auto& linha : jogadas_validas_2) {
        for (bool jogada : linha) {
            if (jogada) ha_jogadas_2 = true;
        }
    }

    if (!ha_jogadas_1 && !ha_jogadas_2) {
    return true;
    }
    return false;
}

std::pair<int, int> Reversi::calcular_pontuacao() const {
    int pontos_jogador1 = 0;
    int pontos_jogador2 = 0;
    
    for (int i = 0; i < getLinhas(); i++) {
        for (int j = 0; j < getColunas(); j++) {
            if (get_casa(i, j) == 1) pontos_jogador1++;
            else if (get_casa(i, j) == 2) pontos_jogador2++;
        }
    }
    
    return std::make_pair(pontos_jogador1, pontos_jogador2);
}

void Reversi::mostrar_pontuacao() const {
    std::pair<int, int> pontos = calcular_pontuacao();
    std::cout << "\nPlacar atual:" << std::endl;
    std::cout << "Jogador 1 (X): " << pontos.first << " peças" << std::endl;
    std::cout << "Jogador 2 (O): " << pontos.second << " peças" << std::endl;
}

int Reversi::determinar_vencedor() const {
    std::pair<int, int> pontos = calcular_pontuacao();
    std::cout << "\nPlacar final:" << std::endl;
    std::cout << "Jogador 1 (X): " << pontos.first << " peças" << std::endl;
    std::cout << "Jogador 2 (O): " << pontos.second << " peças" << std::endl;
    
    if (pontos.first > pontos.second) {
        return 1;
    } else if (pontos.second > pontos.first) {
        return 2;
    } else {
        return 3;
    }
    return 0;
}

int Reversi::anunciar_vencedor() const {
    int vencedor = determinar_vencedor();
    switch (vencedor)
    {
    case 1:
        std::cout << "\nJogador 1 (X) venceu!" << std::endl;
        break;
    case 2:
        std::cout << "\nJogador 2 (O) venceu!" << std::endl;
        break;
    case 3:
        std::cout << "\nEmpate!" << std::endl;
        break;
    }
    return vencedor;
}


JogoDaVelha::JogoDaVelha(int linhas, int colunas) : JogosDeTabuleiro(linhas, colunas) {
    // Inicializa o tabuleiro vazio
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            Tabuleiro_[i][j] = 0;
        }
    }
}


int JogoDaVelha::anunciar_vencedor() const {
    int vencedor = determinar_vencedor();
    if (vencedor == 1) {
        std::cout << "\nJogador 1 (X) venceu!" << std::endl;
    } else if (vencedor == 2) {
        std::cout << "\nJogador 2 (O) venceu!" << std::endl;
    } else {
        std::cout << "\nEmpate!" << std::endl;
    }
    return vencedor;
}

int JogoDaVelha::determinar_vencedor() const {
    // Verifica linhas
    for (int i = 0; i < getLinhas(); i++) {
        if (get_casa(i, 0) != 0 && 
            get_casa(i, 0) == get_casa(i, 1) && 
            get_casa(i, 1) == get_casa(i, 2)) {
            return get_casa(i, 0);
        }
    }
    
    // Verifica colunas
    for (int j = 0; j < getColunas(); j++) {
        if (get_casa(0, j) != 0 && 
            get_casa(0, j) == get_casa(1, j) && 
            get_casa(1, j) == get_casa(2, j)) {
            return get_casa(0, j);
        }
    }
    
    // Verifica diagonais
    if (get_casa(0, 0) != 0 && 
        get_casa(0, 0) == get_casa(1, 1) && 
        get_casa(1, 1) == get_casa(2, 2)) {
        return get_casa(0, 0);
    }
    
    if (get_casa(0, 2) != 0 && 
        get_casa(0, 2) == get_casa(1, 1) && 
        get_casa(1, 1) == get_casa(2, 0)) {
        return get_casa(0, 2);
    }
    
    return 0; // Empate ou jogo em andamento
}

// Nova implementação do método imprimir_vetor
int JogoDaVelha::imprimir_vetor(int jogador) const {
    std::cout << "\n";
    
    // Números das colunas
    std::cout << VERMELHO << "   1   2   3\n" << RESETAR;
    
    for (int i = 0; i < this->getLinhas(); i++) {
        // Número da linha e células
        std::cout << VERMELHO << i + 1 << " " << RESETAR;
        for (int j = 0; j < this->getColunas(); j++) {
            int casa = this->get_casa(i, j);
            // Define o conteúdo da célula
            char simbolo = ' ';
            if (casa == 1) simbolo = 'X';
            else if (casa == 2) simbolo = 'O';
            
            std::cout << " " << (simbolo == 'O' ? AMARELO : "") << simbolo << RESETAR << " "; // Espaçamento da célula
            if (j < this->getColunas() - 1) std::cout << "|"; // Separador
        }
        std::cout << "\n";
        
        // Linha horizontal entre as linhas (exceto após a última)
        if (i < this->getLinhas() - 1) {
            std::cout << "  ";
            for (int j = 0; j < this->getColunas(); j++) {
                std::cout << "___"; // Underscores para a linha
                if (j < this->getColunas() - 1) std::cout << "|"; // Separador
            }
            std::cout << "\n";
        }
    }
    
    return 0;
}

bool JogoDaVelha::verificar_jogada(int linha, int coluna, int jogador) const {
    // Verifica se a posição está dentro dos limites do tabuleiro
    if (linha < 0 || linha >= getLinhas() || coluna < 0 || coluna >= getColunas()) {
        return false;
    }
    
    // Verifica se a posição está vazia
    return (get_casa(linha, coluna) == 0);
}

int JogoDaVelha::ler_jogada(int linha, int coluna, int jogador) {
    if (!verificar_jogada(linha, coluna, jogador)) {
        return 0;  // Jogada inválida
    }
    
    // Coloca a marca do jogador (1 para X, 2 para O)
    Tabuleiro_[linha][coluna] = jogador;
    return 1;  // Jogada bem-sucedida
}

bool JogoDaVelha::testar_condicao_de_vitoria() const {
    // Verifica linhas
    for (int i = 0; i < getLinhas(); i++) {
        if (get_casa(i, 0) != 0 && 
            get_casa(i, 0) == get_casa(i, 1) && 
            get_casa(i, 1) == get_casa(i, 2)) {
            return true;
        }
    }
    
    // Verifica colunas
    for (int j = 0; j < getColunas(); j++) {
        if (get_casa(0, j) != 0 && 
            get_casa(0, j) == get_casa(1, j) && 
            get_casa(1, j) == get_casa(2, j)) {
            return true;
        }
    }
    
    // Verifica diagonais
    if (get_casa(0, 0) != 0 && 
        get_casa(0, 0) == get_casa(1, 1) && 
        get_casa(1, 1) == get_casa(2, 2)) {
        return true;
    }
    
    if (get_casa(0, 2) != 0 && 
        get_casa(0, 2) == get_casa(1, 1) && 
        get_casa(1, 1) == get_casa(2, 0)) {
        return true;
    }
    
    // Verifica empate (tabuleiro cheio)
    bool tem_espaco_vazio = false;
    for (int i = 0; i < getLinhas(); i++) {
        for (int j = 0; j < getColunas(); j++) {
            if (get_casa(i, j) == 0) {
                tem_espaco_vazio = true;
                break;
            }
        }
    }
    
    return !tem_espaco_vazio;  // Retorna true se o tabuleiro estiver cheio (empate)
}

int Lig4::imprimir_vetor(int jogador) const {
    int casa;
    for (int i = 0; i < this->getLinhas(); i++)
    {
        std::cout << VERMELHO << "|" << RESETAR; 
        for (int j = 0; j < this->getColunas(); j++)
        {
            casa = this->get_casa(i, j);
            if(casa == 0)
            {
                std::cout << FUNDO_VERDE << " " << RESETAR;
            }
            else if (casa == 1)
            {
                std::cout << "X";
            }
            else
            {
                std::cout << FUNDO_BRANCO << "O" << RESETAR;
            }
            std::cout << FUNDO_VERDE << "|" << RESETAR;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return 0;
}


int Lig4::determinar_vencedor() const {
    int linhas = getLinhas();
    int colunas = getColunas();

    for (int linha = 0; linha < linhas; ++linha) {
        for (int coluna = 0; coluna < colunas; ++coluna) {
            int jogador = get_casa(linha, coluna);
            if (jogador == 0) continue;

            // Verificar horizontal
            if (coluna + 3 < colunas &&
                get_casa(linha, coluna + 1) == jogador &&
                get_casa(linha, coluna + 2) == jogador &&
                get_casa(linha, coluna + 3) == jogador) {
                return jogador;
            }

            // Verificar vertical
            if (linha + 3 < linhas &&
                get_casa(linha + 1, coluna) == jogador &&
                get_casa(linha + 2, coluna) == jogador &&
                get_casa(linha + 3, coluna) == jogador) {
                return jogador;
            }

            // Verificar diagonal para baixo-direita
            if (linha + 3 < linhas && coluna + 3 < colunas &&
                get_casa(linha + 1, coluna + 1) == jogador &&
                get_casa(linha + 2, coluna + 2) == jogador &&
                get_casa(linha + 3, coluna + 3) == jogador) {
                return jogador;
            }

            // Verificar diagonal para cima-direita
            if (linha - 3 >= 0 && coluna + 3 < colunas &&
                get_casa(linha - 1, coluna + 1) == jogador &&
                get_casa(linha - 2, coluna + 2) == jogador &&
                get_casa(linha - 3, coluna + 3) == jogador) {
                return jogador;
            }
        }
    }

    return 0; // Nenhum vencedor encontrado
}

int Lig4::anunciar_vencedor() const {
    int vencedor = determinar_vencedor();
    bool empate = true;

    // Verifica se todas as colunas estão cheias (primeira linha)
    for (int col = 0; col < getColunas(); ++col) {
        if (get_casa(0, col) == 0) {
            empate = false;
            break;
        }
    }

    if (vencedor != 0) {
        std::cout << "\nJogador " << vencedor << " venceu!" << std::endl;
    } else if (empate) {
        std::cout << "\nEmpate! Todas as posições estão preenchidas." << std::endl;
    } else {
        std::cout << "\nO jogo ainda não terminou." << std::endl;
    }
    return vencedor;
}
bool Lig4::testar_condicao_de_vitoria() const {
    if (determinar_vencedor() != 0) {
        return true;
    }

    // Verifica se todas as colunas estão cheias (empate)
    for (int col = 0; col < getColunas(); ++col) {
        if (get_casa(0, col) == 0) {
            return false;
        }
    }
    return true;
}



bool Lig4::verificar_jogada(int linha, int coluna, int jogador) const {
        if (coluna < 0 || coluna >= getColunas()) {
            return false;  
        }

        for (int linha = 0; linha < getLinhas(); ++linha) {
            if (get_casa(linha, coluna) == 0) {
                return true;  
            }
        }
        return false;  
    }
int Lig4::ler_jogada(int linha, int coluna, int jogador) {
    if (!verificar_jogada(0, coluna, jogador)) { 
        return -1; // Indica jogada inválida
    }

    for (int i = getLinhas() - 1; i >= 0; --i) { 
        if (get_casa(i, coluna) == 0) {
            Tabuleiro_[i][coluna] = jogador;
            return i; // Retorna a linha onde a peça foi colocada
        }
    }
    return -1; // Não deve ocorrer se a jogada foi validada
}

Lig4::Lig4(int linhas, int colunas) : JogosDeTabuleiro(linhas, colunas) {
    // Inicializa o tabuleiro vazio
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            Tabuleiro_[i][j] = 0;
        }
    }
};
