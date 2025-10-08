
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#undef inet_addr

/*
 * Ascii internet address interpretation routine.
 * The value returned is in network order.
 */
u_long inet_addr(const char *cp)
{
  struct in_addr val;

  if (inet_aton(cp, &val))
    return (val.s_addr);
  return (u_long)-1;
}
