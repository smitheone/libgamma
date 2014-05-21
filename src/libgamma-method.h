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
#ifndef LIBGAMMA_METHOD_H
#define LIBGAMMA_METHOD_H


#include <stddef.h>
#include <stdint.h>



/**
 * The identifier for the dummy adjustment method.
 * This method can be configured and is useful for
 * testing your program's ability to handle errors.
 */
#ifdef HAVE_GAMMA_METHOD_DUMMY
# define GAMMA_METHOD_DUMMY  0
#endif

/**
 * The identifier for the adjustment method with
 * uses the RandR protocol under the X display server.
 */
#ifdef HAVE_GAMMA_METHOD_X_RANDR
# define GAMMA_METHOD_X_RANDR  1
#endif

/**
 * The identifier for the adjustment method with
 * uses the VidMode protocol under the X display server.
 * This is an older alternative to RandR that can
 * [not verified] work on some drivers that are not
 * supported by RandR, however it can only control the
 * primary CRTC per screen (partition).
 */
#ifdef HAVE_GAMMA_METHOD_X_VIDMODE
# define GAMMA_METHOD_X_VIDMODE  2
#endif

/**
 * The identifier for the Direct Rendering Manager
 * adjustment method that is available in Linux
 * (built in to the Linux kernel with a userland
 * library for access) and is a part of the
 * Direct Rendering Infrastructure. This adjustment
 * method all work when you are in non-graphical
 * mode; however a display server cannnot be
 * started while this is running, but it can be
 * started while a display server is running.
 */
#ifdef HAVE_GAMMA_METHOD_LINUX_DRM
# define GAMMA_METHOD_LINUX_DRM  3
#endif

/**
 * The identifier for the Graphics Device Interface
 * adjustment method that is available in Windows.
 * This method is not well tested; it can be compiled
 * to be available under X.org using a translation layer.
 */
#ifdef HAVE_GAMMA_METHOD_W32_GDI
# define GAMMA_METHOD_W32_GDI  4
#endif

/**
 * The identifier for the Core Graphics adjustment
 * method that is available in Mac OS X that can
 * adjust gamma ramps under the Quartz display server.
 * This method is not well tested; it can be compiled
 * to be available under X.org using a translation layer.
 */
#ifdef HAVE_GAMMA_METHOD_QUARTZ_CORE_GRAPHICS
# define GAMMA_METHOD_QUARTZ_CORE_GRAPHICS  5
#endif


/**
 * The index of the last gamma method, neither it
 * nor any index before it may actually be supported
 * as it could have been disabled at compile-time
 */
#define GAMMA_METHOD_MAX  5



/**
 * Capabilities of adjustment methods
 */
typedef struct libgamma_method_capabilities {
  
  /**
   * OR of the CRTC information fields in `libgamma_crtc_information_t`
   * that may (but can fail) be read successfully
   */
  int32_t crtc_information;
  
  /**
   * Whether the default site is known, if true the site is integrated
   * to the system or can be determined using environment variables
   */
  int default_site_known : 1;
  
  /**
   * Whether the adjustment method supports multiple sites rather
   * than just the default site
   */
  int multiple_sites : 1;
  
  /**
   * Whether the adjustment method supports multiple partitions
   * per site
   */
  int multiple_partitions : 1;
  
  /**
   * Whether the adjustment method supports multiple CRTC:s
   * per partition per site
   */
  int multiple_crtcs : 1;
  
  /**
   * Whether the adjustment method supports `libgamma_site_restore`
   */
  int site_restore : 1;
  
  /**
   * Whether the adjustment method supports `libgamma_partition_restore`
   */
  int partition_restore : 1;
  
  /**
   * Whether the adjustment method supports `libgamma_crtc_restore`
   */
  int crtc_restore : 1;
  
  /**
   * Whether the `gamma_size` field in `libgamma_crtc_information_t`
   * will always be filled with the same value for the adjustment method
   */
  int fixed_gamma_size : 1;
  
  /**
   * Whether the `gamma_depth` field in `libgamma_crtc_information_t`
   * will always be filled with the same value for the adjustment method
   */
  int fixed_gamma_depth : 1;
  
  /**
   * Whether the adjustment method will actually perform adjustments
   */
  int real : 1;
  
  /**
   * Whether the adjustment method is implement using a translation layer
   */
  int fake : 1;
  
} libgamma_method_capabilities_t;


/**
 * Site state
 * 
 * On operating systems that integrate a graphical environment
 * there is usally just one site. However, one systems with
 * pluggable graphics, like Unix-like systems such as GNU/Linux
 * and the BSD:s, there can usually be any (feasible) number of
 * sites. In X.org parlance they are called displays.
 */
typedef struct libgamma_site_state {
  
  /**
   * Adjustment method implementation specific data.
   * You as a user of this library should not touch this.
   */
  void* data;
  
  /**
   * This field specifies, for the methods if this library,
   * which adjustment method (display server and protocol)
   * is used to adjust the gamma ramps.
   */
  int method;
  
  /**
   * The site identifier. It can either be `NULL` or a string.
   * `NULL` indicates the default site. On systems like the
   * Unix-like systems, where the graphics are pluggable, this
   * is usally resolved by an environment variable, such as
   * "DISPLAY" for X.org.
   */
  char* site;
  
  /**
   * The number of partitions that is available on this site.
   * Probably the majority of display server only one partition
   * per site. However, X.org can, and traditional used to have
   * on multi-headed environments, multiple partitions per site.
   * In X.org partitions are called 'screens'. It is not to be
   * confused with monitor. A screen is a collection of monitors,
   * and the mapping from monitors to screens is a surjection.
   * On hardware-level adjustment methods, such as Direct
   * Rendering Manager, a partition is a graphics card.
   */
  size_t partitions_available;
  
} libgamma_site_state_t;


/**
 * Partition state
 * 
 * Probably the majority of display server only one partition
 * per site. However, X.org can, and traditional used to have
 * on multi-headed environments, multiple partitions per site.
 * In X.org partitions are called 'screens'. It is not to be
 * confused with monitor. A screen is a collection of monitors,
 * and the mapping from monitors to screens is a surjection.
 * On hardware-level adjustment methods, such as Direct
 * Rendering Manager, a partition is a graphics card.
 */
typedef struct libgamma_partition_state {
  
  /**
   * Adjustment method implementation specific data.
   * You as a user of this library should not touch this.
   */
  void* data;
  
  /**
   * The site this partition belongs to
   */
  libgamma_site_state_t* site;
  
  /**
   * The index of the partition
   */
  size_t partition;
  
  /**
   * The number of CRTC:s that are available under this
   * partition. Note that the CRTC:s are not necessarily
   * online.
   */
  size_t crtcs_available;
  
} libgamma_partition_state_t;


/**
 * Cathode ray tube controller state
 * 
 * The CRTC controls the gamma ramps for the
 * monitor that is plugged in to the connector
 * that the CRTC belongs to
 */
typedef struct libgamma_crtc_state {
  
  /**
   * Adjustment method implementation specific data.
   * You as a user of this library should not touch this.
   */
  void* data;
  
  /**
   * The partition this CRTC belongs to
   */
  libgamma_partition_state_t* site;
  
  /**
   * The index of the CRTC within its partition.
   */
  size_t crtc;
  
} libgamma_crtc_state_t;



/**
 * For a `libgamma_crtc_information_t` fill in the
 * values for `edid` and `edid_length` and report errors to `edid_error`
 */
#define CRTC_INFO_EDID  (1 << 0)

/**
 * For a `libgamma_crtc_information_t` fill in the
 * value for `width_mm` and report errors to `width_mm_error`
 */
#define CRTC_INFO_WIDTH_MM  (1 << 1)

/**
 * For a `libgamma_crtc_information_t` fill in the
 * value for `height_mm` and report errors to `height_mm_error`
 */
#define CRTC_INFO_HEIGHT_MM  (1 << 2)

/**
 * For a `libgamma_crtc_information_t` fill in the
 * value for `width_mm_edid` and report errors to `width_mm_edid_error`
 */
#define CRTC_INFO_WIDTH_MM_EDID  (1 << 3)

/**
 * For a `libgamma_crtc_information_t` fill in the
 * value for `height_mm_edid` and report errors to `height_mm_edid_error`
 */
#define CRTC_INFO_HEIGHT_MM_EDID  (1 << 4)

/**
 * For a `libgamma_crtc_information_t` fill in the
 * value for `gamma_size` and report errors to `gamma_size_error`
 */
#define CRTC_INFO_GAMMA_SIZE  (1 << 5)

/**
 * For a `libgamma_crtc_information_t` fill in the
 * value for `gamma_depth` and report errors to `gamma_depth_error`
 */
#define CRTC_INFO_GAMMA_DEPTH  (1 << 6)

/**
 * For a `libgamma_crtc_information_t` fill in the
 * value for `gamma_support` and report errors to `gamma_support_error`
 */
#define CRTC_INFO_GAMMA_SUPPORT  (1 << 7)

/**
 * For a `libgamma_crtc_information_t` fill in the
 * value for `subpixel_order` and report errors to `subpixel_order_error`
 */
#define CRTC_INFO_SUBPIXEL_ORDER  (1 << 8)

/**
 * For a `libgamma_crtc_information_t` fill in the
 * value for `active` and report errors to `active_error`
 */
#define CRTC_INFO_ACTIVE  (1 << 9)

/**
 * For a `libgamma_crtc_information_t` fill in the
 * value for `connector_name` and report errors to `connector_name_error`
 */
#define CRTC_INFO_CONNECTOR_NAME  (1 << 10)

/**
 * For a `libgamma_crtc_information_t` fill in the
 * value for `connector_type` and report errors to `connector_type_error`
 */
#define CRTC_INFO_CONNECTOR_TYPE  (1 << 11)

/**
 * For a `libgamma_crtc_information_t` fill in the
 * values for `gamma_red`, `gamma_green` and `gamma_blue`
 * and report errors to `connector_type_error`
 */
#define CRTC_INFO_GAMMA  (1 << 12)


/**
 * Cathode ray tube controller information data structure
 */
typedef struct libgamma_crtc_information {
  
  /**
   * The Extended Display Identification Data associated with
   * the attached monitor. This is raw byte array that is usually
   * 128 bytes long. It is not NUL-terminate, rather its length
   * is stored in `edid_size`.
   */
  unsigned char* edid;
  
  /**
   * The length of `edid`
   */
  size_t edid_length;
  
  /**
   * Zero on success, positive it holds the value `errno` had
   * when the reading failed, otherwise (negative) the value
   * of an error identifier provided by this library
   */
  int edid_error;
  
  
  /**
   * The phyical width, in millimetres, of the viewport of the
   * attached monitor, as reported by the adjustment method. This
   * value may be incorrect, which is a known issue with the X
   * server where it is the result of the X server attempting
   * the estimate the size on its own.
   * Zero means that its is not applicable, which is the case
   * for projectors.
   */
  size_t width_mm;
  
  /**
   * Zero on success, positive it holds the value `errno` had
   * when the reading failed, otherwise (negative) the value
   * of an error identifier provided by this library
   */
  int width_mm_error;
  
  
  /**
   * The phyical height, in millimetres, of the viewport of the
   * attached monitor, as reported by the adjustment method. This
   * value may be incorrect, which is a known issue with the X
   * server where it is the result of the X server attempting
   * the estimate the size on its own.
   * Zero means that its is not applicable, which is the case
   * for projectors.
   */
  size_t height_mm;
  
  /**
   * Zero on success, positive it holds the value `errno` had
   * when the reading failed, otherwise (negative) the value
   * of an error identifier provided by this library
   */
  int height_mm_error;
  
  
  /**
   * The phyical width, in millimetres, of the viewport of the
   * attached monitor, as reported by it the monitor's Extended
   * Display Information Data. This value can only contain whole
   * centimetres, which means that the result is always zero
   * modulus ten. However, this could change with revisions of
   * the EDID structure.
   * Zero means that its is not applicable, which is the case
   * for projectors.
   */
  size_t width_mm_edid;
  
  /**
   * Zero on success, positive it holds the value `errno` had
   * when the reading failed, otherwise (negative) the value
   * of an error identifier provided by this library
   */
  int width_mm_edid_error;
  
  
  /**
   * The phyical height, in millimetres, of the viewport of the
   * attached monitor, as reported by it the monitor's Extended
   * Display Information Data. This value can only contain whole
   * centimetres, which means that the result is always zero
   * modulus ten. However, this could change with revisions of
   * the EDID structure.
   * Zero means that its is not applicable, which is the case
   * for projectors.
   */
  size_t height_mm_edid;
  
  /**
   * Zero on success, positive it holds the value `errno` had
   * when the reading failed, otherwise (negative) the value
   * of an error identifier provided by this library
   */
  int height_mm_edid_error;
  
  
  /**
   * The size of the encoding axes of gamma ramps
   */
  size_t gamma_size;
  
  /**
   * Zero on success, positive it holds the value `errno` had
   * when the reading failed, otherwise (negative) the value
   * of an error identifier provided by this library
   */
  int gamma_size_error;
  
  
  /**
   * The bit-depth of the value axes of gamma ramps
   */
  size_t gamma_depth;
  
  /**
   * Zero on success, positive it holds the value `errno` had
   * when the reading failed, otherwise (negative) the value
   * of an error identifier provided by this library
   */
  int gamma_depth_error;
  
  
  /**
   * Non-zero gamma ramp adjustments are supported
   */
  int gamma_support;
  
  /**
   * Zero on success, positive it holds the value `errno` had
   * when the reading failed, otherwise (negative) the value
   * of an error identifier provided by this library
   */
  int gamma_support_error;
  
  
  /**
   * The layout of the subpixels.
   * You cannot count on this value, but it is provided
   * anyway as a means of distinguishing monitors.
   */
  int subpixel_order;
  
  /**
   * Zero on success, positive it holds the value `errno` had
   * when the reading failed, otherwise (negative) the value
   * of an error identifier provided by this library
   */
  int subpixel_order_error;
  
  
  /**
   * Whether there is a monitors connected to the CRTC
   */
  int active;
  
  /**
   * Zero on success, positive it holds the value `errno` had
   * when the reading failed, otherwise (negative) the value
   * of an error identifier provided by this library
   */
  int active_error;
  
  
  /**
   * The name of the connector as designated by the display
   * server or as give by this library in case the display
   * server lacks this feature
   */
  char* connector_name;
  
  /**
   * Zero on success, positive it holds the value `errno` had
   * when the reading failed, otherwise (negative) the value
   * of an error identifier provided by this library
   */
  int connector_name_error;
  
  
  /**
   * The type of the connector that is associated with the CRTC
   */
  int connector_type;
  
  /**
   * Zero on success, positive it holds the value `errno` had
   * when the reading failed, otherwise (negative) the value
   * of an error identifier provided by this library
   */
  int connector_type_error;
  
  
  /**
   * The gamma characteristics of the monitor as reported
   * in its Extended Display Information Data. The value
   * holds the value for the red channel. If you do not have
   * and more accurate measurement of the gamma for the
   * monitor this could be used to give a rought gamma
   * correction; simply divide the value with 2.2 and use
   * the result for the red channel in the gamma correction.
   */
  float gamma_red;
  
  /**
   * The gamma characteristics of the monitor as reported
   * in its Extended Display Information Data. The value
   * holds the value for the green channel. If you do not have
   * and more accurate measurement of the gamma for the
   * monitor this could be used to give a rought gamma
   * correction; simply divide the value with 2.2 and use
   * the result for the green channel in the gamma correction.
   */
  float gamma_green;
  
  /**
   * The gamma characteristics of the monitor as reported
   * in its Extended Display Information Data. The value
   * holds the value for the blue channel. If you do not have
   * and more accurate measurement of the gamma for the
   * monitor this could be used to give a rought gamma
   * correction; simply divide the value with 2.2 and use
   * the result for the blue channel in the gamma correction.
   */
  float gamma_blue;
  
  /**
   * Zero on success, positive it holds the value `errno` had
   * when the reading failed, otherwise (negative) the value
   * of an error identifier provided by this library
   */
  int gamma_error;
  
} libgamma_crtc_information_t;



/**
 * Gamma ramp structure for 16-bit gamma ramps
 */
typedef struct libgamma_gamma_ramps
{
  /**
   * The size of `red`
   */
  size_t red_size;
  
  /**
   * The size of `green`
   */
  size_t green_size;
  
  /**
   * The size of `blue`
   */
  size_t blue_size;
  
  /**
   * The gamma ramp for the red channel
   */
  uint16_t* red;
  
  /**
   * The gamma ramp for the green channel
   */
  uint16_t* green;
  
  /**
   * The gamma ramp for the blue channel
   */
  uint16_t* blue;
  
} libgamma_gamma_ramps_t;


/**
 * Gamma ramp structure for 32-bit gamma ramps
 */
typedef struct libgamma_gamma_ramps32
{
  /**
   * The size of `red`
   */
  size_t red_size;
  
  /**
   * The size of `green`
   */
  size_t green_size;
  
  /**
   * The size of `blue`
   */
  size_t blue_size;
  
  /**
   * The gamma ramp for the red channel
   */
  uint32_t* red;
  
  /**
   * The gamma ramp for the green channel
   */
  uint32_t* green;
  
  /**
   * The gamma ramp for the blue channel
   */
  uint32_t* blue;
  
} libgamma_gamma_ramps32_t;


/**
 * Gamma ramp structure for 64-bit gamma ramps
 */
typedef struct libgamma_gamma_ramps64
{
  /**
   * The size of `red`
   */
  size_t red_size;
  
  /**
   * The size of `green`
   */
  size_t green_size;
  
  /**
   * The size of `blue`
   */
  size_t blue_size;
  
  /**
   * The gamma ramp for the red channel
   */
  uint64_t* red;
  
  /**
   * The gamma ramp for the green channel
   */
  uint64_t* green;
  
  /**
   * The gamma ramp for the blue channel
   */
  uint64_t* blue;
  
} libgamma_gamma_ramps64_t;


#endif

