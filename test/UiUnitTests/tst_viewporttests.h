#pragma once

#include <QtTest>

class ViewportTests : public QObject
{
    Q_OBJECT

public:
    ViewportTests();
    virtual ~ViewportTests();

private slots:
    void test();
};

