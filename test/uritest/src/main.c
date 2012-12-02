#if defined(_DEBUG) && defined(_MSC_FULL_VER)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <taa/uri.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef NDEBUG
#error asserts are not enabled
#endif

static int cmp_uri(const char* a, const char* b)
{
    int result = strcmp(a, b);
    if(result != 0)
    {
        printf("fail: %s != %s\n", a, b);    
    }
    return result;
}

static void test_uri()
{
    char uri[taa_URI_SIZE];
    char tmp[taa_URI_SIZE];
    uri[0] = '\0';
    // attempt setting components of uri
    taa_uri_set_scheme(uri, sizeof(uri), "http");
    assert(cmp_uri("http://", uri) == 0);
    taa_uri_set_host(uri, sizeof(uri), "www.tatwood.net");
    assert(cmp_uri("http://www.tatwood.net/", uri) == 0);
    taa_uri_set_path(uri, sizeof(uri), "/index.html");
    assert(cmp_uri("http://www.tatwood.net/index.html", uri) == 0);
    // attempt replacing components of uri
    taa_uri_set_scheme(uri, sizeof(uri), "https");
    assert(cmp_uri("https://www.tatwood.net/index.html", uri) == 0);
    taa_uri_set_scheme(uri, sizeof(uri), "http");
    assert(cmp_uri("http://www.tatwood.net/index.html", uri) == 0);    
    taa_uri_set_host(uri, sizeof(uri), "h");
    assert(cmp_uri("http://h/index.html", uri) == 0);
    taa_uri_set_host(uri, sizeof(uri), "host");
    assert(cmp_uri("http://host/index.html", uri) == 0);
    // attempt appending path to uri
    taa_uri_set_path(uri, sizeof(uri), ".././dir");
    assert(cmp_uri("http://host/../dir", uri) == 0);
    taa_uri_append_path(uri, sizeof(uri), ".././..///\\/\\//file.html");
    assert(cmp_uri("http://host/../file.html", uri) == 0);
    // attempt querying components of uri 
    taa_uri_get_scheme(uri, tmp, sizeof(tmp));
    assert(cmp_uri("http", tmp) == 0);
    taa_uri_get_host(uri, tmp, sizeof(tmp));
    assert(cmp_uri("host", tmp) == 0);    
    taa_uri_get_path(uri, tmp, sizeof(tmp));
    assert(cmp_uri("../file.html", tmp) == 0);
    // attempt setting full uri with fragment
    taa_uri_set(uri, sizeof(uri), "file:///dir/.././././file.txt#frag");
    assert(cmp_uri("file:///./file.txt#frag", uri) == 0);
    taa_uri_get_path(uri, tmp, sizeof(tmp));
    assert(cmp_uri("./file.txt", tmp) == 0);
    taa_uri_get_fragment(uri, tmp, sizeof(tmp));
    assert(cmp_uri("frag", tmp) == 0);
    // attempt a well formed windows file uri
    taa_uri_set(uri, sizeof(uri), "file:///c:/dir/file.txt");
    taa_uri_get_path(uri, tmp, sizeof(tmp));
    assert(cmp_uri("c:/dir/file.txt", tmp) == 0);
    // attempt a malformed windows file uri
    taa_uri_set(uri, sizeof(uri), "file://c:/dir/file.txt");
    taa_uri_get_path(uri, tmp, sizeof(tmp));
    assert(cmp_uri("c:/dir/file.txt", tmp) == 0);
}

int main(int argc, char* argv[])
{
    printf("testing taa_uri...");
    fflush(stdout);
    test_uri();
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
