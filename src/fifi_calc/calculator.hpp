// Copyright (c) 2016 Steinwurf ApS
// All Rights Reserved
//
// THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF STEINWURF
// The copyright notice above does not evidence any
// actual or intended publication of such source code.

#pragma once

#include <cstdint>
#include <memory>

namespace fifi_calc
{
/// This class wraps the vitus::browser so it can be used in a standalone
/// fashion without recursing into any dependencies. This is necessary
/// for integration into an iOS application.
class calculator
{
public:

    calculator();
    ~calculator();

    uint32_t add(uint32_t a, uint32_t b) const;
    uint32_t subtract(uint32_t a, uint32_t b) const;
    uint32_t multiply(uint32_t a, uint32_t b) const;
    uint32_t divide(uint32_t a, uint32_t b) const;
    uint32_t invert(uint32_t a) const;
    uint32_t max_value() const;

    std::string field() const;
    void set_field(const std::string& field);

private:

    // The implementation details should be hidden, so this header can
    // be included without recursing into any dependencies.
    class impl;
    std::unique_ptr<impl> m_impl;
};
}
