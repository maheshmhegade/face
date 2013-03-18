/** ===========================================================
 * @file
 *
 * This file is a part of libface project
 * <a href="http://libface.sourceforge.net">http://libface.sourceforge.net</a>
 *
 * @date    2010-03-03
 * @brief   openTLD interface.
 * @section DESCRIPTION
 *
 * Face detection through openTLD interface.
 *
 * @author Copyright (C) 2012-2013 by Mahesh Hegde
 *         <a href="mailto:maheshmhegade at gmail dot com">maheshmhegade at gmail dot com</a>
 * @author Copyright (C) 2013 by Gilles Caulier
 *         <a href="mailto:caulier dot gilles at gmail dot com">caulier dot gilles at gmail dot com</a>
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

// C++ includes

#include <iostream>

// Qt includes

#include <QList>
#include <QBuffer>
#include <QVariant>

namespace libface
{

class unitFaceModel
{
public:

    unitFaceModel();
    ~unitFaceModel();

    void serialisePositivePatches(const QList<QList<float> >&);
    void serialiseNegativePatches(const QList<QList<float> >&);
    void serialiseFeatures(const QList<QList<QList<float> > >&);
    void serialiseLeaves(const QList<QList<QList<int> > >&);

    QList<QList<float> > deserialisePositivePatches()  const;
    QList<QList<float> >  deserialiseNegativePatches() const;
    QList<QList<QList<float> > > deserialiseFeatures() const;
    QList<QList<QList<int> > > deserialiseLeaves()     const;

public:

    QString serialisedPositivePatches;
    QString serialisedNegativePatches;
    QString serialisedFeatures;
    QString serialisedLeaves;
    QString Name;

    int     faceid;
    int     objHeight;
    int     objWidth;

    float   minVar;
};

} // namespace libface
