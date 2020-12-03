#include "neutrinotrack.h"

NeutrinoTrack::NeutrinoTrack(int id) : id_(id), points_(QList<NeutrinoPoint *>())
{

}

void NeutrinoTrack::to_disk(QString path)
{

}

void NeutrinoTrack::add_point(NeutrinoPoint *point)
{
    points_.append(point);
}
