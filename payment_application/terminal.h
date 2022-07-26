/*
			**************			Author:Mohammed Emad	**************
			**************			Date : July 2022		**************
			**************			Terminal.h				**************
*/
#pragma once
#ifndef terminal_H_
#define terminal_H_
#include"std_types.h"
#include"card.h"
#define Maximmum_amount 8000.0 
typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;
typedef enum EN_terminalError_t
{
	ok, WRONG_DATE, EXPIRED_CARD,
	INVALID_CARD, INVALID_AMOUNT,
	EXCEED_MAX_AMOUNT,
	INVALID_MAX_AMOUNT
}EN_terminalError_t;
static uint8_t string_into_int(uint8_t* cpy_ptrstring, uint8_t cpy_start_index, uint8_t cpy_end_index);
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
EN_terminalError_t isCardExpired(ST_cardData_t cardData,ST_terminalData_t termData);
EN_terminalError_t isValidCardPAN(ST_cardData_t * cardData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t * termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData);
#endif
