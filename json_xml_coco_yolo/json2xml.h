#ifndef JSON2XML_H
#define JSON2XML_H
#include "jsonreader.h"

class json2xml
{

public:
    json2xml();

    void Convert(QString path);

private:

    QString TemplateXML;
    QString TemplateObject;

    //tools
    JsonReader  *JR;
    FileBrowser *FB;





};

#endif // JSON2XML_H
