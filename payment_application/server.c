/*
            **************			Author:Mohammed Emad	**************
            **************			Date : July 2022		**************
            **************			Server.c				**************
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"server.h"
uint8_t AccountIndexInDB = 0;
uint8_t* sequence = 0;
ST_accountsDB_t Server_Valid_BankAccounts[No_Of_Accounts] = {
														{2000.0,"4573764332583690"},
														{30000.0,"51233698745632102"},
														{10000.0,"4573764333258369012"}
														
};
ST_transaction_t Server_ValidTransictionDB[No_Of_Accounts] = { 0 };
EN_transState_t recieveTransactionData(ST_transaction_t * transData)
{
    /*			*******						Test Cases								*******
    *	Case								Excpected Output						Output
    * 1-Account Doesn't Exist				DECLINED_STOLEN_CARD                    DECLINED_STOLEN_CARD
    * 2-Amount Isn't Available				DECLINED_INSUFFECIENT_FUND              DECLINED_INSUFFECIENT_FUND
    * 3-Transiction Cant't Be Saved			INTERNAL_SERVER_ERROR                   INTERNAL_SERVER_ERROR
    * 4-Else    							APPROVED                                APPROVED
    */
    uint8_t valid_account = 0, valid_amount = 0, Save_Check=0;
    valid_account=isValidAccount(transData);
    valid_amount = isAmountAvailable(&transData->terminalData);
    memcpy(Server_ValidTransictionDB,transData,sizeof(ST_transaction_t));
    if (valid_account == OK_S)
    {
        if (valid_amount == LOW_BALANCE)
        {
            saveTransaction(&Server_ValidTransictionDB[AccountIndexInDB]);
            printf("Low Balance \n");
            return DECLINED_INSUFFECIENT_FUND;
        }
        else
        {
            Server_Valid_BankAccounts[AccountIndexInDB].balance =
               Server_Valid_BankAccounts[AccountIndexInDB].balance - Server_ValidTransictionDB[AccountIndexInDB].terminalData.transAmount;
                printf("New Balance : %f \n", Server_Valid_BankAccounts[AccountIndexInDB].balance);
                Save_Check = saveTransaction(&Server_ValidTransictionDB[AccountIndexInDB]);
                if (Save_Check == OK_S)
                {
                    return APPROVED;
                }
                else
                {
                    return INTERNAL_SERVER_ERROR;
                }
        }
    }
    else

    {
        saveTransaction(&Server_ValidTransictionDB[AccountIndexInDB]);
        printf("Invalid Account \n");
        return DECLINED_STOLEN_CARD;
    }
}
EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
    /*			*******						Test Cases								*******
    *	Case								Excpected Output						Output
    * 1-PAN Doesn't Exist   				DECLINED_STOLEN_CARD                    DECLINED_STOLEN_CARD
    * 2-PAN Exist           				OK                                      OK
    */
    uint8_t Iterator = 0, Search_Result=1;
    while (Iterator < No_Of_Accounts && Search_Result==1 )
    {
        Search_Result = Compare_Strings(cardData->primaryAccountNumber, Server_Valid_BankAccounts[Iterator].primaryAccountNumber);
        if (Search_Result == 0)
        {
            AccountIndexInDB = Iterator;
            break;
        }
            Iterator++;
            AccountIndexInDB = Iterator;
    }
    if ( Search_Result == 0)
    {
        //printf("Found Card \n");
        return OK_S;
    }
    else
    {
        printf("Declined Card \n");
        return DECLINED_STOLEN_CARD;
    }
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
    /*	    		*******						Test Cases								*******
       *	Case								Excpected Output						Output
       * 1-Transiction Amount >  Balance		LOW_BALANCE                             LOW_BALANCE
       * 2-Transiction Amount <  Balance		OK                                      OK
       * 3-Transiction Amount =  Balance        OK                                      OK  
       */
    if (termData->transAmount <= Server_Valid_BankAccounts[AccountIndexInDB].balance )
    {
        return OK_S;
    }
    else
    {
        return LOW_BALANCE;
    }
}
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
    /*			*******						Test Cases								*******
    *	Case								Excpected Output						Output
    * 1-Sequence Number   Check				Sequence Number                         Sequence Number                         
    * 2-Transiction State Check				Transiction State                       Transiction State
    * 3-Transiction Cant't Be Saved			SAVING_FAILED                           SAVING_FAILED
    * 4-Transiction Saved                   OK                                      OK
    */
    uint8_t valid_account = 0, valid_amount = 0;
    valid_account = isValidAccount(&transData->cardHolderData);
    valid_amount  = isAmountAvailable(&transData->terminalData);
    if (valid_account == OK_S)
    {
        if (valid_amount == LOW_BALANCE)
        {
            sequence++;
            transData->transState = DECLINED_INSUFFECIENT_FUND;
        }
        else
        {
            sequence++;
            transData->transState = APPROVED;
        }
    }
    else
    {
        sequence++;
        transData->transState = DECLINED_STOLEN_CARD;
    }
    transData->transactionSequenceNumber = sequence;
    if (transData->transactionSequenceNumber > 0)
    {
        printf("Save State : %d \n", transData->transState);
        printf("Sequence Number : %lu \n", transData->transactionSequenceNumber);
        return OK_S;
    }
    else
    {
        return SAVING_FAILED;
    }


}
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{

}
uint8_t Compare_Strings(uint8_t Str1[],uint8_t Str2[])
{
    /*THIS FUNCTION IS DONE TO REPLACE strcmp()
    AS strcmp() ONLY ACCEPTS DIRECT STRINGS */
    uint16_t flag = 0, iterator = 0;    
    while (Str1[iterator] != '\0' && Str2[iterator] != '\0')
    {
        if (Str1[iterator] != Str2[iterator])
        {
            flag = 1;
            break;

        }
        iterator++;
    }
    if (flag == 0)
        return 0;
    else
        return 1;
}