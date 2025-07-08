#ifndef QCS_HPP
#define QCS_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "Qbit.hpp"


class QCS 
{
private:
    unsigned int _n;
    std::vector<Qbit> _array;
    std::vector<std::complex<double>> _amplitudes;

public:
    QCS() = default;
    QCS(unsigned int n) : _n(n), _array(n, Qbit()), _amplitudes(1 << n) {_amplitudes[0] = 1.0;}
    QCS(const QCS& other) = default;
    QCS& operator=(const QCS& other) = default;
    ~QCS() = default;
    
    const std::vector<Qbit>& getArray() const;
    std::complex<double> getSystemAmp(std::string bitstring);
    std::vector<std::complex<double>> getAmplitudes() {return _amplitudes;}
    void NOT(unsigned int i);
    void CNOT(unsigned int i, unsigned int j);
    void CCNOT(unsigned int i, unsigned int j, unsigned int k);
    void H(unsigned int i);
    void H_all();
    void SWAP(unsigned int i, unsigned int j);
    void LCS(unsigned int i, unsigned int j, unsigned int k);
    void RLCS(unsigned int i, unsigned int j, unsigned int k);
    void printState() const;
};

std::vector<std::string> generateBitstrings(int n);
std::ostream& operator<<(std::ostream& os, QCS& qcs);


#endif