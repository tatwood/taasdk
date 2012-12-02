/**
 * @brief     buffered file io implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#include <taa/filestream.h>
#include <stdlib.h>
#include <string.h>

//****************************************************************************
void taa_filestream_create(
    FILE* fp,
    uint32_t bufsize,
    taa_filestream_mode mode,
    taa_filestream* fs_out)
{
    fs_out->fp = fp;
    fs_out->buf = (uint8_t*) malloc(bufsize);
    fs_out->capacity = bufsize;
    fs_out->size = 0;
    fs_out->offset = 0;
}

//****************************************************************************
void taa_filestream_destroy(
    taa_filestream* fs)
{
    if(fs->offset != 0)
    {
        fwrite(fs->buf, 1, fs->offset, fs->fp);
    }
    free(fs->buf);
}

//****************************************************************************
void taa_filestream_fetch(
    taa_filestream* fs)
{
    uint32_t offset = fs->offset;
    uint32_t kept = fs->size - offset;
    memmove(fs->buf, fs->buf + offset, kept);
    fs->size = kept + fread(fs->buf+kept, 1, fs->capacity-kept, fs->fp);
    fs->offset = 0;
}

//****************************************************************************
void taa_filestream_flush(
    taa_filestream* fs)
{
    if(fs->offset > 0)
    {
        fwrite(fs->buf, 1, fs->offset, fs->fp);
        fs->offset = 0;
    }
}

//****************************************************************************
int32_t taa_filestream_read_f32(
    taa_filestream* fs,
    void* f32_out)
{
    return taa_filestream_read_i32(fs, f32_out);
}

//****************************************************************************
int32_t taa_filestream_read_f32n(
    taa_filestream* fs,
    void* f32_out,
    size_t n)
{
    return taa_filestream_read_i32n(fs, f32_out, n);
}

//****************************************************************************
int32_t taa_filestream_read_i8(
    taa_filestream* fs,
    void* i8_out)
{
    int32_t err = 0;
    do
    {
        uint8_t* i8 = (uint8_t*) i8_out;
        if((fs->offset + 1) > fs->size)
        {
            taa_filestream_fetch(fs);
            if((fs->offset + 1) > fs->size)
            {
                err = -1;
                break;
            }
        }
        i8[0] = fs->buf[fs->offset++];
    }
    while(0);
    return err;
}

//****************************************************************************
int32_t taa_filestream_read_i8n(
    taa_filestream* fs,
    void* i8_out,
    size_t n)
{
    int32_t err = 0;
    uint8_t* itr = (uint8_t*) i8_out;
    uint8_t* end = itr + n;
    while(itr != end)
    {
        size_t tn = (size_t) (end - itr);
        if(tn > fs->size)
        {
            tn = fs->size;
        }
        if((fs->offset + tn) > fs->size)
        {
            taa_filestream_fetch(fs);
            if((fs->offset + tn) > fs->size)
            {
                err = -1;
                break;
            }
        }
        memcpy(itr, fs->buf + fs->offset, tn);
        fs->offset += tn;
        itr += tn;
    }
    return err;
}

//****************************************************************************
int32_t taa_filestream_read_i16(
    taa_filestream* fs,
    void* i16_out)
{
    int32_t err = 0;
    do
    {
        uint16_t* i16 = (uint16_t*) i16_out;
        union
        {
            uint8_t i8[2];
            uint16_t i16;
        } ti16;
        if((fs->offset + sizeof(ti16.i16)) > fs->size)
        {
            taa_filestream_fetch(fs);
            if((fs->offset + sizeof(ti16.i16)) > fs->size)
            {
                err = -1;
                break;
            }
        }
        ti16.i8[0] = fs->buf[fs->offset++];
        ti16.i8[1] = fs->buf[fs->offset++];
        *i16 = ti16.i16;
    }
    while(0);
    return err;
}

//****************************************************************************
int32_t taa_filestream_read_i16n(
    taa_filestream* fs,
    void* i16_out,
    size_t n)
{
    int32_t err = 0;
    uint16_t* itr = (uint16_t*) i16_out;
    uint16_t* end = itr + n;
    while(itr != end)
    {
        err = taa_filestream_read_i16(fs, itr);
        if(err != 0)
        {
            break;
        }
        ++itr;
    }
    return err;
}

//****************************************************************************
int32_t taa_filestream_read_i32(
    taa_filestream* fs,
    void* i32_out)
{
    int32_t err = 0;
    do
    {
        uint32_t* i32 = (uint32_t*) i32_out;
        union
        {
            uint8_t i8[4];
            uint32_t i32;
        } ti32;
        if((fs->offset + sizeof(ti32.i32)) > fs->size)
        {
            taa_filestream_fetch(fs);
            if((fs->offset + sizeof(ti32.i32)) > fs->size)
            {
                err = -1;
                break;
            }
        }
        ti32.i8[0] = fs->buf[fs->offset++];
        ti32.i8[1] = fs->buf[fs->offset++];
        ti32.i8[2] = fs->buf[fs->offset++];
        ti32.i8[3] = fs->buf[fs->offset++];
        *i32 = ti32.i32;
    }
    while(0);
    return err;
}

//****************************************************************************
int32_t taa_filestream_read_i32n(
    taa_filestream* fs,
    void* i32_out,
    size_t n)
{
    int32_t err = 0;
    uint32_t* itr = (uint32_t*) i32_out;
    uint32_t* end = itr + n;
    while(itr != end)
    {
        err = taa_filestream_read_i32(fs, itr);
        if(err != 0)
        {
            break;
        }
        ++itr;
    }
    return err;
}

//****************************************************************************
int32_t taa_filestream_read_i64(
    taa_filestream* fs,
    void* i64_out)
{
    int32_t err = 0;
    do
    {
        uint64_t* i64 = (uint64_t*) i64_out;
        union
        {
            uint8_t i8[8];
            uint64_t i64;
        } ti64;
        if((fs->offset + sizeof(ti64.i64)) > fs->size)
        {
            taa_filestream_fetch(fs);
            if((fs->offset + sizeof(ti64.i64)) > fs->size)
            {
                err = -1;
                break;
            }
        }
        ti64.i8[0] = fs->buf[fs->offset++];
        ti64.i8[1] = fs->buf[fs->offset++];
        ti64.i8[2] = fs->buf[fs->offset++];
        ti64.i8[3] = fs->buf[fs->offset++];
        ti64.i8[4] = fs->buf[fs->offset++];
        ti64.i8[5] = fs->buf[fs->offset++];
        ti64.i8[6] = fs->buf[fs->offset++];
        ti64.i8[7] = fs->buf[fs->offset++];
        *i64 = ti64.i64;
    }
    while(0);
    return err;
}

//****************************************************************************
int32_t taa_filestream_read_i64n(
    taa_filestream* fs,
    void* i64_out,
    size_t n)
{
    int32_t err = 0;
    uint64_t* itr = (uint64_t*) i64_out;
    uint64_t* end = itr + n;
    while(itr != end)
    {
        err = taa_filestream_read_i64(fs, itr);
        if(err != 0)
        {
            break;
        }
        ++itr;
    }
    return err;
}

//****************************************************************************
void taa_filestream_write_f32(
    taa_filestream* fs,
    float f32)
{
    union
    {
        uint32_t i32;
        float f32;
    } tf32;
    tf32.f32 = f32;
    taa_filestream_write_i32(fs, tf32.i32);
}

//****************************************************************************
void taa_filestream_write_f32n(
    taa_filestream* fs,
    const void* f32,
    size_t n)
{
    const float* itr = (const float*) f32;
    const float* end = itr + n;
    while(itr != end)
    {
        taa_filestream_write_f32(fs, *itr);
        ++itr;
    }
}

//****************************************************************************
void taa_filestream_write_i8(
    taa_filestream* fs,
    uint8_t i8)
{
    if((fs->offset + 1) > fs->capacity)
    {
        taa_filestream_flush(fs);
    }
    fs->buf[fs->offset++] = i8;
}

//****************************************************************************
void taa_filestream_write_i8n(
    taa_filestream* fs,
    const void* i8,
    size_t n)
{
    const uint8_t* itr = (const uint8_t*) i8;
    const uint8_t* end = itr + n;
    while(itr != end)
    {
        size_t tn = (size_t) (end - itr);
        if(tn > fs->capacity)
        {
            tn = fs->capacity;
        }
        if((fs->offset + tn) > fs->capacity)
        {
            taa_filestream_flush(fs);
        }
        memcpy(fs->buf + fs->offset, itr, tn);
        fs->offset += tn;
        itr += tn;
    }
}

//****************************************************************************
void taa_filestream_write_i16(
    taa_filestream* fs,
    uint16_t i16)
{
    union
    {
        uint8_t i8[2];
        uint16_t i16;
    } ti16;
    if((fs->offset + sizeof(ti16.i16)) > fs->capacity)
    {
        taa_filestream_flush(fs);
    }
    ti16.i16 = i16;
    fs->buf[fs->offset++] = ti16.i8[0];
    fs->buf[fs->offset++] = ti16.i8[1];
}

//****************************************************************************
void taa_filestream_write_i16n(
    taa_filestream* fs,
    const void* i16,
    size_t n)
{
    const uint16_t* itr = (const uint16_t*) i16;
    const uint16_t* end = itr + n;
    while(itr != end)
    {
        taa_filestream_write_i16(fs, *itr);
        ++itr;
    }
}

//****************************************************************************
void taa_filestream_write_i32(
    taa_filestream* fs,
    uint32_t i32)
{
    union
    {
        uint8_t i8[4];
        uint32_t i32;
    } ti32;
    if((fs->offset + sizeof(ti32.i32)) > fs->capacity)
    {
        taa_filestream_flush(fs);
    }
    ti32.i32 = i32;
    fs->buf[fs->offset++] = ti32.i8[0];
    fs->buf[fs->offset++] = ti32.i8[1];
    fs->buf[fs->offset++] = ti32.i8[2];
    fs->buf[fs->offset++] = ti32.i8[3];
}

//****************************************************************************
void taa_filestream_write_i32n(
    taa_filestream* fs,
    const void* i32,
    size_t n)
{
    const uint32_t* itr = (const uint32_t*) i32;
    const uint32_t* end = itr + n;
    while(itr != end)
    {
        taa_filestream_write_i32(fs, *itr);
        ++itr;
    }
}

//****************************************************************************
void taa_filestream_write_i64(
    taa_filestream* fs,
    uint64_t i64)
{
    union
    {
        uint8_t i8[8];
        uint64_t i64;
    } ti64;
    if((fs->offset + + sizeof(ti64.i64)) > fs->capacity)
    {
        taa_filestream_flush(fs);
    }
    ti64.i64 = i64;
    fs->buf[fs->offset++] = ti64.i8[0];
    fs->buf[fs->offset++] = ti64.i8[1];
    fs->buf[fs->offset++] = ti64.i8[2];
    fs->buf[fs->offset++] = ti64.i8[3];
    fs->buf[fs->offset++] = ti64.i8[4];
    fs->buf[fs->offset++] = ti64.i8[5];
    fs->buf[fs->offset++] = ti64.i8[6];
    fs->buf[fs->offset++] = ti64.i8[7];
}

//****************************************************************************
void taa_filestream_write_i64n(
    taa_filestream* fs,
    const void* i64,
    size_t n)
{
    const uint64_t* itr = (const uint64_t*) i64;
    const uint64_t* end = itr + n;
    while(itr != end)
    {
        taa_filestream_write_i64(fs, *itr);
        ++itr;
    }
}
