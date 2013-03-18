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
#include <opencv/cv.h>

#include <iostream>

using namespace libface;

class Tldclassify
{
public:
    void groupFaces(QList<QList<IplImage *> > inputFaceList);
public:
    QList<QList<IplImage*> > resizedinputFaceList;
    QList<QList<bool> > tagged;
    QList<QString> groupnames;
    QList<QList<IplImage*> > allGrouped;
    QList<unitFaceModel *> modelsToStore;
};
