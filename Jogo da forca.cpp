#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <cmath>
#include <ctype.h>
#include <time.h>

char vetorDePalavras[10][25]={"OTORRINOLARINGOLOGISTA", "PAPIBAQUIGRAFO", "COMPUTADOR", "CONTROLE", "PARALELEPIPEDO", "CANETA", "PROJETO", "FERRAMENTA", "URANO", "KEVLAR"};
char letra;
char palavraCorreta[25];
char palavraOculta[25];
char letrasDigitadas[27];
int tamanho;
int erros;
int jogar;

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}
void gambiarra(){// Gambiarra para apagar os prints os prints que irão mudar na tela "system ("ClS") não me ajudaria porque eu teria que imprimir mais coisas na tela a cada enter.
	gotoxy(24,9);	printf("                                                      ");
	gotoxy(24,10);	printf("                                                      ");
	gotoxy(21,8);	printf("                   ");
	gotoxy(43,11);	printf("                   ");
	gotoxy(45,11);	printf("                     ");
	gotoxy(45,8);	printf("                                                     ");
	gotoxy(55,9);	printf("                                                     ");
	gotoxy(75,10);	printf("                                                                                             ");
}
void escolhePalavra(){// Escolhe a palaavra que entrara em jogo.
	srand(time(NULL));
	int i = rand() % 11;
	tamanho = strlen(vetorDePalavras[i]);
	strcpy(palavraCorreta, vetorDePalavras[i]);
	for(int j=0; j < tamanho; j++ ){
		palavraOculta[j]='*';//cria o vetor com asteriscos que sera subistituido caso ocorra acerto.
	}
}
void bemVindo(){// Tela com as informações principais do jogo.
	gotoxy(35,1);	printf("Jogo Da Forca");
	gotoxy(13,3);	printf("Adivinhe a palavra digitando apenas uma letra por tentativa.");
	gotoxy(13,4);	printf("Todas as letras minúsculas serão computadas como maiúsculas.");
	gotoxy(28,5);	printf("Você só pode errar 10 vezes.");
	gotoxy(3,7);	printf("A palavra tem %d letras. ", tamanho);
	puts(palavraOculta);
	gotoxy(3,8);	printf("Escolha uma letra: ");
	letra = getchar();
	letra = toupper(letra);
	fflush(stdin);
}
void erroLetra(){// Verifica se a letra é um caracter valido "mostra erro se digitar algo que não seja uma letra".
	int teste=0;
	while(teste==0){
		if(isalpha(letra)){
			teste=1;
		}else{
			gotoxy(24,10);	printf("Caractere invalido, digite uma letra de A a Z. ");
			gotoxy(24,11);	printf("Escolha uma letra: ");
			letra = getchar();
			letra = toupper(letra);
			fflush(stdin);
			gambiarra();
		}
	}
}
void letraRepetida(){// Verifica se a letra já foi usada antes.
	int i=0;
	int teste=0;
	do{
		if(!isalpha(letrasDigitadas[i])){// Testa se há alguma letra naquela posição do vetor.
			letrasDigitadas[i]=letra;//Atribui a letra digitada a um vetor com o tamanho equivalente ao alfabeto para que ela n seja digitada novamente.
			teste=1;
		}else{
			if(letrasDigitadas[i]==letra){
				gotoxy(24,10);	printf("Letra repetida. ");
				gotoxy(24,11);	printf("Escolha outra letra: ");
				letra = getchar();
				letra = toupper(letra);
				fflush(stdin);
				gambiarra();
				erroLetra();// Chama erroLetra denovo para certificar que o novo caracter é realmente uma letra.
				i=-1;
			}
		}
		i++;
	}while(teste==0);
}
void letraCorreta(){// Verifica se a letra digitada aparece na palavra e apresenta na tela.
	int teste=0;
	int cont=0;
	for(int i=0; i<strlen(palavraOculta);i++){
		if(letra == palavraCorreta[i]){// Verifica se a letra digitada aparece na palavra.
			palavraOculta[i] = letra;// acrescenta a letra correta a seus devidos lugares no vetor com asteriscos assim os substituindo. 
			cont++;
		}
	}
	if(cont>0){
		gotoxy(45,8);	printf("Parabéns, você acertou uma letra!!!   ");
	}else{
		gotoxy(45,8);	printf("A letra '%c' não aparece na palavra...", letra);
		erros++;// conta o número de tentativas erradas.
	}
}
void limiteErros(){// Verifica a quantidade de erros já computados e para o algoritmo se os erros chegarem a 10.
	if(erros < 10){
		if(erros != 9){// Informa o numero de chances restantes.
			gotoxy(55,9);	printf("Você tem mais %d tentativas.                     ", (10-erros));
		}else{
			gotoxy(55,9);	printf("Você tem mais 1 tentativa.                     ");
		}
		
	}else{// Informa que n existem mais tentativas e para o algoritmo.
		gotoxy(55,9);	printf("Lamento, mas desta vez você perdeu o jogo... ");
		gotoxy(75,10);	printf("A palavra era ");
		puts(palavraCorreta);
		jogar=1;
	}
}
void acertou(){// informa que vc acertou a palavra e para o algoritmo.
	if(!strcmp(palavraCorreta, palavraOculta)){
		gotoxy(3,7);	printf("A palavra tem %d letras. ", tamanho);
		puts(palavraCorreta);
		gotoxy(55,7);	printf("Parabens, você acertou a palavra!!!");
		gambiarra();
		jogar=1;
	}
}
int main(){
	setlocale(LC_ALL, "Portuguese");
		
	escolhePalavra();
	while(jogar==0){
		bemVindo();
		gambiarra();
		erroLetra();
		letraRepetida();
		letraCorreta();
		limiteErros();
		acertou();	
	}
	
}

