/**
 * @brief     posix socket header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011 
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_SOCKET_POSIX_H_
#define taa_SOCKET_POSIX_H_

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <errno.h>

#define taa_SOCKET_FD_CLR_TARGET(s_, fdset_) \
    FD_CLR((int) (ptrdiff_t) (s_), fdset_)

#define taa_SOCKET_FD_ISSET_TARGET(s_, fdset_) \
    FD_ISSET((int) (ptrdiff_t) (s_), fdset_)

#define taa_SOCKET_FD_SET_TARGET(s_, fdset_) \
    FD_SET((int) (ptrdiff_t) (s_), fdset_)

#define taa_SOCKET_FD_ZERO_TARGET(fdset_) \
    FD_ZERO(fdset_)

#define taa_SOCKET_INVALID_TARGET ((taa_socket) (-1))

enum
{
    taa_SOCKET_AI_PASSIVE_TARGET     = AI_PASSIVE    ,
    taa_SOCKET_AI_CANONNAME_TARGET   = AI_CANONNAME  ,
    taa_SOCKET_AI_NUMERICHOST_TARGET = AI_NUMERICHOST,
};

enum
{
    taa_SOCKET_FIONBIO_TARGET    = FIONBIO   ,
    taa_SOCKET_FIONREAD_TARGET   = FIONREAD  ,
    taa_SOCKET_SIOCATMARK_TARGET = SIOCATMARK
};

enum
{
    taa_SOCKET_AF_UNSPEC_TARGET = AF_UNSPEC,
    taa_SOCKET_AF_INET_TARGET   = AF_INET  ,
    taa_SOCKET_AF_INET6_TARGET  = AF_INET6 ,
};

enum
{
    taa_SOCKET_IPPROTO_TCP_TARGET = IPPROTO_TCP,
    taa_SOCKET_IPPROTO_UDP_TARGET = IPPROTO_UDP,
};

enum
{
    taa_SOCKET_STREAM_TARGET = SOCK_STREAM,
    taa_SOCKET_DGRAM_TARGET  = SOCK_DGRAM ,
};

enum
{
    taa_SOCKET_MSG_OOB_TARGET       = MSG_OOB      ,
    taa_SOCKET_MSG_PEEK_TARGET      = MSG_PEEK     ,
    taa_SOCKET_MSG_DONTROUTE_TARGET = MSG_DONTROUTE,
};

enum
{
    taa_SOCKET_NI_NOFQDN_TARGET      = NI_NOFQDN      ,
    taa_SOCKET_NI_NUMERICHOST_TARGET = NI_NUMERICHOST ,
    taa_SOCKET_NI_NAMEREQD_TARGET    = NI_NAMEREQD    ,
    taa_SOCKET_NI_NUMERICSERV_TARGET = NI_NUMERICSERV ,
    taa_SOCKET_NI_DGRAM_TARGET       = NI_DGRAM       ,
};

enum
{
    taa_SOCKET_SO_DEBUG_TARGET      = SO_DEBUG     ,
    taa_SOCKET_SO_ACCEPTCONN_TARGET = SO_ACCEPTCONN,
    taa_SOCKET_SO_REUSEADDR_TARGET  = SO_REUSEADDR ,
    taa_SOCKET_SO_KEEPALIVE_TARGET  = SO_KEEPALIVE ,
    taa_SOCKET_SO_DONTROUTE_TARGET  = SO_DONTROUTE ,
    taa_SOCKET_SO_BROADCAST_TARGET  = SO_BROADCAST ,
    taa_SOCKET_SO_LINGER_TARGET     = SO_LINGER    ,
    taa_SOCKET_SO_OOBINLINE_TARGET  = SO_OOBINLINE ,
    taa_SOCKET_SO_SNDBUF_TARGET     = SO_SNDBUF    ,
    taa_SOCKET_SO_RCVBUF_TARGET     = SO_RCVBUF    ,
    taa_SOCKET_SO_ERROR_TARGET      = SO_ERROR     ,
    taa_SOCKET_SO_TYPE_TARGET       = SO_TYPE      ,
    taa_SOCKET_SO_RCVTIMEO_TARGET   = SO_RCVTIMEO  ,
    taa_SOCKET_SO_SNDTIMEO_TARGET   = SO_SNDTIMEO  ,
    taa_SOCKET_TCP_NODELAY_TARGET   = TCP_NODELAY  ,
};

enum
{
    taa_SOCKET_EINTR_TARGET           = EINTR          ,
    taa_SOCKET_EBADF_TARGET           = EBADF          ,
    taa_SOCKET_EWOULDBLOCK_TARGET     = EWOULDBLOCK    ,
    taa_SOCKET_EACCES_TARGET          = EACCES         ,
    taa_SOCKET_EFAULT_TARGET          = EFAULT         ,
    taa_SOCKET_EINVAL_TARGET          = EINVAL         ,
    taa_SOCKET_EMFILE_TARGET          = EMFILE         ,
    taa_SOCKET_ELOOP_TARGET           = ELOOP          ,
    taa_SOCKET_ENOTSOCK_TARGET        = ENOTSOCK       ,
    taa_SOCKET_EDESTADDRREQ_TARGET    = EDESTADDRREQ   ,
    taa_SOCKET_EMSGSIZE_TARGET        = EMSGSIZE       ,
    taa_SOCKET_EPROTOTYPE_TARGET      = EPROTOTYPE     ,
    taa_SOCKET_ENOPROTOOPT_TARGET     = ENOPROTOOPT    ,
    taa_SOCKET_EPROTONOSUPPORT_TARGET = EPROTONOSUPPORT,
    taa_SOCKET_ESOCKTNOSUPPORT_TARGET = ESOCKTNOSUPPORT,
    taa_SOCKET_EOPNOTSUPP_TARGET      = EOPNOTSUPP     ,
    taa_SOCKET_EPFNOSUPPORT_TARGET    = EPFNOSUPPORT   ,
    taa_SOCKET_EAFNOSUPPORT_TARGET    = EAFNOSUPPORT   ,
    taa_SOCKET_EADDRINUSE_TARGET      = EADDRINUSE     ,
    taa_SOCKET_EADDRNOTAVAIL_TARGET   = EADDRNOTAVAIL  ,
    taa_SOCKET_ENETDOWN_TARGET        = ENETDOWN       ,
    taa_SOCKET_ENETUNREACH_TARGET     = ENETUNREACH    ,
    taa_SOCKET_ENETRESET_TARGET       = ENETRESET      ,
    taa_SOCKET_ECONNABORTED_TARGET    = ECONNABORTED   ,
    taa_SOCKET_ECONNRESET_TARGET      = ECONNRESET     ,
    taa_SOCKET_ENOBUFS_TARGET         = ENOBUFS        ,
    taa_SOCKET_EISCONN_TARGET         = EISCONN        ,
    taa_SOCKET_ENOTCONN_TARGET        = ENOTCONN       ,
    taa_SOCKET_ESHUTDOWN_TARGET       = ESHUTDOWN      ,
    taa_SOCKET_ETOOMANYREFS_TARGET    = ETOOMANYREFS   ,
    taa_SOCKET_ETIMEDOUT_TARGET       = ETIMEDOUT      ,
    taa_SOCKET_ECONNREFUSED_TARGET    = ECONNREFUSED   ,
    taa_SOCKET_EHOSTDOWN_TARGET       = EHOSTDOWN      ,
    taa_SOCKET_EHOSTUNREACH_TARGET    = EHOSTUNREACH   ,
    taa_SOCKET_EALREADY_TARGET        = EALREADY       ,
    taa_SOCKET_EINPROGRESS_TARGET     = EINPROGRESS    ,
    taa_SOCKET_ESTALE_TARGET          = ESTALE         ,
};

enum
{
    taa_SOCKET_EAI_AGAIN_TARGET    = EAI_AGAIN   ,
    taa_SOCKET_EAI_BADFLAGS_TARGET = EAI_BADFLAGS,
    taa_SOCKET_EAI_FAIL_TARGET     = EAI_FAIL    ,
    taa_SOCKET_EAI_FAMILY_TARGET   = EAI_FAMILY  ,
    taa_SOCKET_EAI_MEMORY_TARGET   = EAI_MEMORY  ,
    taa_SOCKET_EAI_NONAME_TARGET   = EAI_NONAME  ,
    taa_SOCKET_EAI_SERVICE_TARGET  = EAI_SERVICE ,
    taa_SOCKET_EAI_SOCKTYPE_TARGET = EAI_SOCKTYPE,
};

typedef int taa_socket_target;

typedef struct sockaddr taa_socket_addr_target;

typedef struct addrinfo taa_socket_addrinfo_target;

typedef fd_set taa_socket_fd_set_target;

#endif // taa_SOCKET_POSIX_H_
