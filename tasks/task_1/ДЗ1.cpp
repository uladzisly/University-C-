#include <iostream>
#include <cmath>
#include <windows.h>
using namespace std;

int main()
{
	float x, y, R, S, c, C;
	string f;
	cin >> x;
	cin >> y;
	c = cos(y * y / x);
	R = 1 / c;
	S = cbrt(x + log(1 / x));
	cout <<"R == " << R <<", S == "<< S << "\n";
	C = max(R, S);
	cout <<"C == "<< C << "\n";
	system("pause");
	return 0;
}


