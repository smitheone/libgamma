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
#ifndef LIBGAMMA_GAMMA_QUARTZ_CG_H
#define LIBGAMMA_GAMMA_QUARTZ_CG_H

#ifndef HAVE_LIBGAMMA_METHOD_QUARTZ_CORE_GRAPHICS
# error Including gamma-quartz-cg.h without HAVE_LIBGAMMA_METHOD_QUARTZ_CORE_GRAPHICS
#endif


#include "libgamma-method.h"


/**
 * Return the capabilities of the adjustment method.
 * 
 * @param  this  The data structure to fill with the method's capabilities.
 */
void libgamma_quartz_cg_method_capabilities(libgamma_method_capabilities_t* restrict this);

/**
 * Initialise an allocated site state.
 * 
 * @param   this    The site state to initialise.
 * @param   site    The site identifier, unless it is `NULL` it must a
 *                  `free`:able. Once the state is destroyed the library
 *                  will attempt to free it. There you should not free
 *                  it yourself, and it must not be a string constant
 *                  or allocate on the stack. Note however that it will
 *                  not be free:d if this function fails.
 * @return          Zero on success, otherwise (negative) the value of an
 *                  error identifier provided by this library.
 */
int libgamma_quartz_cg_site_initialise(libgamma_site_state_t* restrict this,
				       char* restrict site);

/**
 * Release all resources held by a site state.
 * 
 * @param  this  The site state.
 */
void libgamma_quartz_cg_site_destroy(libgamma_site_state_t* restrict this);

/**
 * Restore the gamma ramps all CRTC:s with a site to the system settings.
 * 
 * @param   this  The site state.
 * @return        Zero on success, otherwise (negative) the value of an
 *                error identifier provided by this library.
 */
int libgamma_quartz_cg_site_restore(libgamma_site_state_t* restrict this);


/**
 * Initialise an allocated partition state.
 * 
 * @param   this       The partition state to initialise.
 * @param   site       The site state for the site that the partition belongs to.
 * @param   partition  The the index of the partition within the site
 * @return             Zero on success, otherwise (negative) the value of an
 *                     error identifier provided by this library.
 */
int libgamma_quartz_cg_partition_initialise(libgamma_partition_state_t* restrict this,
					    libgamma_site_state_t* restrict site, size_t partition);

/**
 * Release all resources held by a partition state.
 * 
 * @param  this  The partition state.
 */
void libgamma_quartz_cg_partition_destroy(libgamma_partition_state_t* restrict this);

/**
 * Restore the gamma ramps all CRTC:s with a partition to the system settings.
 * 
 * @param   this  The partition state.
 * @return        Zero on success, otherwise (negative) the value of an
 *                error identifier provided by this library.
 */
int libgamma_quartz_cg_partition_restore(libgamma_partition_state_t* restrict this);


/**
 * Initialise an allocated CRTC state.
 * 
 * @param   this       The CRTC state to initialise.
 * @param   partition  The partition state for the partition that the CRTC belongs to.
 * @param   crtc       The the index of the CRTC within the site.
 * @return             Zero on success, otherwise (negative) the value of an
 *                     error identifier provided by this library.
 */
int libgamma_quartz_cg_crtc_initialise(libgamma_crtc_state_t* restrict this,
				       libgamma_partition_state_t* restrict partition, size_t crtc) __attribute__((pure));

/**
 * Release all resources held by a CRTC state.
 * 
 * @param  this  The CRTC state.
 */
void libgamma_quartz_cg_crtc_destroy(libgamma_crtc_state_t* restrict this) __attribute__((const));

/**
 * Restore the gamma ramps for a CRTC to the system settings for that CRTC.
 * 
 * @param   this  The CRTC state.
 * @return        Zero on success, otherwise (negative) the value of an
 *                error identifier provided by this library.
 */
int libgamma_quartz_cg_crtc_restore(libgamma_crtc_state_t* restrict this);


/**
 * Read information about a CRTC.
 * 
 * @param   this    Instance of a data structure to fill with the information about the CRTC.
 * @param   crtc    The state of the CRTC whose information should be read.
 * @param   fields  OR:ed identifiers for the information about the CRTC that should be read.
 * @return          Zero on success, -1 on error. On error refer to the error reports in `this`.
 */
int libgamma_quartz_cg_get_crtc_information(libgamma_crtc_information_t* restrict this,
					    libgamma_crtc_state_t* restrict crtc, int32_t fields);

/**
 * Get the current gamma ramps for a CRTC, `float` version.
 * 
 * @param   this   The CRTC state.
 * @param   ramps  The gamma ramps to fill with the current values.
 * @return         Zero on success, otherwise (negative) the value of an
 *                 error identifier provided by this library.
 */
int libgamma_quartz_cg_crtc_get_gamma_rampsf(libgamma_crtc_state_t* restrict this,
					     libgamma_gamma_rampsf_t* restrict ramps);

/**
 * Set the gamma ramps for a CRTC, `float` version.
 * 
 * @param   this   The CRTC state.
 * @param   ramps  The gamma ramps to apply.
 * @return         Zero on success, otherwise (negative) the value of an
 *                 error identifier provided by this library.
 */
int libgamma_quartz_cg_crtc_set_gamma_rampsf(libgamma_crtc_state_t* restrict this,
					     libgamma_gamma_rampsf_t ramps);


#endif

