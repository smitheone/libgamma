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
#include <libgamma.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


#ifdef __GNUC__
# if LIBGAMMA_ERROR_MIN < -46
#  warning New error codes have been added to libgamma.
# endif
# if LIBGAMMA_METHOD_COUNT > 6
#  warning New adjust methods has been added to libgamma
# endif
# if LIBGAMMA_CONNECTOR_TYPE_COUNT > 19
#  warning New connector types have been added to libgamma.
# endif
# if LIBGAMMA_SUBPIXEL_ORDER_COUNT > 6
#  warning New subpixel orders have been added to libgamma.
# endif
# if LIBGAMMA_CRTC_INFO_COUNT > 13
#  warning New CRTC information fields have been added to libgamma.
# endif
#endif


static const char* method_name(int method)
{
  switch (method)
    {
    case LIBGAMMA_METHOD_DUMMY:                 return "dummy";
    case LIBGAMMA_METHOD_X_RANDR:               return "RandR X extension";
    case LIBGAMMA_METHOD_X_VIDMODE:             return "VidMode X extension";
    case LIBGAMMA_METHOD_LINUX_DRM:             return "Linux DRM";
    case LIBGAMMA_METHOD_W32_GDI:               return "Windows GDI";
    case LIBGAMMA_METHOD_QUARTZ_CORE_GRAPHICS:  return "Quartz using CoreGraphics";
    default:
      return "(unknown)";
    }
}


static void list_methods(const char* description, int* methods, int operation)
{
  size_t i, n = libgamma_list_methods(methods, LIBGAMMA_METHOD_COUNT, operation);
  printf("%s:\n", description);
  for (i = 0; i < n; i++)
    printf("  %s\n", method_name(methods[i]));
  printf("\n");
}


static void list_methods_lists(void)
{
  int* methods = malloc(LIBGAMMA_METHOD_COUNT * sizeof(int));
  size_t n = libgamma_list_methods(methods, LIBGAMMA_METHOD_COUNT, 4);
  
  if (n > LIBGAMMA_METHOD_COUNT)
    {
      printf("Warning: you should to recompile the program, libgamma has been updated.\n");
      methods = realloc(methods, n * sizeof(int));
    }
  
  list_methods("Available adjustment methods",               methods, 4);
  list_methods("Available real adjustment methods",          methods, 3);
  list_methods("Available real non-fake adjustment methods", methods, 2);
  list_methods("Recommended adjustment methods",             methods, 1);
  list_methods("Recommended non-fake adjustment methods",    methods, 0);
  
  free(methods);
}


static void method_availability(void)
{
  int method;
  printf("Testing the availability of an non-existing adjustment method: ");
  printf("%s\n", libgamma_is_method_available(9999) ? "available" : "not available");
  for (method = 0; method < LIBGAMMA_METHOD_COUNT; method++)
    {
      printf("Testing the availability of %s: ", method_name(method));
      printf("%s\n", libgamma_is_method_available(method) ? "available" : "not available");
    }
  printf("\n");
}


static void list_default_sites(void)
{
  int method;
  for (method = 0; method < LIBGAMMA_METHOD_COUNT; method++)
    if (libgamma_is_method_available(method))
      {
	printf("Default site for %s:\n", method_name(method));
	printf("  Variable: %s\n", libgamma_method_default_site_variable(method));
	printf("  Site name: %s\n", libgamma_method_default_site(method));
	printf("\n");
      }
}


static void method_capabilities(void)
{
  libgamma_method_capabilities_t caps;
  int method;
  for (method = 0; method < LIBGAMMA_METHOD_COUNT; method++)
    if (libgamma_is_method_available(method))
      {
	printf("Capabilities of %s:\n", method_name(method));
	libgamma_method_capabilities(&caps, method);
	
	printf("  %s: %X\n", "CRTC information",      caps.crtc_information);
	printf("  %s: %s\n", "Default site known",    caps.default_site_known            ? "yes" : "no");
	printf("  %s: %s\n", "Multiple sites",        caps.multiple_sites                ? "yes" : "no");
	printf("  %s: %s\n", "Multiple partitions",   caps.multiple_partitions           ? "yes" : "no");
	printf("  %s: %s\n", "Multiple crtcs",        caps.multiple_crtcs                ? "yes" : "no");
	printf("  %s: %s\n", "Graphics cards",        caps.partitions_are_graphics_cards ? "yes" : "no");
	printf("  %s: %s\n", "Site restore",          caps.site_restore                  ? "yes" : "no");
	printf("  %s: %s\n", "Partition restore",     caps.partition_restore             ? "yes" : "no");
	printf("  %s: %s\n", "CRTC restore",          caps.crtc_restore                  ? "yes" : "no");
	printf("  %s: %s\n", "Identical gamma sizes", caps.identical_gamma_sizes         ? "yes" : "no");
	printf("  %s: %s\n", "Fixed gamma size",      caps.fixed_gamma_size              ? "yes" : "no");
	printf("  %s: %s\n", "Fixed gamma depth",     caps.fixed_gamma_depth             ? "yes" : "no");
	printf("  %s: %s\n", "Real method",           caps.real                          ? "yes" : "no");
	printf("  %s: %s\n", "Fake method",           caps.fake                          ? "yes" : "no");
	printf("\n");
      }
}


static void error_test(void)
{
  int i;
  printf("Testing error API using LIBGAMMA_STATE_UNKNOWN:\n");
  printf("  Expecting %i: %i\n", LIBGAMMA_STATE_UNKNOWN, libgamma_value_of_error("LIBGAMMA_STATE_UNKNOWN"));
  printf("  Expecting %s: %s\n", "LIBGAMMA_STATE_UNKNOWN", libgamma_name_of_error(LIBGAMMA_STATE_UNKNOWN));
  printf("\n");
  printf("Testing libgamma_perror:\n");
  libgamma_perror("  Expecting LIBGAMMA_STATE_UNKNOWN", LIBGAMMA_STATE_UNKNOWN);
  libgamma_perror("  Expecting an description for ENOMEM", ENOMEM);
  libgamma_perror("  Expecting an description for successfulness", 0);
  libgamma_perror("  Expecting an description for ENOMEM", (errno = ENOMEM, LIBGAMMA_ERRNO_SET));
  libgamma_group_gid = 10;
  libgamma_group_name = "test";
  libgamma_perror("  Expecting 'LIBGAMMA_DEVICE_REQUIRE_GROUP: test (10)'", LIBGAMMA_DEVICE_REQUIRE_GROUP);
  libgamma_group_name = NULL;
  libgamma_perror("  Expecting 'LIBGAMMA_DEVICE_REQUIRE_GROUP: 10'", LIBGAMMA_DEVICE_REQUIRE_GROUP);
  printf("\n");
  printf("Testing error code uniqueness: ");
  for (i = -1; i >= LIBGAMMA_ERROR_MIN; i--)
    if (libgamma_value_of_error(libgamma_name_of_error(i)) != i)
      {
	printf("failed\n");
	goto not_unique;
      }
  printf("passed\n");
 not_unique:
  printf("\n");
}


int main(void)
{
  libgamma_site_state_t* site_state = malloc(sizeof(libgamma_site_state_t));
  libgamma_partition_state_t* part_state = malloc(sizeof(libgamma_partition_state_t));
  libgamma_crtc_state_t* crtc_state = malloc(sizeof(libgamma_crtc_state_t));
  int method;
  char* site;
  char* tmp;
  char buf[256];
  int r;
  
  list_methods_lists();
  method_availability();
  list_default_sites();
  method_capabilities();
  error_test();
  
  printf("Select adjustment method:\n");
  for (method = 0; method < LIBGAMMA_METHOD_COUNT; method++)
    printf("    %i:  %s\n", method, method_name(method));
  printf("> ");
  fflush(stdout);
  fgets(buf, sizeof(buf) / sizeof(char), stdin);
  method = atoi(buf);
  
  printf("Select site: ");
  fflush(stdout);
  fgets(buf, sizeof(buf) / sizeof(char), stdin);
  tmp = strchr(buf, '\n');
  if (tmp != NULL)
    *tmp = '\0';
  if (buf[0] == '\0')
    site = NULL;
  else
    {
      site = malloc((strlen(buf) + 1) * sizeof(char));
      memcpy(site, buf, strlen(buf) + 1);
    }
  
  if ((r = libgamma_site_initialise(site_state, method, site)))
    {
      free(site);
      return libgamma_perror("error", r), 1;
    }
  
  if (site_state->partitions_available == 0)
    {
      libgamma_site_free(site_state);
      return printf("No partitions found\n"), 1;
    }
  
  printf("Select partition [0, %lu]: ", site_state->partitions_available - 1);
  fflush(stdout);
  fgets(buf, sizeof(buf) / sizeof(char), stdin);
  
  if ((r = libgamma_partition_initialise(part_state, site_state, (size_t)atoll(buf))))
    {
      libgamma_site_free(site_state);
      return libgamma_perror("error", r), 1;
    }
  
  if (part_state->crtcs_available == 0)
    {
      libgamma_partition_free(part_state);
      libgamma_site_free(site_state);
      return printf("No CRTC:s found\n"), 1;
    }
  
  printf("Select CRTC [0, %lu]: ", part_state->crtcs_available - 1);
  fflush(stdout);
  fgets(buf, sizeof(buf) / sizeof(char), stdin);
  
  if ((r = libgamma_crtc_initialise(crtc_state, part_state, (size_t)atoll(buf))))
    {
      libgamma_partition_free(part_state);
      libgamma_site_free(site_state);
      return libgamma_perror("error", r), 1;
    }
  
  libgamma_crtc_free(crtc_state);
  libgamma_partition_free(part_state);
  libgamma_site_free(site_state);
  return 0;
}

