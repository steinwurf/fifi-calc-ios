//
//  fifi_calc_wrapper.c
//  FiFiCalc
//
//  Created by Jeppe Krigslund on 08/11/2016.
//  Copyright © 2016 Steinwurf ApS. All rights reserved.
//

#include "fifi_calc_wrapper.h"
#include "calculator.hpp"
#include <string>

fifi_calc_t new_calc()
{
    return (fifi_calc_t) new fifi_calc::calculator();
}

void delete_calc(fifi_calc_t calc)
{
    delete (fifi_calc::calculator*) calc;
}

uint32_t add(fifi_calc_t calc, uint32_t a, uint32_t b)
{
    return ((fifi_calc::calculator*) calc)->add(a, b);
}

uint32_t subtract(fifi_calc_t calc, uint32_t a, uint32_t b)
{
    return ((fifi_calc::calculator*) calc)->subtract(a, b);
}

uint32_t multiply(fifi_calc_t calc, uint32_t a, uint32_t b)
{
    return ((fifi_calc::calculator*) calc)->multiply(a, b);
    
}

uint32_t divide(fifi_calc_t calc, uint32_t a, uint32_t b)
{
    return ((fifi_calc::calculator*) calc)->divide(a, b);
    
}

uint32_t invert(fifi_calc_t calc, uint32_t a)
{
    return ((fifi_calc::calculator*) calc)->invert(a);
    
}

uint32_t max_value(fifi_calc_t calc)
{
    return ((fifi_calc::calculator*) calc)->max_value();
}

void set_field(fifi_calc_t calc, const char* field)
{
    ((fifi_calc::calculator*) calc)->set_field(std::string(field));
}

const char* field(fifi_calc_t calc)
{
    return ((fifi_calc::calculator*) calc)->field().c_str();
}
