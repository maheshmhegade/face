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

#include "tldrecognition.h"

using namespace std;

namespace libface
{

class Tldrecognition::Private
{

public:

    Private()
    {
        tldinterfaceObject  = 0;
        imAcq = 0;
        gui = 0;
    }

    tldinterface*  tldinterfaceObject;
    ImAcq *imAcq;
    Gui *gui;
};

Tldrecognition::Tldrecognition()
    : d(new Private)
{
    d->tldinterfaceObject = new tldinterface();
    srand(d->tldinterfaceObject->seed);

    d->imAcq = imAcqAlloc();
    d->gui = new Gui();

    d->tldinterfaceObject->gui = d->gui;
    d->tldinterfaceObject->imAcq = d->imAcq;

    srand(d->tldinterfaceObject->seed);

    imAcqInit(d->imAcq);

    if(d->tldinterfaceObject->showOutput)
    {
        d->gui->init();
    }
}

Tldrecognition::~Tldrecognition()
{
    delete d->tldinterfaceObject;
    delete d->gui;
    delete d;
}

unitFaceModel* Tldrecognition::getModeltoStore(int *initBoundingBox) const
{
    return d->tldinterfaceObject->generatefacemodel(initBoundingBox);
}

float Tldrecognition::getRecognitionConfidence( unitFaceModel* const comparemodel) const
{
    return d->tldinterfaceObject->getrecognitionconfidence(comparemodel);
}

int Tldrecognition::updateDatabase(IplImage* const /*inputImage*/, const char* const /*faceModelFilename*/) const
{
//    d->main->doWork(inputImage, faceModelFilename, 3);
    return 0;
}

} // namespace libface
