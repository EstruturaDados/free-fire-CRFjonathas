#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

#define QNT_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dado;
    struct No* proximo;
} No;

Item mochilaVetor[QNT_ITENS];
int numItensVetor = 0;
int vetorOrdenado = 0;

No* inicioLista = NULL;

void MenuPrincipal();
void MenuVetor();
void MenuLista();
void AdicionarItemVetor();
void RemoverItemVetor();
void ListarItensVetor();
void OrdenarVetor();      
void BuscaBinariaVetor(); 
void BuscaSequencialVetor();
void AdicionarItemLista();
void RemoverItemLista();
void ListarItensLista();
void BuscaSequencialLista();

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
    
    int opcao;
    do {
        MenuPrincipal();
        printf("Escolha o modo de armazenamento: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                MenuVetor();
                break;
            case 2:
                MenuLista();
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

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

void MenuPrincipal() {
    printf("\n=== SISTEMA DE MOCHILA (Nivel Aventureiro) ===\n");
    printf("1. Modo Vetor (Lista Sequencial + Busca Binaria)\n");
    printf("2. Modo Lista Encadeada (Estrutura Dinamica)\n");
    printf("0. Sair\n");
    printf("==============================================\n");
}

void MenuVetor() {
    int opcao;
    do {
        printf("\n--- MOCHILA VETOR ---\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Ordenar por Nome (Necessario para Busca Binaria)\n");
        printf("5. Busca Sequencial (Comum)\n");
        printf("6. Busca Binaria (Rapida)\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: AdicionarItemVetor(); break;
            case 2: RemoverItemVetor(); break;
            case 3: ListarItensVetor(); break;
            case 4: OrdenarVetor(); break;
            case 5: BuscaSequencialVetor(); break;
            case 6: BuscaBinariaVetor(); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void MenuLista() {
    int opcao;
    do {
        printf("\n--- MOCHILA LISTA ENCADEADA ---\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Busca Sequencial\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: AdicionarItemLista(); break;
            case 2: RemoverItemLista(); break;
            case 3: ListarItensLista(); break;
            case 4: BuscaSequencialLista(); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

// --- IMPLEMENTAÇÃO VETOR (Baseado no seu código original) ---

void AdicionarItemVetor() {
    if (numItensVetor >= QNT_ITENS) {
        printf("\nA mochila (Vetor) esta cheia!\n");
        return;
    }

    Item novoItem;
    printf("\n--- Adicionar (Vetor) ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", novoItem.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novoItem.tipo);
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    getchar();

    mochilaVetor[numItensVetor] = novoItem;
    numItensVetor++;
    vetorOrdenado = 0; // Bagunçou a ordem

    printf("Item cadastrado no vetor!\n");
}

void RemoverItemVetor() {
    if (numItensVetor == 0) {
        printf("\nMochila vazia.\n");
        return;
    }
    char nomeBusca[30];
    printf("Nome para remover: ");
    scanf(" %[^\n]", nomeBusca);

    int encontrado = 0;
    for (int i = 0; i < numItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            // Deslocar itens
            for (int j = i; j < numItensVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            numItensVetor--;
            encontrado = 1;
            printf("Item removido!\n");
            break;
        }
    }
    if (!encontrado) printf("Item nao encontrado.\n");
}

void ListarItensVetor() {
    if (numItensVetor == 0) {
        printf("\nMochila vazia.\n");
        return;
    }
    printf("\n--- Conteudo Vetor ---\n");
    for (int i = 0; i < numItensVetor; i++) {
        printf("%s | %s | %d\n", mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

void OrdenarVetor() { // Bubble Sort
    if (numItensVetor < 2) {
        printf("\nPoucos itens para ordenar.\n");
        vetorOrdenado = 1; 
        return;
    }
    Item temp;
    for (int i = 0; i < numItensVetor - 1; i++) {
        for (int j = 0; j < numItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j+1].nome) > 0) {
                temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j+1];
                mochilaVetor[j+1] = temp;
            }
        }
    }
    vetorOrdenado = 1;
    printf("\nVetor ordenado por nome!\n");
    ListarItensVetor();
}

void BuscaSequencialVetor() {
    char nome[30];
    printf("Buscar (Sequencial): ");
    scanf(" %[^\n]", nome);
    
    int comparacoes = 0;
    for(int i=0; i<numItensVetor; i++) {
        comparacoes++;
        if(strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("Encontrado: %s (Comparacoes: %d)\n", mochilaVetor[i].nome, comparacoes);
            return;
        }
    }
    printf("Nao encontrado. (Comparacoes: %d)\n", comparacoes);
}

void BuscaBinariaVetor() {
    if (!vetorOrdenado) {
        printf("\nErro: Ordene o vetor primeiro (Opcao 4)!\n");
        return;
    }
    char nome[30];
    printf("Buscar (Binaria): ");
    scanf(" %[^\n]", nome);

    int inicio = 0, fim = numItensVetor - 1, meio;
    int comparacoes = 0;

    while (inicio <= fim) {
        comparacoes++;
        meio = (inicio + fim) / 2;
        int res = strcmp(nome, mochilaVetor[meio].nome);

        if (res == 0) {
            printf("Encontrado: %s (Comparacoes: %d)\n", mochilaVetor[meio].nome, comparacoes);
            return;
        } else if (res < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    printf("Nao encontrado. (Comparacoes: %d)\n", comparacoes);
}

// --- IMPLEMENTAÇÃO LISTA ENCADEADA ---

void AdicionarItemLista() {
    No* novoNo = (No*)malloc(sizeof(No));
    
    printf("\n--- Adicionar (Lista) ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", novoNo->dado.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novoNo->dado.tipo);
    printf("Quantidade: ");
    scanf("%d", &novoNo->dado.quantidade);
    getchar();

    // Inserir no início
    novoNo->proximo = inicioLista;
    inicioLista = novoNo;
    printf("Item adicionado a lista!\n");
}

void RemoverItemLista() {
    if (inicioLista == NULL) {
        printf("\nLista vazia.\n");
        return;
    }
    char nomeBusca[30];
    printf("Nome para remover: ");
    scanf(" %[^\n]", nomeBusca);

    No* atual = inicioLista;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dado.nome, nomeBusca) == 0) {
            if (anterior == NULL) {
                inicioLista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Item removido da lista!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item nao encontrado na lista.\n");
}

void ListarItensLista() {
    if (inicioLista == NULL) {
        printf("\nLista vazia.\n");
        return;
    }
    printf("\n--- Conteudo Lista ---\n");
    No* atual = inicioLista;
    while (atual != NULL) {
        printf("%s | %s | %d\n", atual->dado.nome, atual->dado.tipo, atual->dado.quantidade);
        atual = atual->proximo;
    }
}

void BuscaSequencialLista() {
    char nome[30];
    printf("Buscar na Lista: ");
    scanf(" %[^\n]", nome);
    
    No* atual = inicioLista;
    int comparacoes = 0;
    
    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dado.nome, nome) == 0) {
            printf("Encontrado: %s (Comparacoes: %d)\n", atual->dado.nome, comparacoes);
            return;
        }
        atual = atual->proximo;
    }
    printf("Nao encontrado. (Comparacoes: %d)\n", comparacoes);
}