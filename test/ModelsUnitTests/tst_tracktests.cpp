#pragma once

#include "tst_tracktests.h"
#include <models/neutrinotrack.h>

TrackTests::TrackTests()
{

}

TrackTests::~TrackTests()
{

}

void TrackTests::test_add_point_to_track()
{
    QMap<QString, double> point_map;

    NeutrinoTrack* track = new NeutrinoTrack(2);
    track->add_point(new NeutrinoPoint(point_map));

    QCOMPARE(track->id(), 2);
    QCOMPARE(track->get_points().size(), 1);

    delete track;
}

void TrackTests::test_get_max_charge_greater_than_zero()
{
    QMap<QString, double> point_map;
    point_map.insert("charge", 500.203);

    QMap<QString, double> point_map_2;
    point_map_2.insert("charge", 450);

    NeutrinoTrack* track = new NeutrinoTrack(2);
    track->add_point(new NeutrinoPoint(point_map));
    track->add_point(new NeutrinoPoint(point_map_2));

    QCOMPARE(track->get_points().size(), 2);
    QCOMPARE(track->get_max_charge(), 500.203);

    delete track;
}

void TrackTests::test_get_total_charge()
{
    QMap<QString, double> point_map;
    point_map.insert("Point no", 1);
    point_map.insert("TX", 2.3);
    point_map.insert("TY", 2.4);
    point_map.insert("TZ", 2.123);
    point_map.insert("charge", 500.2);

    QMap<QString, double> point_map_2;
    point_map_2.insert("Point no", 1);
    point_map_2.insert("TX", 2.3);
    point_map_2.insert("TY", 2.4);
    point_map_2.insert("TZ", 2.123);
    point_map_2.insert("charge", 450.3);

    NeutrinoTrack* track = new NeutrinoTrack(2);
    track->add_point(new NeutrinoPoint(point_map));
    track->add_point(new NeutrinoPoint(point_map_2));

    QCOMPARE(track->get_points().size(), 2);
    QCOMPARE(track->total_charge(), 950.5);

    delete track;
}

#include "tst_tracktests.moc"
