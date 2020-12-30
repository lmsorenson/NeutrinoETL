#include "tst_eventtests.h"

#include <models/neutrinoevent.h>

EventTests::EventTests()
{

}

EventTests::~EventTests()
{

}

void EventTests::test_last()
{
    QMap<QString, double> point_map;
    point_map.insert("Point no", 01);
    point_map.insert("TX", 0);
    point_map.insert("TY", 0);
    point_map.insert("TZ", 0);
    point_map.insert("charge", 10);

    QMap<QString, double> point_map_2;
    point_map_2.insert("Point no", 11);
    point_map_2.insert("TX", 100);
    point_map_2.insert("TY", 100);
    point_map_2.insert("TZ", 100);
    point_map_2.insert("charge", 1000);

    NeutrinoTrack* track = new NeutrinoTrack(2001);
    track->add_point(new NeutrinoPoint(point_map));
    track->add_point(new NeutrinoPoint(point_map_2));

    NeutrinoEvent *event = new NeutrinoEvent(3001);
    event->add_track(track);

    auto last = event->last();

    QCOMPARE(last->id(), 2001);

    delete event;
}

void EventTests::test_get_tracks()
{
    QMap<QString, double> point_map;
    point_map.insert("Point no", 01);
    point_map.insert("TX", 0);
    point_map.insert("TY", 0);
    point_map.insert("TZ", 0);
    point_map.insert("charge", 10);

    NeutrinoTrack* track1 = new NeutrinoTrack(2001);
    track1->add_point(new NeutrinoPoint(point_map));

    QMap<QString, double> point_map_2;
    point_map_2.insert("Point no", 11);
    point_map_2.insert("TX", 100);
    point_map_2.insert("TY", 100);
    point_map_2.insert("TZ", 100);
    point_map_2.insert("charge", 1000);

    NeutrinoTrack* track2 = new NeutrinoTrack(2002);
    track2->add_point(new NeutrinoPoint(point_map_2));

    NeutrinoEvent *event = new NeutrinoEvent(3001);
    event->add_track(track1);
    event->add_track(track2);

    auto tracks = event->get_tracks();

    QCOMPARE(tracks.size(), 2);

    delete event;
}

void EventTests::test_get_last_when_none_exist()
{
    NeutrinoEvent *event = new NeutrinoEvent(3001);

    auto last = event->last();

    QCOMPARE(last, nullptr);

    delete event;
}

void EventTests::test_get_max_charge()
{
    QMap<QString, double> point_map;
    point_map.insert("Point no", 01);
    point_map.insert("TX", 0);
    point_map.insert("TY", 0);
    point_map.insert("TZ", 0);
    point_map.insert("charge", 1212);

    NeutrinoTrack* track1 = new NeutrinoTrack(2001);
    track1->add_point(new NeutrinoPoint(point_map));

    QMap<QString, double> point_map_2;
    point_map_2.insert("Point no", 11);
    point_map_2.insert("TX", 100);
    point_map_2.insert("TY", 100);
    point_map_2.insert("TZ", 100);
    point_map_2.insert("charge", 400);

    NeutrinoTrack* track2 = new NeutrinoTrack(2002);
    track2->add_point(new NeutrinoPoint(point_map_2));

    NeutrinoEvent *local_event = new NeutrinoEvent(3001);
    local_event->add_track(track1);
    local_event->add_track(track2);

    QCOMPARE(local_event->get_max_charge(), 1212);

    delete local_event;
}

void EventTests::test_to_json()
{
    QMap<QString, double> point_map;
    point_map.insert("Point no", 01);
    point_map.insert("TX", 1);
    point_map.insert("TY", 2);
    point_map.insert("TZ", 2);
    point_map.insert("charge", 1212);

    NeutrinoTrack* track1 = new NeutrinoTrack(2001);
    track1->add_point(new NeutrinoPoint(point_map));
    track1->calculate_extremes();

    QMap<QString, double> point_map_2;
    point_map_2.insert("Point no", 11);
    point_map_2.insert("TX", 100);
    point_map_2.insert("TY", 100);
    point_map_2.insert("TZ", 100);
    point_map_2.insert("charge", 400);

    NeutrinoTrack* track2 = new NeutrinoTrack(2002);
    track2->add_point(new NeutrinoPoint(point_map_2));
    track2->calculate_extremes();

    NeutrinoEvent *event = new NeutrinoEvent(3001);
    event->add_track(track1);
    event->add_track(track2);

    event->print();
    auto json = event->to_json();

    QCOMPARE(json.value("Id"), 3001);
    QCOMPARE(json.value("Tracks").isArray(), true);
    QCOMPARE(json.value("Tracks").toArray().size(), 2);

    delete event;
}

void EventTests::test_calculate_extremes()
{
    QMap<QString, double> x_min_point;
    x_min_point.insert("TX", -100);
    x_min_point.insert("TY", 0);
    x_min_point.insert("TZ", 100);
    x_min_point.insert("charge", 500.203);

    QMap<QString, double> x_max_point;
    x_max_point.insert("TX", 1001);
    x_max_point.insert("TY", 1);
    x_max_point.insert("TZ", 1);
    x_max_point.insert("charge", 450);

    QMap<QString, double> y_min_point;
    y_min_point.insert("TX", 0);
    y_min_point.insert("TY", -112);
    y_min_point.insert("TZ", 100);
    y_min_point.insert("charge", 500.203);

    QMap<QString, double> y_max_point;
    y_max_point.insert("TX", 2);
    y_max_point.insert("TY", 1777);
    y_max_point.insert("TZ", 2);
    y_max_point.insert("charge", 450);

    QMap<QString, double> z_min_point;
    z_min_point.insert("TX", 333);
    z_min_point.insert("TY", 333);
    z_min_point.insert("TZ", -333);
    z_min_point.insert("charge", 500.203);

    QMap<QString, double> z_max_point;
    z_max_point.insert("TX", 333);
    z_max_point.insert("TY", 333);
    z_max_point.insert("TZ", 1333);
    z_max_point.insert("charge", 450);

    NeutrinoTrack* track1 = new NeutrinoTrack(1);
    track1->add_point(new NeutrinoPoint(x_min_point));
    track1->add_point(new NeutrinoPoint(y_min_point));
    track1->add_point(new NeutrinoPoint(z_min_point));

    NeutrinoTrack* track2 = new NeutrinoTrack(2);
    track2->add_point(new NeutrinoPoint(x_max_point));
    track2->add_point(new NeutrinoPoint(y_max_point));
    track2->add_point(new NeutrinoPoint(z_max_point));

    NeutrinoEvent* event = new NeutrinoEvent(1001);
    event->add_track(track1);
    event->add_track(track2);

    event->calculate_extremes();

    auto x_min = event->x_extremes().first;
    auto x_max = event->x_extremes().second;
    auto y_min = event->y_extremes().first;
    auto y_max = event->y_extremes().second;
    auto z_min = event->z_extremes().first;
    auto z_max = event->z_extremes().second;

    QCOMPARE(x_min->x(), -100);
    QCOMPARE(x_max->x(), 1001);
    QCOMPARE(y_min->y(), -112);
    QCOMPARE(y_max->y(), 1777);
    QCOMPARE(z_min->z(), -333);
    QCOMPARE(z_max->z(), 1333);

    delete event;
}
