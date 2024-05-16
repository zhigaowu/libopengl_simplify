

#include <iostream>

extern int test_texture(int argc, char **argv);
extern int test_transform(int argc, char **argv);
extern int test_camera(int argc, char **argv);

int main(int argc, char **argv) 
{
    return test_camera(argc, argv);
}
