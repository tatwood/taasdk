#if defined(_DEBUG) && defined(_MSC_FULL_VER)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <taa/coroutine.h>
#include <cassert>
#include <cstdio>
#include <cstdlib>

#ifdef NDEBUG
#error asserts are not enabled
#endif

struct coro_spawn_instance
{
    int index;
    taa_coroutine coro;
    taa_coroutine next;
    bool started;
    bool created_child;
    bool destroyed_child;
    bool done;
};

// tests creation & execution of a coroutine on the stack of another coroutine
// also tests c++ object construction/destruction on stack of a coroutine
class coro_test_object
{
public:

    coro_test_object(coro_spawn_instance* s) :
        spawn_(s),
        executed_(false)
    {
        taa_coroutine_create(32 * 1024, test_function, this, &coroutine_);
        printf("created child %i\n", spawn_->index);
        spawn_->created_child = true;
    }

    ~coro_test_object()
    {
        printf("destroyed child %i\n", spawn_->index);
        spawn_->destroyed_child = true;
        taa_coroutine_destroy(coroutine_);
    }

    bool is_finished()
    {
        return executed_;
    }

    void activate()
    {
        taa_coroutine_switch(coroutine_);
    }

private:
    coro_spawn_instance* spawn_;
    taa_coroutine coroutine_;
    bool executed_;

    static void test_function(void* args)
    {
        coro_test_object* obj = static_cast<coro_test_object*>(args);
        taa_coroutine_switch(obj->spawn_->coro);
        printf("executed child: %i\n", obj->spawn_->index);
        obj->executed_ = true;
    }
};

static void spawn_function(void* args)
{
    coro_spawn_instance* s = static_cast<coro_spawn_instance*>(args);
    printf("started: %i\n", s->index);
    s->started = true;
    if(!s->done)
    {
        coro_test_object obj(s);
        assert(s->created_child);
        while(!obj.is_finished())
        {
            obj.activate();
            taa_coroutine_switch(s->next);
        }
        s->done = true;
        printf("done: %i\n", s->index);
    }
    assert(s->destroyed_child);
}

void test_coroutine()
{
    coro_spawn_instance co_test[16];
    for(int i = 0; i < 16; ++i)
    {
        coro_spawn_instance* s = co_test + i;
        s->index = i;
        taa_coroutine_create(32*1024, spawn_function, co_test + i, &s->coro);
        s->started = false;
        s->created_child = false;
        s->destroyed_child = false;
        s->done = false;
    }
    for(int i = 0; i < 16; ++i)
    {
        co_test[i].next = co_test[(i + 1) & 0x0F].coro;
    }
    for(int i = 0; i < 16; ++i)
    {
        while(!co_test[i].done)
        {
            taa_coroutine_execute(co_test[i].coro);
        }
        for(int j = 0; j <= i; ++j)
        {
            assert(co_test[j].started);
            assert(co_test[j].created_child);
            assert(co_test[j].destroyed_child);
            assert(co_test[j].done);
        }
        for(int j = i + 1; j < 16; ++j)
        {
            assert(co_test[j].started);
            assert(co_test[j].created_child);
            assert(!co_test[j].destroyed_child);
            assert(!co_test[j].done);
        }
    }
    for(int i = 0; i < 16; ++i)
    {
        taa_coroutine_destroy(co_test[i].coro);
    }
}

int main(int argc, char* argv[])
{
    printf("testing coroutines...\n");
    fflush(stdout);
    test_coroutine();
    printf("success\n");
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
