#include "Qbit.hpp"


Qbit::Qbit() : _a(1.0), _b(0.0), _value(0)
{
    normalize();
}

Qbit::Qbit(std::complex<double> alpha, std::complex<double> beta) : _a(alpha), _b(beta)
{
    normalize();
} 

void Qbit::normalize(){
    const double norm = std::sqrt(std::norm(_a) + std::norm(_b));
    
    if (norm > 0.0)
    {
        _a /= norm;
        _b /= norm;
        _prob[0] = std::norm(_a);  // |α|²
        _prob[1] = std::norm(_b);  // |β|²
    } 
    else
    {
        _a = 1.0;
        _b = 0.0;
        _prob[0] = 1.0;
        _prob[1] = 0.0;
        _value = 0;
    }
}

void Qbit::setState(std::complex<double> a, std::complex<double> b) {
    _a = a;
    _b = b;
    normalize();
}

void Qbit::NOT()
{
    std::swap(_a, _b);
    normalize();
}

void Qbit::H()
{
    const double inv_sqrt2 = 1.0 / std::sqrt(2.0);
    setState((_a + _b) * inv_sqrt2, (_a - _b) * inv_sqrt2);
}

void Qbit::measure() 
{
    normalize();
    thread_local static std::mt19937 gen(std::random_device{}());
    std::bernoulli_distribution d(_prob[0]); 
    bool result = !d(gen);

    if (result)
    {
        _a = 0.0;
        _b = 1.0;
    }
    else
    {
        _a = 1.0;
        _b = 0.0;
    }
    _value = result;
    normalize();
}

double Qbit::getProba(bool value) const
{
    return (_prob[value]);
}

