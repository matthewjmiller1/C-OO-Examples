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
 * This is the implements a class that inherits from base1 and base2.
 */
#include "derived1_friend.h"

/** Size for this object to use for base1_string_size_fn */
#define DERIVED1_STR_SIZE 256

/**
 * Private variables which cannot be directly accessed by any other class
 * including children.
 */
typedef struct derived1_private_st_ {
    /** Virtual function table */
    const derived1_vtable_st *vtable;
} derived1_private_st;

/*
 * This is C, we need explicit casts to each of an object's parent classes.
 */

/**
 * Cast the base1 object to derived1.
 *
 * @param base1_h The base1 object
 * @return The derived1 object
 */
static derived1_handle
base1_cast_to_derived1 (base1_handle base1_h)
{
    derived1_handle derived1_h = NULL;

    if (NULL != base1_h) {
        derived1_h = (derived1_handle) ((uint8_t *) base1_h -
                                        offsetof(derived1_st, base1));
    }

    return (derived1_h);
}

/**
 * Cast the base2 object to derived1.
 *
 * @param base2_h The base2 object
 * @return The derived1 object
 */
static derived1_handle
base2_cast_to_derived1 (base2_handle base2_h)
{
    derived1_handle derived1_h = NULL;

    if (NULL != base2_h) {
        derived1_h = (derived1_handle) ((uint8_t *) base2_h -
                                        offsetof(derived1_st, base2));
    }

    return (derived1_h);
}

/**
 * Override the base2 virtual function and provide an implementation for
 * increasing val1.
 *
 * @param base2_h The base2 object
 * @return Return code
 * @see base2_increase_val1()
 */
static my_rc_e
derived1_base2_increase_val1 (base2_handle base2_h)
{
    if (NULL == base2_h) {
        LOG_ERR("Invalid input, base2_h(%p)", base2_h);
        return (MY_RC_E_EINVAL);
    }

    base2_h->val1 += 5;

    return (MY_RC_E_SUCCESS);
}

/**
 * The internal function for getting the size for objects of type derived1.
 * This is a common implementation for overriding both base1 and base2's
 * virtual functions.
 *
 * @param derived1_h The object
 * @param buffer_size Outputs the size of the buffer that should be used.
 * @return Return code
 * @see base1_string_size()
 * @see base2_string_size()
 */
static my_rc_e
derived1_string_size_internal (derived1_handle derived1_h, size_t *buffer_size)
{
    if ((NULL == derived1_h) || (NULL == buffer_size)) {
        LOG_ERR("Invalid input, derived1_h(%p) buffer_size(%p)",
                derived1_h, buffer_size);
        return (MY_RC_E_EINVAL);
    }
    *buffer_size = DERIVED1_STR_SIZE;

    return (MY_RC_E_SUCCESS);
}

/**
 * Wrapper for to call common function.
 *
 * @param base1_h The object
 * @param buffer_size Outputs the size of the buffer that should be used.
 * @return Return code
 */
static my_rc_e
derived1_base1_string_size (base1_handle base1_h, size_t *buffer_size)
{
    return (derived1_string_size_internal(base1_cast_to_derived1(base1_h), 
                                          buffer_size));
}

/**
 * Wrapper for to call common function.
 *
 * @param base2_h The object
 * @param buffer_size Outputs the size of the buffer that should be used.
 * @return Return code
 */
static my_rc_e
derived1_base2_string_size (base2_handle base2_h, size_t *buffer_size)
{
    return (derived1_string_size_internal(base2_cast_to_derived1(base2_h), 
                                          buffer_size));
}

/**
 * The internal function for getting the type string for objects of type
 * derived1.
 *
 * @param derived1_h The object
 * @return The string indicating the object type.
 */
static const char *
derived1_type_string_internal (derived1_handle derived1_h)
{
    return ("derived1");
}

/**
 * Wrapper for to call common function.
 *
 * @param base1_h The object
 * @return Return code
 */
static const char *
derived1_base1_type_string (base1_handle base1_h)
{
    return (derived1_type_string_internal(base1_cast_to_derived1(base1_h)));
}

/**
 * Wrapper for to call common function.
 *
 * @param base2_h The object
 * @return Return code
 */
static const char *
derived1_base2_type_string (base2_handle base2_h)
{
    return (derived1_type_string_internal(base2_cast_to_derived1(base2_h)));
}

/**
 * The internal function for getting the string representation for objects of
 * type derived1.
 *
 * @param derived1_h The object
 * @param buffer The buffer in which to put the string.
 * @param buffer_size The size of the buffer.
 * @return Return code
 */
static my_rc_e
derived1_string_internal (derived1_handle derived1_h, 
                          char *buffer, size_t buffer_size)
{
    size_t min_size;
    my_rc_e rc = MY_RC_E_SUCCESS;

    if ((NULL == derived1_h) || (NULL == buffer)) {
        LOG_ERR("Invalid input, derived1_h(%p) buffer(%p) buffer_size(%zu)",
                derived1_h, buffer, buffer_size);
        return (MY_RC_E_EINVAL);
    }

    rc = derived1_string_size_internal(derived1_h, &min_size);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    if (buffer_size < min_size) {
        LOG_ERR("Invalid input, buffer_size(%zu)", buffer_size);
        return (MY_RC_E_EINVAL);
    }

    snprintf(buffer, buffer_size, "b1_val1(%u) b1_val2(%u) b1_val3(%u) "
             "b2_val1(%u) d1_val4(%u)", derived1_h->base1.public_data.val1,
             derived1_h->base1.public_data.val2, derived1_h->base1.val3,
             derived1_h->base2.val1, derived1_h->val4);

    return (MY_RC_E_SUCCESS);
}

/**
 * Wrapper for to call common function.
 *
 * @param base1_h The object
 * @param buffer The buffer in which to put the string.
 * @param buffer_size Outputs the size of the buffer that should be used.
 * @return Return code
 */
static my_rc_e
derived1_base1_string (base1_handle base1_h, char *buffer, size_t buffer_size)
{
    return (derived1_string_internal(base1_cast_to_derived1(base1_h), buffer,
                                     buffer_size));
}

/**
 * Wrapper for to call common function.
 *
 * @param base2_h The object
 * @param buffer The buffer in which to put the string.
 * @param buffer_size Outputs the size of the buffer that should be used.
 * @return Return code
 */
static my_rc_e
derived1_base2_string (base2_handle base2_h, char *buffer, size_t buffer_size)
{
    return (derived1_string_internal(base2_cast_to_derived1(base2_h), buffer,
                                     buffer_size));
}

/**
 * The internal function for increasing value3 for objects of type derived1.
 * Will triple the current value.
 *
 * @param derived1_h The object
 * @return Return code
 * @see derived1_increase_val4()
 */
static my_rc_e
derived1_increase_val4_internal (derived1_handle derived1_h)
{
    if (NULL == derived1_h) {
        LOG_ERR("Invalid input, derived1_h(%p)", derived1_h);
        return (MY_RC_E_EINVAL);
    }

    derived1_h->val4 *= 3;

    return (MY_RC_E_SUCCESS);
}

/**
 * Increase val4 for the object.  This is a virtual function.
 *
 * @param derived1_h The object
 * @return Return code
 */
my_rc_e
derived1_increase_val4 (derived1_handle derived1_h)
{
    my_rc_e rc = MY_RC_E_SUCCESS;

    VALIDATE_VTABLE_FN(derived1_h, private_h, vtable, increase_val4_fn, rc);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    return (derived1_h->private_h->vtable->increase_val4_fn(derived1_h));
}

/**
 * The internal function to delete a derived1 object.  Upon return, the object
 * is not longer valid.
 *
 * @param derived1_h The object.  If NULL, then this function is a no-op.
 * @param free_derived1_h Indicates whether the base object should be freed or
 * not.
 * @see derived1_delete()
 * @see derived1_friend_delete()
 * @see derived1_private_delete()
 */
static void
derived1_delete_internal (derived1_handle derived1_h, bool free_derived1_h)
{
    if (NULL == derived1_h) {
        return;
    }

    base1_friend_delete(&(derived1_h->base1));
    base2_friend_delete(&(derived1_h->base2));

    if (NULL != derived1_h->private_h) {
        free(derived1_h->private_h);
        derived1_h->private_h = NULL;
    }

    if (free_derived1_h) {
        free(derived1_h);
    }
}

/**
 * Allow a friend class to delete the derived1 object.  It is assumed that the
 * friend class is managing the memory for the derived1 object and, thus, the
 * object will not be freed.  However, members within the derived1 object may be
 * freed.  This does not call the virtual function table version of delete, but
 * rather the delete specifically for type derived1.
 *
 * @param derived1_h The object.  If NULL, then this function is a no-op.
 * @see derived1_delete()
 */
void
derived1_friend_delete (derived1_handle derived1_h)
{
    derived1_delete_internal(derived1_h, false);
}

/**
 * Delete the derived1 object.  It is assumed that the the derived1 object is
 * directly allocated from the heap and not within another object and, hence,
 * will be freed by this function call.
 *
 * @param derived1_h The object.  If NULL, then this function is a no-op.
 * @see derived1_delete()
 */
static void
derived1_private_delete (derived1_handle derived1_h)
{
    derived1_delete_internal(derived1_h, true);
}

/**
 * Delete the object.  This is a virtual function.  Upon return, the object is
 * not longer valid.
 *
 * @param derived1_h The object.  If NULL, then this function is a no-op.
 */
void
derived1_delete (derived1_handle derived1_h)
{
    my_rc_e rc = MY_RC_E_SUCCESS;

    VALIDATE_VTABLE_FN(derived1_h, private_h, vtable, delete_fn, rc);
    if (my_rc_e_is_notok(rc)) {
        return;
    }

    return (derived1_h->private_h->vtable->delete_fn(derived1_h));
}

/**
 * Wrapper for to call common function.
 *
 * @param base1_h The object
 * @return Return code
 */
static void
derived1_base1_delete (base1_handle base1_h)
{
    return (derived1_delete(base1_cast_to_derived1(base1_h)));
}

/**
 * Wrapper for to call common function.
 *
 * @param base2_h The object
 * @return Return code
 */
static void
derived1_base2_delete (base2_handle base2_h)
{
    return (derived1_delete(base2_cast_to_derived1(base2_h)));
}

/**
 * The virtual function table for base1.  A NULL indicates a pure virtual
 * function in the base class for the function or that the parent object's
 * function is inherited for derived classes.
 */
static base1_vtable_st base1_vtable = {
    derived1_base1_delete,
    derived1_base1_type_string,
    derived1_base1_string,
    derived1_base1_string_size,
    NULL
};

/**
 * The virtual function table for base2.  A NULL indicates a pure virtual
 * function in the base class for the function or that the parent object's
 * function is inherited for derived classes.
 */
static base2_vtable_st base2_vtable = {
    derived1_base2_delete,
    derived1_base2_type_string,
    derived1_base2_string,
    derived1_base2_string_size,
    derived1_base2_increase_val1
};

/**
 * The virtual function table for derived1.  A NULL indicates a pure virtual
 * function in the base class for the function or that the parent object's
 * function is inherited for derived classes.
 */
static derived1_vtable_st derived1_vtable = {
    &base1_vtable,
    &base2_vtable,
    derived1_private_delete,
    derived1_increase_val4_internal
};

/**
 * Cast the derived1 object to base1.
 *
 * @param derived1_h The derived1 object
 * @return The base1 object
 */
base1_handle
derived1_cast_to_base1 (derived1_handle derived1_h)
{
    base1_handle base1_h = NULL;

    if (NULL != derived1_h) {
        base1_h = &(derived1_h->base1);
    }

    return (base1_h);
}

/**
 * Cast the derived1 object to base2.
 *
 * @param derived1_h The derived1 object
 * @return The base2 object
 */
base2_handle
derived1_cast_to_base2 (derived1_handle derived1_h)
{
    base2_handle base2_h = NULL;

    if (NULL != derived1_h) {
        base2_h = &(derived1_h->base2);
    }

    return (base2_h);
}

/**
 * Fill in the child vtable with values inherited from the parent_vtable for all
 * functions left NULL in the child vtable.
 *
 * @param parent_vtable The parent vtable from which to inherit.
 * @param child_vtable The child vtable to which functions may be inherited.
 * @param do_null_check Indicates whether an error should be thrown if a
 * function in the child vtable is NULL after inheritance.
 */
my_rc_e
derived1_inherit_vtable (const derived1_vtable_st *parent_vtable,
                         derived1_vtable_st *child_vtable,
                         bool do_null_check)
{
    my_rc_e rc = MY_RC_E_SUCCESS;

    /* Always add a new check here if functions are added. */
    CT_ASSERT(4 == (sizeof(derived1_vtable_st)/sizeof(void*)));

    if ((NULL == parent_vtable) || (NULL == child_vtable)) {
        LOG_ERR("Invalid input, parent_vtable(%p) "
                "child_vtable(%p)", parent_vtable, child_vtable);
        return (MY_RC_E_EINVAL);
    }

    rc = base1_inherit_vtable(&base1_vtable, child_vtable->base1_vtable, false);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    rc = base2_inherit_vtable(&base2_vtable, child_vtable->base2_vtable, false);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    INHERIT_VTABLE_FN(parent_vtable, child_vtable, delete_fn, do_null_check,
                      rc);
    INHERIT_VTABLE_FN(parent_vtable, child_vtable, increase_val4_fn, 
                      do_null_check, rc);

    return (MY_RC_E_SUCCESS);

err_exit:

    return (rc);
}

/**
 * This is a function used by friend classes to set the virtual table according
 * to which methods they wish to override.  
 *
 * @param derived1_h The object
 * @param vtable The virtual table specification for the friend class.  If a
 * function pointer is NULL, then the base1 function is inherited.
 * @return Return code
 */
my_rc_e
derived1_set_vtable (derived1_handle derived1_h, derived1_vtable_st *vtable)
{
    my_rc_e rc;

    if ((NULL == derived1_h) || (NULL == vtable)) {
        LOG_ERR("Invalid input, derived1_h(%p) vtable(%p)", derived1_h, vtable);
        return (MY_RC_E_EINVAL);
    }

    if (NULL == derived1_h->private_h) {
        LOG_ERR("Invalid input, derived1_h(%p)->private_h(%p)", derived1_h,
                derived1_h->private_h);
        return (MY_RC_E_EINVAL);
    }

    rc = derived1_inherit_vtable(&derived1_vtable, vtable, true);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    rc = base1_set_vtable(&(derived1_h->base1), vtable->base1_vtable);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    rc = base2_set_vtable(&(derived1_h->base2), vtable->base2_vtable);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    derived1_h->private_h->vtable = vtable;

    return (MY_RC_E_SUCCESS);
}

/**
 * Allows a friend class to initialize their inner derived1 object.  Must be
 * called before the derived1 object is used.  If an error is returned, any
 * clean-up was handled internally and there is no need to call a delete
 * function.
 *
 * @param derived1_h The object
 * @return Return code
 */
my_rc_e
derived1_init (derived1_handle derived1_h)
{
    bool did_base1_init = false;
    bool did_base2_init = false;
    my_rc_e rc = MY_RC_E_SUCCESS;

    if (NULL == derived1_h) {
        LOG_ERR("Invalid input, derived1_h(%p)", derived1_h);
        return (MY_RC_E_EINVAL);
    }

    rc = base1_init(&(derived1_h->base1));
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }
    did_base1_init = true;

    rc = base1_set_vtable(&(derived1_h->base1), &base1_vtable);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    rc = base2_init(&(derived1_h->base2));
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }
    did_base2_init = true;

    rc = base2_set_vtable(&(derived1_h->base2), &base2_vtable);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    derived1_h->private_h = calloc(1, sizeof(*derived1_h->private_h));
    if (NULL == derived1_h->private_h) {
        rc = MY_RC_E_ENOMEM;
        goto err_exit;
    }

    derived1_h->private_h->vtable = &derived1_vtable;
    derived1_h->val4 = 500;

    return (MY_RC_E_SUCCESS);

err_exit:

    if (NULL != derived1_h->private_h) {
        free(derived1_h->private_h);
        derived1_h->private_h = NULL;
    }

    if (did_base2_init) {
        base2_friend_delete(&(derived1_h->base2));
    }

    if (did_base1_init) {
        base1_friend_delete(&(derived1_h->base1));
    }

    return (rc);
}

/**
 * Create a new derived1 object.
 *
 * @return The object or NULL if creation failed
 */
derived1_handle
derived1_new1 (void)
{
    derived1_st *derived1 = NULL;
    my_rc_e rc;

    derived1 = calloc(1, sizeof(*derived1));
    if (NULL != derived1) {
        rc = derived1_init(derived1);
        if (my_rc_e_is_notok(rc)) {
            LOG_ERR("Init failed, rc(%s)", my_rc_e_get_string(rc));
            goto err_exit;
        }
    }

    return (derived1);

err_exit:

    derived1_delete(derived1);

    return (NULL);
}
