# libnix-amiga 3.1 - Standard C Library for Amiga and GCC

## What is libnix-amiga 3.1?

libnix is a link library implementing the Standard C Library for Amiga computers to use with GCC, providing a statically linked alternative to the ixemul.library that is the default option for GCC on Amiga.

This distribution traces it's lineage directly back to the original release by Matthias Fleischer and Gunther Nikl, through the releases by Jeff Shepherd and later Diego Casorran, with the complete change history reflected in the GitHub repository.

Unlike other forks of libnix that can be found on GitHub.com and elsewhere, this ToolKit release by amigazen project is designed to be used with the last native version of gcc, version 2.95.3 as found in distributions such as ADE and GeekGadgets, as well as amigazen project's own ToolKit release. This version therefore does not contain any code that requires newer versions of GCC typically used with cross compiler versions of GCC. 

The repository name "libnix-amiga" reflects the intention that this release always retain compatibility with Amiga native builds, while the version number 3.1 reflects that this release will be optimised for, and take full advantage of, features of Amiga's Kickstart 3.1 without regard to backwards compatibility, as well as being the natural successor to the previous 3.0 release.

## [amigazen project](http://www.amigazen.com)

*A web, suddenly*

*Forty years meditation*

*Minds awaken, free*

**amigazen project** uses modern software development tools and methods to update and rerelease classic Amiga open source software. Our upcoming releases include a new AWeb, and a new Amiga Python 2.

Key to our approach is ensuring every project can be built with the same common set of development tools and configurations, so we created the ToolKit project to provide a standard configuration for Amiga development. All *amigazen project* releases will be guaranteed to build against the ToolKit standard so that anyone can download and begin contributing straightaway without having to tailor the toolchain for their own setup.

The original authors of the *CShell* software are not affiliated with the amigazen project. This software is redistributed on terms described in the documentation, particularly the files COPYING or LICENSE.md

Our philosophy is based on openness:

*Open* to anyone and everyone	- *Open* source and free for all	- *Open* your mind and create!

PRs for all of our projects are gratefully received at [GitHub](https://github.com/amigazen/). While our focus now is on classic 68k software, we do intend that all amigazen project releases can be ported to other Amiga-like systems including AROS and MorphOS where feasible.

All amigazen projects have been updated:
- To build against the latest NDK3.2
- Using the latest good version of at least one standard Amiga compiler - either SAS/C (6.58), DICE, VBCC or GCC
- And will build straight out of the box, for anyone who has ToolKit setup correctly

## About ToolKit

**ToolKit** exists to solve the problem that most Amiga software was written in the 1980s and 90s, by individuals working alone, each with their own preferred setup for where their dev tools are run from, where their include files, static libs and other toolchain artifacts could be found, which versions they used and which custom modifications they made. Open source collaboration did not exist then as we know it now. 

**ToolKit** from amigazen project is a work in progress to make a standardised installation of not just the Native Developer Kit, but the compilers, build tools and third party components needed to be able to consistently build projects in collaboration with others, without each contributor having to change build files to work with their particular toolchain configuration. 

All *amigazen project* releases will release in a ready to build configuration according to the ToolKit standard.

Each component of **ToolKit** is open source and like *csh* here will have it's own github repo, while ToolKit itself will eventually be released as an easy to install package containing the redistributable components, as well as scripts to easily install the parts that are not freely redistributable from archive.

### libnix Features

- **Auto-open-library feature** - Automatically opens Amiga system libraries without requiring OpenLibrary
- **Workbench startup message handling** - Follows same pattern as SAS/C for entering main() from Workbench
- **Auto-detach startup code** - Launch background "daemon" processes
- **Compact size** - Very small executable footprint
- **No shared library dependencies** - Only requires standard Amiga system libraries
- **Auto stack-extension** - Handles stack overflow gracefully
- **ANSI C compliant** - Full standard library implementation

## Version History

### libnix 3.1
Based on version 3.0 by Diego Casorran, this release builds a new stable foundation for native GCC development with the ToolKit SDK:

#### Major Changes from 3.0 to 3.1:
- **Makefiles**: Builds out of the box on Amiga with a standard GCC installation
- **Kickstart 3.1**: Optimised for Kickstart 3.1 and later, not tested on older versions of the Amiga operating system
- **Work in progress**: More features to come

### libnix 3.0
Based on version 2.1 by Jeff Shepherd, this release includes significant improvements:

#### Major Changes from 2.1 to 3.0:
- **Time functions**: `gettimeofday.c` now uses `GetSysTime()` with `UNIT_MICROHZ`
- **Memory optimization**: Improved `bcopy.c`, `bzero.c`, and `memset.c` for small operations
- **Standard I/O fixes**: 
  - stdin, stdout, and stderr are now protected from being closed
  - Fixed segfaults in `fputs.c`, `fwrite.c`, and `perror.c`
  - Fixed `open.c` bug with `O_APPEND` mode
  - Improved stderr handling using `CONSOLE:` instead of `*`
- **Memory management**: 
  - Moved `free()` to `malloc.c` with static local variables
  - Removed dummy `dos.library` opening
  - Changed `CopyMem()` to `bcopy()` in `realloc.c`
- **String functions**: Speed improvements in `memchr.c`, `memcmp.c`, `memcpy.c`
- **Clock function**: Now uses `ReadEClock` for better accuracy

#### New Features in 3.0:
- **POSIX Semaphores** Added all new implementation
- **Internationalization**: Dummy implementations for `dcgettext`, `dgettext`, `gettext`, `textdomain`
- **MUI support**: Added `libmui.a` functions
- **Timer device**: Auto-initialization
- **Network support**: Auto-initialization of `bsdsocket.library` with errno/h_errno mapping
- **New functions**: `v/asprintf`, `fnmatch`, `strlcat`, `nl_langinfo`, `basename`, `getline`, `getdelim`, `readpassphrase`, `getpass`, `getpass_r`, `memrchr`, `gmtime_r`, `localtime_r`, `asctime_r`, `ctime_r`, `strerror_r`, `strtok_r`, `poll`, `strcmpi`, `strncmpi`, `stristr`, `strcasestr`, `memdup`, `truncate`, `ftruncate`, `syslog`, `openlog`, `closelog`, `setlogmask`, `inet_addr`, `socketpair`, `inet_aton`, `inet_ntoa`, `inet_ntop`, `inet_pton`, `intoa`, `sleep`, `usleep`, `nanosleep`, `memmem`, `mempcpy`, `stpncpy`, `physmem_total`, `physmem_available`, `getruntime`, `popen`, `pclose`, `ffs`, `unctrl`, `unctrllen`, `telldir`, `seekdir`, `scandir`, `alphasort`, `strndup`, `strnlen`, `strlcpy`, `strchrnul`
- **IEEE math functions**: `sqrt`, `sqrtf`, `sqrtl`, `cbrt`, `cbrtf`, `cbrtl`, `exp`, `expf`, `expl`, `exp2`, `exp2f`, `exp2l`, `hypot`, `hypotf`, `hypotl`, `log2`, `log2f`, `log2l`, `log10`, `log10f`, `log10l`, `copysign`, `copysignf`, `copysignl`, `rint`, `rintf`, `rintl`, `round`, `roundf`, `roundl`, `trunc`, `truncf`, `truncl`, `acosh`, `acoshf`, `acoshl`
- **Console utilities**: Added `ConsoleWidth()` function for terminal width detection

### libnix 2.0 (BETA 2 - Final)
The final BETA version with completed append mode support and improved stderr behavior according to standards.

See (CHANGELOG.md) for additional release history

## Usage

### Basic Compilation
```bash
gcc (-fbaserel) (-resident) -noixemul YOUR_OBJECTS (-nix_main) (-lm)
```

### Key Options
- `-lnix_main`: Use different commandline parser
- `-lm`: Link with math library (required for floating point support)
- `-fbaserel`: For a4-relative programs
- `-resident`: For resident (pure) programs

### Manual Linking
```bash
gcc -nostdlib ncrt0.o YOUR_OBJECTS libnixmain.a (libm.a) libnix.a libstubs.a
```

## Library Components

The libnix package includes several components in the correct linkage order:

1. **Startup codes** - Handle program initialization
2. **Your objects** - Your compiled code
3. **Commandline parser** - Calculates argc and argv
4. **libm.a** - Math library (optional)
5. **libstack.a** - Stack extension code (optional)
6. **libnix.a** - The main library
7. **libamiga.a** - GCC version of amiga.lib functions
8. **detach.o** - Auto-detaching support
9. **libstubs.a** - Library base pointers for system library auto-open

## Special Features

### Stack Extension
libnix provides advanced stack handling:

- **Stack checking**: `-mstackcheck` option
- **Stack extension**: `-mstackextend` option
- **Automatic management**: Handles stack overflow gracefully
- **Performance tuning**: Configurable parameters for different needs

### Memory Management
- Uses local memory pool to reduce fragmentation
- Default block size: 16384 bytes (4 MMU pages)
- Configurable via `_MSTEP` variable

### Standard I/O
- **stdin**: Uses `Input()` from dos.library
- **stdout**: Uses `Output()` from dos.library  
- **stderr**: Smart fallback system (process->pr_CES, CLI terminal, or stdout)

## Writing Small Programs

To create compact executables:

1. **Avoid printf**: Use simpler functions like `puts`
2. **Use low-level I/O**: `read()` and `write()` instead of buffered I/O
3. **Optimize compilation**: Use `-O2 -fstrength-reduce` instead of `-O3`
4. **Strip executables**: Use `-s` flag
5. **Small code/data model**: Use `-msmall-code -fbaserel`
6. **Disable commandline parsing**: Set `__nocommandline` variable

## Frequently Asked Questions

### Why does this release of libnix drop support for older versions of the Amiga operating system?

Several reasons:
- Amiga operating system 3.1 (and even 3.2) is available for all classic Amigas. There is no Amiga that cannot run the latest version of the classic Amiga operating system.
- While ixemul.library and early versions of GCC did originate in the era of Kickstart 1.x, they quickly outgrew the hardware constraints of classic Amiga computers, even expanded ones, with high demands on RAM usage and CPU performace, and the Unix ports they enabled grew at an even faster rate. In practice therefore any user wishing to run software built with GCC, including _gcc_ itself, is not going to be using an outdated, unexpanded Amiga.
- There is no known software still in use or supported today targetting earlier Amiga operating system versions and that needs GCC compiler.
- For retro enthuasiasts who really want a C compiler for targetting older versions, plenty of other options exist that are free and/or open source including VBCC and DICE.
- amigazen projects like ToolKit are not retro-computing projects. They are projects intended to rejuvenate the Amiga platform. With limited time and resources, retaining backwards compatibility is not a sensible endeavour.

### Which is better ixemul.library or libnix?

In the 1990s, ixemul.library and the wider GeekGadgets distribution provided an almost complete GNU environment running natively on the Amiga, an amazing feat. 

However, as GNU software became more intertwined with Linux, and computing platforms continued to evolve new capabilities, it's fair to say that the GeekGadgets approach, of trying to retain 100% compatibility with the standard autoconf/make/gcc build tools and C API was a losing battle, and the original creators of GeekGadgets moved on to other projects on other platforms.

Additionally, the wisdom of using a shared library implementation of the Standard C Library instead of a statically linked library is in hindsight highly questionable - a shared library implementation is only more efficient if every application uses a majority of its functions, or if, like libdl on Linux, MMU tricks can be used to selectively load the library in fragments. In practice, most applications use the same small selection of functions and the bulk of the shared library code will never be needed, yet takes up valuable RAM. The overhead of repeating every function in every binary, is in the end more efficient for the few tools a user might need at any one time that are not fully native programs that bypass the C library and call the operating system functions directly.

ixemul.library is widely considered to use esoteric and unusual techniques, and while forks have been released over the intervening years, the original developers and their domain knowledge has long since left the Amiga scene. The benefits therefore of using ixemul.library seem to be outweighed by the difficulty in debugging and in fixing issues arising from the now very out of date implementation. Likewise, modern software using the autoconf/make/gcc build system likely has many dependencies that simply do not exist on Amiga, rendering the theoretical benefit null and void.

libnix on the other hand is a straightforward and easy to understand ANSI C library, with permissive licensing (in fact, no license at all) and easy to fix and extend.

Since debugging, fixing bugs in the library itself and building with ixemul.library is significantly more difficult, and with the benefits of easy porting rendered irrelevant by years of advances on other platforms that Amiga has not kept pace with, libnix is surely a better option when using GCC.

### Does this libnix include all the changes from other libnix versions found on GitHub and elsewhere

At this time, this fork of libnix only contains code from the original Aminet releases of libnix, the later sourceforge release by Jeff Shepherd and the GitHub release by Diego Casorran. 

It does not contain any of the changes found in releases from beppo, BSzili, AmigaPorts and others.

The reason for this is that many changes in those other forks are both poorly documented, and written without regard for retaining compatibility with Amiga nativebuilds. Indeed usually their changes are designed to improve compatibility with newer versions of GCC used in cross compilers targeting Amiga.

In time, the best patches from other libnix forks may be cherry-picked where it is beneficial to do so, while retaining compatibility with Amiga's native GCC.

### Can GCC 2.95.3 for Amiga be built with libnix instead of ixemul.library?

Earlier versions of GCC and the binutils could indeed be built with libnix instead of ixemul.library, although the source code to those configurations has never been released. This is something being actively explored, in order to create a more maintainable new native release of GCC for Amiga, ideally one that no longer requires the -noixemul option to have it build with libnix by default.

### Does libnix 3.1 support OS4?

The libnix codebase supports building an OS4 shared library variant called 'libnix4.library' using the OS4 GCC-based SDK, however this is not currently tested or supported. It may be supported in future.

### What Standard C Libraries are available for Amiga?

While modern platforms typically provide a Standard C Library as part of the operating system's core functionality, in the 1980s and 90s it was more common for the Standard C Library to be packaged with the C compiler, which in turn were usually commercial products rather than the universal GCC and Clang compilers found on most platforms today.

Being commercial products, long since abandoned, that leaves many of the original C library implementations for Amiga frozen in time, and while they can still be used, they were all released well before C standardised and are missing or incompatible with the more recent C standards such as C99, POSIX and later.

Available Standard C libraries today include:
- **libnix** - libnix, including this libnix-amiga 3.1 fork, is an ANSI C library designed for use with GCC only
- **clib2** - Olaf Barthel's clib2 is a Standard C Library designed for use with both GCC and SAS/C
- **UniLib3** - UniLib3 is a collection of C libraries implementing C99 and POSIX standards based on David Gay's unix.lib, Simon Raybould's curses.lib and other original works, designed to be used alongside the SAS/C sc.lib which only implements the C89 standard
- **vc.lib** - this is the default ANSI C library included with VBCC
- **PosixLib** - designed for use with VBCC, PosixLib is a more comprehensive, and open source, library than vc.lib implementing POSIX / Unix-like functions for aid in porting software
- **DICE C library** - now open source, the DICE C library can be found at https://github.com/dice-nx/

OS4 instead uses:
- **clib2** - Olaf Barthel's clib2 included in the OS4 SDK as a static link library option
- **newlib.library** - a shared library based on the open source newlib project and the default C library for OS4, although now much out of date
- **clib4** - a fork of Olaf Barthel's clib2, designed exclusively for use on OS4 being actively updated to meet modern needs available here https://github.com/AmigaLabs/clib4 in both static and shared library forms
- **libnix4.library** - see FAQ above

### What are the plans for libnix-amiga?

It is planned that this libnix-amiga project will be rounded out with missing functionality, eventually providing equivalent C99 and POSIX functionality to both ixemul.library and amigazen project's UniLib3 library for SAS/C.

## Contact 

- At GitHub https://github.com/amigazen/CShell
- on the web at http://www.amigazen.com/toolkit/ (Amiga browser compatible)
- or email toolkit@amigazen.com

## Acknowledgements

*Amiga* is a trademark of **Amiga Inc**. 
