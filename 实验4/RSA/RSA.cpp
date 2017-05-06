// RSA.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <NTL/ZZ.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>
NTL_CLIENT


void transfer(ZZ m1);
ZZ p, q, n, euler_n, e, M, c, d;
int main(){

	
	M = to_ZZ("0");
	p = GenPrime_ZZ(100);
	q = GenPrime_ZZ(100);
	n = p*q;
	euler_n = (p - 1)*(q - 1);
	e = RandomBnd(euler_n) + 1;
	while (!(GCD(e, euler_n) == 1 && e != 1 && e != euler_n)){
		e = RandomBnd(euler_n) + 1;
	}
	d = InvMod(e, euler_n);
	cout << "e " << e << endl;
	cout << "n " << n << endl;
	cout << "d " << d << endl;
	//加密
	char str[] = "I love Nanjing University of Areanautics and Astronaotics";
	int i;
	int j = 0;
	ZZ cypher[100];
	cout << "********* decimalism cypher text *************" << endl;
	for (i = 0; str[i] != '\0'; i++){
		M = str[i];
//		cout << M << endl;
		cypher[i] = PowerMod(M, e, n);
		
		cout <<cypher[i] << endl;

	}

	cout << "************** plain text ********************" << endl;
	for (i = 0; str[i] != '\0'; i++){
		ZZ m1 = PowerMod(cypher[i], d, n);
//		cout << "decode "<<m1 << endl;
		transfer(m1);
	}

	cout << endl;

	return 0;
}

void transfer(ZZ m1){
	if (32 == m1) cout << " ";
	if (73 == m1) cout << "I";
	if (108 == m1) cout << "l";
	if (111 == m1) cout << "o";
	if (118 == m1) cout << "v";
	if (101 == m1) cout << "e";
	if (78 == m1) cout << "N";
	if (97 == m1) cout << "a";
	if (110 == m1) cout << "n";
	if (74 == m1) cout << "J";
	if (105 == m1) cout << "i";
	if (103 == m1) cout << "g";
	if (85 == m1) cout << "U";
	if (114 == m1) cout << "r";
	if (115 == m1) cout << "s";
	if (116 == m1) cout << "t";
	if (121 == m1) cout << "y";
	if (102 == m1) cout << "f";
	if (65 == m1) cout << "A";
	if (117 == m1) cout << "u";
	if (99 == m1) cout << "c";

}
