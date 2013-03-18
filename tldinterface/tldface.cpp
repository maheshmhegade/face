 
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

#include "tldface.h"

using namespace std;

namespace libface
{

unitFaceModel::unitFaceModel()
{
}

unitFaceModel::~unitFaceModel()
{
}

void unitFaceModel::serialisePositivePatches(const QList<QList<float> >& allPositivePatches)
{
    QByteArray byteArray;
    QBuffer writeBuffer(&byteArray);
    writeBuffer.open(QIODevice::WriteOnly);
    QDataStream out(&writeBuffer);

    out << allPositivePatches;

    writeBuffer.close();

    serialisedPositivePatches = QString(byteArray.toBase64());
}

void unitFaceModel::serialiseNegativePatches(const QList<QList<float> >& allNegativePatches)
{
    QByteArray byteArray;
    QBuffer writeBuffer(&byteArray);
    writeBuffer.open(QIODevice::WriteOnly);
    QDataStream out(&writeBuffer);

    out << allNegativePatches;

    writeBuffer.close();

    serialisedNegativePatches = QString(byteArray.toBase64());
}

void unitFaceModel::serialiseFeatures(const QList<QList<QList<float> > >& allFeatures)
{
    QByteArray byteArray;
    QBuffer writeBuffer(&byteArray);
    writeBuffer.open(QIODevice::WriteOnly);
    QDataStream out(&writeBuffer);

    out << allFeatures;

    writeBuffer.close();

    serialisedFeatures = QString(byteArray.toBase64());
}

void unitFaceModel::serialiseLeaves(const QList<QList<QList<int> > >& allLeaves)
{
    QByteArray byteArray;
    QBuffer writeBuffer(&byteArray);
    writeBuffer.open(QIODevice::WriteOnly);
    QDataStream out(&writeBuffer);

    out << allLeaves;

    writeBuffer.close();

    serialisedLeaves = QString(byteArray.toBase64());
}

QList<QList<float> > unitFaceModel::deserialisePositivePatches() const
{
    QByteArray readArr = QByteArray::fromBase64( this->serialisedPositivePatches.toAscii());
    QBuffer readBuffer(&readArr);
    readBuffer.open(QIODevice::ReadOnly);
    QDataStream in(&readBuffer);
    QList<QList<float> > allPositivePatches;

    in >> allPositivePatches;
    return allPositivePatches;
}

QList<QList<float> > unitFaceModel::deserialiseNegativePatches() const
{
    QByteArray readArr = QByteArray::fromBase64( serialisedNegativePatches.toAscii());
    QBuffer readBuffer(&readArr);
    readBuffer.open(QIODevice::ReadOnly);
    QDataStream in(&readBuffer);

    QList<QList<float> > allNegativePatches;

    in >> allNegativePatches;

    return allNegativePatches;
}

QList<QList<QList<float> > > unitFaceModel::deserialiseFeatures() const
{
    QByteArray readArr = QByteArray::fromBase64( serialisedFeatures.toAscii());
    QBuffer readBuffer(&readArr);
    readBuffer.open(QIODevice::ReadOnly);
    QDataStream in(&readBuffer);

    QList<QList<QList<float> > > allFeatures;

    in >> allFeatures;

    return allFeatures;
}

QList<QList<QList<int> > > unitFaceModel::deserialiseLeaves() const
{
    QByteArray readArr = QByteArray::fromBase64( serialisedLeaves.toAscii());
    QBuffer readBuffer(&readArr);
    readBuffer.open(QIODevice::ReadOnly);
    QDataStream in(&readBuffer);

    QList<QList<QList<int> > > allLeaves;

    in >> allLeaves;

    return allLeaves;
}

} // namespace libface
