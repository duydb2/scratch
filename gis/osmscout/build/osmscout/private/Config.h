// Modified auto-generated Config.h to get rid of some
// stuff not supported on ARM / qnx

/* Support AVX (Advanced Vector Extensions) instructions */
// #define HAVE_AVX /**/

/* Define to 1 if you have the declaration of `atanh(double)', and to 0 if you
   don't. */
#define HAVE_DECL_ATANH 1

/* Define to 1 if you have the declaration of `log2(double)', and to 0 if you
   don't. */
#define HAVE_DECL_LOG2 1

/* Define to 1 if you have the declaration of `lround(double)', and to 0 if
   you don't. */
#define HAVE_DECL_LROUND 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if fseeko (and presumably ftello) exists and is declared. */
#define HAVE_FSEEKO 1

/* Define to 1 if the system has the type `int16_t'. */
#define HAVE_INT16_T 1

/* Define to 1 if the system has the type `int32_t'. */
#define HAVE_INT32_T 1

/* Define to 1 if the system has the type `int64_t'. */
#define HAVE_INT64_T 1

/* Define to 1 if the system has the type `int8_t'. */
#define HAVE_INT8_T 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `mmap' function. */
#define HAVE_MMAP 1

/* Support MMX instructions */
// #define HAVE_MMX /**/

/* Define to 1 if you have the `posix_fadvise' function. */
#define HAVE_POSIX_FADVISE 1

/* Define to 1 if you have the `posix_madvise' function. */
#define HAVE_POSIX_MADVISE 1

/* Support SSE (Streaming SIMD Extensions) instructions */
// #define HAVE_SSE /**/

/* Support SSE2 (Streaming SIMD Extensions 2) instructions */
// #define HAVE_SSE2 /**/

/* Support SSE3 (Streaming SIMD Extensions 3) instructions */
// #define HAVE_SSE3 /**/

/* Support SSE4.1 (Streaming SIMD Extensions 4.1) instructions */
// #define HAVE_SSE41 /**/

/* Support SSE4.2 (Streaming SIMD Extensions 4.2) instructions */
// #define HAVE_SSE42 1

/* Support SSSE3 (Supplemental Streaming SIMD Extensions 3) instructions */
// #define HAVE_SSSE3 /**/

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if the system has the type `std::wstring'. */
#define HAVE_STD__WSTRING 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if the system has the type `uint16_t'. */
#define HAVE_UINT16_T 1

/* Define to 1 if the system has the type `uint32_t'. */
#define HAVE_UINT32_T 1

/* Define to 1 if the system has the type `uint64_t'. */
#define HAVE_UINT64_T 1

/* Define to 1 if the system has the type `uint8_t'. */
#define HAVE_UINT8_T 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the <unordered_map> header file. */
// #define HAVE_UNORDERED_MAP 1

/* Define to 1 if you have the <unordered_set> header file. */
// #define HAVE_UNORDERED_SET 1

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
// #define LT_OBJDIR ".libs/"

/* libosmscout uses special gcc compiler features to export symbols */
#define OSMSCOUT_EXPORT_SYMBOLS 1

/* int16_t is available */
#define OSMSCOUT_HAVE_INT16_T 1

/* int32_t is available */
#define OSMSCOUT_HAVE_INT32_T 1

/* int64_t is available */
#define OSMSCOUT_HAVE_INT64_T 1

/* int8_t is available */
#define OSMSCOUT_HAVE_INT8_T 1

/* SSE2 processor extension available */
// #define OSMSCOUT_HAVE_SSE2 1

/* system header <stdint.h> is available */
#define OSMSCOUT_HAVE_STDINT_H 1

/* std::wstring is available */
#define OSMSCOUT_HAVE_STD__WSTRING 1

/* uint16_t is available */
#define OSMSCOUT_HAVE_UINT16_T 1

/* uint32_t is available */
#define OSMSCOUT_HAVE_UINT32_T 1

/* uint64_t is available */
#define OSMSCOUT_HAVE_UINT64_T 1

/* uint8_t is available */
#define OSMSCOUT_HAVE_UINT8_T 1

/* system header <unordered_map> is available */
// #define OSMSCOUT_HAVE_UNORDERED_MAP 1

/* system header <unordered_set> is available */
// #define OSMSCOUT_HAVE_UNORDERED_SET 1

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "tim@teulings.org"

/* Define to the full name of this package. */
#define PACKAGE_NAME "libosmscout"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "libosmscout 0.1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "libosmscout"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "0.1"

/* The size of `wchar_t', as computed by sizeof. */
#define SIZEOF_WCHAR_T 4

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Enable large inode numbers on Mac OS X 10.5.  */
// #ifndef _DARWIN_USE_64_BIT_INODE
// # define _DARWIN_USE_64_BIT_INODE 1
// #endif

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define to 1 to make fseeko visible on some hosts (e.g. glibc 2.2). */
/* #undef _LARGEFILE_SOURCE */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */
