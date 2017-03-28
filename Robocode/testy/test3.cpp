#include <iostream>
#include <cmath>

using namespace std;

int main()

{
	//Zbieranie danych

	double x1,x2,x3,y1,y2,y3; //Dane
	
	cout<<"x1: ";
	cin>>x1;
	
	cout<<"y1: ";
	cin>>y1;
	
	cout<<"x2: ";
	cin>>x2;
	
	cout<<"y2: ";
	cin>>y2;
	
	cout<<"x3: ";
	cin>>x3;
	
	cout<<"y3: ";
	cin>>y3;

	/*while(alpha == beta || alpha == beta+180 || alpha+180 == beta)
	{
		cout << "alpha =|= beta!!!" << endl << "alpha: ";
		cin >> alpha;
		cout << "beta: ";
		cin >> beta;
	}
	
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
	
	alpha = tan(alpha/180*3.14);
	beta = tan(beta/180*3.14);

	//Obliczanie równania okręgu
	
	double b1 = ya - (alpha*xa); //punkt b1 to punkt b pierwszej prostej stycznej do okregu
	double b2 = yb - (beta*xb);  //punkt b2 to punkt b drugiej prostej stycznej do okregu

	//dla jasnosci wypluwamy na ekran czy dobrze nam obliczylo i co nam obliczylo :D

	//cout<<"prosta 1 to: "<<"ya = "<<alpha<<"x + "<<b1<<endl;
	//cout<<"prosta 2 to: "<<"yb = "<<beta<<"x + "<<b2<<endl;

	//liczymy punkty dla prostopadlych wykorzystujac warunek wspolczynnika kierunkowego (-1/alpha) i analogicznie dla beta

	double b3 = (alpha*xa) + b1 - (-1/alpha)*xa;
	double b4 = (beta*xb) + b2 - (-1/beta)*xb;

	//wypluwamy na ekran dla sprawdzenia

	//cout<<"prosta prostopadla do 1 to: "<<"ya1 = "<<-1/alpha<<"x + "<<b3<<endl;
	//cout<<"prosta prostopadla do 2 to: "<<"yb = "<<-1/beta<<"x + "<<b4<<endl;

	//twrzymy uklad rownan
	// y = (-1/alpha)sx +b3
	// y = (-1/beta)sx + b4 

	//liczymy srodek okregu przeksztalcajac wzor 
	// (-1/beta)sx + b4 -  = (-1/alpha)sx +b3
	// 
	double sx= (b3-b4)/((-1/beta) - (-1/alpha));
	double sy= (-1/alpha)*sx + b3;

	//liczymy promiec po prostu podstawiajac wszytsko do wzoru na okrag

	double r = (xa-sx)*(xa-sx) + (ya-sy)*(ya-sy);*/	

	double sx = 0.5 * (x2 * x2 * y3 + y2 * y2 * y3 - x1 * x1 * y3 + x1 * x1 * y2 - y1 * y1 * y3 + y1 * y1 * y2 + y1 * x3 * x3 + y1 * y3 * y3 - y1 * x2 * x2 - y1 * y2 * y2 - y2 * x3 * x3 - y2 * y3 * y3) / (y1 * x3 - y1 * x2 - y2 * x3 - y3 * x1 + y3 * x2 + y2 * x1);
        double sy = 0.5 * (-x1 * x3 * x3 - x1 * y3 * y3 + x1 * x2 * x2 + x1 * y2 * y2 + x2 * x3 * x3 + x2 * y3 * y3 - x2 * x2 * x3 - y2 * y2 * x3 + x1 * x1 * x3 - x1 * x1 * x2 + y1 * y1 * x3 - y1 * y1 * x2) / (y1 * x3 - y1 * x2 - y2 * x3 - y3 * x1 + y3 * x2 + y2 * x1);
		
        double r = (x1-sx)*(x1-sx) + (y1-sy)*(y1-sy);

	cout << endl << endl << "Okrag:" << endl << "X: " << sx << endl << "Y: " << sy << endl << "r: " << sqrt(r) << endl;
	
	//Liczymy zakres
	cout << endl << endl << "Zakres: " << endl;

	if((sx*sx) + (sy*sy) > r)
	{
		double promien=sqrt(r);

		double delta = ((2*sx*sy)*(2*sx*sy)) - (4*((sx*sx)-r)*((sy*sy)-r));

		double pierwdelta = sqrt(delta);
		 
		double c = ( (((2*sx*sy)) - (pierwdelta))  / (2*((sx*sx)-r))) ;
		double d = ((((2*sx*sy)) + (pierwdelta))  / (2*((sx*sx)-r))) ;

		cout << "Kąt 1 to: " << (atan(c)/3.14*180) << endl;
		cout << "Kąt 2 to: " << (atan(d)/3.14*180) << endl;
	}
	else
		cout << "Nie da się policzyć zakresu, punkt wewnątrz koła" << endl;

	cout << endl << endl << "Punkty przecięcia: " << endl;

	double vp, vc;

	cout << "vp: ";
	cin >> vp;

	cout << "vc: ";
	cin >> vc;

	double omega = vc/sqrt(r);
	double katp, katpp;

	double turn = 99999, czas = 999999;
	
	while(1)
	{
	double turn = 99999, czas = 999999;
		cout << "katp: ";
		cin >> katpp;
			
	for(double i = 0.01; i < 180; i += 1)
	{
		katp = katpp;
		double alpha2, delta2;

		alpha2 = i;
		
		alpha2 = tan(alpha2/180*3.14);

		//liczymy delte wyglada dosc skomplikowanie bo nawiasy itd ale to normalnie wszytsko liczby sa :D 
		delta2 = ((((2*alpha2*sy) + (2*sx))*((2*alpha2*sy) + (2*sx))) -  (4*((alpha2*alpha2) + 1)*((sy*sy) + (sx*sx) -r)));
		
		if(delta2 < 0)
		{
		}

		else
		{
			double pierwdelta2;
			pierwdelta2 = sqrt(delta2);
				
			//isky
			double ee1 = ((((2*alpha2*sy) + (2*sx))) - (pierwdelta2)) / (2*((alpha2*alpha2) + 1));
			double ee2 = ((((2*alpha2*sy) + (2*sx))) + (pierwdelta2)) / (2*((alpha2*alpha2) + 1));

			//wyliczamy ygerki
			double f1 = alpha2*ee1;
			double f2 = alpha2*ee2;

			//Obliczanie drogi dla pocisku i przeciwnika do punktu przecięcia
			double drogas = sqrt(ee1*ee1 + f1*f1);
			double katk = asin((ee1-sx)/sqrt(r));
			if(ee1 < sx) katk += 2*3.14;
			if(f1 < sy) katk += 3.14/2;
				
			//double katp = asin((x1-sx)/sqrt(r));
			if(x1 < sx) katp += 2*3.14;
			if(y1 < sy) katp += 3.14/2;
				
			double drogak = katk - katp;
				
			if(drogak < 0) drogak += 2*3.14;

			double ts, tk;

				//Czas przelotu
			ts = drogas/vp;
			tk = drogak/omega;

				//Znajdź rekordowy czas przelotu
       			if(abs(ts-tk) < czas)
			{
				czas = abs(ts-tk);
				turn = i;
			}
			
			cout << "i: " << i << endl;	
			cout << "ee1: " << ee1 << endl;
			cout << "f1: " << f1 << endl;
			cout << "drogas: " << drogas << endl;
			cout << "katk: " << katk << endl;
			cout << "drogak: " << drogak << endl;
			cout << "ts: " << ts << endl;
			cout << "tk: " << tk << endl << endl;
			
		/*cout << "i: " << i << endl;
		cout << "kat k: " << katk/3.14*180 << endl;
		cout << "czas: " << abs(ts-tk) << endl << endl;	*/


		//To samo dla drugiego punktu
 	            drogas = sqrt(ee2*ee2 + f2*f2);
				
		katk = asin((ee2-sx)/sqrt(r));
		if(ee2 < sx) katk += 2*3.14;
		if(f2 < sy) katk += 3.14/2;
				
		//katp = asin((x1-sx)/sqrt(r));
		if(x1 < sx) katp += 2*3.14;
		if(y1 < sy) katp += 3.14/2;
				
		drogak = katk - katp;
				
		if(drogak < 0) drogak += 2*3.14;
	            
	        ts = drogas/vp;
	        tk = drogak/omega;

	        if(abs(ts-tk) < czas)
	        {
	                   czas = abs(ts-tk);
	                   turn = i;
	        }	
	        
	        cout << "ee2: " << ee2 << endl;
		cout << "f2: " << f2 << endl;
		cout << "drogas: " << drogas << endl;
		cout << "katk: " << katk << endl;
		cout << "drogak: " << drogak << endl;
		cout << "ts: " << ts << endl;
		cout << "tk: " << tk << endl << endl;
	        
		/*cout << "kat k: " << katk/3.14*180 << endl;
		cout << "czas: " << abs(ts-tk) << endl << endl;	*/
	}
	}
	
	cout << "kp: " << katp*180/3.14 << endl;
	cout << "czas: " << czas << endl;
	cout << "Najlepszy kąt: " << turn << endl << endl;
	}
}
