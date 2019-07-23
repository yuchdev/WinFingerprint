#pragma once
#include <winfp/fingerprint_data_interface.h>

#include <cassert>
#include <vector>
#include <algorithm>
#include <random>

namespace antios {

    class FingerprintDataBase : public IFingerprintData
    {
    public:

        /// @brief Polymorph
        virtual ~FingerprintDataBase() = default;

        /// @brief Generate content
        virtual void generate() = 0;

    protected:

        /// @brief Generate random int from the range [lower, upper]
        int random_from_range(int lower_b, int upper_b);

        /// @brief 
        std::string random_string(size_t length, const std::string& alphabet);

        template <typename Container>
        typename Container::value_type choise(const Container& container)
        {
            std::vector<Container::value_type> out;
#if 0
            std::sample(std::begin(container), std::end(container), std::back_inserter(out), 1, std::mt19937{ std::random_device{}() });
#else
            std::sample(std::begin(container), std::end(container), std::back_inserter(out), 1, _generator);
#endif

            assert(!out.empty());
            return out[0];
        }


    private:

        /// Random generator
        std::default_random_engine _generator;
    };

} // namespace antios
