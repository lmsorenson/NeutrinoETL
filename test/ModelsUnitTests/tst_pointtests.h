#pragma once

#include <QtTest>

class PointTests : public QObject
{
    Q_OBJECT

public:
    PointTests();
    ~PointTests();

private slots:
    void constructor_with_valid_arguments_populates_members();
    void constructor_with_null_arguments_populates_members_as_default();
    void to_json_populates_fields();
};
