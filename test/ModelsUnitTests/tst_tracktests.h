#pragma once

#include <QtTest>

class TrackTests : public QObject
{
    Q_OBJECT

public:
    TrackTests();
    ~TrackTests();

private slots:
    void test_add_point_to_track();
    void test_get_max_charge_greater_than_zero();
    void test_get_total_charge();

};