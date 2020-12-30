#pragma once

#include <QtTest>

class EventTests : public QObject
{
    Q_OBJECT

public:
    EventTests();
    virtual ~EventTests();

private slots:
    void test_last();
    void test_get_tracks();
    void test_get_last_when_none_exist();
    void test_get_max_charge();
    void test_to_json();
    void test_calculate_extremes();
};

