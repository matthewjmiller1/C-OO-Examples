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
 * This implements some common functions.
 */
#include "common.h"

/**
 * String representations of the return codes.
 *
 * @see my_rc_e
 */
static const char * const my_rc_e_string[] = {
    "Invalid RC",
    "Success",
    "Invalid input",
    "No memory",
    "Max RC"
};

/** @cond doxygen_suppress */
/* Ensure there is a string for each return code declared */
CT_ASSERT(NELEMS(my_rc_e_string) == (MY_RC_E_MAX + 1));
/** @endcond */

/**
 * Indicates whether the return code is not in error.
 *
 * @param rc The return code to check
 * @return true if the return code is not in error.
 */
bool
my_rc_e_is_notok (my_rc_e rc)
{
    return (MY_RC_E_SUCCESS != rc);
}

/**
 * Indicates whether the return code is in error.
 *
 * @param rc The return code to check
 * @return true if the return code is in error.
 */
bool
my_rc_e_is_ok (my_rc_e rc)
{
    return (MY_RC_E_SUCCESS == rc);
}

/**
 * Indicates whether the return code is valid.
 *
 * @param rc The return code to check
 * @return true if the return code is valid.
 */
bool
my_rc_e_is_valid (my_rc_e rc)
{
    return ((rc >= MY_RC_E_INVALID) && (rc <= MY_RC_E_MAX));
}

/**
 * Get a string representation of the return code.
 *
 * @param rc The return code
 * @return A string representation of the return code or "__Invalid__" if an
 * invalid return code is input.
 */
const char *
my_rc_e_get_string (my_rc_e rc)
{
    const char* retval = "__Invalid__";

    if (my_rc_e_is_valid(rc)) {
        retval = my_rc_e_string[rc];
    }

    return (retval);
}
