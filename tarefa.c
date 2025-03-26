#include <stdlib.h>
#include <stdio.h>
#include <string.h>  

#define max 3

typedef struct tarefa{
    char nome[50];
    struct tarefa * prox;
}Tarefa;

typedef struct pilha{
    struct tarefa * topo;
}Pilha;

typedef struct lista{
    Tarefa * inicio;
}Lista;

Lista* inicializaLista(){
    Lista * lista = (Lista*)malloc(sizeof(Lista));
    if(lista == NULL){
        printf("Erro ao alocar memoria para lista.\n");
        return NULL;
    }
    lista->inicio = NULL;
    return lista;
}


Pilha * inicializaPilha(){
    Pilha * pilha = (Pilha*)malloc(sizeof(Pilha));
    if(pilha == NULL){
        printf("Erro ao alocar memoria.\n");
        return NULL;
    }
    pilha->topo = NULL;
    return pilha;
}

Tarefa * criaTarefa(char * nome){
    Tarefa * tarefa = (Tarefa*)malloc(sizeof(Tarefa));
    if(tarefa == NULL){
        printf("Erro ao alocar memoria.\n");
        return NULL;
    }
    strcpy(tarefa->nome, nome);
    tarefa->prox = NULL;
    return tarefa;
}

void pilhaPush(Tarefa ** topo, Tarefa * tarefa){
    tarefa->prox = *topo;
    *topo = tarefa;

    
}

Tarefa * pegarTopoPilha(Tarefa ** topo){
    Tarefa * removida = *topo;
    *topo = removida->prox;
    removida->prox = NULL;
    return removida;
}

void addLista(Tarefa ** lista, Tarefa * tarefa){
    
    if(*lista == NULL){
        *lista = tarefa;
        return;
    }
    else{
        Tarefa * aux = *lista;
        while (aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = tarefa; 
    }
    
}

void exibir(Tarefa * tarefa){
    int cont = 0;
    printf("\n");
    while (tarefa != NULL){
        cont++;
        printf("%d - %s \n", cont, tarefa->nome);
        tarefa = tarefa->prox;
    }
}

void liberarTarefas(Tarefa * tarefa){
    Tarefa * temp;
    while (tarefa != NULL){
        temp = tarefa;
        tarefa = tarefa->prox;
        free(temp);
    }
}

int main(){
    
    Pilha * pilha = inicializaPilha();
    Lista * lista = inicializaLista();

    int opcao;
    int contPilha = 0;

    do{
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Adicionar nova tarefa\n");
        printf("2. Marcar tarefa como concluida\n");
        printf("3. Exibir tarefas pendentes\n");
        printf("4. Exibir lista de tarefas concluidas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao){
        case 1:
            char nome[50];
            if(contPilha == max){
                printf("\nPilha cheia, limite maximo de tarefas na pilha é 3.\n");
            }
            else{
                printf("Nome da tarefa: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                printf("Adicionando a pilha: %s\n", nome);
                
                //chamada
                pilhaPush(&pilha->topo, criaTarefa(nome));
                contPilha++;
            }
            break;
        case 2:
            if(pilha->topo != NULL){
                printf("Tarefa concluida: %s\n", pilha->topo->nome);
                
                Tarefa * tarefaRemovida = pegarTopoPilha(&pilha->topo);
                Tarefa * tarefaNova = criaTarefa(tarefaRemovida->nome);

                //chamada
                addLista(&lista->inicio, tarefaNova); 
                free(tarefaRemovida);
                contPilha--;
            }
            else{
                printf("Não ha tarefas para marcar como concluida.\n");
            }
            break;
        case 3:
            if(pilha->topo != NULL){
                printf("\n==== Pilha de tarefas pendentes ====");
                exibir(pilha->topo);
            }
            else{
                printf("\nPilha vazia.\n");
            }
            break;
        case 4:
            if(lista->inicio != NULL){
                printf("\n==== lista de tarefas concluidas ====");
                exibir(lista->inicio);
            }
            else{
                printf("\nLista de tarefas concluídas vazia.\n");
            }
            break;
        case 0:
            liberarTarefas(pilha->topo); 
            liberarTarefas(lista->inicio); 
            
            free(pilha);
            free(lista);
            
            printf("Saindo do programa...");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
            break;
        }
    }while (opcao != 0);
    
    return 0;
}