#include <winfp/fingerprint_data_base.h>

using namespace antios;

int FingerprintDataBase::random_from_range(int lower_b, int upper_b)
{
    std::uniform_int_distribution<int> distribution(lower_b, upper_b);
    return distribution(_generator);
}

std::string FingerprintDataBase::random_string(size_t length, const std::string& alphabet)
{
    auto randchar = [this, alphabet]() -> char
    {
        return this->choise(alphabet);
    };

    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}