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

#include "adc.h"

volatile uint16_t battery;
volatile uint16_t adcLeft;
volatile uint16_t adcRight;

void adcInit()
{
	ADMUX = (1 << REFS1) | (1 << REFS0) | (1 << MUX0) | (1 << MUX1) | (1 << ADLAR); //Internal 2.56V
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADCSRA |= (1 << ADSC);
}

ISR(ADC_vect)
{
	static uint8_t pomiar = 0;

	if(pomiar == 0)
	{
		battery = ADC;
		ADMUX = (1 << REFS1) | (1 << REFS0) | (1 << MUX2);
	}
	else if(pomiar == 1)
	{
		adcLeft = ADC;
		ADMUX = (1 << REFS1) | (1 << REFS0) | (1 << MUX2) | (1 << MUX0);
	}
	else if(pomiar == 2)
	{
		adcRight = ADC;
		ADMUX = (1 << REFS1) | (1 << REFS0) | (1 << MUX0) | (1 << MUX1);
	}

	pomiar++;
	if(pomiar > 2) pomiar = 0;

	ADCSRA |= (1 << ADSC);

	/*char nadawanie[100];

	sprintf(nadawanie, "%3d %3d %3d\n", adcBattery(), adcEngineLeft(), adcEngineRight());
	send(nadawanie);*/
}

uint8_t adcEngineLeft()
{
	return adcLeft;
}

uint8_t adcEngineRight()
{
	return adcRight;
}

uint8_t adcBattery()
{
	return battery;
}
