#ifndef JSONREADER_H
#define JSONREADER_H
#include "filebrowser.h"
#include <QStringList>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>


/*
 * this class will be used to read our custom json file
 * but take care that this is not general json file reader
 * as it will read all .json represented like this:-
 *
 * {
    "detections": [
        {
            "bottom_right_xy": [
                value,
                value
            ],
            "class_id": value,
            "class_name": value,
            "top_left_xy": [
                value,
                value
            ]
        },
        {
            "bottom_right_xy": [
                value,
                value
            ],
            "class_id": value,
            "class_name": value,
            "top_left_xy": [
                value,
                value
            ]
        },
        {
            "bottom_right_xy": [
                value,
                value
            ],
            "class_id": value,
            "class_name": value,
            "top_left_xy": [
                value,
                value
            ]
        }
    ],
    "identifier": value,
    "imageHeight": value,
    "imageWidth": value
}

 *
*/

class JsonReader
{
public:

    typedef struct
    {
      QString ObjectStr;
      float bottom_right_x;
      float bottom_right_y;
      int class_id;
      QString class_name;
      float top_left_x;
      float top_left_y;

    }DetectedObjects_t;

    typedef struct
    {
       QList<DetectedObjects_t> detections;
       QString identifier;
       int imageHeight;
       int imageWidth;

    }json_t; /* our main json data structure */


        JsonReader();
 json_t ReadJsonFile(QString path); //read the json file on path



private:
    FileBrowser   *f;
    QString        jsonSTR;

    QStringList keys;
    QByteArray  bb;


};

#endif // JSONREADER_H
