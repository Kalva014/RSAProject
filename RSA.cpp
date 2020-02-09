#include <iostream>
#include<string>
#include<sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <cmath>

using namespace std;

vector<char> readFile(string m);
void storeMessage(string s);
vector<char> getChar(string message);
vector<int> encript(vector<char> c, int e, int n);
vector<char> decript(vector<int> c, int e, int n);
bool checkE(int e, int n);
double getPhi(int n);
int gcd(int a, int b);
bool isPrime(int n);
int modInverse(int a, int m);

//take text file store into string
vector<char> readFile(string m)
{
	vector<char> C;

	ifstream infile(m);
	if (infile.is_open())
	{

		string line;

		while (getline(infile, line))
		{
			for (int i = 0; i < line.length(); i++)
			{
					C.push_back(line[i]);
			}
		}
		
		infile.close();
	}
	return C;
}
//store message into file
void storeMessage(string s)
{

}
//take string message chop it up into characters stored into a vector
int modInverse(int a, int m)
{
	a = a % m;
	for (int x = 1; x < m; x++)
		if ((a * x) % m == 1)
			return x;
}
bool isPrime(int n)
{
	if (n <= 1)
		return false;

	for (int i = 2; i < n; i++)
		if (n % i == 0)
			return false;

	return true;
}
vector<char> getChar(string message)
{
	vector<char> temp;
	for (int i = 0; i < message.length(); i++)
	{
		temp.push_back(message[i]);
	}
	return temp;
}
//take a vector of char's turn to ascii int and encript it return int
vector<int> encript(vector<char> c, int e, int n)
{
	vector<int> temp;
	double m;
	double d = e;
	int cc;
	long long powr;
	for (int i = 0; i < c.size(); i++)
	{
		m = int(c.at(i));
		if (m == 32)
		{
			powr = pow(m, d);
			cc = powr % n;
		}
		else
		{
			m = m - 63;
			powr = pow(m, d);
			cc = powr % n;
		}
		
		temp.push_back(cc);
	}
	return temp;
}
//decript
vector<char> decript(vector<int> c, int e, int n)
{
	vector<char> temp;
	for (int i = 0; i < c.size(); i++)
	{
		/*
		double cc = c.at(i);
		double powr;
		double d_1 = e;
		double d1 = (1.0 / d_1);
		//double d2 = double(getPhi(n));
		double d = fmod(d1, getPhi(n));
		double d_2 = n;
		powr = pow(cc, d);
		int m = fmod(powr,d_2);
		char ch = static_cast<char>(m);
		temp.push_back(ch);
		*/

		double encryptNum = c.at(i);
		double d = modInverse(e, int(getPhi(n)));
		double x = pow(encryptNum, d);
		double asciiCode = fmod(x, n);
		char ch = char(asciiCode);
		temp.push_back(ch);
	}
	return temp;
}
bool checkE(int e, int n)
{
	if (gcd(e,int(getPhi(n))) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
double getPhi(int n)
{
	int p, q,t;
	vector <int> fac;
	vector <int> rPrimes2;
	t = 1;
	while (t <= n)
	{
		if (not(n % t))
		{
			fac.push_back(t);
		}
		t++;
	}
	
	for (int i = 1; i < fac.size(); i++)
	{
		if (isPrime(fac.at(i)) == true) 
		{ 
			rPrimes2.push_back(fac.at(i));
		}
	}
	for (int i = 0; i < rPrimes2.size(); i++)
	{
		for (int j = 1; j < rPrimes2.size(); j++)
		{
			if (rPrimes2.at(i)*rPrimes2.at(j) == n)
			{
				p = rPrimes2.at(i);
				q = rPrimes2.at(j);
			}
		}
	}
	double ret = ((p - 1) * (q - 1));

	return ret ;
}
int gcd(int a, int b)
{
	if (a == b)
	{
		return a;
	}
	else if (a < b)
	{
		gcd(b, a);
	}
	else
	{
		gcd(a - b, b);
	}
}

int main()
{

	int e, n, input;
	string m;
	char c;
	cout << "Encryption(e) or Decryption(d)" << endl;
	cin >> c;

	//cout << modInverse(5, 72);
	
	if (c == 'e')
	{
		cout << "Select the encryption value" << endl;
		cin >> e;

		cout << "And now your N" << endl;
		cin >> n;

		cout << "Input File Name: " << endl;
		cin.ignore();
		getline(cin, m);

		bool Echeck = checkE(e, n);
		while (Echeck == false)
		{
			cout << "encryption value inccorrect input new encryption value" << endl;
			cin >> e;
			Echeck = checkE(e, n);
		}

		vector<char> charMessage = readFile(m);
		vector<int> encriptKey = encript(charMessage, e, n);
		for (int i = 0; i < encriptKey.size(); i++)
		{
			cout << encriptKey.at(i) << endl;
		}
		ofstream myfile;
		myfile.open("incrypted.txt");
		for (int i = 0; i < encriptKey.size(); i++)
		{
			if (i == encriptKey.size() - 1)
			{
				myfile << encriptKey.at(i);
			}
			else
			{
				myfile << encriptKey.at(i) + " ";
			}

		}
		myfile.close();

	}
	else if (c == 'd')
	{
		cout << "Select the encryption value" << endl;
		cin >> e;

		cout << "And now your N" << endl;
		cin >> n;

		bool Echeck = checkE(e, n);
		while (Echeck == false)
		{
			cout << "encryption value inccorrect input new encryption value" << endl;
			cin >> e;
			Echeck = checkE(e, n);
		}

		vector<char> decriptKey;
		vector<int> num; 
		num.push_back(41);
		num.push_back(195);
		decriptKey = decript(num, e, n);
		for (int i = 0; i < decriptKey.size(); i++)
		{
			cout << decriptKey.at(i) << endl;
		}
	}
	else
	{
		cout << "wrong input" << endl;
	}
	return 0;
}

