/**
 * libgamma -- Display server abstraction layer for gamma ramp adjustments
 * Copyright (C) 2014, 2015  Mattias Andrée (maandree@member.fsf.org)
 * 
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBGAMMA_ERROR_H
#define LIBGAMMA_ERROR_H

#if !defined(LIBGAMMA_CONFIG_H) && !defined(DEBUG)
# error libgamma-error.h should not be included directly, include libgamma.h instead
#endif


#include <sys/types.h>

#ifndef __GCC__
# define __attribute__(x)
#endif


/**
 * Group that the user needs to be a member of if
 * `LIBGAMMA_DEVICE_REQUIRE_GROUP` is returned.
 */
#ifndef __WIN32__
extern __thread gid_t libgamma_group_gid;
gid_t libgamma_group_gid_get(void) __attribute__((pure));
void libgamma_group_gid_set(gid_t value);
#else
extern short libgamma_group_gid;
#endif

/**
 * Group that the user needs to be a member of if
 * `LIBGAMMA_DEVICE_REQUIRE_GROUP` is returned,
 * `NULL` if the name of the group `libgamma_group_gid`
 * cannot be determined.
 */
#ifndef __WIN32__
extern __thread const char* libgamma_group_name;
const char* libgamma_group_name_get(void) __attribute__((pure));
void libgamma_group_name_set(const char* value);
#else
extern const char* libgamma_group_name;
#endif


/**
 * `errno` has be set with a standard error number
 * to indicate the what has gone wrong.
 */
#define LIBGAMMA_ERRNO_SET  (-1)

/**
 * The selected adjustment method does not exist
 * or has been excluded at compile-time.
 */
#define LIBGAMMA_NO_SUCH_ADJUSTMENT_METHOD  (-2)

/**
 * The selected site does not exist.
 */
#define LIBGAMMA_NO_SUCH_SITE  (-3)

/**
 * The selected partition does not exist.
 */
#define LIBGAMMA_NO_SUCH_PARTITION  (-4)

/**
 * The selected CRTC does not exist.
 */
#define LIBGAMMA_NO_SUCH_CRTC  (-5)

/**
 * Counter overflowed when counting the number
 * of available items.
 */
#define LIBGAMMA_IMPOSSIBLE_AMOUNT  (-6)

/**
 * The selected connector is disabled, it does
 * not have a CRTC.
 */
#define LIBGAMMA_CONNECTOR_DISABLED  (-7)

/**
 * The selected CRTC could not be opened,
 * reason unknown.
 */
#define LIBGAMMA_OPEN_CRTC_FAILED  (-8)

/**
 * The CRTC information field is not supported
 * by the adjustment method.
 */
#define LIBGAMMA_CRTC_INFO_NOT_SUPPORTED  (-9)

/**
 * Failed to read the current gamma ramps for
 * the selected CRTC, reason unknown.
 */
#define LIBGAMMA_GAMMA_RAMP_READ_FAILED  (-10)

/**
 * Failed to write the current gamma ramps for
 * the selected CRTC, reason unknown.
 */
#define LIBGAMMA_GAMMA_RAMP_WRITE_FAILED  (-11)

/**
 * The specified ramp sizes does not match the
 * ramps sizes returned by the adjustment methods
 * in response to the query/command.
 */
#define LIBGAMMA_GAMMA_RAMP_SIZE_CHANGED  (-12)

/**
 * The specified ramp sizes are not identical
 * which is required by the adjustment method.
 * (Only returned in debug mode.)
 */
#define LIBGAMMA_MIXED_GAMMA_RAMP_SIZE  (-13)

/**
 * The specified ramp sizes are not supported
 * by the adjustment method.
 * (Only returned in debug mode.)
 */
#define LIBGAMMA_WRONG_GAMMA_RAMP_SIZE  (-14)

/**
 * The adjustment method reported that the gamma
 * ramps size is 1, or perhaps even zero or negative.
 */
#define LIBGAMMA_SINGLETON_GAMMA_RAMP  (-15)

/**
 * The adjustment method failed to list
 * available CRTC:s, reason unknown.
 */
#define LIBGAMMA_LIST_CRTCS_FAILED  (-16)

/**
 * Failed to acquire mode resources from the
 * adjustment method.
 */
#define LIBGAMMA_ACQUIRING_MODE_RESOURCES_FAILED  (-17)

/**
 * The adjustment method reported that a negative
 * number of partitions exists in the site.
 */
#define LIBGAMMA_NEGATIVE_PARTITION_COUNT  (-18)

/**
 * The adjustment method reported that a negative
 * number of CRTC:s exists in the partition.
 */
#define LIBGAMMA_NEGATIVE_CRTC_COUNT  (-19)

/**
 * Device cannot be access becauses of
 * insufficient permissions.
 */
#define LIBGAMMA_DEVICE_RESTRICTED  (-20)

/**
 * Device cannot be access, reason unknown.
 */
#define LIBGAMMA_DEVICE_ACCESS_FAILED  (-21)

/**
 * Device cannot be access, membership of the
 * `libgamma_group_gid` (named by `libgamma_group_name`
 * (can be `NULL`, if so `errno` may have been set
 * to tell why)) is required.
 */
#define LIBGAMMA_DEVICE_REQUIRE_GROUP  (-22)

/**
 * The graphics card appear to have been removed.
 */
#define LIBGAMMA_GRAPHICS_CARD_REMOVED  (-23)

/**
 * The state of the requested information is unknown.
 */
#define LIBGAMMA_STATE_UNKNOWN  (-24)

/**
 * Failed to determine which connector the
 * CRTC belongs to.
 */
#define LIBGAMMA_CONNECTOR_UNKNOWN  (-25)

/**
 * The detected connector type is not listed
 * in this library and has to be updated.
 */
#define LIBGAMMA_CONNECTOR_TYPE_NOT_RECOGNISED  (-26)

/**
 * The detected subpixel order is not listed
 * in this library and has to be updated.
 */
#define LIBGAMMA_SUBPIXEL_ORDER_NOT_RECOGNISED  (-27)

/**
 * The length of the EDID does not match that
 * of any supported EDID structure revision.
 */
#define LIBGAMMA_EDID_LENGTH_UNSUPPORTED  (-28)

/**
 * The magic number in the EDID does not match
 * that of any supported EDID structure revision.
 */
#define LIBGAMMA_EDID_WRONG_MAGIC_NUMBER  (-29)

/**
 * The EDID structure revision used by the
 * monitor is not supported.
 */
#define LIBGAMMA_EDID_REVISION_UNSUPPORTED  (-30)

/**
 * The gamma characteristics field in the EDID
 * is left unspecified.
 * (This could be considered a non-error.)
 */
#define LIBGAMMA_GAMMA_NOT_SPECIFIED  (-31)

/**
 * The checksum in the EDID is incorrect, all
 * request information has been provided
 * by you cannot count on it.
 */
#define LIBGAMMA_EDID_CHECKSUM_ERROR  (-32)

/**
 * Both of the errors `LIBGAMMA_GAMMA_NOT_SPECIFIED`
 * and `LIBGAMMA_EDID_CHECKSUM_ERROR` have occurred.
 */
#define LIBGAMMA_GAMMA_NOT_SPECIFIED_AND_EDID_CHECKSUM_ERROR  (-33)

/**
 * Failed to query the gamma ramps size from the
 * adjustment method, reason unknown.
 */
#define LIBGAMMA_GAMMA_RAMPS_SIZE_QUERY_FAILED  (-34)

/**
 * The selected partition could not be opened,
 * reason unknown.
 */
#define LIBGAMMA_OPEN_PARTITION_FAILED  (-35)

/**
 * The selected site could not be opened,
 * reason unknown.
 */
#define LIBGAMMA_OPEN_SITE_FAILED  (-36)

/**
 * Failed to query the adjustment method for
 * its protocol version, reason unknown.
 */
#define LIBGAMMA_PROTOCOL_VERSION_QUERY_FAILED  (-37)

/**
 * The adjustment method's version of its
 * protocol is not supported.
 */
#define LIBGAMMA_PROTOCOL_VERSION_NOT_SUPPORTED  (-38)

/**
 * The adjustment method failed to list
 * available partitions, reason unknown.
 */
#define LIBGAMMA_LIST_PARTITIONS_FAILED  (-39)

/**
 * Partition exists by index, but the partition
 * at that index does not exist.
 */
#define LIBGAMMA_NULL_PARTITION  (-40)

/**
 * There is not monitor connected to the
 * connector of the selected CRTC.
 */
#define LIBGAMMA_NOT_CONNECTED  (-41)

/**
 * Data extraction from a reply from the
 * adjustment method failed, reason unknown.
 */
#define LIBGAMMA_REPLY_VALUE_EXTRACTION_FAILED  (-42)

/**
 * No EDID property was found on the output.
 */
#define LIBGAMMA_EDID_NOT_FOUND  (-43)

/**
 * Failed to list properties on the output,
 * reason unknown.
 */
#define LIBGAMMA_LIST_PROPERTIES_FAILED  (-44)

/**
 * Failed to query a property's value from
 * the output, reason unknown.
 */
#define LIBGAMMA_PROPERTY_VALUE_QUERY_FAILED  (-45)

/**
 * A request for information on an output
 * failed, reason unknown.
 */
#define LIBGAMMA_OUTPUT_INFORMATION_QUERY_FAILED  (-46)



/**
 * The number of the libgamma error with the
 * lowest number. If this is lower than the
 * number your program thinks it should be sould
 * update your program for new errors.
 */
#define LIBGAMMA_ERROR_MIN  (-46)



/**
 * Prints an error to stderr in a `perror` fashion,
 * however this function will not translate the `libgamma`
 * errors into human-readable strings, it will simply
 * print the name of the error. If the value `error_code`
 * is the value of `LIBGAMMA_ERRNO_SET`, `perror` will be
 * used to print the current error stored in `errno`.
 * If `error_code` is non-negative (an `errno` value`), that
 * value will be stored in `errno` and `perror` will be
 * used to print it. Additionally, if the `error_code` is
 * the value of `LIBGAMMA_DEVICE_REQUIRE_GROUP` the
 * required group will be printed with its numerical value
 * and, if known, its name.
 * 
 * @param  name   The text to add at the beginning.
 * @param  value  The error code, may be an `errno` value.
 */
void libgamma_perror(const char* name, int error_code);

/**
 * Returns the name of the definition associated with a `libgamma` error code.
 * 
 * @param   value  The error code.
 * @return         The name of the definition associated with the error code,
 *                 `NULL` if the error code does not exist. The return string
 *                 should not be `free`:d.
 */
const char* libgamma_name_of_error(int value) __attribute__((const));

/**
 * Return the value of a `libgamma` error definition refered to by name.
 * 
 * @param   name  The name of the definition associated with the error code.
 * @return        The error code, zero if the name is `NULL`
 *                or does not refer to a `libgamma` error.
 */
int libgamma_value_of_error(const char* name) __attribute__((const));



#ifndef __GCC__
# undef __attribute__
#endif

#endif

