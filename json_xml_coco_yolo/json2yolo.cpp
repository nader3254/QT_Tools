#include "json2yolo.h"



Json2Yolo::Json2Yolo()
{
     JR = new JsonReader();
     FB=new FileBrowser("");
}

void Json2Yolo::Convert(QString path)
{
    Spath=path;
    JsonReader::json_t JS=JR->ReadJsonFile(path);

    for(int i=0;i<JS.detections.size();i++)
    {
        object_class = JS.detections.at(i).class_id - 1;
        TL_X =JS.detections.at(i).top_left_x;
        TL_Y =JS.detections.at(i).top_left_y;
        BR_X =JS.detections.at(i).bottom_right_x;
        BR_Y =JS.detections.at(i).bottom_right_y;

        x_center = ((TL_X+BR_X)/2);
        y_center = ((TL_Y+BR_Y)/2);

        box_width  =((BR_X-TL_X)/JS.imageWidth);
        box_height =((BR_Y-TL_Y)/JS.imageHeight);

        norm_x = (x_center/JS.imageWidth);
        norm_y = (y_center/JS.imageHeight);

        YoloOutput += QString::number(object_class)+" ";
        YoloOutput += QString::number(norm_x)+" ";
        YoloOutput += QString::number(norm_y)+" ";
        YoloOutput += QString::number(box_width)+" ";
        YoloOutput += QString::number(box_height)+" ";
        YoloOutput += "\n";
        class_names<<JS.detections.at(i).class_name+"\n";

    }
     Spath.replace(".json",".txt");
     FB->WriteFile(Spath,YoloOutput);

     qDebug()<<"yolo path"<<Spath;


     Spath.replace(JS.identifier,"classes");
     QString ClassesOutput;
     qDebug()<<"classes path"<<Spath;
     for (int i = 0; i < class_names.size(); i++)
     {
         if(!(ClassesOutput.contains(class_names.at(i))))
         {
              ClassesOutput += class_names.at(i);
         }

     }
     FB->WriteFile(Spath,ClassesOutput);
     RST();

}

void Json2Yolo::RST()
{
    TL_X=0.0;       TL_Y=0.0;
    BR_X=0.0;       BR_Y=0.0;
    x_center=0.0;   y_center=0.0;
    norm_x=0.0;     norm_y=0.0;
    box_width=0.0;  box_height=0.0;
    object_class=0;

    class_names.clear();
    Spath=" ";
    YoloOutput ="";



}


