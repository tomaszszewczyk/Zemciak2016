/***
 *
 *
 *    ZZZZZZZZZZZZZZZZZZZ                                                                  iiii                    kkkkkkkk
 *    Z:::::::::::::::::Z                                                                 i::::i                   k::::::k
 *    Z:::::::::::::::::Z                                                                  iiii                    k::::::k
 *    Z:::ZZZZZZZZ:::::Z                                                                                           k::::::k
 *    ZZZZZ     Z:::::Z      eeeeeeeeeeee       mmmmmmm    mmmmmmm       cccccccccccccccciiiiiii   aaaaaaaaaaaaa    k:::::k    kkkkkkk
 *            Z:::::Z      ee::::::::::::ee   mm:::::::m  m:::::::mm   cc:::::::::::::::ci:::::i   a::::::::::::a   k:::::k   k:::::k
 *           Z:::::Z      e::::::eeeee:::::eem::::::::::mm::::::::::m c:::::::::::::::::c i::::i   aaaaaaaaa:::::a  k:::::k  k:::::k
 *          Z:::::Z      e::::::e     e:::::em::::::::::::::::::::::mc:::::::cccccc:::::c i::::i            a::::a  k:::::k k:::::k
 *         Z:::::Z       e:::::::eeeee::::::em:::::mmm::::::mmm:::::mc::::::c     ccccccc i::::i     aaaaaaa:::::a  k::::::k:::::k
 *        Z:::::Z        e:::::::::::::::::e m::::m   m::::m   m::::mc:::::c              i::::i   aa::::::::::::a  k:::::::::::k
 *       Z:::::Z         e::::::eeeeeeeeeee  m::::m   m::::m   m::::mc:::::c              i::::i  a::::aaaa::::::a  k:::::::::::k
 *    ZZZ:::::Z     ZZZZZe:::::::e           m::::m   m::::m   m::::mc::::::c     ccccccc i::::i a::::a    a:::::a  k::::::k:::::k
 *    Z::::::ZZZZZZZZ:::Ze::::::::e          m::::m   m::::m   m::::mc:::::::cccccc:::::ci::::::ia::::a    a:::::a k::::::k k:::::k
 *    Z:::::::::::::::::Z e::::::::eeeeeeee  m::::m   m::::m   m::::m c:::::::::::::::::ci::::::ia:::::aaaa::::::a k::::::k  k:::::k
 *    Z:::::::::::::::::Z  ee:::::::::::::e  m::::m   m::::m   m::::m  cc:::::::::::::::ci::::::i a::::::::::aa:::ak::::::k   k:::::k
 *    ZZZZZZZZZZZZZZZZZZZ    eeeeeeeeeeeeee  mmmmmm   mmmmmm   mmmmmm    cccccccccccccccciiiiiiii  aaaaaaaaaa  aaaakkkkkkkk    kkkkkkk
 *
 *		Ola Druciak & Patrycja Zemankiewicz & Grzegorz Dobroń & Tomasz Szewczyk
 *		II LO Świdnica
 *		Diversity 2015, Kraków
 */

#ifndef LED_H_
#define LED_H_

#include <avr/io.h>

//Definicje LEDów
#define LED_FR_DDR DDRC
#define LED_FL_DDR DDRA
#define LED_BR_DDR DDRC
#define LED_BL_DDR DDRA

#define LED_FR_PORT PORTC
#define LED_FL_PORT PORTA
#define LED_BR_PORT PORTC
#define LED_BL_PORT PORTA

#define LED_FR 3
#define LED_FL 7
#define LED_BR 1
#define LED_BL 6

void ledInit();

void ledFR(bool onoff);
void ledFL(bool onoff);
void ledBR(bool onoff);
void ledBL(bool onoff);


#endif /* LED_H_ */
