/**
*  @brief     socket implementation for win32
*  @author    Thomas Atwood (tatwood.net)
*  @date      2011
*  @copyright unlicense / public domain
* ***************************************************************************/
// only compile when included by socket.c
#ifdef taa_SOCKET_C_

#include <taa/socket.h>
#include <stdlib.h>
#include <string.h>

//****************************************************************************
int32_t taa_socket_accept(
    taa_socket socket,
    taa_socket_addr* address,
    uint32_t* address_len,
    taa_socket* sock_out)
{
    SOCKET s = accept(
        (SOCKET) socket,
        address,
        (int*) address_len);
    *sock_out = (taa_socket) s;
    return (s != INVALID_SOCKET) ? 0 : -1 ;
}

//****************************************************************************
int32_t taa_socket_bind(
    taa_socket socket,
    const taa_socket_addr* address,
    uint32_t address_len)
{
    return bind((SOCKET) socket, address, address_len);
}

//****************************************************************************
int32_t taa_socket_cleanup()
{
    return WSACleanup();
}

//****************************************************************************
int32_t taa_socket_close(
    taa_socket socket)
{
    return closesocket((SOCKET) socket);
}

//****************************************************************************
int32_t taa_socket_connect(
    taa_socket socket,
    const taa_socket_addr* address,
    uint32_t address_len)
{
    return connect(
        (SOCKET) socket,
        address,
        address_len);
}

//****************************************************************************
void taa_socket_freeaddrinfo(
    taa_socket_addrinfo* ai)
{
    freeaddrinfo(ai);
}

//****************************************************************************
taa_socket_aierror taa_socket_getaddrinfo(
    const char* nodename,
    const char* servname,
    int32_t ai_flags,
    int32_t ai_family,
    int32_t ai_socktype,
    int32_t ai_protocol,
    taa_socket_addrinfo** res)
{
    struct addrinfo hints;
    hints.ai_flags  = ai_flags;
    hints.ai_family = ai_family;
    hints.ai_socktype = ai_socktype;
    hints.ai_protocol = ai_protocol;
    hints.ai_addrlen = 0;
    hints.ai_addr = NULL;
    hints.ai_canonname = NULL;
    hints.ai_next = NULL;
    return (taa_socket_aierror) getaddrinfo(
        nodename,
        servname,
        &hints,
        res);
}

//****************************************************************************
taa_socket_error taa_socket_getlasterror()
{
    return WSAGetLastError();
}

//****************************************************************************
taa_socket_aierror taa_socket_getnameinfo(
    const taa_socket_addr *sa, 
    uint32_t salen,
    char* node,
    uint32_t nodelen,
    char *service,
    uint32_t servicelen,
    int32_t flags)
{
    return getnameinfo(
        sa,
        salen,
        node,
        nodelen,
        service,
        servicelen,
        flags);
}

//****************************************************************************
int32_t taa_socket_getpeername(
    taa_socket socket, 
    taa_socket_addr* address,
    uint32_t* address_len)
{
    return getpeername(
        (SOCKET) socket,
        address,
        (int*) address_len);
}

//****************************************************************************
int32_t taa_socket_getsockname(
    taa_socket socket,
    taa_socket_addr* address,
    uint32_t* address_len)
{
    return getsockname(
        (SOCKET) socket,
        address,
        (int*) address_len);
}

//****************************************************************************
int32_t taa_socket_getsockopt(
    taa_socket socket,
    taa_socket_option option_name,
    void* option_value,
    uint32_t* option_len)
{
    int32_t err = -1;
    if(
        option_name == taa_SOCKET_SO_RCVTIMEO ||
        option_name == taa_SOCKET_SO_SNDTIMEO)
    {
        uint32_t ms;
        uint32_t size;
        size = sizeof(ms);
        err = getsockopt(
            (SOCKET) socket,
            SOL_SOCKET,
            option_name,
            (char*) &ms,
            &size);
        if(err == 0)
        {
            struct timeval tv;
            tv.tv_sec = ms/1000;
            tv.tv_usec = (ms % 1000) * 1000;
            size = (*option_len >= sizeof(tv)) ? sizeof(tv) : *option_len;
            memcpy(option_value, &tv, size);
            *option_len = size;
        }
    }
    else
    {
        err = getsockopt(
            (SOCKET) socket,
            SOL_SOCKET,
            option_name,
            (char*) option_value,
            (int*) option_len);
    }
    return err;
}

//**************************************************************************** 
int32_t taa_socket_ioctl(
    taa_socket socket,
    taa_socket_cmd cmd,
    uint32_t* argp)
{
    return ioctlsocket((SOCKET) socket, cmd, (u_long*) argp);
}

//****************************************************************************
int32_t taa_socket_listen(
    taa_socket socket,
    int32_t backlog)
{
    return listen((SOCKET) socket, backlog);
}

//****************************************************************************
int32_t taa_socket_open(
    taa_socket_family domain,
    taa_socket_type type,
    int32_t protocol,
    taa_socket* sock_out)
{
    SOCKET s = socket(domain, type, protocol);
    *sock_out = (taa_socket) s;
    return (s != INVALID_SOCKET) ? 0 : -1;
}

//****************************************************************************
taa_socket_addrinfo* taa_socket_readaddrinfo(
    taa_socket_addrinfo* ai,
    taa_socket_family* ai_family_out,
    taa_socket_type* ai_socktype_out,
    taa_socket_protocol* ai_protocol_out,
    const char** ai_canonname_out,
    taa_socket_addr** ai_addr_out,
    uint32_t* ai_addrlen_out)
{
    if(ai_family_out != NULL)
    {
        *ai_family_out = (taa_socket_family) ai->ai_family;
    }
    if(ai_socktype_out != NULL)
    {
        *ai_socktype_out = (taa_socket_type) ai->ai_socktype;
    }
    if(ai_protocol_out != NULL)
    {
        *ai_protocol_out = (taa_socket_protocol) ai->ai_protocol;
    }
    if(ai_canonname_out != NULL)
    {
        *ai_canonname_out = ai->ai_canonname;
    }
    if(ai_addr_out != NULL)
    {
        *ai_addr_out = ai->ai_addr;
    }
    if(ai_addrlen_out != NULL)
    {
        *ai_addrlen_out = ai->ai_addrlen;
    }
    return ai->ai_next;
}

//****************************************************************************
int32_t taa_socket_recv(
    taa_socket socket,
    void* buffer,
    size_t length,
    int32_t flags)
{
    return recv((SOCKET) socket, (char*) buffer, length, flags);
}

//****************************************************************************
int32_t taa_socket_recvfrom(
    taa_socket socket,
    void* buffer,
    size_t length,
    int32_t flags,
    taa_socket_addr* address,
    uint32_t* address_len)
{
    return recvfrom(
        (SOCKET) socket,
        (char*) buffer,
        length,
        flags,
        address,
        (int*) address_len);
}

//****************************************************************************
int32_t taa_socket_select(
    ptrdiff_t nfds,
    taa_socket_fd_set *readfds,
    taa_socket_fd_set *writefds,
    taa_socket_fd_set *errorfds,
    struct timeval *time_out)
{
    return select((int) nfds, readfds, writefds, errorfds, time_out);
}

//****************************************************************************
int32_t taa_socket_send(
    taa_socket socket,
    const void* message,
    size_t length,
    int32_t flags)
{
    return send((SOCKET) socket, (char*) message, length, flags);
}

//****************************************************************************
int32_t taa_socket_sendto(
    taa_socket socket,
    const void* message,
    size_t length,
    int32_t flags,
    const taa_socket_addr* dest_addr,
    uint32_t dest_len)
{
    return sendto(
        (SOCKET) socket,
        (char*) message,
        length,
        flags,
        dest_addr,
        dest_len);
}

//****************************************************************************
int32_t taa_socket_setsockopt(
    taa_socket socket,
    taa_socket_option option_name,
    const void *option_value,
    uint32_t option_len)
{
    uint32_t ms;
    if(
        option_name == taa_SOCKET_SO_RCVTIMEO ||
        option_name == taa_SOCKET_SO_SNDTIMEO)
    {
        const struct timeval* tv = (const struct timeval*) option_value;
        if(option_len == sizeof(*tv))
        {
            ms = (tv->tv_sec*1000) + (tv->tv_usec/1000);
            option_value = &ms;
            option_len = sizeof(ms);
        }
    }
    return setsockopt(
        (SOCKET) socket,
        SOL_SOCKET,
        option_name,
        (const char*) option_value,
        option_len);
}

//****************************************************************************
int32_t taa_socket_startup()
{
    // winsock startup
    WSADATA wsadata;
    return (WSAStartup(MAKEWORD(2,0), &wsadata) == 0) ? 0 : -1;
}

#endif // taa_SOCKET_C_
