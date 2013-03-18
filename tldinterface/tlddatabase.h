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

// C++ includes

#include <iostream>

// SQlite includes

#include <sqlite3.h>

// Qt includes

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDebug>
#include <QObject>
#include <QImage>

// Local includes

#include "tldrecognition.h"

using namespace std;

namespace libface
{

class Tlddatabase
{
public:

    Tlddatabase();
    ~Tlddatabase();

    void openFaceDatabase();
    void createFaceTable();

    int insertFaceModel(unitFaceModel* const) const;
    int querybyName(const QString&)           const;
    int queryNumfacesinDatabase()             const;

    QString querybyFaceid(int faceid)       const;
    unitFaceModel* getFaceModel(int faceid) const;
    IplImage* QImage2IplImage(QImage&)      const;

private:

    QSqlDatabase faceDatabase;
};

} // namespace libface
