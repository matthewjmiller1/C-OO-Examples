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
 * This is the public interface for base2 class.
 */
#ifndef __BASE2_H__
#define __BASE2_H__

#include "common.h"

/** Opaque pointer to reference instances of this class */
typedef struct base2_st_ *base2_handle;

/* APIs below are documented in their implementation file */

extern my_rc_e
base2_increase_val1(base2_handle base2_h);

extern my_rc_e
base2_get_val1(base2_handle base2_h, uint32_t *val1);

extern void
base2_delete(base2_handle base2_h);

extern const char *
base2_type_string(base2_handle base2_h);

extern my_rc_e
base2_string(base2_handle base2_h, char *buffer, size_t buffer_size);

extern my_rc_e
base2_string_size(base2_handle base2_h, size_t *buffer_size);

#endif
