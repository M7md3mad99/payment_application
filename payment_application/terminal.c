/*
			**************			Author:Mohammed Emad	**************
			**************			Date : July 2022		**************
			**************			Terminal.c				**************
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include"std_types.h"
#include"terminal.h"
#include"card.h"
uint8_t transiction_months = 0, transiction_year = 0;
uint8_t transiction_day = 0;
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	/*			*******						Test Cases								*******
	*	Case								Excpected Output						Output
	* 1-NULL Input					   		Wrong Date Error						Wrong Date Error						
	* 2-Less Than 10 Characters Input		Wrong Date Error						Wrong Date Error
	* 3-More Than 10 Characters Input		Wrong Date Error						Wrong Date Error
	* 4-Input   = 10						OK										OK
	*/

    /* //TO READ DIRECT FROM PC BUT THE,  
    //FUNCTION PROTOTYPE MUST BE EDITED
    time_t t;
    t = time(NULL);
    struct tm date = *localtime(&t);
    //printf("Transiction Date: %d/%d/%d", date.tm_mday, date.tm_mon + 1, date.tm_year + 1900);
    */
	printf("PLEASE ENTER TRANSICTION DATE \n");
	printf("e.g: 30/12/2024 \n");
	gets(termData->transactionDate);
	uint8_t DATE_size = strlen(termData->transactionDate);
	transiction_year   = string_into_int(termData->transactionDate, 8, 9);
	transiction_months = string_into_int(termData->transactionDate, 3, 4);
	transiction_day    = string_into_int(termData->transactionDate, 0, 1);
	//Setting Days Max To 31 And Min To 01
	if ( transiction_day>= 32   || transiction_day    <= 0)
	{
		printf("WRONG DATE SYNTAX \n");
		return WRONG_DATE;
	}
	//Setting Months Max To 12 And Min To 01
	if (transiction_months > 12 || transiction_months <= 0)
	{
		printf("WRONG DATE SYNTAX \n");
		return WRONG_DATE;
	}
	if (DATE_size > 10 || DATE_size < 10)
	{
		printf("WRONG DATE SYNTAX \n");
		return WRONG_DATE;
	}
	else
	{
		puts(termData->transactionDate);			//To Print Transiction Date If Wanted
		return ok;
	}

}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	/*			*******						Test Cases								*******
	*	Case								Excpected Output						Output
	* 1-Expiry date <  Transiction Date 	Expired Card							Expired Card
	* 2-Expiry date > Transiction Date		OK										OK
	* 3-Expiry date = Transiction Date		OK										OK
	*/

	uint8_t card_months=0,      card_year=0;
	uint8_t trans_months_t=0,trans_year_t=0;
	trans_months_t = string_into_int   (termData.transactionDate, 3, 4);
	trans_year_t   = string_into_int   (termData.transactionDate, 8, 9);
	card_months    = string_into_int(cardData.cardExpirationDate, 0, 1);
	card_year      = string_into_int(cardData.cardExpirationDate, 3, 4);
	if (card_year > trans_year_t)
	{
		return ok;
	}
	else if (card_months < trans_months_t)
	{
		printf("EXPIRED CARD \n");
		return EXPIRED_CARD;
	}
	else if (card_year = trans_year_t)
	{
		if (card_months >= trans_months_t)
		{
			return ok;
		}
		else if (card_months < trans_months_t)
		{
			printf("EXPIRED CARD \n");
			return EXPIRED_CARD;
		}

	}
}
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{	/*			*******						Test Cases								*******
	*	Case								Excpected Output						Output
	* 1-NULL Input					   		Wrong PAN Error							Wrong PAN Error
	* 2-Less Than 16 Numbers Input			Wrong PAN Error							Wrong PAN Error
	* 3-More Than 19 Numbers Input			Wrong PAN Error							Wrong PAN Error
	* 4- 16 <= Input <= 19					OK										OK
	*/
	uint8_t pan_size = strlen(cardData->primaryAccountNumber);
	if (pan_size > 20 || pan_size < 16)
	{
		return INVALID_CARD;
	}
	else
	{
		return ok;
	}

}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	/*			*******						Test Cases								*******
	*	Case								Excpected Output						Output
	* 1-Input > Max Amount					Exceed Max Account						Exceed Max Amount
	* 2-Input =0							Invalid Amount							Invalid Amount
	* 3-Input <0							Invalid Amount							Invalid Amount
	* 4-Input >0							OK										OK
	*/

	printf("PLEASE ENTER TRANSICTION AMOUNT \n");
	printf("NOTE THAT : Maximum Amount is 8000 \n");
	(void)scanf("%f%*c",&termData->transAmount,fflush(stdin));
	f32 amount = termData->transAmount;
	uint8_t check_max = isBelowMaxAmount(termData);
	if (check_max == ok)
	{
		if (amount <= 0)
		{
			printf("INVALID AMOUNT \n");
			return INVALID_AMOUNT;
		}
		else
		{
			return ok;
		}
	}
	else
	{
	return EXCEED_MAX_AMOUNT;
	}
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	termData->maxTransAmount = Maximmum_amount;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	/*			*******						Test Cases								*******
	*	Case								Excpected Output						Output
	* 1-Transiction Amount > Max Amount  	Exceed Max Amount						Exceed Max Amount
	* 2-Transiction Amount < Max Amount		OK										OK	
	* 3-Transiction Amount = Max Amount		OK										OK
	*/
	setMaxAmount(termData);
	f32 amount = termData->transAmount;
	f32 max_amount = termData->maxTransAmount;
	if (amount > max_amount)
	{
		printf("Maximmum Amount Exceeded \n");
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return OK;
	}
}
static uint8_t string_into_int(uint8_t* cpy_ptrstring, uint8_t cpy_start_index, uint8_t cpy_end_index)
{
	/*THIS FUNCTION IS DONE TO REPLACE atoi()
	AS atoi() ONLY ACCEPTS DIRECT STRINGS */
	uint8_t local_intvalue = 0;
	uint8_t local_loopiterator = 0;
	for (local_loopiterator = cpy_start_index; local_loopiterator <= cpy_end_index; local_loopiterator++)
	{
		local_intvalue = (local_intvalue * 10) + (cpy_ptrstring[local_loopiterator] - '0');
	}

	return local_intvalue;
}