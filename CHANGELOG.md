# Changelog

All notable changes to libnix are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [3.1] - 2025-10-07

### Added 
- **Optimised for Kickstart 3.1** - 

### Fixed
- **Makefiles** - Now builds out of the box natively on Amiga with GCC 2.95.3

### Removed
- **Legacy support** - No longer supports Kickstart 1.3 because it is unnecessary

## [3.0] - 2010-07-04

### Added
- **POSIX Semaphores** - Complete implementation of POSIX semaphore functions
- **Internationalization support** - Dummy implementations for `dcgettext`, `dgettext`, `gettext`, `textdomain`
- **MUI library functions** - Added `libmui.a` functions for MUI support
- **Timer device auto-initialization** - Automatic initialization of timer.device
- **Network support** - Auto-initialization of `bsdsocket.library` with errno/h_errno mapping and program name to syslog messages
- **New standard functions**:
  - `v/asprintf` - Variable argument sprintf
  - `fnmatch` - Filename pattern matching
  - `strlcat` - Safe string concatenation
  - `nl_langinfo` - Language information
  - `basename` - Extract filename from path
  - `getline`, `getdelim` - Safe line reading
  - `readpassphrase`, `getpass`, `getpass_r` - Password input
  - `memrchr` - Reverse memory search
  - `gmtime_r`, `localtime_r`, `asctime_r`, `ctime_r` - Reentrant time functions
  - `strerror_r` - Reentrant error string
  - `strtok_r` - Reentrant string tokenizer
  - `poll` - I/O multiplexing
  - `strcmpi`, `strncmpi` - Case-insensitive string comparison
  - `stristr`, `strcasestr` - Case-insensitive string search
  - `memdup` - Memory duplication
  - `truncate`, `ftruncate` - File truncation
  - `syslog`, `openlog`, `closelog`, `setlogmask` - System logging
  - `inet_addr`, `socketpair`, `inet_aton`, `inet_ntoa`, `inet_ntop`, `inet_pton`, `intoa` - Network address functions
  - `sleep`, `usleep`, `nanosleep` - Sleep functions
  - `memmem`, `mempcpy` - Memory operations
  - `stpncpy` - String copy with padding
  - `physmem_total`, `physmem_available` - Physical memory information
  - `getruntime` - Runtime information
  - `popen`, `pclose` - Process I/O
  - `ffs` - Find first set bit
  - `unctrl`, `unctrllen` - Control character handling
  - `telldir`, `seekdir`, `scandir`, `alphasort` - Directory operations
  - `strndup`, `strnlen`, `strlcpy`, `strchrnul` - Safe string operations
- **IEEE math functions**:
  - Square root: `sqrt`, `sqrtf`, `sqrtl`
  - Cube root: `cbrt`, `cbrtf`, `cbrtl`
  - Exponential: `exp`, `expf`, `expl`, `exp2`, `exp2f`, `exp2l`
  - Hyperbolic: `hypot`, `hypotf`, `hypotl`
  - Logarithmic: `log2`, `log2f`, `log2l`, `log10`, `log10f`, `log10l`
  - Sign functions: `copysign`, `copysignf`, `copysignl`
  - Rounding: `rint`, `rintf`, `rintl`, `round`, `roundf`, `roundl`
  - Truncation: `trunc`, `truncf`, `truncl`
  - Hyperbolic inverse: `acosh`, `acoshf`, `acoshl`
- **Console utilities** - `ConsoleWidth()` function for terminal width detection

### Changed
- **Time functions**:
  - `time/clock.c` - Changed to use `ReadEClock` for better accuracy
  - `extra/gettimeofday.c` - Changed to use `GetSysTime()` with `UNIT_MICROHZ`
- **Memory management**:
  - `stdlib/malloc.c` - Moved `free()` function and made local variables static
  - `stdlib/malloc.c` - Removed dummy opening of `dos.library`
  - `stdlib/realloc.c` - Changed `CopyMem()` to `bcopy()`
- **Standard I/O improvements**:
  - `stdio/open.c` - Improved `write()` function
  - `stdio/open.c` - `_allocfd()` now reallocates stdfiledes in increments of 10
  - `stdio/open.c` - `MODE_READWRITE` only used when `O_CREAT` is set
  - `stdio/open.c` - Fixed bug with `O_APPEND` mode not seeking to EOF
  - `stdio/open.c` - stderr now opened using `CONSOLE:` instead of `*`
  - `stdio/vfprintf.c` - Replaced `fputc` with `putc` for better performance
- **String function optimizations**:
  - `string/memcpy.c` - Replaced `CopyMem()` with internal `bcopy()`
  - `string/memchr.c` - Speed improvements
  - `string/memcmp.c` - Speed improvements
- **Memory operation optimizations**:
  - `misc/bzero.c` - Optimized small operations
  - `misc/bcopy.c` - Optimized small operations
  - `string/memset.c` - Optimized small operations
- **String function improvements**:
  - `strtok`, `strtok_r`, `strspn`, `strdup` - Somewhat improved implementations

### Fixed
- **Standard I/O segfaults**:
  - `stdio/fwrite.c` - Fixed segfaults caused by using stderr
  - `stdio/fputs.c` - Fixed segfaults caused by using stderr
  - `stdio/perror.c` - Fixed segfaults caused by using stderr
- **Buffer handling**:
  - `stdio/__swbuf.c` - Workaround/bugfix for unbuffered streams
  - `stdio/vsnprintf.c` - Fixed "buffer full" state bug
- **Stream protection** - stdin, stdout, and stderr are now protected from being closed

## [2.1] - 2000 (BETA 2 - Final)

### Added
- **Network support** - New link library `libsocket.a` based on work by Jeff Shepherd
- **Append mode** - Completed append mode support (now works for `fdopen()`)
- **Standard stderr behavior** - stderr now always unbuffered according to standard
- **Write-only stream optimization** - Optimized write-only streams (as in *BSD)

### Changed
- **Socket I/O interface** - Changed from using packet in private memory to DOS allocated memory for better system compatibility
- **Optimization level** - Considered changing from `-O3` to `-O2` or `-Os` in makefile

### Fixed
- **Append mode** - Fixed append mode functionality
- **Stderr behavior** - Fixed stderr to be always unbuffered (previously had normal fopen() mode)

## [2.0] - 1996

### Added
- **Network support** - Initial networking capabilities
- **Socket library** - `libsocket.a` for network operations

## [1.2] - 1996

### Features
- **Auto-open-library feature** - Automatic shared library opening
- **SAS compatible handling** - Workbench startup message handling
- **Auto-detach startup code** - Background process support
- **Compact size** - Very small executable footprint
- **No shared library dependencies** - Only requires standard Amiga OS libraries
- **Auto stack-extend** - Stack overflow handling
- **ANSI C compliant** - Full standard library implementation

### Technical Details
- **Memory management** - Uses local memory pool to reduce fragmentation
- **Standard I/O** - Smart stderr fallback system
- **Stack extension** - Advanced stack handling for Amiga OS
- **Library bases** - Automatic library opening system

## [1.1a] - 1996

### Initial Release
- **Core library** - Basic ANSI C standard library implementation
- **Amiga-specific features** - Auto-library opening, stack extension
- **GCC compatibility** - Support for GCC 2.3.3 and above
- **Amiga OS 2.0+** - Minimum system requirements

---

## Version History Summary

| Version | Date | Key Features |
|---------|------|--------------|
| 3.1 | 2025 | Makefile fixes, POSIX compatibility updates |
| 3.0 | 2010-07-04 | POSIX semaphores, network support, IEEE math functions, extensive new standard functions |
| 2.1 | 2000 | Network support, append mode, standard stderr behavior |
| 2.0 | 1996 | Initial networking capabilities |
| 1.2 | 1996 | Core Amiga-specific features, auto-library opening |
| 1.1a | 1996 | Initial release, basic ANSI C support |

## Contributors

- **Matthias Fleischer** - Original author (versions 1.x)
- **Gunther Nikl** - Co-author and maintainer (versions 1.x-2.x)
- **Jeff Shepherd** - Network support implementation (version 2.x)
- **Diego Casorran** - Version 3.0 maintainer and major contributor
- **amigazen project** - Version 3.1

## License

This project is in the **Public Domain**. You can copy, use, and modify it without any restrictions.
