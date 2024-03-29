/**
 * @brief     win32 socket header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011 
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_SOCKET_WIN32_H_
#define taa_SOCKET_WIN32_H_

#include <winsock2.h>
#include <ws2tcpip.h>

#define taa_SOCKET_FD_CLR_TARGET(s_, fdset_) \
    FD_CLR((SOCKET) (s_), fdset_)

#define taa_SOCKET_FD_ISSET_TARGET(s_, fdset_) \
    FD_ISSET((SOCKET) (s_), fdset_)

#define taa_SOCKET_FD_SET_TARGET(s_, fdset_) \
    FD_SET((SOCKET) (s_), fdset_)

#define taa_SOCKET_FD_ZERO_TARGET(fdset_) \
    FD_ZERO(fdset_)

#define taa_SOCKET_INVALID_TARGET ((taa_socket) (INVALID_SOCKET))

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
    taa_SOCKET_EINTR_TARGET           = WSAEINTR          ,
    taa_SOCKET_EBADF_TARGET           = WSAEBADF          ,
    taa_SOCKET_EWOULDBLOCK_TARGET     = WSAEWOULDBLOCK    ,
    taa_SOCKET_EACCES_TARGET          = WSAEACCES         ,
    taa_SOCKET_EFAULT_TARGET          = WSAEFAULT         ,
    taa_SOCKET_EINVAL_TARGET          = WSAEINVAL         ,
    taa_SOCKET_EMFILE_TARGET          = WSAEMFILE         ,
    taa_SOCKET_ELOOP_TARGET           = WSAELOOP          ,
    taa_SOCKET_ENOTSOCK_TARGET        = WSAENOTSOCK       ,
    taa_SOCKET_EDESTADDRREQ_TARGET    = WSAEDESTADDRREQ   ,
    taa_SOCKET_EMSGSIZE_TARGET        = WSAEMSGSIZE       ,
    taa_SOCKET_EPROTOTYPE_TARGET      = WSAEPROTOTYPE     ,
    taa_SOCKET_ENOPROTOOPT_TARGET     = WSAENOPROTOOPT    ,
    taa_SOCKET_EPROTONOSUPPORT_TARGET = WSAEPROTONOSUPPORT,
    taa_SOCKET_ESOCKTNOSUPPORT_TARGET = WSAESOCKTNOSUPPORT,
    taa_SOCKET_EOPNOTSUPP_TARGET      = WSAEOPNOTSUPP     ,
    taa_SOCKET_EPFNOSUPPORT_TARGET    = WSAEPFNOSUPPORT   ,
    taa_SOCKET_EAFNOSUPPORT_TARGET    = WSAEAFNOSUPPORT   ,
    taa_SOCKET_EADDRINUSE_TARGET      = WSAEADDRINUSE     ,
    taa_SOCKET_EADDRNOTAVAIL_TARGET   = WSAEADDRNOTAVAIL  ,
    taa_SOCKET_ENETDOWN_TARGET        = WSAENETDOWN       ,
    taa_SOCKET_ENETUNREACH_TARGET     = WSAENETUNREACH    ,
    taa_SOCKET_ENETRESET_TARGET       = WSAENETRESET      ,
    taa_SOCKET_ECONNABORTED_TARGET    = WSAECONNABORTED   ,
    taa_SOCKET_ECONNRESET_TARGET      = WSAECONNRESET     ,
    taa_SOCKET_ENOBUFS_TARGET         = WSAENOBUFS        ,
    taa_SOCKET_EISCONN_TARGET         = WSAEISCONN        ,
    taa_SOCKET_ENOTCONN_TARGET        = WSAENOTCONN       ,
    taa_SOCKET_ESHUTDOWN_TARGET       = WSAESHUTDOWN      ,
    taa_SOCKET_ETOOMANYREFS_TARGET    = WSAETOOMANYREFS   ,
    taa_SOCKET_ETIMEDOUT_TARGET       = WSAETIMEDOUT      ,
    taa_SOCKET_ECONNREFUSED_TARGET    = WSAECONNREFUSED   ,
    taa_SOCKET_EHOSTDOWN_TARGET       = WSAEHOSTDOWN      ,
    taa_SOCKET_EHOSTUNREACH_TARGET    = WSAEHOSTUNREACH   ,
    taa_SOCKET_EALREADY_TARGET        = WSAEALREADY       ,
    taa_SOCKET_EINPROGRESS_TARGET     = WSAEINPROGRESS    ,
    taa_SOCKET_ESTALE_TARGET          = WSAESTALE         ,
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

typedef SOCKET taa_socket_target;

typedef struct sockaddr taa_socket_addr_target;

typedef struct addrinfo taa_socket_addrinfo_target;

typedef fd_set taa_socket_fd_set_target;

#endif // taa_SOCKET_WIN32_H_
