#include "tst_pointtests.h"
#include "tst_tracktests.h"

int main(int argc, char *argv[])
{
    TrackTests tc;
    PointTests pt;

    int track_test_result = QTest::qExec(&tc, argc, argv);
    int point_test_result = QTest::qExec(&pt, argc, argv);

    if (track_test_result) return track_test_result;
    if (point_test_result) return point_test_result;

    return 0;
}