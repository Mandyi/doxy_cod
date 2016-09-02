/******************************************************************************/
/* @PROJECT : Demo */
/* @SW_RELEASE : 0100 */
/* @NAME : EEPROM25d_driver.c */
/* @PURPOSE :  */
/* @CREATED_BY : D. Pop */
/* @CREATION_DATE : July 15 2016 */
/* @CREATION_SITE : NTT Data Romania */
/* @LANGUAGE : 'C' */
/* @MPROC_TYPE : Independent */
/* ******************************************************************* */
/* @REVISION_BY :  */
/* @SW_RELEASE :  */
/* @CHANGES :  */
/* @CREATION_DATE :  */
/* @CREATION_SITE :  */
/***************************** (C) Copyright NTT Data Romania *******************/


/*_____INCLUDE-FILES__________________________________________________________*/

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "SPId_driver.h"
#include "FLASH_DRIVER.h"
/*_____LOCAL-DEFINE___________________________________________________________*/
/*_____LOCAL-TYPES____________________________________________________________*/
/*_____GLOBAL-DATA____________________________________________________________*/
/*_____LOCAL-DATA_____________________________________________________________*/
/*_____LOCAL-MACROS___________________________________________________________*/
/*_____LOCAL-FUNCTIONS-PROTOTYPES_____________________________________________*/
/*_____GLOBAL-FUNCTIONS_______________________________________________________*/


int getLanguageLine(char acLanguage[10])
{
    int i;
    int iLanguageId;
    enum eLanguageItems eLanguage;
    struct sLanguageItems *pChoice;

    for(i = 0; i < sizeof sLanguageItemsList/sizeof (struct sLanguageItems); i++)
    {
        if(strcmp(acLanguage, sLanguageItemsList[i].pName) == 0)
        {
            pChoice = sLanguageItemsList + i;
            break;
        }
    }
    eLanguage = pChoice->id;
    switch(eLanguage)
    {
    case Romana:
        iLanguageId = 0;
        break;
    case English:
        iLanguageId = 1;
        break;
    case Francais:
        iLanguageId = 2;
        break;
    case Deutsch:
        iLanguageId = 3;
        break;
    case Espanol:
        iLanguageId = 4;
        break;
    case Turkce:
        iLanguageId = 5;
        break;
    case Italino:
        iLanguageId = 6;
        break;
    case Magyar:
        iLanguageId = 7;
        break;
    case Nederlands:
        iLanguageId = 8;
        break;
    case Portugues:
        iLanguageId = 9;
        break;
    default:
        printf("Enter a valid language!");
    }
    return iLanguageId;
}

int getAllarmSector(char acAlarm[5])
{
    int i;
    int iAddress;
    enum eAlarmItems eAlarm;
    struct sAlarmItems *pChoice;

    for(i = 0; i < sizeof sAlarmItemsList/sizeof (struct sAlarmItems); i++)
    {
        if(strcmp(acAlarm, sAlarmItemsList[i].pName) == 0)
        {
            pChoice = sAlarmItemsList + i;
            break;
        }
    }

    eAlarm = pChoice->id;

    switch(eAlarm)
    {
    case Fire:
        iAddress = 0;
        break;
    case Gase:
        iAddress = 1;
        break;
    case Steam:
        iAddress = 2;
        break;
    default:
        printf("Enter a valid alarm!");
    }
    return iAddress;
}

void write_Flash(char acAlarm[5], char acLanguage[10], unsigned char *pText, unsigned char ucTextLength)
{
    int i;
    //contorizam cate elemente vrem sa transmitem prin SPI
    unsigned char count = 0;

    //sectorul din memorie
    int iAllarmSector = getAllarmSector(acAlarm);

    //pagina din sector
    int iLanguagePage = getLanguageLine(acLanguage);

    //vector ce se transmite prin SPI
    unsigned char SPI_command[155];
    unsigned char *pSPI_command;
    pSPI_command = (unsigned char*)SPI_command;

    //adresa de start din memorie in functie de alarma si limba
    int iAddress = iAllarmSector * 4096 + iLanguagePage * 256;

    //primul byte contine comanda pentru scriere in Flash
    pSPI_command = (unsigned char*)nWriteFlash;
    pSPI_command++;
    count++;

    short mask = 0x00FF;
    mask = mask & iAddress;

    //byte-ul 2 contine primii 8 biti din adresa de memorie
    pSPI_command = (unsigned char*)(&mask);
    pSPI_command++;
    count++;

    mask = 0xFF00;
    mask = (mask & iAddress) >> 8;

    //byte-ul 3 contine urmatorii 8 biti din adresa de memorie
    pSPI_command = (unsigned char*)(&mask);
    pSPI_command++;
    count++;

    //urmatorii bytes contin mesajul transmis de la utilizator
    for(i = 0; i < MAX; i++)
    {
        pSPI_command = pText;
        pSPI_command++;
        pText++;
        count++;
    }

    //ultimul byte transmis este caracterul null
    unsigned char cFinal = '/0';
    pSPI_command = (unsigned char*)(&cFinal);
    count++;

    //se apeleaza functia SPI_write, prin care se scrie in Flash
    SPI_write(1, pSPI_command, count);
}

void read_Flash(char acAlarm[5], char acLanguage[10])
{
    //contorizam cate elemente vrem sa transmitem prin SPI
    int count = 0;

    //numarul sectorului specific fiecarei alarme
    int iAllarmSector = getAllarmSector(acAlarm);

    //numarul paginii dintr-un sector in functie de limba
    int iLanguagePage = getLanguageLine(acLanguage);

    //vecotrul ce se transmite prin SPI
    unsigned char SPI_command[MAX + 5];
    unsigned char *pSPI_command;
    pSPI_command = (unsigned char*)SPI_command;

    //adresa care trebuie citita
    int iAddress = iAllarmSector * 4096 + iLanguagePage * 256;

    //primul byte contine comanda pentru citire din Flash
    pSPI_command = (unsigned char*)nReadFlash;
    pSPI_command++;
    count++;

    short int mask = 0x00FF;
    mask = mask & iAddress;

    //al doilea byte din comanda contine primii 8 biti din adresa din memoria Flash
    pSPI_command = (unsigned char*)(&mask);
    pSPI_command++;
    count++;

    mask = 0xFF00;
    mask = (mask & iAddress) >> 8;

    //al treilea byte contine urmatorii 8 biti din adresa din memoria Flash
    pSPI_command = (unsigned char*)(&mask);
    pSPI_command++;
    count++;

    //ultimul byte contine caracterul null
    unsigned char cFinal = '/0';
    pSPI_command = (unsigned char*)(&cFinal);
    count++;

    //sir de caractere pentru a citi din memeorie
    unsigned char cText[MAX];
    unsigned char *pcText;

    //apeleaza functia prin care se trimite prin SPI comanda de citire si adresa de unde se va citi
    SPI_write(1, pSPI_command, count);

    //apeleaza functia de citire din memorie
    SPI_read(1, pcText, MAX);
}
