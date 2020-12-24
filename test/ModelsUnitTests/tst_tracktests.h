#pragma once

#include <QtTest>

class TrackTests : public QObject
{
    Q_OBJECT

public:
    TrackTests();
    virtual ~TrackTests();

private slots:
    void test_add_point_to_track();
    void test_get_max_charge_greater_than_zero();
    void test_get_total_charge();
    void test_get_track_density();
    void to_json_populates_fields();

};
