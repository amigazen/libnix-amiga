# libnix License

## Public Domain

This project is released into the **Public Domain**.

This means that you can:

- **Copy** the software without restrictions
- **Use** the software for any purpose, including commercial use
- **Modify** the software as needed
- **Distribute** the software freely
- **Sell** the software or products that include it
- **Create derivative works** without any obligations

## Third-Party Code Acknowledgments

This project incorporates some code from various third-party sources. While the main libnix code is in the public domain, the following third-party code retains its original licensing:

### BSD Licensed Code
- **University of California, Berkeley** - Network functions (inet_aton, inet_ntoa, strtok_r, fnmatch)
- **NetBSD Foundation** - Byte swap functions (bswap16, bswap32, bswap64) and fnmatch implementation
- **OpenBSD** - strlcpy function under ISC license (Todd C. Miller)
- **James E. Ingram** - getline and getdelim functions (https://gist.github.com/ingramj/1105106)

### Apache Licensed Code
- **Diego Casorran** - poll.c implementation under Apache License 2.0

### Other Licensed Code
- **Stephen L. Moshier** - Mathematical functions (gammaf, cbrtf, acoshf) - copyright retained
- **Olaf Barthel** - Memory functions (memchr, memcmp, bcopy) - custom license terms
- **Todd C. Miller** - asprintf function - ISC license

## Original Contributors

While not required, attribution to the original libnix authors is appreciated:

- **Matthias Fleischer** - Original contributor
- **Gunther Nikl** - Original contributor
- **Jeff Shepherd** - Network support implementation
- **Diego Casorran** - Version 3.0 additions
- **amigazen project** - Version 3.1 additions

## License Compatibility Notes

The third-party code included in this project uses various licenses that are generally compatible with the public domain status of the main libnix code:

- **BSD/ISC Licensed Code**: Can be freely used, modified, and distributed
- **Apache Licensed Code**: Permissive license compatible with most uses
- **Copyrighted Code**: Stephen L. Moshier's mathematical functions retain copyright but are typically used under permissive terms

## Disclaimer

This software is provided "as is" without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose and noninfringement. In no event shall the authors or copyright holders be liable for any claim, damages or other liability, whether in an action of contract, tort or otherwise, arising from, out of or in connection with the software or the use or other dealings in the software.

This software is not copyrighted by the Free Software Foundation (FSF) nor licensed under any version of the GPL. This was a deliberate design choice to make libnix more suitable for commercial Amiga software development compared to GPL-licensed alternatives (such as GCC itself, or ixemul.library)