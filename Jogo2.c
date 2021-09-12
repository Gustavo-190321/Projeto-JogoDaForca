#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <String.h>

int geraNumeroAleatorio(){
	return rand() % 13; //Usado para pegar a palavra de um array de strings
}
void bonecoEnforcado(int tentativasRestantes){ //Função para gerar o boneco
	printf("Tentativas restantes = %d\n", tentativasRestantes);
	printf("\n _____");//cabeça
	printf("\n|  |");
	printf("\n|  "); if(tentativasRestantes <=6) printf("0");//corpo
	printf("\n| "); if(tentativasRestantes <=4) printf("/"); if(tentativasRestantes <=5) printf("|"); if(tentativasRestantes <=3) printf("\\");//pernas
	printf("\n| "); if(tentativasRestantes <=2) printf("/ "); if(tentativasRestantes <=1) printf("\\");
	printf("\n| \n");
}
char upperCase(char letter){ //Transforma alguma letra em sua variante maiuscula
	int i;
	char alfabeto[2][27] = {"abcdefghijklmnopqrstuvwxyz", "ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
	for(i=0; i<27; i++){ //Para evitar incompatibilidade, tudo é transformado em maiuculo
		if(letter == alfabeto[0][i] || letter == alfabeto[1][i]){
			return alfabeto[1][i];
		}
	}
	return '0';
}
void jogo(){
	int flag; //Diz se a letra foi encontrada
	int jogada = 0; //contabiliza as jogadas
	int palavraEscolhida = geraNumeroAleatorio();
	int jogadasRestantes = 6;
	int i=0;
	char opc;
	char letrasJogadas[20] = {"*******************"};
	char palavrasPreSalvas[13][20] = {"Computador", "Vitor", "Windows", "Linux", "Gustavo", "paralelepipedo", "Andrey", "projeto", "offline", "Lucas", "bolacha", "carioca", "sambiquira"};
	char palavraDoJogador[20];


	for(i=0; i<strlen(palavrasPreSalvas[palavraEscolhida]); i++){ //transforma a palavra escolhida em maiucula
		palavrasPreSalvas[palavraEscolhida][i] = upperCase(palavrasPreSalvas[palavraEscolhida][i]);
		palavraDoJogador[i] = '_'; //copia o tamanho da palavra escolhida e muda os caractere para "_"
	}
	
	palavraDoJogador[i] = '\0'; //para avisar que é o fim da string
	do{
		flag = 0;
		system("cls");
		bonecoEnforcado(jogadasRestantes); //gera boneco enforcado
		printf("palavra: %s\n\n", palavraDoJogador); //Exibe a palavra no formato certo, com as letras encontradas pelo jogador
		printf("Digite uma letra para chutar uma letra, ou '0' para chutar a palavra\n");
		printf("Letras usadas: %s\n", letrasJogadas);
		fflush(stdin);
		scanf("%c", &opc);
		if(opc != '0'){
			if(((opc >= 65 && opc <= 90)||(opc >= 97 && opc <= 122))){//verifica se é letra usando a tabela ascii
				opc = upperCase(opc); //transforma a letra digitada em sua variante maiuscula
				int letraUsada = 0; //flag para ver se a letra ja foi usada
				for(i=0;i<strlen(letrasJogadas);i++){ //Scanner para ver se letra ja foi usada
					if(opc==letrasJogadas[i]){
						letraUsada = 1;
					}
				}
				if(!letraUsada){ //Realizado se a letra NÃO foi usada
				
					letrasJogadas[jogada] = opc; //Salva a letra usada em letrasJogadas
					jogada++; //para organizar os arrays
					for(i = 0; i<strlen(palavrasPreSalvas[palavraEscolhida]); i++){
						if(opc == palavrasPreSalvas[palavraEscolhida][i]){ //Verifica se o jogador acertou
							printf("\a");
							palavraDoJogador[i] = palavrasPreSalvas[palavraEscolhida][i]; //Se o jogador ter acertado a letra é armazenada no array que contém a palavra escolhida oculta para o jogador
							flag = 1; //Diz que o jogador acertou
						}
					}
					if(!flag){ //Se o jogador não acertou ele perde uma jogada

						jogadasRestantes--;
						printf("\a");
					}
			}
		}
			
		}else{ //Lógica se o jogador quer chutar a palavra
			int ehLetra=1; //verifica se o item dentro da String é letra
			char palavraBackup[20]; //backup da palavra para caso o jogador coloque um número
			strcpy(palavraBackup, palavraDoJogador); //faz uma cópia da palavra digitada pelo jogador para backup
			do{
				strcpy(palavraDoJogador, palavraBackup); //coloca o backup na palavraDoJogador
				system("cls");
				ehLetra = 1;
				bonecoEnforcado(jogadasRestantes);
				printf("palavra: %s\n\n", palavraDoJogador);
				printf("Bem vindo ao tudo ou nada, uma vez aqui nao ha mais saida, por favor, digite a palavra que achas que eh: ");
				scanf("%s", palavraDoJogador);
				for(i=0; i<strlen(palavraDoJogador); i++){ //verifica se TUDO da String é letra
					if(!(((palavraDoJogador[i] >= 65 && palavraDoJogador[i] <= 90)||(palavraDoJogador[i] >= 97 && palavraDoJogador[i] <= 122)))){ //Verifica se não é letra
						ehLetra = 0;
					}
					palavraDoJogador[i] = upperCase(palavraDoJogador[i]);
				}
			}while(!ehLetra); //se ter um único item que não seja letra, o jogador terá que digitar outra palavra
			break;
		}
		if(strncmp(palavraDoJogador, palavrasPreSalvas[palavraEscolhida], 20) == 0){ //Se o jogador ter acertado a palavra chutando as letras
			//o do..while é quebrado
			break;
		}
	}while(jogadasRestantes != 0); //O jogo irá parar quando as jogadas acabarem
	system("pause");
	system("cls");
	if(strncmp(palavraDoJogador, palavrasPreSalvas[palavraEscolhida], 20) == 0){ //Se as palavras forem iguais, o jogador ganha
		printf("\n\nA palavra era %s, voce chegou nisso: %s \n", palavrasPreSalvas[palavraEscolhida], palavraDoJogador);
		printf("Logo voce acertou \\o/ voce ganhou essa delicia de jogo, meus parabens, que tragam os cafes\n");
	}else{//Se forem diferentes, o jogador perde
		printf("\n\nA palavra era %s, voce chegou nisso: %s \n", palavrasPreSalvas[palavraEscolhida], palavraDoJogador);
		printf("Logo voce perdeu\n");
	}
		
	system("pause");
}

int main(){
	srand(time(NULL));
	int opc;
	do{
		system("cls");
		printf("1-Jogar\n");
		printf("2-Sair\n");
		scanf("%d", &opc);
		
		if(opc == 1){
			jogo();
		}
	}while(opc != 2);
	
	return 0;
}
