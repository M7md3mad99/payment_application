/*
			**************			Author:Mohammed Emad	**************
			**************			Date : July 2022		**************
			**************			Card.c					**************
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include"std_types.h"
#include"card.h"
uint8_t card_months = 0, card_year = 0;

EN_cardError_t  getCardHolderName(ST_cardData_t* cardData)
{	
	/*			*******						Test Cases								*******
	*	Case								Excpected Output						Output
	* 1-NULL Input					   		Wrong Name Error						Wrong Name Error	
	* 2-Less Than 20 Characters Input		Wrong Name Error						Wrong Name Error
	* 3-More Than 24 Characters Input		Wrong Name Error						Wrong Name Error
	* 4- 20 <= Input <= 24					OK										OK
	*/
	printf("PLEASE ENTER CARD HOLDER NAME \n");
	gets(cardData->cardHolderName);
	uint8_t name_size = strlen(cardData->cardHolderName);
	if (name_size < 20 || name_size > 25)
	{
		printf("WRONG NAME \n");
		return WRONG_NAME;
	}
	else 
	{
		puts(cardData->cardHolderName); // TO PRINT THE NAME IF WANTED
		return OK;
	}
	
}
EN_cardError_t  getCardExpiryDate(ST_cardData_t* cardData)
{
	/*			*******						Test Cases								*******
	*	Case								Excpected Output						Output
	* 1-NULL Input					   		Wrong EXP Date Error					Wrong EXP Date Error
	* 2-Less Than 5 Characters Input		Wrong EXP Date Error					Wrong EXP Date Error
	* 3-More Than 5 Characters Input		Wrong EXP Date Error					Wrong EXP Date Error
	* 4-Input	= 5							OK										OK
	*/
	printf("PLEASE ENTER CARD EXPIRATION DATE \n");
	printf("eg : 05/25 \n");
	gets(cardData->cardExpirationDate);
	uint8_t date_size = strlen(cardData->cardExpirationDate);
	card_months = string_into_int(cardData->cardExpirationDate, 0, 1);
	card_year = string_into_int(cardData->cardExpirationDate, 3, 4);
	//Setting Months Max To 12 And Min To 01
	if (card_months > 12 || card_months <= 0)
	{
		printf("WRONG DATE SYNTAX \n");
		return WRONG_EXP_DATE;
	}
	//Setting Years Max to 99
	if (card_year > 99)
	{
		printf("WRONG DATE SYNTAX \n");
		return WRONG_EXP_DATE;
	}
	if (date_size > 5 || date_size < 5)
	{
		printf("WRONG DATE SYNTAX \n");
		return WRONG_EXP_DATE;
	}
	else
	{
		puts(cardData->cardExpirationDate);			//To Print The Expiry Date If Wanted
		return OK;
	}

}
EN_cardError_t  getCardPAN(ST_cardData_t* cardData)
{
	/*			*******						Test Cases								*******
	*	Case								Excpected Output						Output
	* 1-NULL Input					   		Wrong PAN Error							Wrong PAN Error							
	* 2-Less Than 16 Numbers Input			Wrong PAN Error							Wrong PAN Error
	* 3-More Than 19 Numbers Input			Wrong PAN Error							Wrong PAN Error
	* 4- 16 <= Input <= 19					OK										OK
	*/
	printf("PLEASE ENTER PRIMARY ACCOUNT NUMBER \n");
	gets(cardData->primaryAccountNumber);
	uint8_t PAN_size = strlen(cardData->primaryAccountNumber);
	if (PAN_size < 16 || PAN_size > 19)
	{
		printf("WRONG PAN \n");
		return WRONG_PAN;
	}
	else
	{
		puts(cardData->primaryAccountNumber); //TO PRINT THE PAN IF WANTED
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