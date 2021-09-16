
// PIC16F628A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable bit (RB4/PGM pin has PGM function, low-voltage programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#include <xc.h>
#include <string.h>
int val = 0;
int chbr = 0;
int i = 0;
double chiffr ;
double vol;
double *point = &vol ;


void config() {
    PSA = 0;
    PS0 = 1;
    PS1 = 1;
    PS2 = 1;
    TXEN = 1;
    SYNC = 0;
    BRGH = 1;
    SPBRG = 129;
    SPEN = 1;
    CREN = 1; //activation de la reception de données
    GIE = 1; //interruption globale 
    PEIE = 1; //interruprion des périphiques 
    RCIE = 1; //interruption pour la recption de données
    RBIE = 1; // interruption sur le port B activée
    EEIE = 1; //imnterruption sur l'écriture et la lecture des données stockées en mémoire
}

void uart_txChar(unsigned char ch) { // initialisation de l'envoi des données
    while (!TRMT);
    TXREG = ch;
}

void uart_txDouble(const chiffr) { // initialisation de l'envoi des données
    while (!TRMT);
    TXREG = chiffr;
}

void uart_txStr(unsigned const char *str) { // fonction pour l'envoi de caractères
    while (*str != '\0') {
        uart_txChar(*str);
        str++;
    }

    uart_txChar('\r');
    uart_txChar('\n');

}

double uart_txStd(*point) {
     while (*point != NULL) {
        uart_txDouble(*point);
        point++;
    }
    uart_txDouble('\r');
  
}

/*double uart_txDouble( vol ) { // initialisation de l'envoi des données
    while (!TRMT);
    TXREG = vol;
    return(TXREG) ;
}

double uart_txStd(const double *std) { // fonction pour l'envoi de caractères
    while (*std != '\0') {
        uart_txDouble(*std);
        std++;
    }
    uart_txDouble('\r');
    uart_txDouble('\n');
}
 */

/*void ReadEEprom(const unsigned char addr) { //fonction de lecture des donnés stockées
    EEADR = addr;
    RD = 1;
    byte = EEDATA;
}

double WriteEEprom(double vol, const unsigned char addr) { // fonction d'écriture des données sauvegardées 
    EEADR = addr;
    EEDATA = vol;
    WREN = 1;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    WR = 1;
    if (EEIF) {
        EEIF = 0;
    }

}
 */
void interrupt jdk1() { // fonction d'interruption
    if (RCIF) {
        RCIF = 0;
        if (RCREG == 'I') { // lorsque le programme recoit le caractère I il affiche Bienvenue
            uart_txStr("\rBIENVENUE ");

        }
        if (RCREG == 'A') {// lorsque le programme recoit le caractère A il affiche l'index de la chambre n°1
            uart_txStr("\rINDEX CHAMBRE 1 :");
            //ReadEEprom(0x0A); //ici il affiche la valeur de la variable de stockage de volume
            chbr == 1;

        }
        if (RCREG == 'B') {// lorsque le programme recoit le caractère B il affiche l'index de la chambre n°2
            uart_txStr("\rINDEX CHAMBRE 2 :");

        }
        if (RCREG == 'C') {// lorsque le programme recoit le caractère C il affiche l'index de la chambre n°3
            uart_txStr("\rINDEX CHAMBRE 3 :");

        }
        if (RCREG == 'D') {// lorsque le programme recoit le caractère D il affiche l'index de la chambre n°4
            uart_txStr("\rINDEX CHAMBRE 4 :");

        }
        if (RCREG == 'E') {// lorsque le programme recoit le caractère E il affiche l'index de la chambre n°5
            uart_txStr("\rINDEX CHAMBRE 5 :");

        }
        if (RCREG == 'Q') {// lorsque le programme recoit le caractère Q il affiche quitter 
            uart_txStr("\rA BIENTOT");
        }
    }

    if (RBIF) {


        if (RB0 == 0) {
            RB0 = 1;
            i = i + 1;
        }
        if (i == 20) {
            vol = vol + 1;
            uart_txStd(&vol);
            i = 0;
        }
    }
    RBIF = 0;


}

void main(void) {
    config();
    while (1);
}