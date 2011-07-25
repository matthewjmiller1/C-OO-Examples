/**
 * @file
 * @author Matt Miller <matt@matthewjmiller.net>
 *
 * @section LICENSE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
 * This is the public interface for derived2 class, which inherits from
 * derived2.
 */
#ifndef __DERIVED2_H__
#define __DERIVED2_H__

#include "common.h"
#include "derived1.h"

/** Opaque pointer to reference instances of this class */
typedef struct derived2_st_ *derived2_handle;

/* APIs below are documented in their implementation file */

extern derived1_handle
derived2_cast_to_derived1(derived2_handle derived2_h);

extern derived2_handle
derived2_new1(void);

#endif
