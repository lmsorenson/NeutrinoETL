#include "tst_pointtests.h"
#include "tst_tracktests.h"
#include "tst_eventtests.h"

int main(int argc, char *argv[])
{
    EventTests event_tests;
    TrackTests track_tests;
    PointTests point_tests;

    int point_test_result = QTest::qExec(&point_tests, argc, argv);
    int track_test_result = QTest::qExec(&track_tests, argc, argv);
    int event_test_result = QTest::qExec(&event_tests, argc, argv);

    if (point_test_result) return point_test_result;
    if (track_test_result) return track_test_result;
    if (event_test_result) return event_test_result;

    return 0;
}