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

// Qt includes

#include <QImage>

// OpenTLD includes

#include "tldinterface.h"
#include "Settings.h"
#include "ImAcq.h"
#include "Gui.h"
#include <iostream>
using namespace std;
using tld::Gui;
using tld::Settings;

namespace libface
{

class Tldrecognition
{
public:

    Tldrecognition();
   ~Tldrecognition();

    pair<unitFaceModel*,IplImage*> getModeltoStore() const;

    int updateDatabase(IplImage* const, const char* const) const;

    float getRecognitionConfidence(unitFaceModel* const comparemodel) const;

private:

    class Private;
    Private* const d;
};

} // namespace libface
