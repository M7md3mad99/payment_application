/*
			**************			Author:Mohammed Emad	**************
			**************			Date : July 2022		**************
			**************			App.c					**************
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"std_types.h"
#include"card.h"
#include"terminal.h"
#include"server.h"
#include"app.h"
void appStart()
{
	/*			*******						Test Cases								*******
	*	Case								Excpected Output						Output
	* 1-Expired Card						Expired Card Fail						Expired Card Fail
	* 2-Exceeded Amount						Max Amount Exceeded						Max Amount Exceeded
	* 3-Invalid  Account					Declined Card							Declined Card
	* 4-Unavailable Amount					Low Balance								Low Balance
	* 5-Saved Transiction    				APPROVED								APPROVED
	*/
	uint8_t valid_pan = 0,BalanceCheck = 0,date_valid = 0 ,amount_check = 0;
	ST_cardData_t* card = (ST_cardData_t*)malloc(sizeof(ST_cardData_t));
	ST_terminalData_t* transiction = (ST_terminalData_t*)malloc(sizeof(ST_terminalData_t));
	ST_transaction_t* Server = (ST_transaction_t*)malloc(sizeof(ST_transaction_t));

	while (1)
	{
			getCardHolderName(card);
			getCardExpiryDate(card);
			getCardPAN(card);
			getTransactionDate(transiction);
			date_valid=isCardExpired(*card,*transiction);
			if (date_valid == ok)
			{
				amount_check=getTransactionAmount(transiction);
				if (amount_check==ok)
				{
					valid_pan=isValidAccount(card);
					if (valid_pan==OK_S)
					{
						memcpy(Server->cardHolderData.cardHolderName, &card->cardHolderName, sizeof(card->cardHolderName));
						memcpy(Server->cardHolderData.cardExpirationDate, &card->cardExpirationDate, sizeof(card->cardExpirationDate));
						memcpy(Server->cardHolderData.primaryAccountNumber, &card->primaryAccountNumber, sizeof(card->primaryAccountNumber));
						memcpy(Server->terminalData.transactionDate, &transiction->transactionDate, sizeof(transiction->transactionDate));
						memcpy(&Server->terminalData.transAmount, &transiction->transAmount, sizeof(float));
						memcpy(&Server->terminalData.maxTransAmount, &transiction->maxTransAmount, sizeof(float));
						BalanceCheck= recieveTransactionData(Server);
						if (BalanceCheck != OK_S)
						{
							break;
						}
					}
					else
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
	
	}
}