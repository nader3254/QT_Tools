#include "json2coco.h"

json2coco::json2coco()
{
    JR = new JsonReader();
    FB = new FileBrowser("");

    TemplateCOCO ="{\n";
    TemplateCOCO +=    "\"info\": {\n";
    TemplateCOCO +=    "\"year\": \"##YEAR##\",\n";
    TemplateCOCO +=    "\"version\": \"1\", \n";
    TemplateCOCO +=    "\"description\": \"created by converting another json file\", \n";
    TemplateCOCO +=    "\"contributor\": \"ESM Institut\",\n" ;
    TemplateCOCO +=    "\"url\": \"https://www.esm.hs-mannheim.de/institut.html\",\n" ;
    TemplateCOCO +=    "\"date_created\": \"\"\n";
    TemplateCOCO +=    "  }, \n";

    TemplateCOCO += " \"licenses\": [\n";
    TemplateCOCO += " {\n";
    TemplateCOCO += "\"id\": 1,\n" ;
    TemplateCOCO += "\"url\": \"https://creativecommons.org/licenses/by/4.0/\",\n" ;
    TemplateCOCO += "\"name\": \"CC BY 4.0\"\n";
    TemplateCOCO += "}\n";
    TemplateCOCO += " ],\n" ;

    TemplateCOCO +=   "\"categories\": [\n";
    TemplateCOCO +=   "{\n";
    TemplateCOCO +=   " \"id\": ##CATEGORY_ID##,\n" ;
    TemplateCOCO +=   "\"name\": \"##CATEGORY_NAME##\", \n";
    TemplateCOCO +=   "\"supercategory\": \"none\"\n";
    TemplateCOCO +=   "}\n";
    TemplateCOCO +=   "],\n";

    TemplateCOCO +=  "\"images\": [\n";
    TemplateCOCO +=  "{\n" ;
    TemplateCOCO +=  "\"id\": 0,\n";
    TemplateCOCO +=  "\"license\": 1,\n" ;
    TemplateCOCO +=  "\"file_name\": \"##IMAGE_FILENAME##\",\n" ;
    TemplateCOCO +=  "\"height\": ##IMAGE_HEIGHT##,\n" ;
    TemplateCOCO +=  "\"width\": ##IMAGE_WIDTH##,\n" ;
    TemplateCOCO +=  "\"date_captured\": \"##IMAGE_CAPTUREDATE##\"\n";
    TemplateCOCO +=  " }\n";
    TemplateCOCO +=  "],\n" ;

    TemplateCOCO +=  "\"annotations\":\n" ;
    TemplateCOCO +=  "[\n";
    TemplateCOCO +=  "##OBJECTS##\n";
    TemplateCOCO +=  "]\n";
    TemplateCOCO +=  "}"  ;



    TemplateObject  = "{\n";
    TemplateObject += "\"id\": ##OBJECT_ID##,\n" ;
    TemplateObject += "\"image_id\": 0,\n" ;
    TemplateObject += "\"category_id\": 1,\n" ;
    TemplateObject += "\"bbox\": [##TOP_LEFT_X##, ##TOP_LEFT_Y##,\n";
    TemplateObject += "##BOTTOM_RIGHT_X##,##BOTTOM_RIGHT_Y##],\n";
    TemplateObject += "\"area\": ##OBJECT_AREA##,\n" ;
    TemplateObject += "\"segmentation\": [],\n";
    TemplateObject += "\"iscrowd\": 0\n";
    TemplateObject += "}\n";




}

void json2coco::Convert(QString path)
{

    JsonReader::json_t JS = JR->ReadJsonFile(path);
    QString OutputCOCO = TemplateCOCO;
    QString OBJTmp = TemplateObject;
    QString objects;
    QString SPath = path;

    QDate   date = QDate::currentDate();
    int     yr   = date.year();
    QString Year = QString::number(yr);

    QString Category_id   = QString::number(JS.detections.at(0).class_id-1) ;
    QString Category_name = JS.detections.at(0).class_name ;

    QString IMG_fileName = SPath;
    IMG_fileName.replace(".json",".jpg");
    QString IMG_width       = QString::number(JS.imageWidth);
    QString IMG_height      = QString::number(JS.imageHeight);
    QString IMG_CaptureDate = GetFileLastModifiedTime(IMG_fileName);


    for(int i=0;i<JS.detections.size();i++)
    {
        float height = JS.detections.at(i).bottom_right_y - JS.detections.at(i).top_left_y;
        float width = JS.detections.at(i).bottom_right_x - JS.detections.at(i).top_left_x;
        QString TLX=QString::number(JS.detections.at(i).top_left_x  );
        QString TLY=QString::number(JS.detections.at(i).top_left_y  );
        QString BRX=QString::number(width);
        QString BRY=QString::number(height);
        QString Area=QString::number(height*height);
        QString OBJID=QString::number(i);


        OBJTmp.replace("##CLASSNAME##",JS.detections.at(i).class_name);
        OBJTmp.replace("##OBJECT_ID##",OBJID);
        OBJTmp.replace("##TOP_LEFT_X##",TLX);
        OBJTmp.replace("##TOP_LEFT_Y##",TLY);
        OBJTmp.replace("##BOTTOM_RIGHT_X##",BRX);
        OBJTmp.replace("##BOTTOM_RIGHT_Y##",BRY);
        OBJTmp.replace("##OBJECT_AREA##",Area);

        if(i!=JS.detections.size()-1)
        {
            OBJTmp += ",\n";
        }

        objects += OBJTmp;
        OBJTmp = TemplateObject;
    }

    OutputCOCO.replace("##YEAR##",Year);
    OutputCOCO.replace("##CATEGORY_ID##",Category_id);
    OutputCOCO.replace("##CATEGORY_NAME##",Category_name);
    OutputCOCO.replace("##IMAGE_FILENAME##",IMG_fileName);
    OutputCOCO.replace("##IMAGE_HEIGHT##",IMG_height);
    OutputCOCO.replace("##IMAGE_WIDTH##",IMG_width);
    OutputCOCO.replace("##IMAGE_CAPTUREDATE##",IMG_CaptureDate);
    OutputCOCO.replace("##OBJECTS##",objects);



    QString COCOPath = SPath.replace(".json",".coco.json");
    qDebug()<<COCOPath;


    FB->WriteFile(COCOPath,OutputCOCO);

}

QString json2coco::GetFileLastModifiedTime(QString path)
{

  //  QFileInfo *f =new QFileInfo("C:/Users/Nader/Desktop/Ammar Project/bachelorarbeit-ws-22/software/apps/images/i_1655119917245.jpg");
    QFileInfo *f =new QFileInfo(path);
    QDateTime dd =f->fileTime(QFileDevice::FileModificationTime);
    return  dd.toString(Qt::ISODate);
}
