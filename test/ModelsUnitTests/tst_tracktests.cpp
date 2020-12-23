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

void TrackTests::test_get_track_density()
{
    QMap<QString, double> point_map;
    point_map.insert("Point no", 0);
    point_map.insert("TX", 0);
    point_map.insert("TY", 0);
    point_map.insert("TZ", 0);
    point_map.insert("charge", 10);

    QMap<QString, double> point_map_2;
    point_map_2.insert("Point no", 1);
    point_map_2.insert("TX", 100);
    point_map_2.insert("TY", 100);
    point_map_2.insert("TZ", 100);
    point_map_2.insert("charge", 1000);

    NeutrinoTrack* track = new NeutrinoTrack(2);
    track->add_point(new NeutrinoPoint(point_map));
    track->add_point(new NeutrinoPoint(point_map_2));
    track->calculate_extremes();

    QCOMPARE(track->get_points().size(), 2);
    QCOMPARE(track->track_density(), (double)0.00101);

    delete track;
}

void TrackTests::to_json_populates_fields()
{
    QMap<QString, double> point_map;
    point_map.insert("Point no", 0);
    point_map.insert("TX", 0);
    point_map.insert("TY", 0);
    point_map.insert("TZ", 0);
    point_map.insert("charge", 10);

    QMap<QString, double> point_map_2;
    point_map_2.insert("Point no", 1);
    point_map_2.insert("TX", 100);
    point_map_2.insert("TY", 100);
    point_map_2.insert("TZ", 100);
    point_map_2.insert("charge", 1000);

    QMap<QString, double> point_map_3;
    point_map_3.insert("Point no", 2);
    point_map_3.insert("TX", 1001);
    point_map_3.insert("TY", 101);
    point_map_3.insert("TZ", 501);
    point_map_3.insert("charge", 322);

    QMap<QString, double> point_map_4;
    point_map_4.insert("Point no", 3);
    point_map_4.insert("TX", 343);
    point_map_4.insert("TY", 1002);
    point_map_4.insert("TZ", 50);
    point_map_4.insert("charge", 542);

    QMap<QString, double> point_map_5;
    point_map_5.insert("Point no", 4);
    point_map_5.insert("TX", 0);
    point_map_5.insert("TY", 0);
    point_map_5.insert("TZ", 1003);
    point_map_5.insert("charge", 1600);

    NeutrinoTrack* track = new NeutrinoTrack(54454);
    track->add_point(new NeutrinoPoint(point_map));
    track->add_point(new NeutrinoPoint(point_map_2));
    track->add_point(new NeutrinoPoint(point_map_3));
    track->add_point(new NeutrinoPoint(point_map_4));
    track->add_point(new NeutrinoPoint(point_map_5));
    track->calculate_extremes();

    track->print();
    auto json = track->to_json();
    auto points_json = json.value("Points");
    auto metadata = json.value("Metadata").toObject();

    QCOMPARE(json.value("Id"), 54454);
    QCOMPARE( metadata.value("XAxisMaximum"), (double)1001);
    QCOMPARE( metadata.value("YAxisMaximum"), (double)1002);
    QCOMPARE( metadata.value("ZAxisMaximum"), (double)1003);
    QCOMPARE( metadata.value("XAxisMinimum"), (double)0);
    QCOMPARE( metadata.value("YAxisMinimum"), (double)0);
    QCOMPARE( metadata.value("ZAxisMinimum"), (double)0);
    QCOMPARE( metadata.value("TotalCharge"), (double)3474);
    QCOMPARE( points_json.isArray(), true);
    QCOMPARE( points_json.toArray().size(), 5);

    delete track;
}

#include "tst_tracktests.moc"
