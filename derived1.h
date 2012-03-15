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
 * This is the public interface for derived1 class, which inherits from base1
 * and base2.
 */
#ifndef __DERIVED1_H__
#define __DERIVED1_H__

#include "common.h"
#include "base1.h"
#include "base2.h"

/** Opaque pointer to reference instances of this class */
typedef struct derived1_st_ *derived1_handle;

/* APIs below are documented in their implementation file */

extern my_rc_e
derived1_increase_val4(derived1_handle derived1_h);

extern base1_handle
derived1_cast_to_base1(derived1_handle derived1_h);

extern base2_handle
derived1_cast_to_base2(derived1_handle derived1_h);

extern derived1_handle
derived1_new1(void);

#endif
