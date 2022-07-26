/*
			**************			Author:Mohammed Emad	**************
			**************			Date : July 2022		**************
			**************			Card.h					**************
*/
#pragma once
#ifndef card_H_
#define card_H_
typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;
typedef enum EN_cardError_t
{
	OK, WRONG_NAME, WRONG_EXP_DATE,
	WRONG_PAN
}EN_cardError_t;
static uint8_t string_into_int(uint8_t* cpy_ptrstring, uint8_t cpy_start_index, uint8_t cpy_end_index);
EN_cardError_t  getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t  getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t  getCardPAN(ST_cardData_t* cardData);
#endif 
