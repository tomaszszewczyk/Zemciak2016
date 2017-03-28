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
 *		Ola Druciak & Patrycja Zemankiewicz & Damian Antos & Tomasz Szewczyk
 *		II LO Świdnica
 *		Diversity 2016, Kraków
 */


package II_LO_Świdnica;
import robocode.*;
import robocode.control.events.TurnStartedEvent;

import java.awt.*;
import java.lang.Math.*;

public class Zemciak extends AdvancedRobot 
{
	//Kierunek skanowania
	private byte kierunek_skan = 1;
	private byte kierunek_ruch = 1;
	private double size;
	private String enemy = "null";
	private int watchdog = 0;
	ScannedRobotEvent elast = null;
	ScannedRobotEvent elastlast = null;
			
	public void run()
	{
		//Kolory!
		setBodyColor(Color.cyan);
		setGunColor(Color.pink);
		setRadarColor(Color.cyan);
		setScanColor(Color.white);
		setBulletColor(Color.pink);
		
		//Lufa chodzi niezależnie
		setAdjustGunForRobotTurn(true);
		//Radar chodzi niezależnie
		setAdjustRadarForRobotTurn(true);
		setAdjustRadarForGunTurn(true);
		
		//Krótszy wymiar planszy
		size = min(getBattleFieldHeight(), getBattleFieldWidth());
		
		//Skan inicjalizacyjny
		while(true)
		{
		setTurnRadarRight(720);
		//setAhead(size*0.5*Math.random()+50);
		execute();	
		}
	}
	
	//Watchdog - nie dziła, nie wiem czemu ;)
	public void onSkippedTurn(SkippedTurnEvent e)
	{
		out.println("Watchdog!");
		watchdog++;
		if(watchdog > 3)
		{
			enemy = "null";
			scan();
			setTurnRadarRight(720);
			//setAhead(size*0.5*Math.random()+50);
			execute();
			watchdog=0;
		}
	}
	
	//Nowy przeciwnik
	public void onRobotDeath(RobotDeathEvent e) 
	{ 
		if(e.getName() == enemy)
		{
			enemy = "null";
			scan();
			setTurnRadarRight(720);
			//setAhead(size*0.5*Math.random()+50);
			execute();
		}
	}
	
	//Nowy przeciwnik
	public void onHitByBullet(HitByBulletEvent e) 
	{ 
		enemy = e.getName();
			scan();
			setTurnRadarRight(720);
			//setAhead(size*0.5*Math.random()+50);
			execute();
	}
	
	//Nowy przeciwnik
	public void onHitRobot(HitRobotEvent e) 
	{ 
		enemy = e.getName();
			scan();
			setTurnRadarRight(720);
			//setAhead(size*0.5*Math.random()+50);
			execute();
	}
	
	//Namierzono robota
	public void onScannedRobot(ScannedRobotEvent e) 
	{
		//Do weryfikacji czy przeciwnik jeździ po prostej czy po okręgu
		if(elast == null) elast = e;
		if(elastlast == null) elastlast = e;
		
		//Watchdog
		watchdog=0;
		
		//Weryfikacja przeciwnika, staramy się celować cały czas w tego samego przeciwnika
		out.println("Przeciwnik: " + e.getName());
		if(enemy == "null")
			enemy = e.getName();
		else
			if(enemy != e.getName())
				return;
		
		//Skanowanie + trochę histerezy
		double turn = getHeading() - getRadarHeading() + e.getBearing();
		if(turn > 360) turn -= 360;
		if(turn < -360) turn += 360;
		
		if(turn > 0 && turn <= 180)
			setTurnRadarRight(turn+5);
		if(turn > 180)
			setTurnRadarRight(turn - 365);
		
		if(turn <= 0 && turn > -180)
			setTurnRadarRight(turn-5);
		if(turn <= -180)
			setTurnRadarRight(turn + 365);
		
		out.println("Turning radar " + (getHeading() - getRadarHeading() + e.getBearing())); // <<< dane wychodzą do terminala dostępnego po kliknięciu na nazwę robota
		
		//Uniki
		/*if(getDistanceRemaining() == 0)
		{
			kierunek_ruch *= -1;
			setAhead((size*(e.getDistance()/600)*Math.random()+150) * kierunek_ruch);
		}
			
		setTurnRight(e.getBearing() + 90 - (60*(e.getDistance()/600 -0.3)*kierunek_ruch));*/
		
		
		//Obliczanie kąta strzału z uzwględniem ruchu przeciwnika
		if(e.getHeading() == elast.getHeading()) // Jeśli jeździ po prostej
			turn = lineTarget(e);
		
		else //Jeśli jeździ po okręgu
			turn = circleTarget2(e, elast, elastlast); //Na podstawie trzech punktów
		
			//lub
			//turn = circleTarget(e, elast); //Na podstawie dwóch punktów i kątów
		
		//Gdyby obliczanie zakończyło się błędem
		if(turn == -999)
		{
			execute();
			elast = e;
			return;
		}
			
		//skręcanie lufy
		if(turn > 360) turn -= 360;
		if(turn < -360) turn += 360;
		
		if(turn > 0 && turn <= 180)
			setTurnGunRight(turn);
		if(turn > 180)
			setTurnGunRight(turn - 360);
		
		if(turn <= 0 && turn > -180)
			setTurnGunRight(turn);
		if(turn <= -180)
			setTurnGunRight(turn + 360);
		
		out.println("Turning gun " + getGunTurnRemaining());
		
		//Wybór mocy uderzenie (wpłyna na prędkość pocisku)
		if(e.getDistance() < 800)
		{
			if(getGunTurnRemaining() < 3)
			{
				if(e.getDistance() < 100)
					setFire(3);
				else if(e.getDistance() < 300)
					setFire(2);
				else
					setFire(1);
			}
		}
		else
			if(getGunTurnRemaining() < 1)
					setFire(1);
		
		
		
		execute();
		
		//Uzwględniaj tylko punkty które leżą odpowiednio daleko od siebie (nic nie daje)
		//if(Math.abs( (elast.getDistance() * Math.sin(getHeadingRadians() + elast.getBearingRadians())) - (e.getDistance() * Math.sin(getHeadingRadians() + e.getBearingRadians())) ) > 5 ||
		//   Math.abs( (elast.getDistance() * Math.cos(getHeadingRadians() + elast.getBearingRadians())) - (e.getDistance() * Math.cos(getHeadingRadians() + e.getBearingRadians())) ) > 5)
		
		//Zapisz poprzednie punkty do obliczeń
		elastlast = elast;
		elast = e;
	}
	
	private double circleTarget2(ScannedRobotEvent e1, ScannedRobotEvent e2, ScannedRobotEvent e3)
	{
		//Pobierz trzy punkty należące do okręgu
		double x1 = e1.getDistance() * Math.sin(getHeadingRadians() + e1.getBearingRadians()),
			   y1 = e1.getDistance() * Math.cos(getHeadingRadians() + e1.getBearingRadians()),
			   x2 = e2.getDistance() * Math.sin(getHeadingRadians() + e2.getBearingRadians()),
			   y2 = e2.getDistance() * Math.cos(getHeadingRadians() + e2.getBearingRadians()),
			   x3 = e3.getDistance() * Math.sin(getHeadingRadians() + e3.getBearingRadians()),
			   y3 = e3.getDistance() * Math.cos(getHeadingRadians() + e3.getBearingRadians());
						
		 out.println("x1: " + x1);  // <<< dane wychodzą do terminala dostępnego po kliknięciu na nazwę robota
		 out.println("y1: " + y1);
		 out.println("x2: " + x2);
		 out.println("y2: " + y2);
		 out.println("x3: " + x3);
		 out.println("y3: " + y3);
		
		 //Obliczanie równania okręgu na podstawie trzech punktów
		double sx = 0.5 * (x2 * x2 * y3 + y2 * y2 * y3 - x1 * x1 * y3 + x1 * x1 * y2 - y1 * y1 * y3 + y1 * y1 * y2 + y1 * x3 * x3 + y1 * y3 * y3 - y1 * x2 * x2 - y1 * y2 * y2 - y2 * x3 * x3 - y2 * y3 * y3) / (y1 * x3 - y1 * x2 - y2 * x3 - y3 * x1 + y3 * x2 + y2 * x1);
        double sy = 0.5 * (-x1 * x3 * x3 - x1 * y3 * y3 + x1 * x2 * x2 + x1 * y2 * y2 + x2 * x3 * x3 + x2 * y3 * y3 - x2 * x2 * x3 - y2 * y2 * x3 + x1 * x1 * x3 - x1 * x1 * x2 + y1 * y1 * x3 - y1 * y1 * x2) / (y1 * x3 - y1 * x2 - y2 * x3 - y3 * x1 + y3 * x2 + y2 * x1);
        double r = (x1-sx)*(x1-sx) + (y1-sy)*(y1-sy);
        
		out.println("sx: " + sx);
		out.println("sy: " + sy);
		out.println("r: " + Math.sqrt(r));
        
		//Prędkość pocisku i przeciwnika
		double vp = 17, vc = e1.getVelocity();
		
		if(e1.getDistance() < 800)	//Prędkość w zależności od mocy pocisku (por. onScannedRobot(ScannedRobotEvent e) )
		{
			if(getGunTurnRemaining() < 3)
			{
				if(e1.getDistance() < 100)
					vp = 11;
				else if(e1.getDistance() < 300)
					vp = 14;
				else
					vp = 17;
			}
		}

		//Prędkość kątowa przeciwnika
		double omega = vc/Math.sqrt(r);
		
		//Zmienne do zapisu najlepszego dopasowania
		double turn = 99999, czas = 999999, xkon = 0, ykon = 0;
		double drogak = 0;
		
		double katpr = 0;
		double katkr = 0;

		//W pętli są sprawdzane wszystkie kąty i szukany ten dla którego pocisk zderzy się z przeciwnikiem
		for(double i = 0.01; i < 180; i += 0.1)
		{
			double alpha2 = Math.tan(Math.toRadians(i));

			double delta2 = ((((2*alpha2*sy) + (2*sx))*((2*alpha2*sy) + (2*sx))) -  (4*((alpha2*alpha2) + 1)*((sy*sy) + (sx*sx) -r)));
			
			if(delta2 < 0)
			{
				//Jeśli delta < 0 to nie ma punktów przecięcia, nic nie rób
			}

			else
			{
				double pierwdelta2;
				pierwdelta2 = Math.sqrt(delta2);
				
				//isky
				double ee1 = ((((2*alpha2*sy) + (2*sx))) - (pierwdelta2)) / (2*((alpha2*alpha2) + 1));
				double ee2 = ((((2*alpha2*sy) + (2*sx))) + (pierwdelta2)) / (2*((alpha2*alpha2) + 1));

				//wyliczamy ygerki
				double f1 = alpha2*ee1;
				double f2 = alpha2*ee2;

				//dzieki temu wypluwamy punkty przeciecia
				//cout <<"Punkt 1 to: P1=("<<e1<<" , "<<f1<<" )"<<endl;
				//cout <<"Punkt 2 to: P2=("<<e2<<" , "<<f2<<" )"<<endl;

				//Obliczanie drogi dla pocisku i przeciwnika do punktu przecięcia
				double drogas = Math.sqrt(ee1*ee1 + f1*f1);
				double katk = Math.asin((ee1-sx)/Math.sqrt(r));
				if(ee1 < sx) katk += 2*Math.PI;
				if(f1 < sy) katk -= Math.PI/2;
				
				double katp = Math.asin((x1-sx)/Math.sqrt(r));
				if(x1 < sx) katp += 2*Math.PI;
				if(y1 < sy) katp -= Math.PI/2;
				
				drogak = katk - katp;
				
				if(drogak < 0) drogak += 2*Math.PI;

				double ts, tk;

				//Czas przelotu
				ts = drogas/vp;
	            while(ts > 2*Math.PI/omega) drogak += 2*Math.PI;
				tk = drogak/omega;

				//Znajdź rekordowy czas przelotu
       			if(Math.abs(ts-tk) < czas)
				{
					czas = Math.abs(ts-tk);
					turn = i;
	                ykon = f1;
	                katpr = katp;
	                katkr = katk;
				}


				//To samo dla drugiego punktu
 	            drogas = Math.sqrt(ee2*ee2 + f2*f2);
				
				katk = Math.asin((ee2-sx)/Math.sqrt(r));
				if(ee2 < sx) katk += 2*Math.PI;
				if(f2 < sy) katk -= Math.PI/2;
				
				katp = Math.asin((x1-sx)/Math.sqrt(r));
				if(x1 < sx) katp += 2*Math.PI;
				if(y1 < sy) katp -= Math.PI/2;
				
				drogak = katk - katp;
				
				if(drogak < 0) drogak += 2*Math.PI;
	            
	            ts = drogas/vp;
	            while(ts > 2*Math.PI/omega) drogak += 2*Math.PI;
	            tk = drogak/omega;
	           

	            if(Math.abs(ts-tk) < czas)
	            {
	                   	czas = Math.abs(ts-tk);
	                   	turn = i;
	                   	ykon = f2;
		               	katpr = katp;
		               	katkr = katk;
	            }	
	            
	            out.println("	i: " +i);
	    		out.println("	ee1: " +(ee1-sx));
	    		out.println("	f1: " +(f1-sy));
	    		out.println("	czas: " +Math.abs(ts-tk));
	    		out.println("	ts: " +ts);
	    		out.println("	tk: " +tk);
	    		out.println("	katp: " +katp);
	    		out.println("	katk: " +katk);
	    		out.println("");
			}
		}

		//Gdy zderzenie zachodzi w III lub IV ćwiartce
		if(ykon < 0) turn = turn + 180;
		
		out.println(turn);
		out.println("x1: " + x1);
		out.println("katkr: " +katkr);
		out.println("katpr: " +katpr);
		out.println("d czas: " +czas);
		//Poprawka na organizację kątów w grze
		return (90 - turn) - getGunHeadingDegrees();
	}
	
	//Obliczanie kąta strzału dla ruchu po okręgu (por. circleTarget2(...))
	private double circleTarget(ScannedRobotEvent e1, ScannedRobotEvent e2)
	{
		//Zbieranie danych, dwie styczne do okręgu
		double xa = e1.getDistance() * Math.sin(getHeadingRadians() + e1.getBearingRadians()),
			   xb = e2.getDistance() * Math.sin(getHeadingRadians() + e2.getBearingRadians()),
			   ya = e1.getDistance() * Math.cos(getHeadingRadians() + e1.getBearingRadians()),
			   yb = e2.getDistance() * Math.cos(getHeadingRadians() + e2.getBearingRadians()),
			   alpha = 90 - e1.getHeading(),
			   beta = 90 - e2.getHeading();
		
		 out.println("xa: " + xa);// <<< dane wychodzą do terminala dostępnego po kliknięciu na nazwę robota
		 out.println("ya: " + ya);
		 out.println("xb: " + xb);
		 out.println("yb: " + yb);
		 out.println("alpha: " + alpha);
		 out.println("beta: " + beta);

		//Załóżmy, że nie ma takich problemów
		/*while(alpha == beta || alpha == beta+180 || alpha+180 == beta)
		{
			cout << "alpha =|= beta!!!" << endl << "alpha: ";
			cin >> alpha;
			cout << "beta: ";
			cin >> beta;
		}*/
		
		//Mały hack, żeby oszczędzić sobie założeń
		if(alpha == 0) alpha += 0.001;	//Good enough
		if(alpha == 90) alpha += 0.001;
		if(alpha == 180) alpha += 0.001;
		if(alpha == 270) alpha += 0.001;
		if(alpha == 360) alpha -= 0.001;
		
		if(beta == 0) beta += 0.001;	//Good enough
		if(beta == 90) beta += 0.001;
		if(beta == 180) beta += 0.001;
		if(beta == 270) beta += 0.001;
		if(beta == 360) beta -= 0.001;
		
		//Obliczanie równania okręgu
		alpha = Math.tan(alpha/180*3.14);
		beta = Math.tan(beta/180*3.14);
		double b1 = ya - (alpha*xa); //punkt b1 to punkt b pierwszej prostej stycznej do okregu
		double b2 = yb - (beta*xb);  //punkt b2 to punkt b drugiej prostej stycznej do okregu

		//liczymy punkty dla prostopadlych wykorzystujac warunek wspolczynnika kierunkowego (-1/alpha) i analogicznie dla beta
		double b3 = (alpha*xa) + b1 - (-1/alpha)*xa;
		double b4 = (beta*xb) + b2 - (-1/beta)*xb;

		//liczymy srodek okregu przeksztalcajac wzor 
		// (-1/beta)sx + b4 -  = (-1/alpha)sx +b3
		double sx= (b3-b4)/((-1/beta) - (-1/alpha));
		double sy= (-1/alpha)*sx + b3;

		//liczymy promiec po prostu podstawiajac wszytsko do wzoru na okrag
		double r = (xa-sx)*(xa-sx) + (ya-sy)*(ya-sy);
		
		//liczymy średni promień z dwóch punktów (nic nie daje)
		//double r = ((Math.sqrt((xa-sx)*(xa-sx) + (ya-sy)*(ya-sy)) + Math.sqrt((xb-sx)*(xb-sx) + (yb-sy)*(yb-sy))) /2 ) * ((Math.sqrt((xa-sx)*(xa-sx) + (ya-sy)*(ya-sy)) + Math.sqrt((xb-sx)*(xb-sx) + (yb-sy)*(yb-sy))) /2 );

		out.println("sx: " + sx);
		out.println("sy: " + sy);
		out.println("r: " + Math.sqrt(r));

		//Liczymy zakres strzału (nie potrzebne)
		/*if((sx*sx) + (sy*sy) > r)
		{
			double delta = ((2*sx*sy)*(2*sx*sy)) - (4*((sx*sx)-r)*((sy*sy)-r));

			double pierwdelta = Math.sqrt(delta);
			 
			double c = ( (((2*sx*sy)) - (pierwdelta))  / (2*((sx*sx)-r))) ;
			double d = ((((2*sx*sy)) + (pierwdelta))  / (2*((sx*sx)-r))) ;

			//cout << "Kąt 1 to: " << (atan(c)/3.14*180) << endl;
			//cout << "Kąt 2 to: " << (atan(d)/3.14*180) << endl;
		}
				else
		{}//cout << "Nie da się policzyć zakresu, punkt wewnątrz koła" << endl;
*/
		//Prędkość pocisku i przeciwnika
		double vp = 17, vc = e1.getVelocity();
		
		if(e1.getDistance() < 800)	//Prędkość w zależności od mocy pocisku (por. onScannedRobot(ScannedRobotEvent e) )
		{
			if(getGunTurnRemaining() < 3)
			{
				if(e1.getDistance() < 100)
					vp = 11;
				else if(e1.getDistance() < 300)
					vp = 14;
				else
					vp = 17;
			}
		}

		//Prędkość kątowa przeciwnika
		double omega = vc/Math.sqrt(r);
		
		//Zmienne do zapisu najlepszego dopasowania
		double turn = 99999, czas = 999999, xkon = 0, ykon = 0;
		double drogak = 0;

		//W pętli są sprawdzane wszystkie kąty i szukany ten dla którego pocisk zderzy się z przeciwnikiem
		for(double i = 0.01; i < 180; i += 0.1)
		{
			double alpha2, delta2;
			alpha2 = i;
			alpha2 = Math.tan(alpha2/180*3.14);

			delta2 = ((((2*alpha2*sy) + (2*sx))*((2*alpha2*sy) + (2*sx))) -  (4*((alpha2*alpha2) + 1)*((sy*sy) + (sx*sx) -r)));
			
			if(delta2 < 0)
			{
				//Jeśli delta < 0 to nie ma punktów przecięcia, nic nie rób
			}

			else
			{
				double pierwdelta2;
				pierwdelta2 = Math.sqrt(delta2);
				
				//isky
				double ee1 = ((((2*alpha2*sy) + (2*sx))) - (pierwdelta2)) / (2*((alpha2*alpha2) + 1));
				double ee2 = ((((2*alpha2*sy) + (2*sx))) + (pierwdelta2)) / (2*((alpha2*alpha2) + 1));

				//wyliczamy ygerki
				double f1 = alpha2*ee1;
				double f2 = alpha2*ee2;

				//dzieki temu wypluwamy punkty przeciecia
				//cout <<"Punkt 1 to: P1=("<<e1<<" , "<<f1<<" )"<<endl;
				//cout <<"Punkt 2 to: P2=("<<e2<<" , "<<f2<<" )"<<endl;

				//Obliczanie drogi dla pocisku i przeciwnika do punktu przecięcia
				double drogas = Math.sqrt(ee1*ee1 + f1*f1);
				double katp = Math.asin((ee1-sx)/Math.sqrt(r));
				double katk = Math.asin((xa-sx)/Math.sqrt(r));
				
				if(katp < 0) katp = 360 - katp;
				if(katk < 0) katk = 360 - katk;
				
				drogak = Math.abs(katp - katk);
				
				if(drogak < 0) drogak += 2*Math.PI;

				double ts, tk;

				//Czas przelotu
				ts = drogas/vp;
				tk = drogak/omega;

				//Znajdź rekordowy czas przelotu
				if(Math.abs(ts-tk) < czas)
				{
					czas = Math.abs(ts-tk);
					turn = i;
	                ykon = f1;
				}


				//To samo dla drugiego punktu
 	            drogas = Math.sqrt(ee2*ee2 + f2*f2);
				
 	            katp = Math.asin((ee1-sx)/Math.sqrt(r));
				katk = Math.asin((xa-sx)/Math.sqrt(r));
				
				if(katp < 0) katp = 360 - katp;
				if(katk < 0) katk = 360 - katk;
				
				drogak = Math.abs(katp - katk);
	            
	            ts = drogas/vp;
	            tk = drogak/omega;

	            if(Math.abs(ts-tk) < czas)
	            {
	                   czas = Math.abs(ts-tk);
	                   turn = i;
	                   ykon = f2;
	            }	
			}
		}

		//Gdy zderzenie zachodzi w III lub IV ćwiartce
		if(ykon < 0) turn = turn + 180;
		
		out.println(turn);
		//Poprawka na organizację kątów w grze
		return (90 - turn) - getGunHeadingDegrees();
	}
	
	//Obliczanie kąta strzału dla przeciwnika (działa doskonale)
	private double lineTarget(ScannedRobotEvent e)
	{
		double turn = 0;
		//Strzelanie
		
				//Tutaj obliczamy customowy turn uwzględniający ruchy przeciwnika
				
				//Dane:
				out.println("Dane");
				//Położenie przeciwnika względem mojego
				double x = e.getDistance() * Math.sin(getHeadingRadians() + e.getBearingRadians());
				out.println("x: " + x);
				double y = e.getDistance() * Math.cos(getHeadingRadians() + e.getBearingRadians());
				out.println("y: " + y);
				
				//Prędkość pocisku
				double va = 17;
				
				if(e.getDistance() < 800)
				{
					if(getGunTurnRemaining() < 3)
					{
						if(e.getDistance() < 100)
							va = 11;
						else if(e.getDistance() < 300)
							va = 14;
						else
							va = 17;
					}
				}
				out.println("va: " + va);
				
				//Prędkość przeciwnika
				double vb = e.getVelocity();
				out.println("vb: " + vb);
				
				//Kąt ruchu przeciwnika w radianach
				double beta = e.getHeadingRadians();
				out.println("beta: " + beta);
				
				//Obliczenia
				out.println("Obliczenia");
				//A:
				double Astala = (vb/va) * ( (x * Math.cos(beta)) - (y * Math.sin(beta)) );
				out.println("A: " + Astala);
				out.println("vb/va: " + vb/va);
				out.println("(x*Math.cos(beta)) - (y*Math.sin(beta)): " + ((x*Math.cos(beta)) - (y*Math.sin(beta))));
				out.println("(Math.cos(beta)): " + (Math.cos(beta)));
				out.println("(Math.sin(beta)): " + (Math.sin(beta)));
				
				//a:
				double a = y*y + x*x;
				out.println("a: " + a);
				//b:
				double b = 2*Astala*y;
				out.println("b: " + b);
				//c:
				double c = Astala*Astala - x*x;
				out.println("c: " + c);
				//delta:
				double delta = b*b - 4*a*c;
				out.println("delta: " + delta);
				//sinusy:
				double sinus_1 = (-(b) + Math.sqrt(delta)) / (2*a);
				out.println("sinus_1: " + sinus_1);
				double sinus_2 = (-(b) - Math.sqrt(delta)) / (2*a);
				out.println("sinus_2: " + sinus_2);
				//kąty w radianach:
				double alfa_1 = Math.asin(sinus_1);	//Pierwsza ćwiartka
				out.println("alfa_1: " + alfa_1);
				double alfa_2 = Math.PI/2 + Math.abs(Math.PI/2 - alfa_1);	//Druga ćwiartka
				out.println("alfa_2: " + alfa_2);
				double alfa_4 = Math.asin(sinus_2);	//Czwarta ćwiartka (celowo nie pokolei)
				double alfa_3 = (-1)*Math.PI/2 - Math.abs((-1)*Math.PI/2 - alfa_4); //Trzecia ćwiartka
				out.println("alfa_3: " + alfa_3);
				out.println("alfa_4: " + alfa_4);
				//czas:
				double czas_1 = x / (va*sinus_1 - vb * Math.sin(beta));
				out.println("czas_1: " + czas_1);
				double czas_2 = x / (va*sinus_2 - vb * Math.sin(beta));
				out.println("czas_2: " + czas_2);
				double czas;
				
				if(czas_1 >= czas_2) czas = czas_1;	//Wybierz dodatni
				else czas = czas_2;
				out.println("czas: " + czas);
				//moment zderzenia:
				double xkon = x + vb*Math.sin(beta)*czas;
				out.println("xkon: " + xkon);
				double ykon = y + vb*Math.cos(beta)*czas;
				out.println("ykon: " + ykon);
				
				if(xkon + this.getX() < -300 ||
				   ykon + this.getY() < -300 ||
				   xkon + this.getX() > getBattleFieldWidth() +300 ||
				   ykon + this.getY() > getBattleFieldHeight() +300)
				{
					return -999;
				}
				//wybór ćwiartki
				if(xkon >= 0 && ykon >= 0) turn = alfa_1 - getGunHeadingRadians(); //pierwsza
				if(xkon >= 0 && ykon < 0) turn = alfa_2 - getGunHeadingRadians();//druga
				if(xkon < 0 && ykon < 0) turn = alfa_3 - getGunHeadingRadians(); //trzecia
				if(xkon < 0 && ykon >= 0) turn = alfa_4 - getGunHeadingRadians(); //czwarta

				out.println("turn: " + turn);
				
				turn = turn / (2*Math.PI) * 360;
				
				return turn;
	}
	
	//Wybierz mniejszy
	private double min(double a, double b) 
	{
		if(a < b)
			return a;
		else
			return b;
	}
	
	//Wybierz większy
	private double max(double a, double b) 
	{
		if(a > b)
			return a;
		else
			return b;
	}
}
