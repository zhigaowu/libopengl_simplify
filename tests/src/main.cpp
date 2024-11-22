
#include "glfw/libglsimplify_window.h"

#include <map>
#include <string>

#include <iostream>

#define DECLARE_TEST_CASE(name) extern int test_##name(int argc, char **argv, int, int)
#define DEFINE_TEST_CASE(cases, name) cases.insert(std::make_pair("test_"#name, test_##name))

DECLARE_TEST_CASE(all);
DECLARE_TEST_CASE(points);
DECLARE_TEST_CASE(plane);
DECLARE_TEST_CASE(cube);

int main(int argc, char **argv) 
{
    using testcase = int (*)(int, char**, int, int);
    using testcases = std::map<std::string, testcase>;

    testcases avaliable_cases;
    do
    {
        DEFINE_TEST_CASE(avaliable_cases, all);
        DEFINE_TEST_CASE(avaliable_cases, points);
        DEFINE_TEST_CASE(avaliable_cases, plane);
        DEFINE_TEST_CASE(avaliable_cases, cube);
    } while (false);

    int res = -1;
    do
    {
        if (argc < 2)
        {
            std::cerr << "usage:"
                << std::endl
                << argv[0] << " test_case_name width[800] height[600]" << std::endl;

            break;
        }

        testcases::iterator it = avaliable_cases.find(argv[1]);
        if (it == avaliable_cases.end())
        {
            std::cerr << "test case["
                << argv[1] << "] is not defined" << std::endl;

            break;
        }

        int width = 800;
        int height = 600;

        if (argc >= 3)
        {
            width = atoi(argv[2]);
        }

        if (argc >= 4)
        {
            height = atoi(argv[3]);
        }

        gl_simplify::glfw::Initialize();

        res = it->second(argc, argv, width, height);

        gl_simplify::glfw::Shutdown();
    } while (false);

    if (res < 0)
    {
        std::cin >> argc;
    }

    return res;
}
