#pragma once
#include <winfp/fingerprint_data_interface.h>

namespace antios {

class FingerprintDataBase : public IFingerprintData
{
public:

    /// @brief Polymorph
    virtual ~FingerprintDataBase() = default;

    /// @brief Generate content
    virtual void generate() = 0;
private:

    /// Random generator
}

} // namespace antios 
