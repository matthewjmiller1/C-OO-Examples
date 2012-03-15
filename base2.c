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
 * This is the implements a base class from which children class may inherit.
 * Note that this is an abstract class with a pure virtual function and no
 * constructor.
 */
#include "base2_friend.h"

/** Size for this object to use for base2_string_size_fn */
#define BASE2_STR_SIZE 64

/**
 * Private variables which cannot be directly accessed by any other class
 * including children.
 */
typedef struct base2_private_st_ {
    /** Virtual function table */
    const base2_vtable_st *vtable;
} base2_private_st;

/**
 * Get the minimum size of a string buffer that should be used to get a string
 * representation of the object.  This is a virtual function.
 *
 * @param base2_h The object
 * @param buffer_size Outputs the size of the buffer that should be used.
 * @return Return code
 * @see base2_string()
 */
my_rc_e
base2_string_size (base2_handle base2_h, size_t *buffer_size)
{
    my_rc_e rc = MY_RC_E_SUCCESS;

    VALIDATE_VTABLE_FN(base2_h, private_h, vtable, string_size_fn, rc);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    return (base2_h->private_h->vtable->string_size_fn(base2_h, buffer_size));
}

/**
 * The internal function for getting the size for objects of type base2.
 *
 * @param base2_h The object
 * @param buffer_size Outputs the size of the buffer that should be used.
 * @return Return code
 * @see base2_string_size()
 */
static my_rc_e
base2_string_size_internal (base2_handle base2_h, size_t *buffer_size)
{
    if ((NULL == base2_h) || (NULL == buffer_size)) {
        LOG_ERR("Invalid input, base2_h(%p) buffer_size(%p)",
                base2_h, buffer_size);
        return (MY_RC_E_EINVAL);
    }

    *buffer_size = BASE2_STR_SIZE;

    return (MY_RC_E_SUCCESS);
}

/**
 * The internal function for getting the type string for objects of type base2.
 *
 * @param base2_h The object
 * @return The string indicating the object type.
 * @see base2_type_string()
 */
static const char *
base2_type_string_internal (base2_handle base2_h)
{
    return ("base2");
}

/**
 * Get the string describing the type of the object.  This is a virtual
 * function.
 *
 * @param base2_h The object
 * @return The string indicating the object type.
 */
const char *
base2_type_string (base2_handle base2_h)
{
    my_rc_e rc = MY_RC_E_SUCCESS;

    VALIDATE_VTABLE_FN(base2_h, private_h, vtable, type_string_fn, rc);
    if (my_rc_e_is_notok(rc)) {
        return ("");
    }

    return (base2_h->private_h->vtable->type_string_fn(base2_h));
}

/**
 * Get a string representation of the object.  This is a virtual function.
 *
 * @param base2_h The object
 * @param buffer The buffer in which to put the string.
 * @param buffer_size The size of the buffer.
 * @return Return code
 * @see base2_string_size()
 */
my_rc_e
base2_string (base2_handle base2_h, char *buffer, size_t buffer_size)
{
    my_rc_e rc = MY_RC_E_SUCCESS;

    VALIDATE_VTABLE_FN(base2_h, private_h, vtable, string_fn, rc);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    return (base2_h->private_h->vtable->string_fn(base2_h, buffer,
                                                  buffer_size));
}

/**
 * The internal function for getting the string representation for objects of
 * type base2.
 *
 * @param base2_h The object
 * @param buffer The buffer in which to put the string.
 * @param buffer_size The size of the buffer.
 * @return Return code
 * @see base2_string()
 */
static my_rc_e
base2_string_internal (base2_handle base2_h, char *buffer, size_t buffer_size)
{
    size_t min_size;
    my_rc_e rc = MY_RC_E_SUCCESS;

    if ((NULL == base2_h) || (NULL == buffer)) {
        LOG_ERR("Invalid input, base2_h(%p) buffer(%p) buffer_size(%zu)",
                base2_h, buffer, buffer_size);
        return (MY_RC_E_EINVAL);
    }

    VALIDATE_VTABLE_FN(base2_h, private_h, vtable, string_size_fn, rc);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    rc = base2_h->private_h->vtable->string_size_fn(base2_h, &min_size);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    if (buffer_size < min_size) {
        LOG_ERR("Invalid input, buffer_size(%zu)", buffer_size);
        return (MY_RC_E_EINVAL);
    }

    snprintf(buffer, buffer_size, "val1(%u)", base2_h->val1);

    return (MY_RC_E_SUCCESS);
}

/**
 * The internal function to delete a base2 object.  Upon return, the object is
 * not longer valid.
 *
 * @param base2_h The object.  If NULL, then this function is a no-op.
 * @param free_base2_h Indicates whether the base object should be freed or not.
 * @see base2_delete()
 * @see base2_friend_delete()
 * @see base2_private_delete()
 */
static void
base2_delete_internal (base2_handle base2_h, bool free_base2_h)
{
    if (NULL == base2_h) {
        return;
    }

    if (NULL != base2_h->private_h) {
        free(base2_h->private_h);
        base2_h->private_h = NULL;
    }

    if (free_base2_h) {
        free(base2_h);
    }
}

/**
 * Allow a friend class to delete the base2 object.  It is assumed that the
 * friend class is managing the memory for the base2 object and, thus, the
 * object will not be freed.  However, members within the base2 object may be
 * freed.  This does not call the virtual function table version of delete, but
 * rather the delete specifically for type base2.
 *
 * @param base2_h The object.  If NULL, then this function is a no-op.
 * @see base2_delete()
 */
void
base2_friend_delete (base2_handle base2_h)
{
    base2_delete_internal(base2_h, false);
}

/**
 * Delete the base2 object.  It is assumed that the the base2 object is directly
 * allocated from the heap and not within another object and, hence, will be
 * freed by this function call.
 *
 * @param base2_h The object.  If NULL, then this function is a no-op.
 * @see base2_delete()
 */
static void
base2_private_delete (base2_handle base2_h)
{
    base2_delete_internal(base2_h, true);
}

/**
 * Delete the object.  This is a virtual function.  Upon return, the object is
 * not longer valid.
 *
 * @param base2_h The object.  If NULL, then this function is a no-op.
 */
void
base2_delete (base2_handle base2_h)
{
    my_rc_e rc = MY_RC_E_SUCCESS;

    VALIDATE_VTABLE_FN(base2_h, private_h, vtable, delete_fn, rc);
    if (my_rc_e_is_notok(rc)) {
        return;
    }

    return (base2_h->private_h->vtable->delete_fn(base2_h));
}

/**
 * Increase val3 for the object.  This is a pure virtual function.
 *
 * @param base2_h The object
 * @return Return code
 */
my_rc_e
base2_increase_val1 (base2_handle base2_h)
{
    my_rc_e rc = MY_RC_E_SUCCESS;

    VALIDATE_VTABLE_FN(base2_h, private_h, vtable, increase_val1_fn, rc);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    return (base2_h->private_h->vtable->increase_val1_fn(base2_h));
}

/**
 * Get the current val1 value for the object.
 *
 * @param base2_h The object
 * @param val1 Outputs the current value.
 * @return Return code
 */
my_rc_e
base2_get_val1 (base2_handle base2_h, uint32_t *val1)
{
    if ((NULL == base2_h) || (NULL == val1)) {
        LOG_ERR("Invalid input, base2_h(%p) val1(%p)", base2_h, val1);
        return (MY_RC_E_EINVAL);
    }

    *val1 = base2_h->val1;

    return (MY_RC_E_SUCCESS);
}

/**
 * The virtual function table used for objects of type base2.  A NULL indicates
 * a pure virtual function in the base class for the function or that the parent
 * object's function is inherited for derived classes.
 */
static const base2_vtable_st base2_vtable = {
    base2_private_delete,
    base2_type_string_internal,
    base2_string_internal,
    base2_string_size_internal,
    NULL
};

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
base2_inherit_vtable (const base2_vtable_st *parent_vtable,
                      base2_vtable_st *child_vtable,
                      bool do_null_check)
{
    my_rc_e rc = MY_RC_E_SUCCESS;

    /* Always add a new check here if functions are added. */
    CT_ASSERT(5 == (sizeof(base2_vtable_st)/sizeof(void*)));

    if ((NULL == parent_vtable) || (NULL == child_vtable)) {
        LOG_ERR("Invalid input, parent_vtable(%p) "
                "child_vtable(%p)", parent_vtable, child_vtable);
        return (MY_RC_E_EINVAL);
    }

    INHERIT_VTABLE_FN(parent_vtable, child_vtable, delete_fn, do_null_check,
                      rc);
    INHERIT_VTABLE_FN(parent_vtable, child_vtable, type_string_fn,
                      do_null_check, rc);
    INHERIT_VTABLE_FN(parent_vtable, child_vtable, string_fn, do_null_check,
                      rc);
    INHERIT_VTABLE_FN(parent_vtable, child_vtable, string_size_fn,
                      do_null_check, rc);
    INHERIT_VTABLE_FN(parent_vtable, child_vtable, increase_val1_fn,
                      do_null_check, rc);

    return (MY_RC_E_SUCCESS);

err_exit:

    return (rc);
}

/**
 * This is a function used by friend classes to set the virtual table according
 * to which methods they wish to override.  
 *
 * @param base2_h The object
 * @param vtable The virtual table specification for the friend class.  If a
 * function pointer is NULL, then the base2 function is inherited.
 * @return Return code
 */
my_rc_e
base2_set_vtable (base2_handle base2_h, base2_vtable_st *vtable)
{
    my_rc_e rc;

    if ((NULL == base2_h) || (NULL == vtable)) {
        LOG_ERR("Invalid input, base2_h(%p) vtable(%p)", base2_h, vtable);
        return (MY_RC_E_EINVAL);
    }

    if (NULL == base2_h->private_h) {
        LOG_ERR("Invalid input, base2_h(%p)->private_h(%p)", base2_h,
                base2_h->private_h);
        return (MY_RC_E_EINVAL);
    }

    rc = base2_inherit_vtable(&base2_vtable, vtable, true);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    base2_h->private_h->vtable = vtable;

    return (MY_RC_E_SUCCESS);
}

/**
 * Allows a friend class to initialize their inner base2 object.  Must be called
 * before the base2 object is used.  If an error is returned, any clean-up was
 * handled internally and there is no need to call a delete function.
 *
 * @param base2_h The object
 * @return Return code
 * @see base2_delete()
 * @see base2_friend_delete()
 */
my_rc_e
base2_init (base2_handle base2_h)
{
    my_rc_e rc = MY_RC_E_SUCCESS;

    if (NULL == base2_h) {
        LOG_ERR("Invalid input, base2_h(%p)", base2_h);
        return (MY_RC_E_EINVAL);
    }

    base2_h->private_h = calloc(1, sizeof(*base2_h->private_h));
    if (NULL == base2_h->private_h) {
        rc = MY_RC_E_ENOMEM;
        goto err_exit;
    }

    base2_h->private_h->vtable = &base2_vtable;
    base2_h->val1 = 7;

    return (MY_RC_E_SUCCESS);

err_exit:

    if (NULL != base2_h->private_h) {
        free(base2_h->private_h);
        base2_h->private_h = NULL;
    }

    return (rc);
}
