#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre

// --- CONFIGURAÇÕES DA MISSÃO ---
#define MAX_COMPONENTES 20

// --- ESTRUTURA DE DADOS ---
// Enumeração para os critérios de ordenação (Requisito README)
typedef enum {
    CRITERIO_NOME = 1,
    CRITERIO_TIPO,
    CRITERIO_PRIORIDADE
} CriterioOrdenacao;

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;     // Requisito README: Adicionado campo Quantidade
    int prioridade;     // Requisito README: Prioridade (1 a 5)
} Componente;

// --- VARIÁVEIS GLOBAIS ---
Componente torre[MAX_COMPONENTES];
int qtdComponentes = 0;
bool ordenadoPorNome = false; // Requisito README: Uso de bool para controle de estado

// --- PROTÓTIPOS ---
void limparBuffer();
void lerTexto(char* buffer, int tamanho);
void menuPrincipal();
void cadastrarComponente();
void exibirTorre();

// Algoritmos de Ordenação
void bubbleSortNome(long *comparacoes);
void insertionSortTipo(long *comparacoes);
void selectionSortPrioridade(long *comparacoes);

// Busca
void buscaBinariaPorNome();

int main() {
    menuPrincipal();
    return 0;
}

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
        printf("3. Ordenar por NOME (Bubble Sort)\n");
        printf("4. Ordenar por TIPO (Insertion Sort)\n");
        printf("5. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("6. Localizar Modulo Ativador (Busca Binaria)\n");
        printf("0. Abortar Missao (Sair)\n");
        printf(">> Comando: ");
        scanf("%d", &opcao);
        limparBuffer();

        comparacoes = 0;

        switch (opcao) {
            case 1:
                cadastrarComponente();
                break;
            case 2:
                exibirTorre();
                break;
            case 3: // CRITERIO_NOME
                printf("\n[PROCESSANDO] Iniciando Bubble Sort por Nome...\n");
                inicio = clock();
                bubbleSortNome(&comparacoes);
                fim = clock();
                
                tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("[RELATORIO] Tempo: %f s | Comparacoes: %ld\n", tempoGasto, comparacoes);
                ordenadoPorNome = true; 
                exibirTorre();
                break;

            case 4: // CRITERIO_TIPO
                printf("\n[PROCESSANDO] Iniciando Insertion Sort por Tipo...\n");
                inicio = clock();
                insertionSortTipo(&comparacoes);
                fim = clock();
                
                tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("[RELATORIO] Tempo: %f s | Comparacoes: %ld\n", tempoGasto, comparacoes);
                ordenadoPorNome = false; 
                exibirTorre();
                break;

            case 5: // CRITERIO_PRIORIDADE
                printf("\n[PROCESSANDO] Iniciando Selection Sort por Prioridade...\n");
                inicio = clock();
                selectionSortPrioridade(&comparacoes);
                fim = clock();

                tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("[RELATORIO] Tempo: %f s | Comparacoes: %ld\n", tempoGasto, comparacoes);
                ordenadoPorNome = false; 
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
    
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade); // Campo adicionado

    // Validação de Prioridade (1-5) conforme README
    do {
        printf("Prioridade (1-5): ");
        scanf("%d", &novo.prioridade);
        if (novo.prioridade < 1 || novo.prioridade > 5) {
            printf("[ERRO] Prioridade deve ser entre 1 e 5.\n");
        }
    } while (novo.prioridade < 1 || novo.prioridade > 5);
    
    limparBuffer();

    torre[qtdComponentes] = novo;
    qtdComponentes++;
    ordenadoPorNome = false; // Novo item inserido, lista não está mais ordenada
    printf("[OK] Componente integrado ao sistema.\n");
}

void exibirTorre() {
    if (qtdComponentes == 0) {
        printf("\n[AVISO] Nenhum componente instalado na torre.\n");
        return;
    }
    printf("\n--- STATUS DA TORRE (%d/%d) ---\n", qtdComponentes, MAX_COMPONENTES);
    // Adicionado coluna QTD
    printf("%-20s | %-15s | %-5s | %s\n", "NOME", "TIPO", "QTD", "PRIORIDADE");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < qtdComponentes; i++) {
        printf("%-20s | %-15s | %-5d | %d\n", 
            torre[i].nome, 
            torre[i].tipo, 
            torre[i].quantidade, 
            torre[i].prioridade);
    }
    printf("------------------------------------------------------------------\n");
}

// --- ALGORITMOS DE ORDENAÇÃO ---

// 1. Bubble Sort (Por Nome)
void bubbleSortNome(long *comparacoes) {
    Componente aux;
    for (int i = 0; i < qtdComponentes - 1; i++) {
        for (int j = 0; j < qtdComponentes - i - 1; j++) {
            (*comparacoes)++;
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

        while (j >= 0) {
            (*comparacoes)++;
            if (strcasecmp(torre[j].tipo, pivo.tipo) > 0) {
                torre[j + 1] = torre[j];
                j = j - 1;
            } else {
                break;
            }
        }
        torre[j + 1] = pivo;
    }
}

// 3. Selection Sort (Por Prioridade - Decrescente)
void selectionSortPrioridade(long *comparacoes) {
    int idxMaior;
    Componente aux;

    for (int i = 0; i < qtdComponentes - 1; i++) {
        idxMaior = i;
        for (int j = i + 1; j < qtdComponentes; j++) {
            (*comparacoes)++;
            if (torre[j].prioridade > torre[idxMaior].prioridade) {
                idxMaior = j;
            }
        }
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
    bool achou = false; // Uso de bool
    long compsBusca = 0;

    clock_t tIni = clock();

    while (inicio <= fim) {
        compsBusca++;
        meio = (inicio + fim) / 2;
        
        int resultado = strcasecmp(alvo, torre[meio].nome);

        if (resultado == 0) {
            printf("\n[SUCESSO] Modulo '%s' localizado no slot %d!\n", torre[meio].nome, meio);
            printf("Tipo: %s | Qtd: %d | Prioridade: %d\n", 
                torre[meio].tipo, torre[meio].quantidade, torre[meio].prioridade);
            achou = true;
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