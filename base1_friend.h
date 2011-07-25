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
 * This is the friend interface for base1 class.  It should only be included by
 * sub-classes of base1.
 */
#ifndef __BASE1_FRIEND_H__
#define __BASE1_FRIEND_H__

#include "base1.h"

/** Opaque pointer to reference private data for the class */
typedef struct base1_private_st_ *base1_private_handle;

/** Friend accessible data for this class */
typedef struct base1_st_ {
    /** Reference to private data */
    base1_private_handle private_h;
    /** Public data */
    base1_public_data_st public_data;
    /** Some value */
    uint32_t val3;
} base1_st;

/**
 * Virtual function declaration.
 */
typedef void
(*base1_delete_fn)(base1_handle base1_h);

/**
 * Virtual function declaration.
 */
typedef const char *
(*base1_type_string_fn)(base1_handle base1_h);

/**
 * Virtual function declaration.
 */
typedef my_rc_e
(*base1_string_fn)(base1_handle base1_h, char *buffer, size_t buffer_size);

/**
 * Virtual function declaration.
 */
typedef my_rc_e
(*base1_string_size_fn)(base1_handle base1_h, size_t *buffer_size);

/**
 * Virtual function declaration.
 */
typedef my_rc_e
(*base1_increase_val3_fn)(base1_handle base1_h);

/**
 * The virtual table to be specified by friend classes.
 *
 * @see base1_set_vtable()
 */
typedef struct base1_vtable_st_ {
    /** Function to delete object */
    base1_delete_fn delete_fn;
    /** Function to give string for object type */
    base1_type_string_fn type_string_fn;
    /** Function to give string for object state */
    base1_string_fn string_fn;
    /** Function to give size to use for object state string */
    base1_string_size_fn string_size_fn;
    /** Function to increase val3 */
    base1_increase_val3_fn increase_val3_fn;
} base1_vtable_st;

/* APIs below are documented in their implementation file */

extern my_rc_e
base1_inherit_vtable(const base1_vtable_st *parent_vtable,
                     base1_vtable_st *child_vtable,
                     bool do_null_check);

extern my_rc_e
base1_set_vtable(base1_handle base1_h, base1_vtable_st *vtable);

extern void
base1_friend_delete(base1_handle base1_h);

extern my_rc_e
base1_init(base1_handle base1_h);

#endif
