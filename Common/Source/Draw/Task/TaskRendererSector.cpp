/*
 * LK8000 Tactical Flight Computer -  WWW.LK8000.IT
 * Released under GNU/GPL License v.2
 * See CREDITS.TXT file for authors and copyrights
 *
 * File:   TaskRendererSector.cpp
 * Author: Bruno de Lacheisserie
 *
 * Created on October 21, 2016, 3:01 AM
 */
#include "externs.h"
#include "TaskRendererSector.h"

TaskRendererSector::TaskRendererSector(const GeoPoint& center, double radius, double start, double end) {

    const int start_bearing = std::ceil(start);
    const int end_bearing = std::floor((end > start) ? end : end + 360);
    assert(end_bearing > start_bearing);

    _GeoPoints.reserve(3 + (end_bearing - start_bearing));

    _GeoPoints.push_back(center);
    _GeoPoints.push_back(center.Direct(start, radius));

    for (int i = start_bearing; i <= end_bearing; ++i) {
        _GeoPoints.push_back(center.Direct(static_cast<double> (i), radius));
    }

    _GeoPoints.push_back(center.Direct(end, radius));


    _bounds.minx = _bounds.maxx = center.longitude;
    _bounds.miny = _bounds.maxy = center.latitude;

    for (GeoPoint& Pt : _GeoPoints) {
        _bounds.minx = std::min(Pt.longitude, _bounds.minx);
        _bounds.maxx = std::max(Pt.longitude, _bounds.maxx);
        _bounds.miny = std::min(Pt.latitude, _bounds.miny);
        _bounds.maxy = std::max(Pt.latitude, _bounds.maxy);
    }
}
