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
 * This is the implements a class that inherits from derived1.
 */
#include "derived2.h"
#include "derived1_friend.h"

/** Size for this object to use for base1_string_size_fn */
#define DERIVED2_STR_SIZE 256

/** Private data for this class */
typedef struct derived2_st_ {
    /** Inherited derived1 state */
    derived1_st derived1;
} derived2_st;

/**
 * Cast the derived1 object to derived2.
 *
 * @param derived1_h The derived1 object
 * @return The derived2 object
 */
static derived2_handle
derived1_cast_to_derived2 (derived1_handle derived1_h)
{
    derived2_handle derived2_h = NULL;

    if (NULL != derived1_h) {
        derived2_h = (derived2_handle) ((uint8_t *) derived1_h -
                                        offsetof(derived2_st, derived1));
    }

    return (derived2_h);
}

/**
 * Cast the base1 object to derived2.
 *
 * @param base1_h The base1 object
 * @return The derived2 object
 */
static derived2_handle
base1_cast_to_derived2 (base1_handle base1_h)
{
    derived2_handle derived2_h = NULL;

    if (NULL != base1_h) {
        derived2_h = (derived2_handle) ((uint8_t *) base1_h -
                                        offsetof(derived2_st, derived1) -
                                        offsetof(derived1_st, base1));
    }

    return (derived2_h);
}

/**
 * Cast the base2 object to derived2.
 *
 * @param base2_h The base2 object
 * @return The derived2 object
 */
static derived2_handle
base2_cast_to_derived2 (base2_handle base2_h)
{
    derived2_handle derived2_h = NULL;

    if (NULL != base2_h) {
        derived2_h = (derived2_handle) ((uint8_t *) base2_h -
                                        offsetof(derived2_st, derived1) -
                                        offsetof(derived1_st, base2));
    }

    return (derived2_h);
}

/**
 * The internal function for increasing value4 for objects of type derived1.
 * Will add twenty to the current value.
 *
 * @param derived1_h The object
 * @return Return code
 */
static my_rc_e
derived2_derived1_increase_val4 (derived1_handle derived1_h)
{
    if (NULL == derived1_h) {
        LOG_ERR("Invalid input, derived1_h(%p)", derived1_h);
        return (MY_RC_E_EINVAL);
    }

    derived1_h->val4 += 20;

    return (MY_RC_E_SUCCESS);
}

/**
 * The internal function for getting the type string for objects of type
 * derived2.
 *
 * @param derived2_h The object
 * @return The string indicating the object type.
 */
static const char *
derived2_type_string_internal (derived2_handle derived2_h)
{
    return ("derived2");
}

/**
 * Wrapper for to call common function.
 *
 * @param base1_h The object
 * @return Return code
 */
static const char *
derived2_base1_type_string (base1_handle base1_h)
{
    return (derived2_type_string_internal(base1_cast_to_derived2(base1_h)));
}

/**
 * Wrapper for to call common function.
 *
 * @param base2_h The object
 * @return Return code
 */
static const char *
derived2_base2_type_string (base2_handle base2_h)
{
    return (derived2_type_string_internal(base2_cast_to_derived2(base2_h)));
}

/**
 * The internal function to delete a derived2 object.  Upon return, the object
 * is not longer valid.
 *
 * @param derived2_h The object.  If NULL, then this function is a no-op.
 */
static void
derived2_delete (derived2_handle derived2_h)
{
    if (NULL == derived2_h) {
        return;
    }

    derived1_friend_delete(&(derived2_h->derived1));

    free(derived2_h);
}

/**
 * Wrapper for to call common function.
 *
 * @param base1_h The object
 * @return Return code
 */
static void
derived2_base1_delete (base1_handle base1_h)
{
    return (derived2_delete(base1_cast_to_derived2(base1_h)));
}

/**
 * Wrapper for to call common function.
 *
 * @param base2_h The object
 * @return Return code
 */
static void
derived2_base2_delete (base2_handle base2_h)
{
    return (derived2_delete(base2_cast_to_derived2(base2_h)));
}

/**
 * Wrapper for to call common function.
 *
 * @param derived1_h The object
 * @return Return code
 */
static void
derived2_derived1_delete (derived1_handle derived1_h)
{
    return (derived2_delete(derived1_cast_to_derived2(derived1_h)));
}


/**
 * The virtual function table for base1.  A NULL indicates a pure virtual
 * function in the base class for the function or that the parent object's
 * function is inherited for derived classes.
 */
static base1_vtable_st base1_vtable = {
    derived2_base1_delete,
    derived2_base1_type_string,
    NULL,
    NULL,
    NULL
};

/**
 * The virtual function table for base2.  A NULL indicates a pure virtual
 * function in the base class for the function or that the parent object's
 * function is inherited for derived classes.
 */
static base2_vtable_st base2_vtable = {
    derived2_base2_delete,
    derived2_base2_type_string,
    NULL,
    NULL,
    NULL
};

/**
 * The virtual function table for derived1.  A NULL indicates a pure virtual
 * function in the base class for the function or that the parent object's
 * function is inherited for derived classes.
 */
static derived1_vtable_st derived1_vtable = {
    &base1_vtable,
    &base2_vtable,
    derived2_derived1_delete,
    derived2_derived1_increase_val4
};

/**
 * Cast the derived2 object to derived1.
 *
 * @param derived2_h The derived2 object
 * @return The derived1 object
 */
derived1_handle
derived2_cast_to_derived1 (derived2_handle derived2_h)
{
    derived1_handle derived1_h = NULL;

    if (NULL != derived2_h) {
        derived1_h = &(derived2_h->derived1);
    }

    return (derived1_h);
}

/**
 * Initialize the derived2 objects.
 *
 * @param derived2_h The object
 * @return Return code
 */
static my_rc_e
derived2_init (derived2_handle derived2_h)
{
    my_rc_e rc = MY_RC_E_SUCCESS;

    if (NULL == derived2_h) {
        LOG_ERR("Invalid input, derived2_h(%p)", derived2_h);
        return (MY_RC_E_EINVAL);
    }

    rc = derived1_init(&(derived2_h->derived1));
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    rc = derived1_set_vtable(&(derived2_h->derived1), &derived1_vtable);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    derived2_h->derived1.base2.val1 = 999;
    derived2_h->derived1.val4 = 700;

    return (MY_RC_E_SUCCESS);
}


/**
 * Create a new derived2 object.
 *
 * @return The object or NULL if creation failed
 */
derived2_handle
derived2_new1 (void)
{
    derived2_st *derived2 = NULL;
    my_rc_e rc;

    derived2 = calloc(1, sizeof(*derived2));
    if (NULL != derived2) {
        rc = derived2_init(derived2);
        if (my_rc_e_is_notok(rc)) {
            LOG_ERR("Init failed, rc(%s)", my_rc_e_get_string(rc));
            goto err_exit;
        }
    }

    return (derived2);

err_exit:

    derived2_delete(derived2);

    return (NULL);
}
