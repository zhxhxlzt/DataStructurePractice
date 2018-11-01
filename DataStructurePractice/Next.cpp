#include<string.h>
#include<iostream>

using namespace std;

int * buildNext( const char * P )
{
	size_t m = strlen( P ), j = 0;
	int * N = new int[m];
	int t = N[0] = -1;

	while( j < m - 1 )
	{
		if( 0 > t || P[j] == P[t] )
			N[++j] = ++t;
		else
			t = N[t];
	}

	return N;
}

int main()
{
	const char * P = "abcnabdi";
	int *N = buildNext( P );
	
	for( int i = 0; i < strlen( P ); i++ )
	{
		cout << N[i] << endl;
	}
	getchar();
	return 0;
}