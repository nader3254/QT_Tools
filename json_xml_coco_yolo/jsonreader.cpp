#include "jsonreader.h"

JsonReader::JsonReader()
{
    f= new FileBrowser("");

}

JsonReader::json_t JsonReader::ReadJsonFile(QString path)
{
     json_t js; json_t JSON_FILE;
     //read the json file and stor it at jsonSTR
     jsonSTR = f->ReadFile(path);
     bb=jsonSTR.toUtf8(); // may be useful in future use ...
     QStringList spt;    QStringList spt2;
     // check if the selected json file is at our json representation or not
     if(jsonSTR.contains("detections") && jsonSTR.contains("identifier") &&\
        jsonSTR.contains("imageHeight") && jsonSTR.contains("imageWidth")     )
     {
         spt  = jsonSTR.split("identifier");
         spt2 = spt.at(1).split("\n");
/********************** identifier *************************/
         // extract the identifire value
         QString id = spt2.at(0);
         id.remove(" ");id.remove('"');id.remove(':');id.remove(',');
         js.identifier=id;
         JSON_FILE.identifier=id;
/*********************** imageHeight *************************/
         // extract the imageHeight value
         QStringList p1=spt2.at(1).split(":");
         QString ih = p1.at(1);
         ih.remove(" ");ih.remove('"');ih.remove(',');
         js.imageHeight =ih.toInt();
         JSON_FILE.imageHeight =ih.toInt();
/******************** imageWidth **************************/
         // extract the imageWidth value
         QStringList p2=spt2.at(2).split(":");
         QString iw = p2.at(1);
         iw.remove(" ");iw.remove('"');
         js.imageWidth = iw.toInt();
         JSON_FILE.imageWidth = iw.toInt();
/*********************** Detected Objects *****************************/
         // extract the Detected Objects values as string first
         QStringList objs =spt.at(0).split("}");
         for(int i=0;i<objs.size();i++)
         {

             if(objs.at(i).contains("bottom_right_xy") && objs.at(i).contains("top_left_xy") )
             {
                 DetectedObjects_t dobj;
                 dobj.ObjectStr = objs.at(i);
                 js.detections <<dobj;

             }
         }
         // parsing the Detected Objects values
         for(int i=0;i<js.detections.size();i++)
         {
             QStringList BRSplt =js.detections.at(i).ObjectStr.split("bottom_right_xy");
             QStringList CISplt =js.detections.at(i).ObjectStr.split("class_id");
             QStringList CNSplt =js.detections.at(i).ObjectStr.split("class_name");
             QStringList TLSplt =js.detections.at(i).ObjectStr.split("top_left_xy");

             DetectedObjects_t dobj;
             dobj.ObjectStr = js.detections.at(i).ObjectStr;

             QString BR = BRSplt.at(1);
             BR.remove("class_id");
             BR.remove(CISplt.at(0));
             BR.remove(CISplt.at(1));
             BR.remove(" ");BR.remove("\"");
             BR.remove("\n");BR.remove(":");
             BR.remove("[");BR.remove("]");
             QStringList BRSplt2 = BR.split(",");
             QString BR1=BRSplt2.at(0);BR1.remove(",");
             QString BR2=BRSplt2.at(1);BR2.remove(",");
             dobj.bottom_right_x = BR1.toFloat();
             dobj.bottom_right_y = BR2.toFloat();



             QString CI = CISplt.at(1);
             CI.remove("class_name");
             CI.remove(CNSplt.at(0));
             CI.remove(CNSplt.at(1));
             CI.remove(" ");CI.remove("\"");
             CI.remove("\n");CI.remove(":");
             CI.remove(",");
             dobj.class_id = CI.toInt();


             QString CN = CNSplt.at(1);
             CN.remove("top_left_xy");
             CN.remove(TLSplt.at(0));
             CN.remove(TLSplt.at(1));
             CN.remove(" ");CN.remove("\"");
             CN.remove("\n");CN.remove(":");
             CN.remove(",");
             dobj.class_name = CN;


             QString TL = TLSplt.at(1);
             TL.remove(" ");TL.remove("\"");
             TL.remove("\n");TL.remove(":");
             TL.remove("[");TL.remove("]");
             QStringList TLSplt2 = TL.split(",");
             QString TL1=TLSplt2.at(0);TL1.remove(",");
             QString TL2=TLSplt2.at(1);TL2.remove(",");
             dobj.top_left_x = TL1.toFloat();
             dobj.top_left_y = TL2.toFloat();

             JSON_FILE.detections<<dobj;

         }

     }

/************************ Debugging ****************************/
     qDebug()<<"Json file contents .......";
     qDebug()<<"identifier="<<JSON_FILE.identifier;
     qDebug()<<"imgHeight="<<JSON_FILE.imageHeight;
     qDebug()<<"imgWidth="<<JSON_FILE.imageWidth;

     for (int i = 0; i < JSON_FILE.detections.size(); i++)
     {
          qDebug()<<"******** Object "<<i<<"**********";
          qDebug()<<"bottom_right_x="<<JSON_FILE.detections.at(i).bottom_right_x<<"bottom_right_x="<<JSON_FILE.detections.at(i).bottom_right_y;
          qDebug()<<"class_id"<<JSON_FILE.detections.at(i).class_id;
          qDebug()<<"class_name"<<JSON_FILE.detections.at(i).class_name;
          qDebug()<<"top_left_x="<<JSON_FILE.detections.at(i).top_left_x<<"top_left_y="<<JSON_FILE.detections.at(i).top_left_y;

     }

  return JSON_FILE;
}



