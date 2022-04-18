#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int num;
	struct Node *next; //procurar entender isso
} node;

void add(node *inicio);
void remover(node *inicio);
void exibir(node *inicio);

int main(void) {

	node *inicio = (node*)malloc(sizeof(node));
  inicio->next = NULL;
  int opcao;
  
	do
	{
    printf("1 - Inserir\n");
		printf("2 - Remover\n");
		printf("3 - Exibir\n");
		printf("0 - Sair\n");
		printf("Digite a opcao desejada:\n");

		scanf("%d", &opcao);

		switch (opcao)
		{
  		case 1:
        add(inicio);
  			break;
  		case 2:
  			remover(inicio);
  			break;
  		case 3:
  			exibir(inicio);
  			break;
  		default:
  			break;
		}
	} while (opcao != 0);
	return 0;
}

void add(node *inicio) {
  node *novoNo = (node*)malloc(sizeof(node));
	novoNo->next = inicio->next;
  
  printf("Qual numero deseja inserir?\n");
	scanf("%d", &novoNo->num);
  inicio->next = novoNo;
}
  
void remover(node *inicio) {
	node *noAnterior = inicio;
	node *aux = inicio;
	
  while (aux->next != NULL)
	{
		noAnterior = aux;
		aux = aux->next;
	}

	noAnterior->next = NULL;
  if(aux->num)
    free(aux);
}

void exibir(node *inicio) {
	node *aux = inicio;
	if (inicio->next == NULL)
	{
		printf("Lista vazia\n");
		return;
	}
	do {
		aux = aux->next;
		printf("%d\n", aux->num);
	} while (aux->next != NULL);
}