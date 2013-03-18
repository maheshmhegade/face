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

#include "tldclassify.h"


void Tldclassify::groupFaces(QList<QList<IplImage*> > inputFaceList)
{
    for(int i=0;i< inputFaceList.size();i++)//resize images and initialise all faces status as not tagged(false)
    {
        QList<IplImage*> tmpfaceList;
        QList<bool> singlephototagged;
        for (int j=0;j<inputFaceList.at(i).size();j++)
        {
            IplImage* const inputfaceimage = cvCreateImage(cvSize(47,47),inputFaceList.at(i).at(j)->depth,inputFaceList.at(i).at(j)->nChannels);
            cvResize(inputFaceList.at(i).at(j),inputfaceimage);
            tmpfaceList.append(inputfaceimage);
            singlephototagged.append(false);
        }
        resizedinputFaceList.append(tmpfaceList);
        tagged.append(singlephototagged);
    }
    Tlddatabase *tlddatabase = new Tlddatabase;
    for (int i = 1; i <= tlddatabase->queryNumfacesinDatabase();i++ )//first grouping based on data present in database
    {
        int numfacesingroup = -1;
        unitFaceModel* const comparemodel = tlddatabase->getFaceModel(i);
        QList<IplImage*> recognisedGroup;
        for(int j=0;j< inputFaceList.size();j++)
        {
            for (int k=0;k<inputFaceList.at(j).size();k++)
            {
                Tldrecognition* const tmpTLD      = new Tldrecognition;
                if (tmpTLD->getRecognitionConfidence(resizedinputFaceList.at(j).at(k),comparemodel) > 0.6)
                {
                    recognisedGroup.append(resizedinputFaceList.at(j).at(k));
                    tagged[j].replace(k,true);
                    numfacesingroup++;
                }
                delete tmpTLD;
            }
        }
        if(numfacesingroup >= 0)
        {
            allGrouped.append(recognisedGroup);
            groupnames.append(tlddatabase->querybyFaceid(i));
        }
    }
    for(int i=0;i<inputFaceList.size()-1;i++)//group similar faces and not recognised from database
    {
        for(int j=0;j<inputFaceList.at(i).size();j++)
        {
            if(tagged.at(i).at(j) == false)
            {
                Tldrecognition* const tmpTLD      = new Tldrecognition;
                unitFaceModel *comparemodel = tmpTLD->getModeltoStore(resizedinputFaceList.at(i).at(j));
                delete tmpTLD;
                QList<IplImage*> tmpGroup;
                tmpGroup.append(resizedinputFaceList.at(i).at(j));
                int tmpfacecount = 0;
                for(int m=i+1; m < resizedinputFaceList.size(); m++)
                {
                    for (int n=0; n< resizedinputFaceList.at(m).size(); n++)
                    {
                        if(tagged.at(m).at(n) == false)
                        {
                            Tldrecognition* const tmpTLD      = new Tldrecognition;
                            if(tmpTLD->getRecognitionConfidence(resizedinputFaceList.at(m).at(n),comparemodel) > 0.6)
                            {
                                tmpGroup.append(resizedinputFaceList.at(m).at(n));
                                tagged[i].replace(j,true);
                                tmpfacecount++;
                            }
                        }
                    }
                }
                if(tmpfacecount > 0)
                {
                    groupnames.append("found similar");
                    allGrouped.append(tmpGroup);//create new group if more than one among nottagged faces found similar
                    modelsToStore.append(comparemodel);//model to store in database later on based on new name to group choosen by user
                }
            }
        }
    }
    QList<IplImage *> tmpgroup;
    for(int i=0; i<resizedinputFaceList.size(); i++)//group all faces not classified anywhere above(unknown new faces)
    {
        for (int j=0; j<resizedinputFaceList.at(i).size();j++)
        {
            if(tagged.at(i).at(j) == false)
            {
                Tldrecognition* const tmpTLD      = new Tldrecognition;
                modelsToStore.append(tmpTLD->getModeltoStore(resizedinputFaceList.at(i).at(j)));
                delete tmpTLD;
                tmpgroup.append(resizedinputFaceList.at(i).at(j));
                tagged[i].replace(j,true);
            }
        }
    }
    groupnames.append("unknown");
    allGrouped.append(tmpgroup);
}
