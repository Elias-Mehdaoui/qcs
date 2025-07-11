#include "QCS.hpp"

void enigma(QCS& qcs)
{
    (void)qcs;
    // qcs.NOT(1);

    // qcs.NOT(0);
    // qcs.CNOT(0, 1);
    // qcs.NOT(0);
}

int getMinus(QCS& qcs)
{
    std::vector<std::complex<double>> state = qcs.getAmplitudes();
    for (size_t i = 0; i < state.size(); i++)
    {
        if (state[i].real() < 0)
            return (i);
    }
    return (-1);
}

int main(int argc, char**argv)
{
    if (argc == 2)
    {
        std::vector<std::string> bs = generateBitstrings(atoi(argv[1]));
        QCS qcs = QCS(atoi(argv[1]));
        qcs.H(0);
        qcs.CNOT(0, 1);
        qcs.H(0);
        

        qcs.printState();
        std::cout << qcs << std::endl;
        // if (getMinus(qcs) == -1)
        //     std::cout << "non binary !" << std::endl;
        // else
        //     std::cout << "binary !" << std::endl;
        
        return 0;
    }
    std::cout << "Usage : ./QCS <number of bits>" << std::endl;
}