#ifndef JSON2COCO_H
#define JSON2COCO_H

#include "jsonreader.h"

class json2coco
{
public:
    json2coco();

    void Convert(QString path);

private:

    QString TemplateCOCO;
    QString TemplateObject;

    //tools
    JsonReader  *JR;
    FileBrowser *FB;

    QString GetFileLastModifiedTime(QString path);
};

#endif // JSON2COCO_H
