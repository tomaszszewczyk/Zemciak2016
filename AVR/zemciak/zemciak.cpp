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

#include "zemciak.h"

volatile uint32_t time = 0;

int main()
{
	//--------------------------------------------------------------------------
	//Inicjalizacja
	ledInit();
	sonarInit();
	engineInit();
	lineInit();
	switchInit();
	loopInit();
	debugInit();
	adcInit();
	sei();

	//--------------------------------------------------------------------------
	//Aktywacja
	ledFL(true);
	ledFR(true);
	ledBR(true);
	ledBL(true);
	while(getSwitch() == false) {}	//Czekaj na naciśnięcie
	ledFL(false);
	ledFR(false);
	ledBR(false);
	ledBL(false);

	ledFL(true);	//Potwierdź aktywację diodą
	_delay_ms(1000);	//Czekaj 1000ms

	//--------------------------------------------------------------------------
	if(getSwitch() == true)	//Jeśli przytrzymano włącz czyszczenie silników
	{
		ledFL(true);
		ledFR(true);
		ledBR(true);
		ledBL(true);
		setEngine(127,127);
		while(1){}
	}
	//--------------------------------------------------------------------------

	ledFR(true);	//1000ms
	_delay_ms(1000);
	ledBR(true);	//2000ms
	_delay_ms(1000);
	ledBL(true);	//3000ms
	_delay_ms(1000);
	ledFL(false);	//4000ms
	ledFR(false);
	ledBR(false);
	ledBL(false);
	_delay_ms(500);
	ledFL(true);	//4500ms
	ledFR(true);
	ledBR(true);
	ledBL(true);
	_delay_ms(450);
	ledFL(false);	//5000ms
	ledFR(false);
	ledBR(false);
	ledBL(false);

	//--------------------------------------------------------------------------
	//Rozwijanie lemieszy
	setEngine(-127, -127);
	_delay_ms(1000);
	setEngine(127, 127);
	_delay_ms(1000);

	//--------------------------------------------------------------------------
	//Początek pętli głównej
	bool strona = false;
	uint8_t proba = 0;
	uint32_t ataktime = 0;
	uint32_t szukanietime = 0;

	while(1)	//Pętla główna
	{
		//--------------------------------------------------------------------------
		//Moduł atak

		atak:
		ataktime = time;

		while(sonarMin() < PROGSONAR)
		{
			szukanietime=time;
			ledBL(true);
			if(time - ataktime <= ATAK)	//Jeśli nie przekroczono czasu ataku => atakuj
			{
				if(sonarLeft() < sonarRight()) {ledFL(true); ledFR(false);}	//Zapal odpowiednie diody
				else {ledFR(true); ledFL(false);}

				if(sonarLeft() > sonarRight() - 10 && sonarRight() > sonarLeft() - 10)	//Jeśli sonary oba, jedź w przód
				{
					setEngine(127, 127);
					for(uint32_t i = time; time - i < ATAKSTEP*3;)	//Cofaj przez ATAKSTEP, dbając o linię
					{
						if(lineFR() == true || lineFL()  == true || lineBR()  == true || lineBL() == true)
							goto linia;
					}
				}

				else if(sonarLeft() > sonarRight())	//Wybór kierunku ataku
				{
					setEngine(127, -50);
					for(uint32_t i = time; time - i < ATAKSTEP;)	//Cofaj przez ATAKSTEP, dbając o linię
					{
						if(lineFR() == true || lineFL()  == true || lineBR()  == true || lineBL() == true)
							goto linia;
					}
				}

				else
				{
					setEngine(-50, 127);
					for(uint32_t i = time; time - i < ATAKSTEP;)	//Cofaj przez ATAKSTEP, dbając o linię
					{
						if(lineFR() == true || lineFL()  == true || lineBR()  == true || lineBL() == true)
							goto linia;
					}
				}

				if(sonarLeft() < sonarRight()) strona = false;	//Zapisz gdzie ostatnio widziano przeciwnika
				else strona = true;

				if(lineFR() == true || lineFL()  == true || lineBR()  == true || lineBL() == true)	//Zadbaj o linie
					goto linia;
			}
			else	//Jeśli przekroczono czas
			{
				if(adcEngineLeft() > 100 && adcEngineRight() > 100)	//Sprawdź obciążenie silników
				{
					setEngine(-127, -127);	//Cofaj

					for(uint32_t i = time; time - i < ATAKCORR;)	//Cofaj przez ATAKCORR, dbając o linię
					{
						if(lineFR() == true || lineFL()  == true || lineBR()  == true || lineBL() == true)
							goto linia;
					}

					setEngine(127, 127);
				}
				else if(adcEngineLeft() > 80)
				{
					setEngine(-127, -50);

					for(uint32_t i = time; time - i < ATAKCORR;)
					{
						if(lineFR() == true || lineFL()  == true || lineBR()  == true || lineBL() == true)
							goto linia;
					}

					setEngine(127, 127);
				}
				else if(adcEngineRight() > 80)
				{
					setEngine(-50, -127);

					for(uint32_t i = time; time - i < ATAKCORR;)
					{
						if(lineFR() == true || lineFL()  == true || lineBR()  == true || lineBL() == true)
											goto linia;
					}

					setEngine(127, 127);
				}
				ataktime = time;	//Wyzeruj
			}
		}

		if(time - ataktime > 1)
		{
			//Po wyjściu z sonaru przemiataj
			if(strona == true) //W prawo
			{
				setEngine(127, -50);
				for(uint32_t i = time; time - i < SWAP*2;)	//Przemiatanie w obie strony
				{
					if(lineFR() == true || lineFL()  == true || lineBR()  == true || lineBL() == true)
						goto linia;
					if(sonarMin() < PROGSONAR)
						goto atak;
				}

				setEngine(-50, 127);
				for(uint32_t i = time; time - i < SWAP;)
				{
					if(lineFR() == true || lineFL()  == true || lineBR()  == true || lineBL() == true)
						goto linia;
					if(sonarMin() < PROGSONAR)
						goto atak;
				}
			}
			else	//W lewo
			{
				setEngine(-50, 127);
				for(uint32_t i = time; time - i < SWAP*2;)	//Przemiatanie w obie strony
				{
					if(lineFR() == true || lineFL()  == true || lineBR()  == true || lineBL() == true)
						goto linia;
					if(sonarMin() < PROGSONAR)
						goto atak;

				}

				setEngine(127, -50);
				for(uint32_t i = time; time - i < SWAP;)
				{
					if(lineFR() == true || lineFL()  == true || lineBR()  == true || lineBL() == true)
						goto linia;
					if(sonarMin() < PROGSONAR)
						goto atak;
				}
			}
		}

		//--------------------------------------------------------------------------
		//Moduł szukanie

		sonar:
		//szukanietime = 0;

		while(sonarMin() > PROGSONAR)
		{
			if(time - szukanietime < SZUKANIE)	//Jeśli nie przekroczono czasu szukania
			{
				if(sonarLeft() < sonarRight()) {ledFL(true); ledFR(false);}	//Zapal odpowiednie diody
				else {ledFR(true); ledFL(false);}

				if(strona == false)	//Szukaj tam gdzie ostatnio widziany
					setEngine(-127, 127);
				else
					setEngine(127, -127);

				if(lineFR() == true || lineFL()  == true || lineBR()  == true || lineBL() == true )	//Zadbaj o linię
					goto linia;
			}
			else
			{
				setEngine(127, 127);	//Jeśli przekroczono czas, jedź do przodu
				for(uint32_t i = time; time - i < SZUKANIECORR;)
				{
					if(lineFR() == true || lineFL()  == true || lineBR()  == true || lineBL() == true )	//Zadbaj o linię
						goto linia;
					if(sonarMin() < PROGSONAR)
						goto atak;
				}
				szukanietime = time;
			}
		}

		linia:

		//--------------------------------------------------------------------------
		//Moduł linia
		while(lineFR() == true || lineFL()  == true || lineBR()  == true || lineBL() == true)	//Jeśli wykryto linię
		{
			szukanietime = time;
			ataktime = time;

			ledBR(true);
			if(lineFR() == true)
			{
				setEngine(-127,-110);
				for(uint32_t i = time; time - i < 250;) {}
				strona = false;
			}
			if(lineFL() == true)
			{
				setEngine(-110,-127);
				for(uint32_t i = time; time - i < 250;) {}
				strona = true;
			}

			if(lineBR() == true)
			{
				setEngine(110,127);
				for(uint32_t i = time; time - i < 250;) {}
				strona = false;
			}
			if(lineBL() == true)
			{
				setEngine(127,110);
				for(uint32_t i = time; time - i < 250;) {}
				strona = true;
			}


			if(sonarAvg() < 200)	//Wykrywanie zapętlenia przy linii
			{
				proba++;
				if(proba > PROBA)
				{
					if(strona == false)
						setEngine(-127, 127);
					else
						setEngine(127, -127);
					for(uint32_t i = time; time - i < 500;) {}
					proba = 0;
				}
			}
			else
				proba = 0;
		}

		ledFR(false);
		ledFL(false);
		ledBR(false);
		ledBL(false);
	}
}

void loopInit()
{
	ASSR &= ~(1 << AS2);
	TCCR2 |= (1 << WGM21) | (1 << CS22) | (1 << CS21) | (1 << CS20);	//CTC, div1024
	OCR2 = 15; //T=1ms
	TIMSK |= (1 << OCIE2);
}

ISR(TIMER2_COMP_vect)
{
	time++;
}

void switchInit()
{
	DDRD &= ~(1 << PD3);
	PORTD |= (1 << PD3);
}

bool getSwitch()
{
	if(PIND & (1 << PD3))
	{
		_delay_ms(10);
		if(PIND & (1 << PD3))
			return false;
	}
	else return true;
	return true;
}
