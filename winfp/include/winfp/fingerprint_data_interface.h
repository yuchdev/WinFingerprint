#pragma once

class IFingerprintData
{
public:

    /// @brief Polymorph
    virtual ~IFingerprintData() = default;

    /// @brief Generate content
    virtual void generate() = 0;
}