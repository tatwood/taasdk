#if defined(_DEBUG) && defined(_MSC_FULL_VER)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <taa/path.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef NDEBUG
#error asserts are not enabled
#endif

static int cmp_path(const char* a, const char* b)
{
    int result = strcmp(a, b);
    if(result != 0)
    {
        printf("fail: %s != %s\n", a, b);    
    }
    return result;
}

static void test_path()
{
    enum
    {
        SEP_SLASH = taa_PATH_SLASH,
        REV_SLASH = (SEP_SLASH == '/') ? '\\' : '/'
    };

    char path[taa_PATH_SIZE];
    char tmp[taa_PATH_SIZE]; // working buffer
    char tgt[taa_PATH_SIZE]; // target result

    // try to throw a bunch of confusing cases at it

    sprintf(tgt, "..%crel", SEP_SLASH);
    taa_path_set(path, sizeof(path), tgt);
    assert(cmp_path(tgt, path) == 0);
    sprintf(tmp, "%c", SEP_SLASH);
    strcat(tgt, tmp);
    taa_path_set(path, sizeof(path), "..////////////////rel//");
    assert(cmp_path(tgt, path) == 0);
    taa_path_set(path, sizeof(path), "");
    assert(path[0] == '\0');
    taa_path_set(path, sizeof(path), "..\\\\\\\\\\\\\\rel\\\\");
    assert(cmp_path(tgt, path) == 0);

    sprintf(tgt, ".%c", SEP_SLASH);
    taa_path_set(path, sizeof(path), "././././././././");
    assert(cmp_path(tgt, path) == 0);
    taa_path_set(path, sizeof(path), ".\\.\\.\\.\\.\\.\\.\\");
    assert(cmp_path(tgt, path) == 0);
    
    sprintf(tgt, "..%c..%c..%c",SEP_SLASH,SEP_SLASH,SEP_SLASH);
    taa_path_set(path, sizeof(path), "../../dir/../../");
    assert(cmp_path(tgt, path) == 0);    
    taa_path_set(path, sizeof(path), "..\\..\\dir\\..\\..\\");
    assert(cmp_path(tgt, path) == 0); 
    
    sprintf(tgt, ".%c..%c..%c..%c",SEP_SLASH,SEP_SLASH,SEP_SLASH,SEP_SLASH);
    taa_path_set(path, sizeof(path), "./../.././../../");
    assert(cmp_path(tgt, path) == 0);    
    taa_path_set(path, sizeof(path), ".\\..\\..\\.\\..\\..\\");
    assert(cmp_path(tgt, path) == 0);     

    sprintf(tgt, ".%cdir0%cdir1%cfile.ext",SEP_SLASH,SEP_SLASH,SEP_SLASH);
    sprintf(tmp, ".%cdir0%cdir5%c", SEP_SLASH, SEP_SLASH, SEP_SLASH);
    taa_path_set(path, sizeof(path), tmp);
    sprintf(tmp, "..%cdir1%c%cdir6", SEP_SLASH, REV_SLASH, REV_SLASH);
    taa_path_append(path, sizeof(path), tmp);
    sprintf(tmp, "%cdir7%c..", SEP_SLASH, REV_SLASH);
    taa_path_append(path, sizeof(path), tmp);
    sprintf(tmp, "..%c.%cfile.ext", SEP_SLASH, SEP_SLASH);
    taa_path_append(path, sizeof(path), tmp);
    assert(cmp_path(tgt, path) == 0);
    taa_path_get_dir(path, tmp, sizeof(tmp));
    assert(strlen(tmp) == 11);
    assert(!memcmp(tgt, tmp, 11));
    taa_path_get_file(path, tmp, sizeof(tmp));
    assert(cmp_path(tgt + 12, tmp) == 0);
    taa_path_get_ext(path, tmp, sizeof(tmp));
    assert(cmp_path(tgt + 17, tmp) == 0);
}

int main(int argc, char* argv[])
{
    printf("testing taa_path...");
    fflush(stdout);
    test_path();
    printf("pass\n");

#if defined(_DEBUG) && defined(_MSC_FULL_VER)
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtCheckMemory();
    _CrtDumpMemoryLeaks();
#endif
    return EXIT_SUCCESS;
}
