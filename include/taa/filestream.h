/**
 * @brief     buffered file io header
 * @details   TODO: support endian conversion
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_FILESTREAM_H_
#define taa_FILESTREAM_H_

#include <taa/system.h>
#include <stdio.h>

//****************************************************************************
// enums

enum taa_filestream_mode_e
{
    taa_FILESTREAM_READ,
    taa_FILESTREAM_WRITE
};

//****************************************************************************
// typedefs

typedef enum taa_filestream_mode_e taa_filestream_mode;
typedef struct taa_filestream_s taa_filestream;

//****************************************************************************
// structs

struct taa_filestream_s
{
    FILE* fp;
    uint8_t* buf;
    uint32_t capacity;
    uint32_t size;
    uint32_t offset;
};

//****************************************************************************
// functions

taa_SDK_LINKAGE void taa_filestream_create(
    FILE* fp,
    uint32_t bufsize,
    taa_filestream_mode mode,
    taa_filestream* fs_out);

taa_SDK_LINKAGE void taa_filestream_destroy(
    taa_filestream* fs);

taa_SDK_LINKAGE void taa_filestream_fetch(
    taa_filestream* fs);

taa_SDK_LINKAGE void taa_filestream_flush(
    taa_filestream* fs);

taa_SDK_LINKAGE int32_t taa_filestream_read_f32(
    taa_filestream* fs,
    void* f32_out);

taa_SDK_LINKAGE int32_t taa_filestream_read_f32n(
    taa_filestream* fs,
    void* f32_out,
    size_t n);

taa_SDK_LINKAGE int32_t taa_filestream_read_i8(
    taa_filestream* fs,
    void* i8_out);

taa_SDK_LINKAGE int32_t taa_filestream_read_i8n(
    taa_filestream* fs,
    void* i8_out,
    size_t n);

taa_SDK_LINKAGE int32_t taa_filestream_read_i16(
    taa_filestream* fs,
    void* i16_out);

taa_SDK_LINKAGE int32_t taa_filestream_read_i16n(
    taa_filestream* fs,
    void* i16_out,
    size_t n);

taa_SDK_LINKAGE int32_t taa_filestream_read_i32(
    taa_filestream* fs,
    void* i32_out);

taa_SDK_LINKAGE int32_t taa_filestream_read_i32n(
    taa_filestream* fs,
    void* i32_out,
    size_t n);

taa_SDK_LINKAGE int32_t taa_filestream_read_i64(
    taa_filestream* fs,
    void* i64_out);

taa_SDK_LINKAGE int32_t taa_filestream_read_i64n(
    taa_filestream* fs,
    void* i64_out,
    size_t n);

taa_SDK_LINKAGE void taa_filestream_write_i8(
    taa_filestream* fs,
    uint8_t i8);

taa_SDK_LINKAGE void taa_filestream_write_i8n(
    taa_filestream* fs,
    const void* i8,
    size_t n);

taa_SDK_LINKAGE void taa_filestream_write_i16(
    taa_filestream* fs,
    uint16_t i16);

taa_SDK_LINKAGE void taa_filestream_write_i16n(
    taa_filestream* fs,
    const void* i16,
    size_t n);

taa_SDK_LINKAGE void taa_filestream_write_i32(
    taa_filestream* fs,
    uint32_t i32);

taa_SDK_LINKAGE void taa_filestream_write_i32n(
    taa_filestream* fs,
    const void* i32,
    size_t n);

taa_SDK_LINKAGE void taa_filestream_write_i64(
    taa_filestream* fs,
    uint64_t i64);

taa_SDK_LINKAGE void taa_filestream_write_i64n(
    taa_filestream* fs,
    const void* i64,
    size_t n);

taa_SDK_LINKAGE void taa_filestream_write_f32(
    taa_filestream* fs,
    float f32);

taa_SDK_LINKAGE void taa_filestream_write_f32n(
    taa_filestream* fs,
    const void* f32,
    size_t n);

#endif // taa_FILESTREAM_H_
