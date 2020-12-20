#include "tst_pointtests.h"

#include <models/neutrinopoint.h>

PointTests::PointTests()
{

}

PointTests::~PointTests()
{

}

void PointTests::constructor_with_valid_arguments_populates_members()
{
    QMap<QString, double> point_map;
    point_map.insert("Point no", 1);
    point_map.insert("TX", 2.3);
    point_map.insert("TY", 2.4);
    point_map.insert("TZ", 2.123);
    point_map.insert("charge", 500.203);

    NeutrinoPoint* point = new NeutrinoPoint(point_map);

    QCOMPARE(point->id(), 1);
    QCOMPARE(point->x(), 2.3);
    QCOMPARE(point->y(), 2.4);
    QCOMPARE(point->z(), 2.123);
    QCOMPARE(point->charge(), 500.203);

    delete point;
}

void PointTests::constructor_with_null_arguments_populates_members_as_default()
{
    QMap<QString, double> point_map;

    NeutrinoPoint* point = new NeutrinoPoint(point_map);

    QCOMPARE(point->id(), 0);
    QCOMPARE(point->x(), 0);
    QCOMPARE(point->y(), 0);
    QCOMPARE(point->z(), 0);
    QCOMPARE(point->charge(), 0);

    delete point;
}

void PointTests::to_json_populates_fields()
{
    QMap<QString, double> point_map;
    point_map.insert("Point no", 1);
    point_map.insert("TX", 2.3);
    point_map.insert("TY", 2.4);
    point_map.insert("TZ", 2.123);
    point_map.insert("charge", 500.203);

    NeutrinoPoint* point = new NeutrinoPoint(point_map);

    point->print();
    auto json = point->to_json();

    QCOMPARE(json.value("Id"), 1);
    QCOMPARE(json.value("X"), 2.3);
    QCOMPARE(json.value("Y"), 2.4);
    QCOMPARE(json.value("Z"), 2.123);
    QCOMPARE(json.value("Charge"), 500.203);

    delete point;
}

#include "tst_pointtests.moc"
