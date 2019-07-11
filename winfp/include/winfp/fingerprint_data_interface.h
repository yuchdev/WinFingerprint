#pragma once

namespace antios {

class IFingerprintData
{
public:

    /// @brief Polymorph
    virtual ~IFingerprintData() = default;

    /// @brief Generate content
    virtual void generate() = 0;
};

} // namespace antios 
