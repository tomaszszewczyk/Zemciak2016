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

#ifndef ZEMCIAK_H_
#define ZEMCIAK_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "zemciak.h"
#include "led/led.h"
#include "sonar/sonar.h"
#include "line/line.h"
#include "engine/engine.h"
#include "debug/debug.h"
#include "adc/adc.h"

#define PROBA 2
#define ATAK 1500
#define SZUKANIE 1200
#define PROGSONAR 60
#define ATAKCORR 500
#define ATAKSTEP 1
#define SZUKANIECORR 350
#define SWAP 150

void switchInit();
void loopInit();

bool getSwitch();

#endif /* ZEMCIAK_H_ */
