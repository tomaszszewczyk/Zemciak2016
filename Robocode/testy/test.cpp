#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

int main()
{
	//Test obliczania równania okręg
	double xa, xb, ya, yb, alpha, beta;

	cin >> xa >> xb >> ya >> yb >> alpha >> beta;

	alpha = tan(alpha);
	beta = tan(beta);

	double b1 = ya - (alpha*xa);
	double b2 = yb - (beta*xb);

	cout << "b1, b2: " << b1 << endl << b2 << endl;

	double b3 = ya + (xa/alpha);
	double b4 = yb + (xb/beta);

	cout << "b3, b4: " << b3 << endl << b4 << endl;

	double sx= (yb*alpha*beta + xb*alpha - ya*alpha*beta - xa*beta) / (alpha - beta);
	double sy= (-1/alpha)*sx + b3;

	cout << "sx, sy: " << sx << endl << sy << endl;

	double r = (xa-sx)*(xa-sx) + (ya-sy)*(ya-sy);
	cout << "r: " << r << endl;
	return 0;
}
