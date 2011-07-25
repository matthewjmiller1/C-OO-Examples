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
 * Main program to do some basic tests on the object-oriented C code.
 */

/**
 * @mainpage Example of Object-Oriented C
 * \author Matthew J. Miller (matt@matthewjmiller.net)
 * \date 2011
 *
 * @section sec_intro Introduction
 *
 * This gives an idea of how aspects of object-oriented programming can be
 * implmented in C.  It particular, it demonstrates multiple inheritance, an
 * abstract class, and multiple levels of inheritance.  Opaque pointers are used
 * to completely encapsulate a class's virtual function table so it is
 * inaccessible directly even to friend classes.
 *
 * It and of itself, this isn't particularly useful because there is so much
 * manual work to setup basic OO-relations.  This is more of a playground to try
 * stuff for which a code generator could then be built to automate the code for
 * these relationships.
 *
 * \c base1 and \c base2 are base classes.  \c base2 is an abstract class that
 * has a pure virtual function (\c base2_increase_val1()).  \c derived1 inherits
 * from both \c base1 and \c base2.  \c derived2 inherits from \c derived1.
 *
 * The files follow the convention:
 *    - \b base1.h: Public API for class \c base1.
 *    - \b base1_friend.h: Friend API for class \c base1.  Should only be
 *    included by classes that inherit from \c base1.
 *    - \b base1.c: Implementation of \c base1 and includes private data not
 *    directly accessible by even friend classes.
 *
 * \section sec_usage Usage
 *
 * Just run \c make and the \c test_c_oo test program will be run.  You can
 * edit \c test_c_oo.c to try various things with this class hierarchy.
 * Running <tt>make clean</tt> will remove the executable and .o files.
 *
 * @section sec_license GNU General Public License
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
 */

#include "base1.h"
#include "base2.h"
#include "derived1.h"
#include "derived2.h"

/**
 * Output a string representation of a base1 object.
 *
 * @param base1_h The object
 */
static void
display_base1 (base1_handle base1_h)
{
    size_t string_size;
    my_rc_e rc;

    rc = base1_string_size(base1_h, &string_size);
    if (my_rc_e_is_notok(rc)) {
        return;
    }

    {
        char base1_str[string_size];
        base1_string(base1_h, base1_str, sizeof(base1_str));
        printf("type(%s): %s\n", base1_type_string(base1_h), base1_str);
    }
}

/**
 * Output a string representation of a base2 object.
 *
 * @param base2_h The object
 */
static void
display_base2 (base2_handle base2_h)
{
    size_t string_size;
    my_rc_e rc;

    rc = base2_string_size(base2_h, &string_size);
    if (my_rc_e_is_notok(rc)) {
        return;
    }

    {
        char base2_str[string_size];
        base2_string(base2_h, base2_str, sizeof(base2_str));
        printf("type(%s): %s\n", base2_type_string(base2_h), base2_str);
    }
}

/**
 * Main function to test objects.
 */
int 
main (int argc, char *argv[])
{
    base1_handle base1_h, base1_2_h, base1_3_h;
    base2_handle base2_h;
    derived1_handle derived1_h, derived1_2_h;
    derived2_handle derived2_h;
    base1_public_data_st base1_data = {0};
    base1_public_data_st derived1_data = {0};
    my_rc_e rc;

    printf("\n");

    base1_h = base1_new1();
    if (NULL == base1_h) {
        return (1);
    }

    derived1_h = derived1_new1();
    if (NULL == derived1_h) {
        return (1);
    }
    base1_2_h = derived1_cast_to_base1(derived1_h);
    base2_h = derived1_cast_to_base2(derived1_h);

    derived2_h = derived2_new1();
    if (NULL == derived1_h) {
        return (1);
    }
    derived1_2_h = derived2_cast_to_derived1(derived2_h);
    base1_3_h = derived1_cast_to_base1(derived1_2_h);

    printf("***\n");
    display_base1(base1_h);
    display_base1(base1_2_h);
    display_base1(base1_3_h);
    printf("***\n");

    rc = base1_get_public_data(base1_h, &base1_data);
    if (my_rc_e_is_notok(rc)) {
        return (1);
    }

    rc = base1_get_public_data(base1_2_h, &derived1_data);
    if (my_rc_e_is_notok(rc)) {
        return (1);
    }

    base1_data.val1 = 53;
    derived1_data.val1 = 253;

    rc = base1_set_public_data(base1_h, &base1_data);
    if (my_rc_e_is_notok(rc)) {
        return (1);
    }

    rc = base1_set_public_data(base1_2_h, &derived1_data);
    if (my_rc_e_is_notok(rc)) {
        return (1);
    }

    rc = base2_increase_val1(base2_h);
    if (my_rc_e_is_notok(rc)) {
        return (1);
    }

    rc = base1_increase_val3(base1_h);
    if (my_rc_e_is_notok(rc)) {
        return (1);
    }

    rc = base1_increase_val3(base1_2_h);
    if (my_rc_e_is_notok(rc)) {
        return (1);
    }

    rc = derived1_increase_val4(derived1_h);
    if (my_rc_e_is_notok(rc)) {
        return (1);
    }

    rc = derived1_increase_val4(derived1_2_h);
    if (my_rc_e_is_notok(rc)) {
        return (1);
    }

    printf("\n***\n");
    display_base1(base1_h);
    display_base1(base1_2_h);
    display_base2(base2_h);
    display_base1(base1_3_h);
    printf("***\n");

    base1_delete(base1_h);
    base1_delete(base1_2_h);
    base1_delete(base1_3_h);

    printf("\n");

    return (0);
}
