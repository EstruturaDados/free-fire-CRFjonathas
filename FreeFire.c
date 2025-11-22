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

Item mochila[QNT_ITENS];
int numItens = 0;

void Menu();

void AdicionarItem();
void RemoverItem();
void ListarItem();

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
        Menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer do teclado

        switch (opcao) {
            case 1:
                AdicionarItem();
                break;
            case 2:
                RemoverItem();
                break;
            case 3:
                ListarItens();
                break;
            case 0:
                printf("Saindo do inventario...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
        
        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();
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

void Menu() {
    // system("cls"); // Use "clear" no Linux/Mac se preferir limpar a tela
    printf("\n=== MOCHILA FREE FIRE (Nivel Novato) ===\n");
    printf("1. Adicionar Item\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens\n");
    printf("0. Sair\n");
    printf("========================================\n");
}

void AdicionarItem() {
    if (numItens >= QNT_ITENS) {
        printf("\nA mochila esta cheia! Remova um item antes de adicionar outro.\n");
        return;
    }

    Item novoItem;

    printf("\n--- Adicionar Novo Item ---\n");
    
    printf("Nome: ");
    scanf(" %[^\n]", novoItem.nome); // Lê string com espaços
    
    printf("Tipo (ex: Arma, Municao, Cura): ");
    scanf(" %[^\n]", novoItem.tipo);
    
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    getchar(); // Limpar buffer após ler inteiro

    // Salva no vetor e incrementa o contador
    mochila[numItens] = novoItem;
    numItens++;

    printf("Item cadastrado com sucesso!\n");
}

void RemoverItem() {
    if (numItens == 0) {
        printf("\nA mochila esta vazia.\n");
        return;
    }

    char nomeBusca[30];
    int encontrado = 0;

    printf("\n--- Remover Item ---\n");
    printf("Informe o nome do item para remover: ");
    scanf(" %[^\n]", nomeBusca);

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            // Item encontrado. Deslocar os itens seguintes para "tapar o buraco"
            for (int j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            
            numItens--; // Diminui a quantidade total
            encontrado = 1;
            printf("Item '%s' removido com sucesso!\n", nomeBusca);
            break; // Sai do loop pois já removeu
        }
    }

    if (!encontrado) {
        printf("Item nao encontrado na mochila.\n");
    }
}

void ListarItens() {
    if (numItens == 0) {
        printf("\nA mochila esta vazia.\n");
        return;
    }

    printf("\n--- Conteudo da Mochila (%d/%d) ---\n", numItens, QNT_ITENS);
    printf("%-30s | %-20s | %s\n", "NOME", "TIPO", "QTD");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < numItens; i++) {
        printf("%-30s | %-20s | %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}