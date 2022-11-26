#ifndef JSON2YOLO_H
#define JSON2YOLO_H
#include "jsonreader.h"

class Json2Yolo
{
public:
    Json2Yolo();
    void Convert(QString path);

private:
    float TL_X,TL_Y,BR_X,BR_Y,x_center,y_center;
    float norm_x,norm_y;
    float box_width,box_height;
    int   object_class;


    QStringList class_names;
    QString     Spath;
    QString     YoloOutput;

    //tools
    JsonReader  *JR;
    FileBrowser *FB;

    void RST();

};

#endif // JSON2YOLO_H
