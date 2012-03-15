/**
 * @file
 * @author Matt Miller <matt@matthewjmiller.net>
 *
 * @section LICENSE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 * This is the public interface for base1 class.
 */
#ifndef __BASE1_H__
#define __BASE1_H__

#include "common.h"

/** Opaque pointer to reference instances of this class */
typedef struct base1_st_ *base1_handle;

/** Public data for the class */
typedef struct base1_public_data_st_ {
    /** Some value */
    uint8_t val1;
    /** Some other value */
    uint32_t val2;
} base1_public_data_st;

/* APIs below are documented in their implementation file */

extern const char *
base1_get_val1_description(void);

extern my_rc_e
base1_get_public_data(base1_handle base1_h, base1_public_data_st *public_data);

extern my_rc_e
base1_set_public_data(base1_handle base1_h, base1_public_data_st *public_data);

extern my_rc_e
base1_increase_val3(base1_handle base1_h);

extern base1_handle
base1_new1(void);

extern base1_handle
base1_new2(base1_public_data_st *public_data);

extern base1_handle
base1_new3(uint8_t val1, uint32_t val3);

extern void
base1_delete(base1_handle base1_h);

extern const char *
base1_type_string(base1_handle base1_h);

extern my_rc_e
base1_string(base1_handle base1_h, char *buffer, size_t buffer_size);

extern my_rc_e
base1_string_size(base1_handle base1_h, size_t *buffer_size);

#endif
