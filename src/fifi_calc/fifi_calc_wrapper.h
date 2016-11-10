//
//  fifi_calc_wrapper.h
//  FiFiCalc
//
//  Created by Jeppe Krigslund on 08/11/2016.
//  Copyright © 2016 Steinwurf ApS. All rights reserved.
//

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct fifi_calculator* fifi_calc_t;

fifi_calc_t new_calc();
void delete_calc(fifi_calc_t calc);

uint32_t add(fifi_calc_t calc, uint32_t a, uint32_t b);
uint32_t subtract(fifi_calc_t calc, uint32_t a, uint32_t b);
uint32_t multiply(fifi_calc_t calc, uint32_t a, uint32_t b);
uint32_t divide(fifi_calc_t calc, uint32_t a, uint32_t b);
uint32_t invert(fifi_calc_t calc, uint32_t a);
uint32_t max_value(fifi_calc_t calc);
void set_field(fifi_calc_t calc, const char* field);
const char* field(fifi_calc_t calc);

#ifdef __cplusplus
}
#endif
