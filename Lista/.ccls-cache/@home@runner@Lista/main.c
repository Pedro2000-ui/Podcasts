#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

typedef struct PalavraChave {
  char key[65];
	struct PalavraChave *next; 
} palavrachave;

typedef struct Episodio {
  char nomeEpisodio[65];
	int numEpisodio;
  struct PalavraChave *keyEp;
  struct Episodio *next;
} episodio;

typedef struct Podcast {
  char nomePodcast[65];
	int numPodcast;
  int idPodcast;
  struct Episodio *ep;
  struct Podcast *next; 
} podcast;

int adicionar(podcast *inicio, int idPodcast) {
  system("clear");
  printf("Máx de caracteres = 64\nDigite as palavras sem espaço!!\n");
  int continuar, continuarKeyword;
  int numEpisodio = 1;
  podcast *newPodcast = (podcast*)malloc(sizeof(podcast));
  newPodcast->ep = (episodio*)malloc(sizeof(episodio));
  newPodcast->idPodcast = idPodcast;
  printf("Nome do Podcast: ");
  scanf("%s", newPodcast->nomePodcast);
  newPodcast->ep->next = NULL;
  episodio *auxEp = newPodcast->ep;
  podcast *aux = inicio;
  do {
    episodio *novoEpisodio = (episodio*)malloc(sizeof(episodio));
    printf("Nome do Episódio: ");
    scanf("%s", novoEpisodio->nomeEpisodio);
    novoEpisodio->numEpisodio = numEpisodio;
    numEpisodio++;
    novoEpisodio->keyEp = (palavrachave*)malloc(sizeof(palavrachave));
    novoEpisodio->keyEp->next = NULL;
    do {
      palavrachave *novaPalavraChave = (palavrachave*)malloc(sizeof(palavrachave));
      printf("Palavra Chave: ");
      scanf("%s", novaPalavraChave->key);
      novaPalavraChave->next = novoEpisodio->keyEp->next; //Inserindo a palavra chave no começo da lista
      novoEpisodio->keyEp->next = novaPalavraChave; 
      printf("Inserir mais palavras chaves no episódio %s?\n1 - Sim 0 - Não\n", novoEpisodio->nomeEpisodio);
      scanf("%d", &continuarKeyword);
    } while(continuarKeyword);
    
    while(auxEp->next != NULL) { //Inserindo o Ep no fim da lista
      auxEp = auxEp->next;
    }
    auxEp->next = novoEpisodio;
    novoEpisodio->next = NULL;
    printf("Inserir mais Episódios no podcast %s?\n1 - Sim 0 - Não\n", newPodcast->nomePodcast);
    scanf("%d", &continuar);
  } while(continuar);
  
  while(aux->next != NULL) { //Inserindo o Podcast no fim da lista
    aux = aux->next;
  }
  aux->next = newPodcast;
  newPodcast->next = NULL;
  printf("Sucesso ao adicionar!\n");
  idPodcast++;
  return idPodcast;
}

void relatorio (podcast *inicio) {
  system("clear");
  printf("\n");
  if (inicio->next == NULL) {
    printf("Lista vazia!\n");
    return;
  }
  podcast *aux = inicio;
  while(aux->next != NULL){
    aux = aux->next;
    episodio *auxEp = aux->ep;
    printf("Podcast: %s(id: %d)\n", aux->nomePodcast, aux->idPodcast);
    while(auxEp->next != NULL) {
      auxEp = auxEp->next;
      palavrachave *auxKeyWord = auxEp->keyEp;
      printf("  Episódio: %s(Num: %d)\n", auxEp->nomeEpisodio, auxEp->numEpisodio);
      printf("    keyWords: {");
      while(auxKeyWord->next != NULL) {
        auxKeyWord = auxKeyWord->next;
        printf("%s, ", auxKeyWord->key);
      }
      printf("}");
      printf("\n");
    } 
    printf("\n");
  }
}

void removerEpisodio (podcast *inicio, int removerPodcast, int removerEpisodio) {
  system("clear");
  if (inicio->next == NULL) {
    printf("Não é possível remover, lista vazia!\n");
    return;
  }
  podcast *aux = inicio;
  podcast *noAnterior = inicio;
  while(aux->next != NULL) {
    noAnterior = aux;
    aux = aux->next;
    episodio *auxEp = aux->ep;
    episodio *noAnteriorEp = auxEp;
    if(removerPodcast == aux->idPodcast) {
      while(auxEp->next != NULL) {
        noAnteriorEp = auxEp;
        auxEp = auxEp->next;
        if(removerEpisodio == auxEp->numEpisodio) {
          noAnteriorEp->next = auxEp->next;
          printf("Episódio %s do Podcast %s removido com sucesso", auxEp->nomeEpisodio, aux->nomePodcast);
          palavrachave *auxPalavraChave = auxEp->keyEp;
          palavrachave *noAnteriorPalavraChave = auxPalavraChave;
          while(noAnteriorPalavraChave->next != NULL) {
            noAnteriorPalavraChave = auxPalavraChave;
            auxPalavraChave = auxPalavraChave->next;
            free(noAnteriorPalavraChave);
          }
          free(auxEp);
          return;
        }
      }
      printf("Episódio não encontrado!");
      return;
    }
  }
  printf("Podcast não encontrado!");
}

void exibirAtual (podcast *inicio) {
  system("clear");
  printf("\n");
  if (inicio->next == NULL) {
    printf("Lista vazia!\n");
    return;
  }
  podcast *atualPod;
  episodio *atualEp;
  podcast *aux = inicio;
  aux = aux->next;
  printf("Podcast: %s(id: %d)\n", aux->nomePodcast, aux->idPodcast);
  episodio *auxEp = aux->ep;
  if(auxEp->next == NULL) {
    return;
  }
  auxEp = auxEp->next;
  printf("  Episódio: %s(em reprodução)\n", auxEp->nomeEpisodio);
}

void proximoEpisodio (podcast *inicio, bool shuffleAtual) { 
  system("clear");
  printf("\n");
  podcast *aux = inicio;
  aux = aux->next;
  printf("Podcast: %s\n", aux->nomePodcast);
  episodio *auxEp = aux->ep;
  if(auxEp->next == NULL) {
    return;
  }
  printf("  Episódio: %s (em reprodução)\n", auxEp->next->nomeEpisodio);
  if(shuffleAtual) {
    auxEp = auxEp->next->next;
    if(auxEp->next != NULL) 
      printf("  Episódio: %s (próximo a tocar)\n", auxEp->next->next->nomeEpisodio);
    else if (auxEp != NULL)
      printf("  Episódio: %s (próximo a tocar)\n", auxEp->nomeEpisodio);
    else
      printf("  Não há mais episódios nesse podcast!\n");
  }  
  else {
    auxEp = auxEp->next->next;
    if(auxEp != NULL) 
      printf("  Episódio: %s (próximo a tocar)\n", auxEp->nomeEpisodio);
    else 
      printf("  Não há mais episódios nesse podcast!\n");
  }  
}

bool shuffle (bool shuffleAtual) {
  system("clear");
  if (!shuffleAtual) 
    printf("Shuffle ativado!");
  else
    printf("Shuffle desativado!");
  return !shuffleAtual;
}

int main(void) {
  podcast *inicio = (podcast*)malloc(sizeof(podcast));
  inicio->next = NULL;
  int podcastRemover, episodioRemover, opcao;
  int idPodcast = 1;
  bool shuffleAtual = false;
  do
	{
    printf("\n1 - Inserir\n");
		printf("2 - Remover Episódio\n");
		printf("3 - Exibir Episódio Atual\n");
    printf("4 - Relatório\n");
    printf("5 - Verificar Próximo Episódio\n");
    printf("6 - Shuffle\n");
    printf("0 - Sair\n");
		printf("Digite a opcao desejada: ");
    scanf("%d", &opcao);
    
    switch (opcao)
		{
  		case 1:
        idPodcast = adicionar(inicio, idPodcast);
        break;
  		case 2:
        printf("IdPodcast e NumEpisódio a ser excluído: ");
        scanf("%d %d", &podcastRemover, &episodioRemover);
        removerEpisodio(inicio, podcastRemover, episodioRemover);
        break;
  		case 3:
        exibirAtual(inicio);
       break;
      case 4:
        relatorio(inicio);
        break;
      case 5:
        proximoEpisodio(inicio, shuffleAtual);
        break;
      case 6:
        shuffleAtual = shuffle(shuffleAtual);
        break;
      default:
        break;
		}
  } while (opcao);
  return 0;
}