#include <QtTest>
#include <models/neutrinopoint.h>

#include <models/neutrinotrack.h>

class PointTests : public QObject
{
    Q_OBJECT

public:
    PointTests();
    ~PointTests();

private slots:
    void test();
    void test2();

};

PointTests::PointTests()
{

}

PointTests::~PointTests()
{

}

void PointTests::constructor_with_valid_arguments_populates_members()
{
}

void PointTests::constructor_with_null_arguments_populates_members_as_default()
{
}

QTEST_APPLESS_MAIN(PointTests)

#include "tst_pointtests.moc"
