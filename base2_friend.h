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
 * This is the friend interface for base2 class.  It should only be included by
 * sub-classes of base2.
 */
#ifndef __BASE2_FRIEND_H__
#define __BASE2_FRIEND_H__

#include "base2.h"

/** Opaque pointer to reference private data for the class */
typedef struct base2_private_st_ *base2_private_handle;

/** Friend accessible data for this class */
typedef struct base2_st_ {
    /** Reference to private data */
    base2_private_handle private_h;
    /** Some value */
    uint32_t val1;
} base2_st;

/**
 * Virtual function declaration.
 */
typedef void
(*base2_delete_fn)(base2_handle base2_h);

/**
 * Virtual function declaration.
 */
typedef my_rc_e
(*base2_increase_val1_fn)(base2_handle base2_h);

/**
 * Virtual function declaration.
 */
typedef const char *
(*base2_type_string_fn)(base2_handle base2_h);

/**
 * Virtual function declaration.
 */
typedef my_rc_e
(*base2_string_fn)(base2_handle base2_h, char *buffer, size_t buffer_size);

/**
 * Virtual function declaration.
 */
typedef my_rc_e
(*base2_string_size_fn)(base2_handle base2_h, size_t *buffer_size);

/**
 * The virtual table to be specified by friend classes.
 *
 * @see base2_set_vtable()
 */
typedef struct base2_vtable_st_ {
    /** Function to delete object */
    base2_delete_fn delete_fn;
    /** Function to give string for object type */
    base2_type_string_fn type_string_fn;
    /** Function to give string for object state */
    base2_string_fn string_fn;
    /** Function to give size to use for object state string */
    base2_string_size_fn string_size_fn;
    /** Function to increase val1 */
    base2_increase_val1_fn increase_val1_fn;
} base2_vtable_st;

/* APIs below are documented in their implementation file */

extern my_rc_e
base2_inherit_vtable(const base2_vtable_st *parent_vtable,
                     base2_vtable_st *child_vtable,
                     bool do_null_check);

extern my_rc_e
base2_set_vtable(base2_handle base2_h, base2_vtable_st *vtable);

extern void
base2_friend_delete(base2_handle base2_h);

extern my_rc_e
base2_init(base2_handle base2_h);

#endif
