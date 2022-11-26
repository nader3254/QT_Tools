#include "json2xml.h"

json2xml::json2xml()
{
    JR = new JsonReader();
    FB = new FileBrowser("");

    TemplateXML  = "<annotation>\n";
    TemplateXML += "<folder>##FOLDER##</folder>\n";
    TemplateXML += "<filename>##FILENAME##</filename>\n";
    TemplateXML += "<path>##PATH##</path>\n";
    TemplateXML += "<source><database>Unknown</database></source>\n";
    TemplateXML += "<size><width>##WIDTH##</width><height>##HEIGHT##</height><depth>##DEPTH##</depth></size>";
    TemplateXML += "<segmented>0</segmented>\n";
    TemplateXML += "##OBJECTS##";
    TemplateXML += "</annotation>";

    TemplateObject = "<object><name>##CLASSNAME##</name><pose>Unspecified</pose><truncated>0</truncated><difficult>0</difficult><bndbox><xmin>##TOP_LEFT_X##</xmin><ymin>##TOP_LEFT_Y##</ymin><xmax>##BOTTOM_RIGHT_X##</xmax><ymax>##BOTTOM_RIGHT_Y##</ymax></bndbox></object>\n";


}

void json2xml::Convert(QString path)
{
    JsonReader::json_t JS = JR->ReadJsonFile(path);
    QString OutputXML = TemplateXML;
    QString OBJTmp = TemplateObject;
    QString objects;
    QString SPath = path;

    QString Folder =path.replace("/"+JS.identifier+".json","");
    QStringList folderSplt = Folder.split("/");
    Folder = folderSplt.at(folderSplt.size()-1);
   // qDebug()<<Folder;

    QString width  = QString::number(JS.imageWidth);
    QString height = QString::number(JS.imageHeight);
    QString pth    = SPath;
    QString depth  ="3";
    pth.replace(".json",".jpg");

    for(int i=0;i<JS.detections.size();i++)
    {
        QString TLX=QString::number(JS.detections.at(i).top_left_x);
        QString TLY=QString::number(JS.detections.at(i).top_left_y);
        QString BRX=QString::number(JS.detections.at(i).bottom_right_x);
        QString BRY=QString::number(JS.detections.at(i).bottom_right_y);


        OBJTmp.replace("##CLASSNAME##",JS.detections.at(i).class_name);
        OBJTmp.replace("##TOP_LEFT_X##",TLX);
        OBJTmp.replace("##TOP_LEFT_Y##",TLY);
        OBJTmp.replace("##BOTTOM_RIGHT_X##",BRX);
        OBJTmp.replace("##BOTTOM_RIGHT_Y##",BRY);

        objects += OBJTmp;
        OBJTmp = TemplateObject;
    }


    OutputXML.replace("##FOLDER##",Folder);
    OutputXML.replace("##FILENAME##",JS.identifier+".jpg");  // generates bug if the image not jpg !!
    OutputXML.replace("##PATH##",pth);
    OutputXML.replace("##WIDTH##",width);
    OutputXML.replace("##HEIGHT##",height);
    OutputXML.replace("##DEPTH##",depth);
    OutputXML.replace("##OBJECTS##",objects);

   // qDebug()<<OutputXML;

    QString XMLPath = SPath.replace(".json",".xml");
    qDebug()<<XMLPath;


    FB->WriteFile(XMLPath,OutputXML);


}
