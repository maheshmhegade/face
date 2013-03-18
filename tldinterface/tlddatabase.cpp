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
 * Face detection data storage in SQlite database.
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

#include "tlddatabase.h"

namespace libface
{

Tlddatabase::Tlddatabase()
{
    this->openFaceDatabase();
    this->createFaceTable();
}

void Tlddatabase::openFaceDatabase()
{
    faceDatabase = QSqlDatabase::addDatabase("QSQLITE");

    faceDatabase.setDatabaseName("faceDatabase.db");

    faceDatabase.open();
}

Tlddatabase::~Tlddatabase()
{
    faceDatabase.close();
}

void Tlddatabase::createFaceTable()
{
    if (faceDatabase.isOpen())
    {
        QSqlQuery query;
        query.exec("create table faceDatabase "
                   "(id integer primary key, "
                   "modelname varchar, "
                   "modelheight integer, "
                   "modelwidth integer, "
                   "modelminvar float, "
                   "positivepatches varchar, "
                   "negativepatches varchar, "
                   "allfeatures varchar, "
                   "allleaves varchar)");
    }
}

int  Tlddatabase::queryNumfacesinDatabase() const
{
    QSqlTableModel query;
    query.setTable("faceDatabase");
    query.select();
    return query.rowCount();
}

QString Tlddatabase::querybyFaceid(int faceid) const
{
    QSqlQuery query(QString("select * from faceDatabase where id = %1").arg(faceid));

    if (query.next())
    {
        return query.value(1).toString();
    }

    return QString();
}

int Tlddatabase::querybyName(const QString& nametoquery) const
{
    QSqlQuery query(QString("select * from faceDatabase where modelname = %1").arg(nametoquery));

    if (query.next())
    {
        return query.value(1).toInt();
    }

    return -1;
}

int Tlddatabase::insertFaceModel(unitFaceModel* const facemodel) const
{
    int newId = -1;
    bool ret  = false;

    if (faceDatabase.isOpen())
    {
        QSqlQuery query;
        ret = query.exec(QString("insert into faceDatabase values(NULL,'%1',%2,%3,%4,'%5','%6','%7','%8')")
                         .arg(facemodel->Name).arg(facemodel->objHeight).arg(facemodel->objWidth).arg(facemodel->minVar)
                         .arg(facemodel->serialisedPositivePatches).arg(facemodel->serialisedNegativePatches)
                         .arg(facemodel->serialisedFeatures).arg(facemodel->serialisedLeaves));
        // Get database given autoincrement value
        if (ret)
        {
            newId = query.lastInsertId().toInt();
        }
    }

    return newId;
}

unitFaceModel* Tlddatabase::getFaceModel(int faceid) const
{
    unitFaceModel* const facemodel = new unitFaceModel;
    QSqlQuery query(QString("select * from faceDatabase where id = %1").arg(faceid));

    if (query.next())
    {
        facemodel->faceid                    = query.value(0).toInt();
        facemodel->Name                      = query.value(1).toString();
        facemodel->objHeight                 = query.value(2).toInt();
        facemodel->objWidth                  = query.value(3).toInt();
        facemodel->minVar                    = query.value(4).toFloat();
        facemodel->serialisedPositivePatches = query.value(5).toString();
        facemodel->serialisedNegativePatches = query.value(6).toString();
        facemodel->serialisedFeatures        = query.value(7).toString() ;
        facemodel->serialisedLeaves          = query.value(8).toString();
    }

    return facemodel;
}

IplImage* Tlddatabase::QImage2IplImage(QImage& qimg) const
{

    IplImage* const imgHeader = cvCreateImageHeader(cvSize(qimg.width(), qimg.height()), IPL_DEPTH_8U, 4);
    imgHeader->imageData      = (char*) qimg.bits();

    uchar* const newdata      = (uchar*) malloc(sizeof(uchar) * qimg.byteCount());
    memcpy(newdata, qimg.bits(), qimg.byteCount());
    imgHeader->imageData      = (char*) newdata;

    return imgHeader;
}

} // namespace libface
