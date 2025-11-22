#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

// --- CONFIGURAÇÕES DA MISSÃO ---
#define MAX_COMPONENTES 20

// --- ESTRUTURA DE DADOS ---
typedef struct {
    char nome[30];      // Ex: "Chip Central"
    char tipo[20];      // Ex: "Hardware", "Software"
    int prioridade;     // 1 (Baixa) a 10 (Alta/Crítica)
} Componente;

// --- VARIÁVEIS GLOBAIS ---
Componente torre[MAX_COMPONENTES];
int qtdComponentes = 0;
int ordenadoPorNome = 0; // Flag de segurança para a busca binária

// --- PROTÓTIPOS ---
void limparBuffer();
void lerTexto(char* buffer, int tamanho);
void menuPrincipal();
void cadastrarComponente();
void exibirTorre();

// Algoritmos de Ordenação (Obrigatórios)
void bubbleSortNome(long *comparacoes);
void insertionSortTipo(long *comparacoes);
void selectionSortPrioridade(long *comparacoes);

// Busca
void buscaBinariaPorNome();

int main() {

    
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.
    
    menuPrincipal();

    return 0;
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.

// --- INTERFACE DO SISTEMA ---

void menuPrincipal() {
    int opcao;
    clock_t inicio, fim;
    double tempoGasto;
    long comparacoes;

    do {
        printf("\n=== SISTEMA DE MONTAGEM: TORRE DE RESGATE (NIVEL MESTRE) ===\n");
        printf("1. Cadastrar Componente (Max %d)\n", MAX_COMPONENTES);
        printf("2. Listar Componentes Atuais\n");
        printf("3. Ordenar por NOME (Bubble Sort) -> Prepara p/ Busca Binaria\n");
        printf("4. Ordenar por TIPO (Insertion Sort)\n");
        printf("5. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("6. Localizar Modulo Ativador (Busca Binaria)\n");
        printf("0. Abortar Missao (Sair)\n");
        printf(">> Comando: ");
        scanf("%d", &opcao);
        limparBuffer();

        comparacoes = 0; // Reseta contador

        switch (opcao) {
            case 1:
                cadastrarComponente();
                break;
            case 2:
                exibirTorre();
                break;
            case 3:
                printf("\n[PROCESSANDO] Iniciando Bubble Sort por Nome...\n");
                inicio = clock(); // Inicia cronômetro
                bubbleSortNome(&comparacoes);
                fim = clock(); // Para cronômetro
                
                tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("[RELATORIO] Tempo: %f s | Comparacoes: %ld\n", tempoGasto, comparacoes);
                ordenadoPorNome = 1; // Habilita busca binária
                exibirTorre();
                break;

            case 4:
                printf("\n[PROCESSANDO] Iniciando Insertion Sort por Tipo...\n");
                inicio = clock();
                insertionSortTipo(&comparacoes);
                fim = clock();
                
                tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("[RELATORIO] Tempo: %f s | Comparacoes: %ld\n", tempoGasto, comparacoes);
                ordenadoPorNome = 0; // Bagunçou a ordem de nomes
                exibirTorre();
                break;

            case 5:
                printf("\n[PROCESSANDO] Iniciando Selection Sort por Prioridade...\n");
                inicio = clock();
                selectionSortPrioridade(&comparacoes);
                fim = clock();

                tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("[RELATORIO] Tempo: %f s | Comparacoes: %ld\n", tempoGasto, comparacoes);
                ordenadoPorNome = 0; // Bagunçou a ordem de nomes
                exibirTorre();
                break;

            case 6:
                buscaBinariaPorNome();
                break;

            case 0:
                printf("Encerrando protocolo de fuga...\n");
                break;

            default:
                printf("[ERRO] Comando desconhecido!\n");
        }
    } while (opcao != 0);
}

// --- FUNÇÕES DE ENTRADA/SAÍDA ---

void cadastrarComponente() {
    if (qtdComponentes >= MAX_COMPONENTES) {
        printf("\n[ALERTA] Capacidade maxima da torre atingida!\n");
        return;
    }

    Componente novo;
    printf("\n--- NOVO COMPONENTE ---\n");
    printf("Nome (ex: Chip, Antena): ");
    lerTexto(novo.nome, 30);
    printf("Tipo (ex: Controle, Energia): ");
    lerTexto(novo.tipo, 20);
    printf("Prioridade (1-10): ");
    scanf("%d", &novo.prioridade);
    limparBuffer();

    torre[qtdComponentes] = novo;
    qtdComponentes++;
    ordenadoPorNome = 0; // Novo item inserido no fim, lista não está mais ordenada
    printf("[OK] Componente integrado ao sistema.\n");
}

void exibirTorre() {
    if (qtdComponentes == 0) {
        printf("\n[AVISO] Nenhum componente instalado na torre.\n");
        return;
    }
    printf("\n--- STATUS DA TORRE (%d/%d) ---\n", qtdComponentes, MAX_COMPONENTES);
    printf("%-20s | %-15s | %s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < qtdComponentes; i++) {
        printf("%-20s | %-15s | %d\n", torre[i].nome, torre[i].tipo, torre[i].prioridade);
    }
    printf("--------------------------------------------------------\n");
}

// --- ALGORITMOS DE ORDENAÇÃO ---

// 1. Bubble Sort (Por Nome)
void bubbleSortNome(long *comparacoes) {
    Componente aux;
    for (int i = 0; i < qtdComponentes - 1; i++) {
        for (int j = 0; j < qtdComponentes - i - 1; j++) {
            (*comparacoes)++; // Conta a comparação abaixo
            // strcmp > 0 significa que a primeira string é "maior" (vem depois) alfabeticamente
            if (strcasecmp(torre[j].nome, torre[j + 1].nome) > 0) {
                aux = torre[j];
                torre[j] = torre[j + 1];
                torre[j + 1] = aux;
            }
        }
    }
}

// 2. Insertion Sort (Por Tipo)
void insertionSortTipo(long *comparacoes) {
    Componente pivo;
    int j;
    for (int i = 1; i < qtdComponentes; i++) {
        pivo = torre[i];
        j = i - 1;

        // Move os elementos maiores que o pivô para a frente
        while (j >= 0) {
            (*comparacoes)++;
            if (strcasecmp(torre[j].tipo, pivo.tipo) > 0) {
                torre[j + 1] = torre[j];
                j = j - 1;
            } else {
                break; // Encontrou a posição, para de comparar
            }
        }
        torre[j + 1] = pivo;
    }
}

// 3. Selection Sort (Por Prioridade - Decrescente: Maior prioridade primeiro)
void selectionSortPrioridade(long *comparacoes) {
    int idxMaior;
    Componente aux;

    for (int i = 0; i < qtdComponentes - 1; i++) {
        idxMaior = i;
        for (int j = i + 1; j < qtdComponentes; j++) {
            (*comparacoes)++;
            // Queremos os de MAIOR prioridade no topo (ordem decrescente)
            if (torre[j].prioridade > torre[idxMaior].prioridade) {
                idxMaior = j;
            }
        }
        // Troca se encontrou alguém com prioridade maior
        if (idxMaior != i) {
            aux = torre[i];
            torre[i] = torre[idxMaior];
            torre[idxMaior] = aux;
        }
    }
}

// --- BUSCA BINÁRIA ---

void buscaBinariaPorNome() {
    if (!ordenadoPorNome) {
        printf("\n[ERRO CRITICO] Sistema nao calibrado! Execute a Ordenacao por NOME (Opcao 3) primeiro.\n");
        return;
    }
    if (qtdComponentes == 0) return;

    char alvo[30];
    printf("\nDigite o nome do Modulo Ativador: ");
    lerTexto(alvo, 30);

    int inicio = 0;
    int fim = qtdComponentes - 1;
    int meio;
    int achou = 0;
    long compsBusca = 0;

    clock_t tIni = clock(); // Medindo tempo da busca também

    while (inicio <= fim) {
        compsBusca++;
        meio = (inicio + fim) / 2;
        
        int resultado = strcasecmp(alvo, torre[meio].nome);

        if (resultado == 0) {
            printf("\n[SUCESSO] Modulo '%s' localizado no slot %d!\n", torre[meio].nome, meio);
            printf("Tipo: %s | Prioridade: %d\n", torre[meio].tipo, torre[meio].prioridade);
            achou = 1;
            break;
        } else if (resultado < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    clock_t tFim = clock();
    double tempo = ((double)(tFim - tIni)) / CLOCKS_PER_SEC;

    if (!achou) {
        printf("\n[FALHA] Modulo '%s' nao encontrado nos escombros.\n", alvo);
    }
    printf("[METRICAS] Tempo de busca: %f s | Comparacoes: %ld\n", tempo, compsBusca);
}

// --- UTILITÁRIOS ---

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void lerTexto(char* buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}