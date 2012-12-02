/**
 * @brief     target agnostic socket header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011 
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_SOCKET_H_
#define taa_SOCKET_H_

#include "system.h"

#ifdef WIN32
#include "socket_win32.h"
#else
#include "socket_posix.h"
#endif

#define taa_socket_htonl htonl

#define taa_socket_htons htons

#define taa_socket_ntohl ntohl

#define taa_socket_ntohs ntohs

#define taa_SOCKET_FD_CLR(s_, fdset_) \
    taa_SOCKET_FD_CLR_TARGET(s_, fdset_)

#define taa_SOCKET_FD_ISSET(s_, fdset_) \
    taa_SOCKET_FD_ISSET_TARGET(s_, fdset_)

#define taa_SOCKET_FD_SET(s_, fdset_) \
    taa_SOCKET_FD_SET_TARGET(s_, fdset_)

#define taa_SOCKET_FD_ZERO(fdset_) \
    taa_SOCKET_FD_ZERO_TARGET(fdset_)

#define taa_SOCKET_INVALID taa_SOCKET_INVALID_TARGET

//****************************************************************************
// enums

enum taa_socket_aiflags_e
{
    taa_SOCKET_AI_PASSIVE     = taa_SOCKET_AI_PASSIVE_TARGET     ,
    taa_SOCKET_AI_CANONNAME   = taa_SOCKET_AI_CANONNAME_TARGET   ,
    taa_SOCKET_AI_NUMERICHOST = taa_SOCKET_AI_NUMERICHOST_TARGET ,
};

enum taa_socket_cmd_e
{
    taa_SOCKET_FIONBIO    = taa_SOCKET_FIONBIO_TARGET    ,
    taa_SOCKET_FIONREAD   = taa_SOCKET_FIONREAD_TARGET   ,
    taa_SOCKET_SIOCATMARK = taa_SOCKET_SIOCATMARK_TARGET ,
};

enum taa_socket_family_e
{
    taa_SOCKET_AF_UNSPEC = taa_SOCKET_AF_UNSPEC_TARGET,
    taa_SOCKET_AF_INET   = taa_SOCKET_AF_INET_TARGET  ,
    taa_SOCKET_AF_INET6  = taa_SOCKET_AF_INET6_TARGET ,
};

enum taa_socket_protocol_e
{
    taa_SOCKET_IPPROTO_TCP = taa_SOCKET_IPPROTO_TCP_TARGET,
    taa_SOCKET_IPPROTO_UDP = taa_SOCKET_IPPROTO_UDP_TARGET,
};

enum taa_socket_type_e
{
    taa_SOCKET_STREAM = taa_SOCKET_STREAM_TARGET,
    taa_SOCKET_DGRAM  = taa_SOCKET_DGRAM_TARGET ,
};

enum taa_socket_msgflags_e
{
    taa_SOCKET_MSG_OOB       = taa_SOCKET_MSG_OOB_TARGET      ,
    taa_SOCKET_MSG_PEEK      = taa_SOCKET_MSG_PEEK_TARGET     ,
    taa_SOCKET_MSG_DONTROUTE = taa_SOCKET_MSG_DONTROUTE_TARGET,
};

enum taa_socket_niflags_e
{
    taa_SOCKET_NI_NOFQDN      = taa_SOCKET_NI_NOFQDN_TARGET     ,
    taa_SOCKET_NI_NUMERICHOST = taa_SOCKET_NI_NUMERICHOST_TARGET,
    taa_SOCKET_NI_NAMEREQD    = taa_SOCKET_NI_NAMEREQD_TARGET   ,
    taa_SOCKET_NI_NUMERICSERV = taa_SOCKET_NI_NUMERICSERV_TARGET,
    taa_SOCKET_NI_DGRAM       = taa_SOCKET_NI_DGRAM_TARGET      ,
};

enum taa_socket_option_e
{
    taa_SOCKET_SO_DEBUG      = taa_SOCKET_SO_DEBUG_TARGET     ,
    taa_SOCKET_SO_ACCEPTCONN = taa_SOCKET_SO_ACCEPTCONN_TARGET,
    taa_SOCKET_SO_REUSEADDR  = taa_SOCKET_SO_REUSEADDR_TARGET ,
    taa_SOCKET_SO_KEEPALIVE  = taa_SOCKET_SO_KEEPALIVE_TARGET ,
    taa_SOCKET_SO_DONTROUTE  = taa_SOCKET_SO_DONTROUTE_TARGET ,
    taa_SOCKET_SO_BROADCAST  = taa_SOCKET_SO_BROADCAST_TARGET ,
    taa_SOCKET_SO_LINGER     = taa_SOCKET_SO_LINGER_TARGET    ,
    taa_SOCKET_SO_OOBINLINE  = taa_SOCKET_SO_OOBINLINE_TARGET ,
    taa_SOCKET_SO_SNDBUF     = taa_SOCKET_SO_SNDBUF_TARGET    ,
    taa_SOCKET_SO_RCVBUF     = taa_SOCKET_SO_RCVBUF_TARGET    ,
    taa_SOCKET_SO_ERROR      = taa_SOCKET_SO_ERROR_TARGET     ,
    taa_SOCKET_SO_TYPE       = taa_SOCKET_SO_TYPE_TARGET      ,
    taa_SOCKET_SO_RCVTIMEO   = taa_SOCKET_SO_RCVTIMEO_TARGET  ,
    taa_SOCKET_SO_SNDTIMEO   = taa_SOCKET_SO_SNDTIMEO_TARGET  ,
    taa_SOCKET_TCP_NODELAY   = taa_SOCKET_TCP_NODELAY_TARGET  ,
};

enum taa_socket_error_e
{
    taa_SOCKET_ENONE           = 0                                ,
    taa_SOCKET_EINTR           = taa_SOCKET_EINTR_TARGET          ,
    taa_SOCKET_EBADF           = taa_SOCKET_EBADF_TARGET          ,
    taa_SOCKET_EWOULDBLOCK     = taa_SOCKET_EWOULDBLOCK_TARGET    ,
    taa_SOCKET_EACCES          = taa_SOCKET_EACCES_TARGET         ,
    taa_SOCKET_EFAULT          = taa_SOCKET_EFAULT_TARGET         ,
    taa_SOCKET_EINVAL          = taa_SOCKET_EINVAL_TARGET         ,
    taa_SOCKET_EMFILE          = taa_SOCKET_EMFILE_TARGET         ,
    taa_SOCKET_ELOOP           = taa_SOCKET_ELOOP_TARGET          ,
    taa_SOCKET_ENOTSOCK        = taa_SOCKET_ENOTSOCK_TARGET       ,
    taa_SOCKET_EDESTADDRREQ    = taa_SOCKET_EDESTADDRREQ_TARGET   ,
    taa_SOCKET_EMSGSIZE        = taa_SOCKET_EMSGSIZE_TARGET       ,
    taa_SOCKET_EPROTOTYPE      = taa_SOCKET_EPROTOTYPE_TARGET     ,
    taa_SOCKET_ENOPROTOOPT     = taa_SOCKET_ENOPROTOOPT_TARGET    ,
    taa_SOCKET_EPROTONOSUPPORT = taa_SOCKET_EPROTONOSUPPORT_TARGET,
    taa_SOCKET_ESOCKTNOSUPPORT = taa_SOCKET_ESOCKTNOSUPPORT_TARGET,
    taa_SOCKET_EOPNOTSUPP      = taa_SOCKET_EOPNOTSUPP_TARGET     ,
    taa_SOCKET_EPFNOSUPPORT    = taa_SOCKET_EPFNOSUPPORT_TARGET   ,
    taa_SOCKET_EAFNOSUPPORT    = taa_SOCKET_EAFNOSUPPORT_TARGET   ,
    taa_SOCKET_EADDRINUSE      = taa_SOCKET_EADDRINUSE_TARGET     ,
    taa_SOCKET_EADDRNOTAVAIL   = taa_SOCKET_EADDRNOTAVAIL_TARGET  ,
    taa_SOCKET_ENETDOWN        = taa_SOCKET_ENETDOWN_TARGET       ,
    taa_SOCKET_ENETUNREACH     = taa_SOCKET_ENETUNREACH_TARGET    ,
    taa_SOCKET_ENETRESET       = taa_SOCKET_ENETRESET_TARGET      ,
    taa_SOCKET_ECONNABORTED    = taa_SOCKET_ECONNABORTED_TARGET   ,
    taa_SOCKET_ECONNRESET      = taa_SOCKET_ECONNRESET_TARGET     ,
    taa_SOCKET_ENOBUFS         = taa_SOCKET_ENOBUFS_TARGET        ,
    taa_SOCKET_EISCONN         = taa_SOCKET_EISCONN_TARGET        ,
    taa_SOCKET_ENOTCONN        = taa_SOCKET_ENOTCONN_TARGET       ,
    taa_SOCKET_ESHUTDOWN       = taa_SOCKET_ESHUTDOWN_TARGET      ,
    taa_SOCKET_ETOOMANYREFS    = taa_SOCKET_ETOOMANYREFS_TARGET   ,
    taa_SOCKET_ETIMEDOUT       = taa_SOCKET_ETIMEDOUT_TARGET      ,
    taa_SOCKET_ECONNREFUSED    = taa_SOCKET_ECONNREFUSED_TARGET   ,
    taa_SOCKET_EHOSTDOWN       = taa_SOCKET_EHOSTDOWN_TARGET      ,
    taa_SOCKET_EHOSTUNREACH    = taa_SOCKET_EHOSTUNREACH_TARGET   ,
    taa_SOCKET_EALREADY        = taa_SOCKET_EALREADY_TARGET       ,
    taa_SOCKET_EINPROGRESS     = taa_SOCKET_EINPROGRESS_TARGET    ,
    taa_SOCKET_ESTALE          = taa_SOCKET_ESTALE_TARGET         ,
};

enum taa_socket_aierror_e
{
    taa_SOCKET_EAI_NONE     = 0                             ,
    taa_SOCKET_EAI_AGAIN    = taa_SOCKET_EAI_AGAIN_TARGET   ,
    taa_SOCKET_EAI_BADFLAGS = taa_SOCKET_EAI_BADFLAGS_TARGET,
    taa_SOCKET_EAI_FAIL     = taa_SOCKET_EAI_FAIL_TARGET    ,
    taa_SOCKET_EAI_FAMILY   = taa_SOCKET_EAI_FAMILY_TARGET  ,
    taa_SOCKET_EAI_MEMORY   = taa_SOCKET_EAI_MEMORY_TARGET  ,
    taa_SOCKET_EAI_NONAME   = taa_SOCKET_EAI_NONAME_TARGET  ,
    taa_SOCKET_EAI_SERVICE  = taa_SOCKET_EAI_SERVICE_TARGET ,
    taa_SOCKET_EAI_SOCKTYPE = taa_SOCKET_EAI_SOCKTYPE_TARGET,
};

//****************************************************************************
// typedefs

typedef enum taa_socket_aiflags_e taa_socket_aiflags;  
typedef enum taa_socket_cmd_e taa_socket_cmd;
typedef enum taa_socket_family_e taa_socket_family;
typedef enum taa_socket_protocol_e taa_socket_protocol;
typedef enum taa_socket_type_e taa_socket_type;
typedef enum taa_socket_option_e taa_socket_option;
typedef enum taa_socket_error_e taa_socket_error;
typedef enum taa_socket_aierror_e taa_socket_aierror;

/**
 * @details on win32, this is a (SOCKET) handle; on posix, this is a (int)
 * descriptor.
 */
typedef taa_socket_target taa_socket;

/**
 * @brief opaque type representing sockaddr struct
 * @details this is a native struct sockaddr
 */
typedef taa_socket_addr_target taa_socket_addr;

/**
 * @brief opaque type representing addrinfo struct
 * @details this is a native struct addrinfo
 */
typedef taa_socket_addrinfo_target taa_socket_addrinfo;

typedef taa_socket_fd_set_target taa_socket_fd_set;

//****************************************************************************
// structs

struct taa_socket_addr_s
{
    uint8_t data[28];
};

//****************************************************************************'
// functions

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int32_t taa_socket_accept(
    taa_socket socket,
    taa_socket_addr* address,
    uint32_t* address_len,
    taa_socket* sock_out);

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int32_t taa_socket_bind(
    taa_socket socket,
    const taa_socket_addr* address,
    uint32_t address_len);

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int32_t taa_socket_cleanup();

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int32_t taa_socket_close(
    taa_socket socket); 

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int32_t taa_socket_connect(
    taa_socket socket,
    const taa_socket_addr* address,
    uint32_t address_len);

taa_SDK_LINKAGE void taa_socket_freeaddrinfo(
    taa_socket_addrinfo* ai);

taa_SDK_LINKAGE taa_socket_aierror taa_socket_getaddrinfo(
    const char* nodename,
    const char* servname,
    int32_t ai_flags,
    int32_t ai_family,
    int32_t ai_socktype,
    int32_t ai_protocol,
    taa_socket_addrinfo** res);

taa_SDK_LINKAGE taa_socket_error taa_socket_getlasterror();

taa_SDK_LINKAGE taa_socket_aierror taa_socket_getnameinfo(
    const taa_socket_addr *sa, 
    uint32_t salen,
    char* node,
    uint32_t nodelen,
    char *service,
    uint32_t servicelen,
    int32_t flags);

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int32_t taa_socket_getpeername(
    taa_socket socket, 
    taa_socket_addr* address,
    uint32_t* address_len);

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int32_t taa_socket_getsockname(
    taa_socket socket,
    taa_socket_addr* address,
    uint32_t* address_len);

/**
 * @details if the option name is taa_SOCKET_SO_RCVTIMEO or
 * taa_SOCKET_SO_SNDTIMEO, the value should be of type
 * struct timeval*, otherwise it should be a 32 bit int.
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int32_t taa_socket_getsockopt(
    taa_socket socket,
    taa_socket_option option_name,
    void* option_value,
    uint32_t* option_len);

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int32_t taa_socket_ioctl(
    taa_socket socket,
    taa_socket_cmd cmd,
    uint32_t* argp);

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int32_t taa_socket_listen(
    taa_socket socket,
    int32_t backlog);

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int32_t taa_socket_open(
    taa_socket_family domain,
    taa_socket_type type,
    int32_t protocol,
    taa_socket* sock_out);

/**
 * @brief exposes the contents of taa_socket_addrinfo and increments iterator
 * @details if an out param is not NULL, it will the contents of the address
 *          info struct. if an out param is NULL, it will be ignored.
 * @return the next addrinfo structure in the list, or NULL at end
 */
taa_SDK_LINKAGE taa_socket_addrinfo* taa_socket_readaddrinfo(
    taa_socket_addrinfo* ai,
    taa_socket_family* ai_family_out,
    taa_socket_type* ai_socktype_out,
    taa_socket_protocol* ai_protocol_out,
    const char** ai_canonname_out,
    taa_socket_addr** ai_addr_out,
    uint32_t* ai_addrlen_out);

taa_SDK_LINKAGE int32_t taa_socket_recv(
    taa_socket socket,
    void* buffer,
    size_t length,
    int32_t flags);

taa_SDK_LINKAGE int32_t taa_socket_recvfrom(
    taa_socket socket,
    void* buffer,
    size_t length,
    int32_t flags,
    taa_socket_addr* address,
    uint32_t* address_len);

taa_SDK_LINKAGE int32_t taa_socket_select(
    ptrdiff_t nfds,
    taa_socket_fd_set *readfds,
    taa_socket_fd_set *writefds,
    taa_socket_fd_set *errorfds,
    struct timeval *time_out);

taa_SDK_LINKAGE int32_t taa_socket_send(
    taa_socket socket,
    const void* message,
    size_t length,
    int32_t flags);

taa_SDK_LINKAGE int32_t taa_socket_sendto(
    taa_socket socket,
    const void* message,
    size_t length,
    int32_t flags,
    const taa_socket_addr* dest_addr,
    uint32_t dest_len);

/**
 * @details if the option name is taa_SOCKET_SO_RCVTIMEO or
 * taa_SOCKET_SO_SNDTIMEO, the value should be of type
 * struct timeval*, otherwise it should be a 32 bit int.
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int32_t taa_socket_setsockopt(
    taa_socket socket,
    taa_socket_option option_name,
    const void *option_value,
    uint32_t option_len);

taa_SDK_LINKAGE int32_t taa_socket_startup();

#endif // taa_SOCKET_H_
