#include "tst_viewporttests.h"

int main(int argc, char *argv[])
{
    ViewportTests viewport_tests;

    int viewport_test_result = QTest::qExec(&viewport_tests, argc, argv);

    if (viewport_test_result) return viewport_test_result;

    return 0;
}