#include "QCS.hpp"
#include <random>
#include "Qbit.hpp"
#include <bitset>
#include <iomanip>


std::vector<std::string> generateBitstrings(int n) {
    std::vector<std::string> bitstrings;
    for (int i = 0; i < (1 << n); ++i) {
        bitstrings.push_back(std::bitset<32>(i).to_string().substr(32 - n));
    }
    return bitstrings;
}

void QCS::printState() const {
    std::cout << "Quantum State (" << _n << " qubits):\n";
    std::cout << "-----------------------------\n";
    std::vector<std::string> bitstring = generateBitstrings(_n);
    
    for (size_t i = 0; i < _amplitudes.size(); ++i) 
    {
        // if (std::abs(_amplitudes[i]) < 1e-10)
        //     continue;
        std::cout << "|" << bitstring[i] << "⟩: " 
                    << std::setw(8) << std::fixed << std::setprecision(4)
                    << _amplitudes[i].real();
        
        if (std::abs(_amplitudes[i].imag()) > 1e-10) {
            std::cout << " + " << _amplitudes[i].imag() << "i";
        }
        std::cout << "  [P=" << std::norm(_amplitudes[i]) << "]";
        std::cout << "\n";
    }
}


std::complex<double> QCS::getSystemAmp(std::string bs)
{
    std::complex<double> result = 1;

    for (unsigned int i = 0; i < _n; i++)
    {
        _array[i].normalize();
        if (bs[i] == '1')
            result *= _array[i].beta();
        else
            result *= _array[i].alpha();
    }
    return (result);
}

const std::vector<Qbit>& QCS::getArray() const
{
    return _array;
}

void QCS::NOT(unsigned int t)
{
    _array[t].NOT();
    t = _n - 1 - t;
    for (size_t i = 0; i < _amplitudes.size(); ++i)
    {
        if (i & (1 << t))
        { 
            size_t j = i ^ (1 << t);
            std::swap(_amplitudes[i], _amplitudes[j]);
        }
    }
}

void QCS::CNOT(unsigned int c, unsigned int t)
{
    int physical_control = _n - 1 - c;  
    int physical_target = _n - 1 - t;   
    
    for (size_t i = 0; i < _amplitudes.size(); ++i) {
        if (i & (1 << physical_control)) {
            size_t j = i ^ (1 << physical_target);
            if (j > i)
            {
                _array[t].NOT();
                std::swap(_amplitudes[i], _amplitudes[j]);
            }
        }
    }
}

void QCS::CCNOT(unsigned int c1, unsigned int c2, unsigned int t)
{
    int physical_control1 = _n - 1 - c1;
    int physical_control2 = _n - 1 - c2;
    int physical_target = _n - 1 - t;   
    
    for (size_t i = 0; i < _amplitudes.size(); ++i) {
        if ((i & (1 << physical_control1)) && (i & (1 << physical_control2)))
        {
            size_t j = i ^ (1 << physical_target);
            if (j > i)
            {
                _array[t].NOT();
                std::swap(_amplitudes[i], _amplitudes[j]);
            }
        }
    }
}

void QCS::H(unsigned int t)
{
    const double inv_sqrt2 = 1.0 / std::sqrt(2.0);
    std::vector<std::complex<double>> new_state = _amplitudes;
    
    t = _n - 1 - t;
    for (size_t i = 0; i < _amplitudes.size(); ++i)
    {
        if (i & (1 << t))
            continue;
        size_t j = i ^ (1 << t);
        new_state[i] = (_amplitudes[i] + _amplitudes[j]) * inv_sqrt2;
        new_state[j] = (_amplitudes[i] - _amplitudes[j]) * inv_sqrt2;
    }
    _amplitudes = new_state;
    _array[t].H();
}

void QCS::H_all()
{
    for(size_t i = 0; i < _n; i++)
    {
        H(i);
    }
}


void QCS::SWAP(unsigned int i, unsigned int j)
{
    std::swap(_array[i], _array[j]);
}

void QCS::LCS(unsigned int i, unsigned int j, unsigned int k)
{
    SWAP(i, j);
    SWAP(j, k);
}

void QCS::RLCS(unsigned int i, unsigned int j, unsigned int k)
{
    SWAP(k, j);
    SWAP(j, i);
}


std::ostream& operator<<(std::ostream& os, QCS& qcs) {
    std::vector<Qbit> arr = qcs.getArray();

    os << "Quantum System measurement:\n";
    os << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i].measure();
        os << arr[i].getValue();
        if (i != arr.size() - 1) {
            os << ", ";
        }
    }
    os << "]\n";
    return os;
}

