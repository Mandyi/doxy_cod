#ifndef FLASH_DRIVER
#define FLASH_DRIVER

enum eLanguageItems
{
  Romana = 0,
  English,
  Francais,
  Deutsch,
  Espanol,
  Turkce,
  Italino,
  Magyar,
  Nederlands,
  Portugues
};

enum eAlarmItems
{
  Fire = 0,
  Gase,
  Steam
};

struct sLanguageItems
{
    char *pName;
    enum eLanguageItems id;
} sLanguageItemsList[] = {
        {"Romana", Romana},
        {"English", English},
        {"Francais", Francais},
        {"Deutsh", Deutsch},
        {"Espanol", Espanol},
        {"Turkce", Turkce},
        {"Italino", Italino},
        {"Magyar", Magyar},
        {"Nederlands", Nederlands},
        {"Portugues", Portugues}
};

struct sAlarmItems
{
    char *pName;
    enum eAlarmItems id;
} sAlarmItemsList[] = {
        {"Fire", Fire},
        {"Gase", Gase},
        {"Steam", Steam}
};

/*
functia getLanguageLine returneaza numarul paginii dintr-un sector al memoriei ce
primeste ca si parametru limba primita de la utilizator si returneaza
*/
int getLanguageLine(char acLanguage[10]);

/*
functia getAllarmSector returneaza numarul sectorului din memoria Flash, in
functie de alarma primita ca si parametru de la utilizator
*/
int getAllarmSector(char acAlarm[5]);

/*
functia write_Flash scrie in memoria Flash un mesaj, trimis de la utilizator;
functia primeste ca si parametru tipul de alarma acAlarm[5], limba in care e mesajul
acLanguage[10], un pointer spre un sir de caractere ce contine mesajul dat de utilizator,
si lungimea sirului de caractere ce trebuiesc trasmise.
*/
void write_Flash(char acAlarm[5], char acLanguage[10], unsigned char *pText, unsigned char ucTextLength);

/*
functia read_Flash citeste din memoria Flash un mesaj;
functia primeste ca si parametri tipul de alarma acAlarm[5] si limba in care e mesajul,
acLanguage[10].
*/
void read_Flash(char acAlarm[5], char acLanguage[10]);

//defineste comanda pentru scriere in FLASH
#define nWriteFlash 0x06;

//defineste comanda pentru citirea din Flash
#define nReadFlash 0x03;

//defineste numarul de caractere dintr-un mesaj de alarma, ficare alarma are un numar fix de caractere
#define MAX 150;

#endif
