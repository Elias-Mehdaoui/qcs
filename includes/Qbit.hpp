#ifndef QBIT_HPP
#define QBIT_HPP

#include <complex>
#include <vector>
#include <random>
#include <cmath>
#include <iostream>

class Qbit 
{
    private :
        std::complex<double> _a;
        std::complex<double> _b;
        double _prob[2];
        bool _value;
        

    public :
        Qbit();
        Qbit(std::complex<double> alpha, std::complex<double> beta); 
        Qbit(const Qbit& other) = default;
        Qbit& operator=(const Qbit& other) = default;
        ~Qbit() = default;

        const std::complex<double>& alpha() const { return _a; }
        const std::complex<double>& beta() const { return _b; }
        bool getValue() { return _value;}
        void setValue(bool value) { _value = value; }
        double getProba(bool value) const;
        std::complex<double> getStateFactor();
        void setState();
        void setState(std::complex<double> a, std::complex<double> b);
        void measure();
        void normalize();

        void NOT();
        void H();
};

#endif