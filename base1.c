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
 * This is the implements a base class from which children class may inherit.
 */
#include "base1_friend.h"

/** Size for this object to use for base1_string_size_fn */
#define BASE1_STR_SIZE 128

/**
 * Private variables which cannot be directly accessed by any other class
 * including children.
 */
typedef struct base1_private_st_ {
    /** Virtual function table */
    const base1_vtable_st *vtable;
} base1_private_st;

/**
 * Example of a static class method.  It takes no instance of an object.
 * @return Description of val1
 */
const char *
base1_get_val1_description (void)
{
    return ("Value 1");
}

/**
 * Gets a copy of the public data for the given object.  Note this is a shallow
 * copy of the data, modifying it will not change the object's state.  Writing
 * the object's state is handled seperately by base1_set_public_data().
 *
 * @param base1_h The object
 * @param public_data The data buffer into which the values should be read
 * @return Return code
 * @see base1_set_public_data()
 */
my_rc_e
base1_get_public_data (base1_handle base1_h, base1_public_data_st *public_data)
{

    if ((NULL == base1_h) || (NULL == public_data)) {
        LOG_ERR("Invalid input, base1_h(%p) public_data(%p)", base1_h,
                public_data);
        return (MY_RC_E_EINVAL);
    }

    memcpy(public_data, &(base1_h->public_data), sizeof(*public_data));

    return (MY_RC_E_SUCCESS);
}

/**
 * Set the public data for the given object.  Note that this creates a deep copy
 * of the data in the object.  Also note that it overwrites all public data in
 * the object, not certain fields seletively.
 *
 * @param base1_h The object
 * @param public_data The data buffer whose values should be written into the
 * object
 * @return Return code
 * @see base1_get_public_data()
 */
my_rc_e
base1_set_public_data (base1_handle base1_h, base1_public_data_st *public_data)
{

    if ((NULL == base1_h) || (NULL == public_data)) {
        LOG_ERR("Invalid input, base1_h(%p) public_data(%p)", base1_h,
                public_data);
        return (MY_RC_E_EINVAL);
    }

    memcpy(&(base1_h->public_data), public_data, sizeof(base1_h->public_data));

    return (MY_RC_E_SUCCESS);
}

/**
 * Get the minimum size of a string buffer that should be used to get a string
 * representation of the object.  This is a virtual function.
 *
 * @param base1_h The object
 * @param buffer_size Outputs the size of the buffer that should be used.
 * @return Return code
 * @see base1_string()
 */
my_rc_e
base1_string_size (base1_handle base1_h, size_t *buffer_size)
{
    my_rc_e rc = MY_RC_E_SUCCESS;

    VALIDATE_VTABLE_FN(base1_h, private_h, vtable, string_size_fn, rc);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    return (base1_h->private_h->vtable->string_size_fn(base1_h, buffer_size));
}

/**
 * The internal function for getting the size for objects of type base1.
 *
 * @param base1_h The object
 * @param buffer_size Outputs the size of the buffer that should be used.
 * @return Return code
 * @see base1_string_size()
 */
static my_rc_e
base1_string_size_internal (base1_handle base1_h, size_t *buffer_size)
{
    if ((NULL == base1_h) || (NULL == buffer_size)) {
        LOG_ERR("Invalid input, base1_h(%p) buffer_size(%p)",
                base1_h, buffer_size);
        return (MY_RC_E_EINVAL);
    }

    *buffer_size = BASE1_STR_SIZE;

    return (MY_RC_E_SUCCESS);
}

/**
 * The internal function for getting the type string for objects of type base1.
 *
 * @param base1_h The object
 * @return The string indicating the object type.
 * @see base1_type_string()
 */
static const char *
base1_type_string_internal (base1_handle base1_h)
{
    return ("base1");
}

/**
 * Get the string describing the type of the object.  This is a virtual
 * function.
 *
 * @param base1_h The object
 * @return The string indicating the object type.
 */
const char *
base1_type_string (base1_handle base1_h)
{
    my_rc_e rc = MY_RC_E_SUCCESS;

    VALIDATE_VTABLE_FN(base1_h, private_h, vtable, type_string_fn, rc);
    if (my_rc_e_is_notok(rc)) {
        return ("");
    }

    return (base1_h->private_h->vtable->type_string_fn(base1_h));
}

/**
 * Get a string representation of the object.  This is a virtual function.
 *
 * @param base1_h The object
 * @param buffer The buffer in which to put the string.
 * @param buffer_size The size of the buffer.
 * @return Return code
 * @see base1_string_size()
 */
my_rc_e
base1_string (base1_handle base1_h, char *buffer, size_t buffer_size)
{
    my_rc_e rc = MY_RC_E_SUCCESS;

    VALIDATE_VTABLE_FN(base1_h, private_h, vtable, string_fn, rc);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    return (base1_h->private_h->vtable->string_fn(base1_h, buffer,
                                                  buffer_size));
}

/**
 * The internal function for getting the string representation for objects of
 * type base1.
 *
 * @param base1_h The object
 * @param buffer The buffer in which to put the string.
 * @param buffer_size The size of the buffer.
 * @return Return code
 * @see base1_string()
 */
static my_rc_e
base1_string_internal (base1_handle base1_h, char *buffer, size_t buffer_size)
{
    size_t min_size;
    my_rc_e rc = MY_RC_E_SUCCESS;

    if ((NULL == base1_h) || (NULL == buffer)) {
        LOG_ERR("Invalid input, base1_h(%p) buffer(%p) buffer_size(%zu)",
                base1_h, buffer, buffer_size);
        return (MY_RC_E_EINVAL);
    }

    VALIDATE_VTABLE_FN(base1_h, private_h, vtable, string_size_fn, rc);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    rc = base1_h->private_h->vtable->string_size_fn(base1_h, &min_size);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    if (buffer_size < min_size) {
        LOG_ERR("Invalid input, buffer_size(%zu)", buffer_size);
        return (MY_RC_E_EINVAL);
    }

    snprintf(buffer, buffer_size, "val1(%u) val2(%u) val3(%u)",
             base1_h->public_data.val1, base1_h->public_data.val2,
             base1_h->val3);

    return (MY_RC_E_SUCCESS);
}

/**
 * The internal function to delete a base1 object.  Upon return, the object is
 * not longer valid.
 *
 * @param base1_h The object.  If NULL, then this function is a no-op.
 * @param free_base1_h Indicates whether the base object should be freed or not.
 * @see base1_delete()
 * @see base1_friend_delete()
 * @see base1_private_delete()
 */
static void
base1_delete_internal (base1_handle base1_h, bool free_base1_h)
{
    if (NULL == base1_h) {
        return;
    }

    if (NULL != base1_h->private_h) {
        free(base1_h->private_h);
        base1_h->private_h = NULL;
    }

    if (free_base1_h) {
        free(base1_h);
    }
}

/**
 * Allow a friend class to delete the base1 object.  It is assumed that the
 * friend class is managing the memory for the base1 object and, thus, the
 * object will not be freed.  However, members within the base1 object may be
 * freed.  This does not call the virtual function table version of delete, but
 * rather the delete specifically for type base1.
 *
 * @param base1_h The object.  If NULL, then this function is a no-op.
 * @see base1_delete()
 */
void
base1_friend_delete (base1_handle base1_h)
{
    base1_delete_internal(base1_h, false);
}

/**
 * Delete the base1 object.  It is assumed that the the base1 object is directly
 * allocated from the heap and not within another object and, hence, will be
 * freed by this function call.
 *
 * @param base1_h The object.  If NULL, then this function is a no-op.
 * @see base1_delete()
 */
static void
base1_private_delete (base1_handle base1_h)
{
    base1_delete_internal(base1_h, true);
}

/**
 * Delete the object.  This is a virtual function.  Upon return, the object is
 * not longer valid.
 *
 * @param base1_h The object.  If NULL, then this function is a no-op.
 */
void
base1_delete (base1_handle base1_h)
{
    my_rc_e rc = MY_RC_E_SUCCESS;

    VALIDATE_VTABLE_FN(base1_h, private_h, vtable, delete_fn, rc);
    if (my_rc_e_is_notok(rc)) {
        return;
    }

    return (base1_h->private_h->vtable->delete_fn(base1_h));
}

/**
 * The internal function for increasing value3 for objects of type base1.  Will
 * double the current value.
 *
 * @param base1_h The object
 * @return Return code
 * @see base1_increase_val3()
 */
static my_rc_e
base1_increase_val3_internal (base1_handle base1_h)
{
    if (NULL == base1_h) {
        LOG_ERR("Invalid input, base1_h(%p)", base1_h);
        return (MY_RC_E_EINVAL);
    }

    base1_h->val3 *= 2;

    return (MY_RC_E_SUCCESS);
}

/**
 * Increase val3 for the object.  This is a virtual function.
 *
 * @param base1_h The object
 * @return Return code
 */
my_rc_e
base1_increase_val3 (base1_handle base1_h)
{
    my_rc_e rc = MY_RC_E_SUCCESS;

    VALIDATE_VTABLE_FN(base1_h, private_h, vtable, increase_val3_fn, rc);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    return (base1_h->private_h->vtable->increase_val3_fn(base1_h));
}

/**
 * The virtual function table used for objects of type base1.  A NULL indicates
 * a pure virtual function in the base class for the function or that the parent
 * object's function is inherited for derived classes.
 */
static const base1_vtable_st base1_vtable = {
    base1_private_delete,
    base1_type_string_internal,
    base1_string_internal,
    base1_string_size_internal,
    base1_increase_val3_internal
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
base1_inherit_vtable (const base1_vtable_st *parent_vtable,
                      base1_vtable_st *child_vtable,
                      bool do_null_check)
{
    my_rc_e rc = MY_RC_E_SUCCESS;

    /* Always add a new check here if functions are added. */
    CT_ASSERT(5 == (sizeof(base1_vtable_st)/sizeof(void*)));

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
    INHERIT_VTABLE_FN(parent_vtable, child_vtable, increase_val3_fn,
                      do_null_check, rc);

    return (MY_RC_E_SUCCESS);

err_exit:

    return (rc);
}

/**
 * This is a function used by friend classes to set the virtual table according
 * to which methods they wish to override.  
 *
 * @param base1_h The object
 * @param vtable The virtual table specification for the friend class.  If a
 * function pointer is NULL, then the base1 function is inherited.
 * @return Return code
 */
my_rc_e
base1_set_vtable (base1_handle base1_h, base1_vtable_st *vtable)
{
    my_rc_e rc;

    if ((NULL == base1_h) || (NULL == vtable)) {
        LOG_ERR("Invalid input, base1_h(%p) vtable(%p)", base1_h, vtable);
        return (MY_RC_E_EINVAL);
    }

    if (NULL == base1_h->private_h) {
        LOG_ERR("Invalid input, base1_h(%p)->private_h(%p)", base1_h,
                base1_h->private_h);
        return (MY_RC_E_EINVAL);
    }

    rc = base1_inherit_vtable(&base1_vtable, vtable, true);
    if (my_rc_e_is_notok(rc)) {
        return (rc);
    }

    base1_h->private_h->vtable = vtable;

    return (MY_RC_E_SUCCESS);
}

/**
 * Allows a friend class to initialize their inner base1 object.  Must be called
 * before the base1 object is used.  If an error is returned, any clean-up was
 * handled internally and there is no need to call a delete function.
 *
 * @param base1_h The object
 * @return Return code
 * @see base1_delete()
 * @see base1_friend_delete()
 */
my_rc_e
base1_init (base1_handle base1_h)
{
    my_rc_e rc = MY_RC_E_SUCCESS;

    if (NULL == base1_h) {
        LOG_ERR("Invalid input, base1_h(%p)", base1_h);
        return (MY_RC_E_EINVAL);
    }

    base1_h->private_h = calloc(1, sizeof(*base1_h->private_h));
    if (NULL == base1_h->private_h) {
        rc = MY_RC_E_ENOMEM;
        goto err_exit;
    }

    base1_h->private_h->vtable = &base1_vtable;
    base1_h->public_data.val1 = 1;
    base1_h->public_data.val2 = 2;
    base1_h->val3 = 42;

    return (MY_RC_E_SUCCESS);

err_exit:

    if (NULL != base1_h->private_h) {
        free(base1_h->private_h);
        base1_h->private_h = NULL;
    }

    return (rc);
}

/**
 * Create a new base1 object.
 *
 * @return The object or NULL if creation failed
 */
base1_handle
base1_new1 (void)
{
    base1_st *base1 = NULL;
    my_rc_e rc;

    base1 = calloc(1, sizeof(*base1));
    if (NULL != base1) {
        rc = base1_init(base1);
        if (my_rc_e_is_notok(rc)) {
            LOG_ERR("Init failed, rc(%s)", my_rc_e_get_string(rc));
            goto err_exit;
        }
    }

    return (base1);

err_exit:

    base1_private_delete(base1);

    return (NULL);
}

/**
 * Create a new base1 object.
 *
 * @param public_data The initial public data for the new object.
 * @return The object or NULL if creation failed
 */
base1_handle
base1_new2 (base1_public_data_st *public_data)
{
    base1_st *base1 = NULL;

    if (NULL == public_data) {
        LOG_ERR("Invalid input, public_data(%p)", public_data);
        return (NULL);
    }

    base1 = base1_new1();
    if (NULL != base1) {
        memcpy(&(base1->public_data), public_data, sizeof(base1->public_data));
     }

    return (base1);
}

/**
 * Create a new base1 object.
 *
 * @param val1 The initial val1 for the new object.
 * @param val3 The initial val3 for the new object.
 * @return The object or NULL if creation failed
 */
base1_handle
base1_new3 (uint8_t val1, uint32_t val3)
{
    base1_st *base1 = NULL;

    base1 = base1_new1();
    if (NULL != base1) {
        base1->public_data.val1 = val1;
        base1->val3 = val3;
     }

    return (base1);
}
