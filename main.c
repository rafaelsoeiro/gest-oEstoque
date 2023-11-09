#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#define TAMANHO 5

struct tipo_produto {
    int id;
    char nomeProduto[50];
    float preco;
    int quantidade;
};

// gerar id aleatorio a partir da data atual
int geraId(int min, int max) {
    srand(time(NULL));
    int id = (rand() % (max - min + 1)) + min;
    return id;
}

int procuraEspacoVazio(struct tipo_produto produtos[]) {
    for (int i = 0; i < TAMANHO; i++) {
        if (produtos[i].id == -1) {
            return i;
        }
    }
  return -1;
}
void inicializaEstoque(struct tipo_produto produtos[]) {
  for (int i = 0; i < TAMANHO; i++) {
    produtos[i].id = -1;
    strcpy(produtos[i].nomeProduto, "disponivel");
    produtos[i].quantidade = -1;
    produtos[i].preco = -1;
  }
}
int validaCampos(char nomeProduto[],float precoUnitario,int quantidadeProduto){
     int tamanhoNomeProduto=strlen(nomeProduto);
    if(tamanhoNomeProduto>0 && quantidadeProduto>0 && precoUnitario>0){
        return 1;
    }else{
        return -1;
    }
}
void adicionarProduto(struct tipo_produto produtos[], char nomeProduto[],float precoUnitario,int quantidadeProduto) {
    int id=procuraEspacoVazio(produtos);
    int tamanhoNomeProduto=strlen(nomeProduto);
    if(id==-1){
        printf("---------impossivel cadastrar produto! --------- \n");
        return ;
    }

    printf("%d %s %.2f %d\n",id,nomeProduto,precoUnitario,quantidadeProduto);

    if(validaCampos(nomeProduto,precoUnitario,quantidadeProduto)==1){
        produtos[id].id = geraId(999, 9999);
        strcpy(produtos[id].nomeProduto, nomeProduto);
        produtos[id].quantidade = quantidadeProduto;
        produtos[id].preco = precoUnitario;
        printf("--------- Produto cadastrado com sucesso! ---------\n");
    }else{
        printf("Os valores informados são invalidos! Tente Novamente!\n");
    }
}

void listarProdutos(struct tipo_produto produtos[]) {
    if(procuraEspacoVazio(produtos)==-1 ||procuraEspacoVazio(produtos)==0){
        printf(" Estoque vazio!\n");
    }else{
        printf("- ID | NOME PRODUTO | PREÇO UND | QUANTIDADE\n");
        for (int i = 0; i < TAMANHO; i++) {
        //printf("- %d | %s | %.2f | %d\n", produtos[i].id, produtos[i].nomeProduto, produtos[i].preco, produtos[i].quantidade);
            if (produtos[i].id == -1) {

            } else {
                printf("- %d | %s | %.2f | %d\n", produtos[i].id, produtos[i].nomeProduto, produtos[i].preco, produtos[i].quantidade);
            }
        }
    }
}
void atualizarProduto(struct tipo_produto produtos[]) {
    int id, opcao;
    listarProdutos(produtos);
    printf("\nInforme o ID do produto que deseja atualizar: ");
    scanf("%d", &id);

    for (int i = 0; i < TAMANHO; i++) {
        if (produtos[i].id != -1) {
            printf("Produto encontrado.\n");

            printf("Novo nome: ");
            scanf("%s", produtos[i].nomeProduto);
            printf("Novo preço: ");
            scanf("%f", &produtos[i].preco);
            printf("Nova quantidade: ");
            scanf("%d", &produtos[i].quantidade);
            printf("Produto atualizado com sucesso!\n");

        }
    }


}

void deletarProduto(struct tipo_produto produtos[]) {
    int id=0;
    int produtoEncontrado = 0;
    listarProdutos(produtos);
    printf("\nInforme o id do produto que deseja deletar: ");
    scanf("%d",&id);
    for(int i = 0; i < TAMANHO; i++){
        if(id == produtos[i].id){
            produtos[i].id = -1;
            strcpy(produtos[i].nomeProduto, "disponivel");
            produtos[i].quantidade = -1;
            produtos[i].preco = -1;
            printf("Produto deletado com sucesso!");
            produtoEncontrado = 1;
            break;
        }
    }
    if (!produtoEncontrado) {
        printf("Erro ao deletar o produto. Produto não encontrado.");
    }
}

int main(void) {
    setlocale(LC_ALL, "portuguese");

    int op=0,continuar=1;
    struct tipo_produto produtos[TAMANHO];
    inicializaEstoque(produtos);

    char nomeProduto[30]= "";
    int quantidadeProduto=0;
    float precoUnitario=0;
    
    do{
        nomeProduto[30];
        quantidadeProduto=0;
        precoUnitario=0;
        printf("-------------------- Gestão de estoque ----------------\n");
        printf("1-Adicionar\n2-Listar\n3-Atualizar\n4-Deletar\n0-Encerrar\n\nOpção: ");
        scanf("%d",&op);
        switch(op){
        case 0:
            continuar=0;
            break;
        break;
        case 1:
            printf("Nome do produto: ");
            scanf("%s",nomeProduto);
            printf("Preço do produto: ");
            scanf("%f",&precoUnitario);
            printf("Quantidade: ");
            scanf("%d",&quantidadeProduto);

            adicionarProduto(produtos,nomeProduto,precoUnitario,quantidadeProduto);
            break;
        case 2:
            listarProdutos(produtos);
            break;
        case 3:
            atualizarProduto(produtos);
            break;
        case 4:
           deletarProduto(produtos);
            break;
        default:
           printf("Opção invalida");
            break;
        }
    }while(continuar==1);
      return 0;
}
