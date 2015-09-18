#include "detector.h"

int main ()
{
   Detector detector;
   cv::VideoCapture vc;
   cv::UMat frame;
   cv::Mat img_to_show;

   vc.open("/home/ubuntu/development/pedestrian/768x576.avi");

   while (true)
   {
      vc >> frame;
      frame.copyTo(img_to_show);

      Detected found;

      //detection of pedestrians
      found = detector.detect(frame);

      // Draw positive classified windows

      for (size_t i = 0; i < found.pedestrians_found.size(); i++)
      {
         cv::Rect r = found.pedestrians_found[i];
         rectangle(img_to_show, r.tl(), r.br(), cv::Scalar(0, 255, 0), 3);
      }

      for (size_t i = 0; i < found.cycles_found.size(); i++)
      {
         cv::Rect r = found.cycles_found[i];
         rectangle(img_to_show, r.tl(), r.br(), cv::Scalar(255, 0, 0), 3);
      }

      for (size_t i = 0; i < found.cars_found.size(); i++)
      {
         cv::Rect r = found.cars_found[i];
         rectangle(img_to_show, r.tl(), r.br(), cv::Scalar(0, 0, 255), 3);
      }

      //realtime output of elaborated frame
      imshow("debug", img_to_show);
      cv::waitKey(3);

   }

   return 0;
}
