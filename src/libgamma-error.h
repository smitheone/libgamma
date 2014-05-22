/**
 * libgamma — Display server abstraction layer for gamma ramp adjustments
 * Copyright © 2014  Mattias Andrée (maandree@member.fsf.org)
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


/**
 * The selected adjustment method does not exist
 * or has been excluded at compile-time
 */
#define LIBGAMMA_NO_SUCH_ADJUSTMENT_METHOD  (-1)

/**
 * `errno` has be set with a standard error number
 * to indicate the what has gone wrong
 */
#define LIBGAMMA_ERRNO_SET  (-2)

/**
 * The selected site does not exist
 */
#define LIBGAMMA_NO_SUCH_SITE  (-3)

/**
 * The selected partition does not exist
 */
#define LIBGAMMA_NO_SUCH_PARTITION  (-4)

/**
 * The selected CRTC does not exist
 */
#define LIBGAMMA_NO_SUCH_CRTC  (-5)

/**
 * Counter overflowed when counting the number of available items
 */
#define LIBGAMMA_IMPOSSIBLE_AMOUNT  (-6)

/**
 * The selected connector is disabled, it does not have a CRTC
 */
#define LIBGAMMA_CONNECTOR_DISABLED  (-7)

/**
 * The selected CRTC could not be opened, reason unknown
 */
#define LIBGAMMA_OPEN_CRTC_FAILED  (-8)

/**
 * The CRTC information field is not supported by the adjustment method
 */
#define LIBGAMMA_CRTC_INFO_NOT_SUPPORTED  (-9)

/**
 * Failed to read the current gamma ramps for the selected CRTC, reason unknown
 */
#define LIBGAMMA_GAMMA_RAMP_READ_FAILED  (-10)

/**
 * Failed to write the current gamma ramps for the selected CRTC, reason unknown
 */
#define LIBGAMMA_GAMMA_RAMP_WRITE_FAILED  (-11)

/**
 * The specified ramp sizes does not match the ramps sizes returned by the
 * adjustment methods in response to the query/command
 */
#define LIBGAMMA_GAMMA_RAMP_SIZE_CHANGED  (-12)

/**
 * The specified ramp sizes are not identical which is required by the adjustment method
 * (Only returned in debug mode)
 */
#define LIBGAMMA_MIXED_GAMMA_RAMP_SIZE  (-13)

/**
 * The specified ramp sizes are not supported by the adjustment method
 * (Only returned in debug mode)
 */
#define LIBGAMMA_WRONG_GAMMA_RAMP_SIZE  (-14)

/**
 * The adjustment method reported that the gamma ramps size is 1 or 0
 */
#define LIBGAMMA_SINGLETON_GAMMA_RAMP  (-15)

/**
 * The adjustment method failed to list available CRTC:s, reason unknown
 */
#define LIBGAMMA_LIST_CRTCS_FAILED  (-16)



#endif

