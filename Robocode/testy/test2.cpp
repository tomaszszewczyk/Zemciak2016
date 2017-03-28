#include <iostream>
#include <cmath>

using namespace std;

int main()

{
	//Zbieranie danych

	double xa,xb,ya,yb,alpha,beta; //Dane
	
	cout<<"Xa: ";
	cin>>xa;
	
	cout<<"Ya: ";
	cin>>ya;
	
	cout<<"alpha: ";
	cin>>alpha;
	
	cout<<"Xb: ";
	cin>>xb;
	
	cout<<"Yb: ";
	cin>>yb;
	
	cout<<"beta: ";
	cin>>beta;

	while(alpha == beta || alpha == beta+180 || alpha+180 == beta)
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

	double r = (xa-sx)*(xa-sx) + (ya-sy)*(ya-sy);

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
	double turn = 99999, czas = 999999;

	for(double i = 0.01; i < 180; i += 0.1)
	{
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

			double e1,e2;  // miejscazerowe xDDD
			 

			e1 = ((((2*alpha2*sy) + (2*sx))) - (pierwdelta2)) / (2*((alpha2*alpha2) + 1));
			e2 = ((((2*alpha2*sy) + (2*sx))) + (pierwdelta2)) / (2*((alpha2*alpha2) + 1));

			double f1,f2; //to sa ygreki

			//wyliczamy ygerki
			f1 = alpha2*e1;
			f2 = alpha2*e2;

			//dzieki temu wypluwamy punkty przeciecia
			//cout <<"Punkt 1 to: P1=("<<e1<<" , "<<f1<<" )"<<endl;
			//cout <<"Punkt 2 to: P2=("<<e2<<" , "<<f2<<" )"<<endl;

			double drogas, drogak;

			drogas = sqrt(e1*e1 + f1*f1);
			drogak = asin((e1-sx)/sqrt(r));

			if(drogak < 0) drogak = 3.14 + drogak;

			double ts, tk;

			ts = drogas/vp;
			tk = drogak/omega;

			if(abs(ts-tk) < czas)
			{
				czas = abs(ts-tk);
				turn = i;
			}


                        drogas = sqrt(e2*e2 + f2*f2);
                        drogak = asin((e2-sx)/sqrt(r));

                        if(drogak < 0) drogak = 3.14 + drogak;


                        ts = drogas/vp;
                        tk = drogak/omega;

                        if(abs(ts-tk) < czas)
                        {
                              czas = abs(ts-tk);
                              turn = i;
		  	}
			
		}
	}

	cout << "Najlepszy kąt: " << turn;
}
