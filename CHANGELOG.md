# Changelog

All notable changes to libnix are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [3.1] - 2025-10-10

### Added 
- **Optimised for Kickstart 3.1** - 
- **StringLib Integration** - Integrated Henry Spencer's public domain string library functions:
  - `memccpy` - Copy bytes up to a certain character (new function)
  - `index` - Find first occurrence of character (V7 compatibility)
  - `rindex` - Find last occurrence of character (V7 compatibility)
  - Enhanced `strstr` - Better algorithm with improved edge case handling
  - Enhanced `strtok` - More robust implementation with comprehensive testing
  - Enhanced `memcpy` - Proper overlap handling as required by X3J11 standard
- **GetOpt Integration** - Added complete `getopt()` command-line argument parsing:
  - Full POSIX-compliant implementation based on Daniel J. Barrett's GetOpt-1.3 originally for Aztec Manx compiler
  - Support for single-character options (`-a`, `-b`, `-c`)
  - Support for options requiring arguments (`-o filename`)
  - Support for grouped short options (`-abc`)
  - Recognition of `--` end-of-options marker
  - Configurable error reporting via `opterr` variable
  - Global variables: `optarg`, `optind`, `optopt`, `opterr`
- **System V IPC Integration** - Added complete System V Inter-Process Communication support:
  - **Semaphores** - `semget()`, `semop()`, `semctl()` with full POSIX compliance
  - **Shared Memory** - `shmget()`, `shmat()`, `shmdt()`, `shmctl()` with Amiga-optimized memory management
  - **Message Queues** - `msgget()`, `msgsnd()`, `msgrcv()`, `msgctl()` with robust message handling
  - **IPC Keys** - `ftok()` function for generating IPC keys from file paths
  - **Headers** - Complete `sys/ipc.h`, `sys/sem.h`, `sys/shm.h`, `sys/msg.h` header implementations
  - **Amiga Integration** - Uses native Amiga memory allocation (`AllocVec`/`FreeVec`) and semaphore primitives
  - **Error Handling** - Proper errno mapping and error reporting throughout
- **Headers** - Created local `string.h`, `getopt.h`, and System V IPC headers in `sources/nix/headers/`
- **License Compliance** - Replaced all GNU GPL/LGPL licensed code included by Diego Casorran with permissive alternatives:
  - `strchrnul.c` - Replaced with public domain implementation
  - `getdelim.c` - Replaced with BSD licensed implementation (James E. Ingram, 2011) - includes both getdelim and getline functions
  - `libintl.h` - Replaced with simple public domain stub implementation
  - `intl_*.c files` - Updated no-op stub implementations
  - `getline.c` - Removed (functionality merged into getdelim.c)

### Fixed
- **Makefiles** - Now builds out of the box natively on Amiga with GCC 2.95.3
- **String Function Compatibility** - Improved V7 and Berkeley compatibility with `index`, `rindex`, `bcmp`, `bcopy`, `bzero`
- **Memory Operations** - Fixed `memcpy` to handle overlapping memory regions correctly

### Removed
- **Legacy support** - No longer supports Kickstart 1.3 because it is irrelevant
- **GNU Licensed Code** - Removed all GPL/LGPL licensed files added in version 3.0 by Diego Casorran

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
- **Console utilities** - `ConsoleWidth()` function for terminal width detection (equivalent to Unix `ioctl(fd, TIOCGWINSZ, &wsz)` functionality)

### Changed
- **Time functions**:
  - `time/clock.c` - Changed to use `ReadEClock` for better accuracy
  - `extra/gettimeofday.c` - Changed to use `GetSysTime()` with `UNIT_MICROHZ`
- **Memory management**:
  - `stdlib/malloc.c` - Moved `free()` function and made local variables static
  - `stdlib/malloc.c` - Removed dummy opening of `dos.library` from within `__initmalloc()`
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

## [3.0-beta] - 2009-11-29

### Added
- **POSIX Semaphores** - Own-made implementation of POSIX Semaphores
- **Internationalization support** - Dummy implementations for `dcgettext`, `dgettext`, `gettext`, `textdomain`
- **MUI library functions** - Added `libmui.a` functions
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
- **Console utilities** - `ConsoleWidth()` function for terminal width detection (equivalent to Unix `ioctl(fd, TIOCGWINSZ, &wsz)` functionality)

### Changed
- **Time functions**:
  - `extra/gettimeofday.c` - Changed to use `GetSysTime()` with `UNIT_MICROHZ`
- **Memory management**:
  - `stdlib/malloc.c` - Moved `free()` function and made local variables static
  - `stdlib/malloc.c` - Removed dummy opening of `dos.library` from within `__initmalloc()`
- **Standard I/O improvements**:
  - `stdio/open.c` - `_allocfd()` now reallocates stdfiledes in increments of 10
  - `stdio/open.c` - `MODE_READWRITE` only used when `O_CREAT` is set
  - `stdio/open.c` - Fixed bug with `O_APPEND` mode not seeking to EOF
  - `stdio/open.c` - stderr now opened using `CONSOLE:` instead of `*`
  - `stdio/vfprintf.c` - Replaced `fputc` with `putc` for better performance
- **String function optimizations**:
  - `string/memcpy.c` - Replaced `CopyMem()` with internal `bcopy()`
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

## [2.1] - 2004 (BETA 2 - Final)

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

## [2.0 beta 1] - 1996

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

## [1.3] - 1996

### Added
- **Networking support** - Based on initial work by Jeff Sheperd (supports AmiTCP and AS225 compatible stacks)
- **Debug scheme** - Added a better and more general debug scheme
- **gettimeofday()** - Added from libnixPPC package
- **fdopen()** - Added (required changes in freopen())

### Changed
- **fdopen()** - Changed to be independent from freopen()
- **stdin/stdout/stderr initialization** - Now use fdopen() (removed freopen()'s stdio open kludge)
- **chmod()** - Adapted to return success if SetProtection fails because source is locked
- **devinit.c** - Finally rewrote to use GCC 2.7.2.1 features (now in sync with libinit.c/libinitr.c)
- **Makefiles** - Fixed for case sensitive filesystems, cross compilation support and proper $(MAKE) handling
- **Code cleanup** - General cleanup (e.g., replaced all numerical stdio flags with #defines)
- **Headers** - Updated headers/strsup.h once again

### Fixed
- **strftime()** - Fixed formats for date and date/time that were swapped (apparently due to outdated manpage)
- **Type usage** - Fixed incorrect types usage with proper system types (makes library better prepared for PPC)
- **freopen()** - Fixed (harmless?) bug in open mode handling (did only handle rwa[b]+ but not rwa+[b])
- **Append filemode** - Fixed to really write at end of file only
- **Makefiles** - Fixed hole in math/Makefile.in (didn't reference *all* objects leading to vfprint/vfscanf)
- **auto-initialization** - Fixed of init_stk.c (broken since 1.2)
- **mktime()** - Fixed bug (tm_mday starts with 1!) (reported by Detlef Wuerkner)
- **rename()** - Modified according to man-page, __seterrno() now maps rename() error (was disabled!?)

### Performance
- **Memory functions** - Improved memset(), bcopy() and bzero()

## [1.2] - 1996

### Added
- **fdopen()** - Added (required changes in freopen())

### Changed
- **Headers** - Updated headers/strsup.h once again
- **rename()** - Modified according to man-page
- **__seterrno()** - Now maps rename() error (was disabled!?)

### Fixed
- **auto-initialization** - Fixed of init_stk.c (broken since 1.2)
- **mktime()** - Fixed bug (tm_mday starts with 1!) (reported by Detlef Wuerkner)

## [1.1b] - 1996

### Added
- **libnix13.a** - Moved all 1.3 compatibility stuff into separate library (contains integer math functions, useful for linking with -nostdlib)
- **Math functions** - Added three math functions from vc.lib: frexp.c, ldexp.c and modf.c
- **libamiga.a functions** - Tweaked functions

### Changed
- **Automatic library opening** - Changed once again (moved openliberror() function into __initlibraries source)
- **String functions** - Tweaked and removed some asm versions
- **Headers** - Updated headers/strsup.h with new string functions
- **Const qualifiers** - Added some const qualifiers at several places
- **libinit.c, libinitr.c and devinit.c** - Rewrote (requires ADE/GG GCC 2.7.2.1 or up)
- **Default stdiowin options** - Added "/WAIT" (suggested by Martin Hauner)

### Fixed
- **strncpy()** - Fixed "off-by-one" error of portable strncpy()
- **open()** - Fixed to ignore stdio slots now
- **longjmp()** - Fixed to not return 1 if passed a 0
- **atol() and atoi()** - Fixed serious bug

## [1.1a] - 1996

### Added
- **Cache flush function** - Added for gcc support
- **Support functions** - Updated for amiga.lib
- **Code cleanup** - General cleanup

### Fixed
- **stabs.h** - Fixed macro for shared library support
- **Automatic library functions** - Replaced asm functions with c functions

## [1.1] - 1996

### Added
- **Cache flush function** - Added for gcc support
- **Support functions** - Updated for amiga.lib
- **Code cleanup** - General cleanup

### Fixed
- **stabs.h** - Fixed macro for shared library support
- **Automatic library functions** - Replaced asm functions with c functions

## [1.0] - 1996

### Added
- **Non-ANSI functions** - Added bunch of non-ansi functions (mktemp, getrusage, etc.)
- **snprintf() and vsnprintf()** - Added
- **CPU check** - Added with error requester for non-68000 versions (changed startups, too)

### Changed
- **raise()** - Switched from fputs() to write(2,..)

### Fixed
- **gets()** - Fixed to return NULL if no characters are read. Dropped unnecessary ferror() call in fgets
- **strtoul()** - Fixed to not read characters which were invalid for the current base

## [0.9] - 1996

### Fixed
- **ANSI compliance** - Fixed flushing of line or unbuffered output files when reading from line buffered input
- **Float output** - Fixed bug that wrote weird characters for floats on some machines (system math libraries don't work correct if opened in alphabetical order)

### Performance
- **Commandline parsers and shared library opener** - Optimized
- **C-files** - Removed some unused prototypes

## [0.8] - 1996 (Third Official Release)

### Added
- **Stack extension/checking** - Added code to handle stackextension/checking
- **libnix requesters** - All now check pr_WindowPtr first
- **fileno() and fdtofh()** - Added
- **Version strings** - Added to ALL modules

### Changed
- **Includes** - Changed all includes to use proto/ instead of inline/
- **__chkabort()** - Moved one level down into read(), write(), lseek()

### Fixed
- **close(STDIN_FILENO)** - Fixed returncode and errno after lseek()
- **fflush(NULL)** - Fixed to not flush stdout and stderr twice
- **atan2()** - Fixed bug
- **strncat()** - Fixed missing terminator

## [0.7] - 1996 (Second Official Release)

### Added
- **fileno() and fdtofh()** - Added
- **Version strings** - Added to ALL modules
- **Startups** - Prepared for third argument of main(int argc, char *argv[], char *env[]) (not supported, but prepared)

### Changed
- **open()** - Dropped ChangeMode call. Now mode "a" files have shared lock, but other method didn't work with all handlers
- **Build system** - Got rid of ARexx-scripts when building library. Now can build libnix on sun using cross-compiler
- **fread() and fwrite()** - Made buffered

### Fixed
- **fseek()** - Fixed to clear EOF flag
- **Commandline parser** - Fixed holes that could give empty arguments
- **vprintf()** - Fixed bug in floating point part (introduced with last revision)
- **vfprintf()** - Improved precision
- **vfscanf()** - Fixed returncode on EOF

## [0.6] - 1996

### Added
- **Stackswap module** - Added
- **Default values** - Added to libstubs.a for some variables used by certain modules (__stack, _procname, __priority)
- **Version string** - Added to libnix.a

### Changed
- **stat()** - Changed to work silently (now suppresses all *DOS* requesters)
- **Signal handling** - Heavily changed - now more unix-like
- **Main redirection** - Moved redirection of 'main' to '_main' into separate file (in libnix_main.a)

### Fixed
- **__swbuf()** - Fixed bug (overrun buffersize by one character)
- **__chkabort()** - Fixed to clear ctrl-c signal
- **vfprintf()** - Improved precision
- **vfscanf()** - Fixed returncode on EOF

## [0.5] - 1996 (First Official Release)

### Added
- **Open("*", MODE_NEWFILE)** - Added as fallback for process->pr_CES
- **String functions** - strdup, stricmp, strlower, strnicmp, strupper added
- **Un*x style pathnames** - Added optional support
- **Hook and boopsi functions** - Added to libamiga.a
- **Auto-detach** - Reintegrated (clean this time) as object module
- **Random functions** - FastRand and RangeRand added to libamiga.a
- **3.1 system libraries** - Added to libstubs.a
- **Un*x functions** - Added (mkdir, chdir, rmdir, getwd, getcwd, opendir, readdir, closedir)
- **Shared amiga-library creation** - Added support (library and device initcode)

### Changed
- **Library startup module** - Changed kludge
- **Standard I/O initialization** - Optimized
- **Disk layout** - Changed for better handling of different library compilations
- **__initlibraries function** - Cleaned up
- **Main and _exit** - Implemented with symbol redirection for full C++ support with libg++.a

### Fixed
- **Low-level-I/O cleanup routine** - Fixed bug
- **open()** - Added more error handling
- **Low-level-I/O cleanup function** - Fixed bug
- **strftime()** - Fixed yet another bug
- **Glue code generator** - Fixed to work correctly on void-'...'-functions
- **freopen()** - Fixed bug when using mode "w" on already existing file
- **Commandline parser** - Fixed to not overwrite __commandline variable (was NASTY feature)
- **LocaleBase** - Fixed to not be defined twice
- **__decimalpoint** - Moved from libm.a into libnix.a

## [0.4] - 1996

### Added
- **strcasecmp()** - Added
- **Inline strlen()** - Added in vfprintf, vsscanf, strxfrm, setlocale

### Changed
- **Stub functions** - Rewrote all as symbol redirections to single one
- **__modsi3, __umodsi3** - Moved into div-equivalents
- **Startups** - Did some work on them
- **Auto-detach startups** - Removed from distribution until better method (had holes)

### Fixed
- **fstat()** - Fixed bug
- **fread() and fwrite()** - Fixed bugs when processing no data at all
- **locale.library** - Fixed to not cause program exit if missing
- **asctime()** - Fixed to use 'C' instead of 'c'
- **strftime()** - Fixed to work correctly on numbers longer than 2 characters
- **Low level I/O** - Some additional work needed

## [0.3] - 1996

### Added
- **POSIX compliance** - Low level standard-I/O functions now posix compliant
- **New functions** - access(), stricmp(), unlink(), fstat(), bcmp() added

### Performance
- **Math functions** - Optimized atan2, fmod, strlen

### Fixed
- **strtod()** - Fixed warning
- **strftime()** - Fixed to count correctly
- **Math libraries makefile** - Fixed bug

## [0.2] - 1996

### Added
- **Specs file** - Added
- **libgcc.a stub** - Added to get specs file to work
- **Functions** - Some functions added to libamiga.a

### Changed
- **Global makefile** - Adjusted for auto detach startups

### Fixed
- **gas EOF handling** - Fixed to handle 0xff as gas writes EOF
- **Symbol redirections** - Removed most as they didn't work as expected
- **-lm linking** - Fixed to link libm.a BEFORE libnix (moved some functions)
- **vfscanf()** - Fixed to not ungetc EOF

### Performance
- **Math functions** - Optimized __udivsi3, __umodsi3, __divsi3, __modsi3, div, ldiv

## [0.1] - 1996 (Start)

### Added
- **bzero()** - Half initialized local arrays reference bzero() - added
- **setbuffer()** - Added to be able to compile gas1.38
- **sys_errlist and sys_nerr** - Changed from 'static char *errorlist[]' for better compatibility
- **Documentation** - Rewrote documentation & some new chapters in texinfo format
- **Distribution structure** - Changed directory structure to distribution form, added 'distribution' makefile entry

### Changed
- **memchr.c** - Changed (C code looks not very good, but assembler code is very smart now)
- **malloc** - Now rounds even _MSTEP up to full MMU page
- **String functions** - strcat(), strncat(), strcpy(), strncpy(), strchr(), strrchr() rewritten in asm
- **fgetc() and fputc()** - Removed __chkabort() (not necessary to poll CTRL-C for EVERY character written)
- **Buffer flags** - Changed code for setting buffer flags in setvbuf()
- **_main()** - Has commandline as argument INCLUDING program's name. Renamed _main as __submain and wrote new __submain calling _main. Moved call to open shared libraries out of startups
- **Private library bases** - Now have two '_'
- **I/O functions** - All now run over unix-alike interface. Standard I/O streams now use fopen

### Fixed
- **Symbol usage** - Fixed that symbol and its indirected counterpart cannot be used both
- **__stdio.c** - Fixed wrong flag for testing if filehandle has to be closed (standard filehandle was closed three times)
- **strcmp(), strncmp()** - Fixed to work on signed char
- **freopen()** - Deleted extraneous semicolon (';')
- **setvbuf()** - Fixed to set buffer size
- **libm.a** - Fixed to need private library bases too

---

## Version History Summary

| Version | Date | Key Features |
|---------|------|--------------|
| 3.1 | 2025 | Makefile fixes, POSIX compatibility updates |
| 3.0 | 2010-07-04 | POSIX semaphores, network support, IEEE math functions, extensive new standard functions |
| 3.0-beta | 2009-11-29 | Initial 3.0 development, POSIX semaphores, extensive new functions, IEEE math functions |
| 2.1 | 2004 | Network support, append mode, standard stderr behavior |
| 2.0 | 1996 | Initial networking capabilities |
| 1.3 | 1996 | Networking support, debug scheme, gettimeofday(), fdopen() |
| 1.2 | 1996 | fdopen(), header updates, rename() improvements |
| 1.1b | 1996 | libnix13.a, math functions, const qualifiers, library improvements |
| 1.1a | 1996 | Cache flush, amiga.lib support, code cleanup |
| 1.1 | 1996 | Cache flush, amiga.lib support, code cleanup |
| 1.0 | 1996 | Non-ANSI functions, snprintf/vsnprintf, CPU check |
| 0.9 | 1996 | ANSI compliance fixes, performance optimizations |
| 0.8 | 1996 | Stack extension, libnix requesters, fileno/fdtofh |
| 0.7 | 1996 | Build system improvements, buffered I/O, version strings |
| 0.6 | 1996 | Stackswap module, signal handling, unix-like features |
| 0.5 | 1996 | First official release, Un*x functions, auto-detach |
| 0.4 | 1996 | strcasecmp(), inline strlen(), stub function improvements |
| 0.3 | 1996 | POSIX compliance, new functions, math optimizations |
| 0.2 | 1996 | Specs file, libgcc.a stub, math function optimizations |
| 0.1 | 1996 | Initial development, basic ANSI C support, Amiga features |

## Contributors

- **Matthias Fleischer** - Original author (versions 1.x)
- **Gunther Nikl** - Co-author and maintainer (versions 1.x-2.x)
- **Jeff Shepherd** - Network support implementation (version 2.x, 2004)
- **Diego Casorran** - Version 3.0 maintainer and major contributor (2009-2010)
  - 2009-11-29: Major 3.0-beta development including POSIX semaphores, extensive new functions, IEEE math functions, and numerous bug fixes
  - 2010-07-04: Final 3.0 release with performance optimizations and additional improvements
- **amigazen project** - Version 3.1

## License

This project is in the **Public Domain**. You can copy, use, and modify it without any restrictions.
