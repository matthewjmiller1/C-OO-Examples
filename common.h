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
 * This is an interface for some common declarations.
 */
#ifndef __COMMON_HEADER_H__
#define __COMMON_HEADER_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

/**
 * Compile time assert macro from:
 * http://www.pixelbeat.org/programming/gcc/static_assert.html 
 */
#define CT_ASSERT(e) extern char (*CT_ASSERT(void)) [sizeof(char[1 - 2*!(e)])]

/**
 * Determine the number of elements in an array.
 */
#define NELEMS(x) (sizeof(x) / sizeof(x[0]))

/**
 * Display an error message.
 */
#define LOG_ERR(fmt, ...) \
do { \
    printf("(%s:%u) ERROR: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
} while (0)

/**
 * Validate that a function in an object's virtual table exists.  If not, set
 * the return code.  Callers should set the return code to MY_RC_E_SUCCESS prior
 * to calling the macro and check it after the macro is executed to make sure it
 * is not an error return code.
 */
#define VALIDATE_VTABLE_FN(obj_h, private_h, vtable, fn, rc) \
do { \
    if (NULL == obj_h) { \
        LOG_ERR("Invalid input, " #obj_h "(%p)", obj_h); \
        rc = MY_RC_E_EINVAL;  \
        break; \
    } \
\
    if (NULL == obj_h->private_h) { \
        LOG_ERR("Invalid input, " #obj_h "(%p) " #private_h "(%p)", obj_h, \
                obj_h->private_h); \
        rc = MY_RC_E_EINVAL;  \
        break; \
    } \
\
    if (NULL == obj_h->private_h->vtable) { \
        LOG_ERR("Invalid input, " #obj_h "(%p) " #private_h "(%p) " #vtable \
                "(%p)", obj_h, obj_h->private_h, obj_h->private_h->vtable); \
        rc = MY_RC_E_EINVAL;  \
        break; \
    } \
\
    if (NULL == obj_h->private_h->vtable->fn) { \
        LOG_ERR("Invalid input, " #obj_h "(%p) " #private_h "(%p) " #vtable \
                "(%p) " #fn "(%p)",  obj_h, obj_h->private_h, \
                obj_h->private_h->vtable, obj_h->private_h->vtable->fn); \
        rc = MY_RC_E_EINVAL;  \
        break; \
    } \
} while (0)

/**
 * If the function in the child's table is NULL, then inherit the function from
 * the parent table.  In do_null_check is true, then it is considered an error
 * condition if the function is NULL after inheritance (e.g., when the base
 * class is setting the vtable, all functions should be non-NULL).  If the error
 * condition is reached, we set the rc and goto an err_exit label.
 */
#define INHERIT_VTABLE_FN(parent_vtable, child_vtable, fn, do_null_check, rc) \
do { \
    if (NULL == child_vtable->fn) { \
        child_vtable->fn = parent_vtable->fn; \
        if (do_null_check && (NULL == child_vtable->fn)) { \
            LOG_ERR("Invalid input, " #fn "(%p)", child_vtable->fn); \
            rc = MY_RC_E_EINVAL; \
            goto err_exit; \
        } \
    } \
} while (0)

/**
 * Return codes used to indicate whether a function call was successful.
 */
typedef enum my_rc_e_ {
    /** Invalid return code, should never be used */
    MY_RC_E_INVALID,
    /** Successful return */
    MY_RC_E_SUCCESS,
    /** Function received an invalid input */
    MY_RC_E_EINVAL,
    /** Function failed to allocate memory */
    MY_RC_E_ENOMEM,
    /** Max return code for bounds testing */
    MY_RC_E_MAX,
} my_rc_e;

/* APIs below are documented in their implementation file */

extern bool
my_rc_e_is_notok(my_rc_e rc);

extern bool
my_rc_e_is_ok(my_rc_e rc);

extern bool
my_rc_e_is_valid(my_rc_e rc);

extern const char *
my_rc_e_get_string(my_rc_e rc);

#endif
