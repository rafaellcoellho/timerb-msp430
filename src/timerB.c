#include <msp430f5529.h>

#include "timerB.h"

unsigned long millisecSinceBegin = 0;
bool startCounter = false;
unsigned long int counter = 0;
unsigned long int countMax;
bool countFinished = false;

unsigned long millis(void){
	return millisecSinceBegin;
}

void timerbStart(unsigned int countVal){

	//Configura a variável que vai contar o quantos milisegundos máximos são contados
	countMax = countVal;

	//Avisa para comçar a contar
	startCounter = true;
}

unsigned long int timerbRead(void){

	//Retorna o valor atual do contador
	return counter;
}

void timerbWait(void){

	//Espera a flag de controle indicar com o timer já atingiu as contagens indicadas
	while(!countFinished);

	//Reinicia a variável para próximas contagens
	countFinished = false;
}

bool timerbFinished(void){

	//Reinicia a variável para próximas contagens e retorna o valor dela
	if(countFinished){
		countFinished = false;
		return true;
	}else{
		return false;
	}
}

void timerbInit(void){

	/*
	Número de contagens = 0x07CE + 0x0001 = 1998 + 1 = 1999
	TBSSEL__SMCLK -> Seleciona o SMCLK como fonte do timer b
	ID__2 		  -> Seleciona o prescaler para fclk/4
	TBCLR         -> Limpa o clock e reinicia as configurações

	T = 1ms
	 */
	TB0CCR0 = 0x07CE;
	TB0CTL = TBSSEL__SMCLK + ID__2 + TBIE + TBCLR;

	//Inicializa o contador
	counter = 0;

	//Liga o timer
	TB0CTL |= MC__UP;
}

#pragma vector = TIMER0_B1_VECTOR
__interrupt void timerB (void){

	//Limpa a flag de interrupção do timer b
	TB0CTL &= ~TBIFG;
	TB0CCTL1 &= ~CCIFG;

	//Conta o número de milisegundos desde a inicialização do sistema
	if(millisecSinceBegin == 0xFFFFFFFF){
		millisecSinceBegin = 0;
	}else{
		millisecSinceBegin++;
	}

	if(startCounter == true){
		//Conta mais 1ms
		counter++;

		//Se contador chegou na contagem desejada
		if(counter == countMax){
			//Indica que a contagem terminou
			countFinished = true;
			//Reinicia o contador para próxima contagem
			counter = 0;
			//Reset na flag de contagem
			startCounter = false;
		}
	}

}
