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
 * This is the friend interface for derived1 class.  It should only be included
 * by sub-classes of derived1.
 */
#ifndef __DERIVED1_FRIEND_H__
#define __DERIVED1_FRIEND_H__

#include "derived1.h"
#include "base1_friend.h"
#include "base2_friend.h"

/** Opaque pointer to reference private data for the class */
typedef struct derived1_private_st_ *derived1_private_handle;

/** Friend accessible data for this class */
typedef struct derived1_st_ {
    /** Reference to private data */
    derived1_private_handle private_h;
    /** Inherited base1 state */
    base1_st base1;
    /** Inherited base2 state */
    base2_st base2;
    /** Some value */
    uint32_t val4;
} derived1_st;

/**
 * Virtual function declaration.
 */
typedef void
(*derived1_delete_fn)(derived1_handle derived1_h);

/**
 * Virtual function declaration.
 */
typedef my_rc_e
(*derived1_increase_val4_fn)(derived1_handle derived1_h);

/**
 * The virtual table to be specified by friend classes.
 *
 * @see derived1_set_vtable()
 */
typedef struct derived1_vtable_st_ {
    /** Pointer to the base1 functions to use */
    base1_vtable_st *base1_vtable;
    /** Pointer to the base2 functions to use */
    base2_vtable_st *base2_vtable;
    /** Function to delete object */
    derived1_delete_fn delete_fn;
    /** Function to increase val4 */
    derived1_increase_val4_fn increase_val4_fn;
} derived1_vtable_st;

/* APIs below are documented in their implementation file */

extern my_rc_e
derived1_inherit_vtable(const derived1_vtable_st *parent_vtable,
                        derived1_vtable_st *child_vtable,
                        bool do_null_check);

extern my_rc_e
derived1_set_vtable(derived1_handle derived1_h, derived1_vtable_st *vtable);

extern void
derived1_friend_delete(derived1_handle derived1_h);

extern my_rc_e
derived1_init(derived1_handle derived1_h);

#endif
