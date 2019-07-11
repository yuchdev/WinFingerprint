#include <winfp/fingerprint_data_base.h>

using namespace antios;

int FingerprintDataBase::rnd(int lower_b, int upper_b)
{
    std::uniform_int_distribution<int> distribution(lower_b, upper_b);
    return distribution(_generator);
}
