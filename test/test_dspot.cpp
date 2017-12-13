#include "dspot.h"
#include <random>
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;
using T = std::chrono::steady_clock::time_point;
using usec = std::chrono::microseconds;
using sec = std::chrono::seconds;
const auto& tick = std::chrono::steady_clock::now;


int duration(T start, T end)
{
	return std::chrono::duration_cast<usec>(end - start).count();
}

int operator-(const T& end, const T& start)
{
	return(duration(start,end));
}

double alea()
{
	std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<double> u(0,1);
    return u(gen);
}


vector<double> uniform(double a, double b, int N)
{
	vector<double> v(N);
	std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<double> u(a,b);
    
    for (int i = 0; i < N; i++)
	{
		v[i] = u(gen);
	}

	return(v); 
}



vector<double> gaussian_with_drift(double mu, double sigma, double e, int N)
{
	vector<double> v(N);
	std::random_device rd;
    std::default_random_engine gen(rd());
    std::normal_distribution<double> d(mu,sigma);

	for (int i = 0; i < N; i++)
	{
		v[i] = d(gen) + e*i;
	}

	return(v);   
}

int main(int argc, const char * argv[])
{
	double mu = 0.0;
	double sigma = 1.0;
	int N = 25000;
	double e = 1e-4;
	vector<double> data = gaussian_with_drift(mu,sigma,e,N);
	
	int d = 30;
	DSpot DS(d);
	
	for(auto x : data)
	{
		DS.step(x);
	}
	cout << DS.stringStatus() << endl;
	return 0;
}
