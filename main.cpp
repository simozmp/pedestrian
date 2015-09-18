/*
###################################################################
#
#   Author: Lunetto Gaspare, Zomparelli Simone
#   Date:   17/09/15
#
###################################################################
*/

#include "common_defs.h"
#include "detector.h"
#include "kalman.h"
#include "point_image.h"

/* main for detector */

struct Found_Id
{
  unsigned int  id;
  unsigned int  life : 3;    // Time to live
  cv::Rect      location;
  bool          old;
  Kalman_Filter kf;
};


int main ()
{
  /* Un oggetto detector per trovare "persone" nel video */
  Detector detector(PEDESTRIANS);

  /* Viedo stream declaration */
  cv::VideoCapture vc;

  /* Images matrixes (actual frame, output image) */
  cv::UMat frame;
  cv::Mat img_to_show;
  Point_Image point_image;

  /* Opening videostram */
  vc.open("/home/ubuntu/development/pedestrian/768x576.avi");

  std::vector<Found_Id>  id_list;

  while (true)
  {
    /* Import the frame */
    vc >> frame;
    point_image.set_image(frame);
    frame.copyTo(img_to_show);

    /* Containers for Detection results */
    std::vector<cv::Rect> found;

    //detection of things
    found = detector.detect(point_image.image());

    // for each Rect found
    for (size_t i = 0; i < found.size(); i++)
    {
      /* id_found controls the existence of this rect in the id_list */
      bool id_found = false;

      //  Check for match
      for(size_t j = 0; j < id_list.size(); j++)
      {
        double distance = (double)sqrt( pow( found.at(i).x - id_list.at(j).location.x, 2 ) + pow( found.at(i).y - id_list.at(j).location.y, 2 ) );

        if( distance < TRESHOLD )
        {
          id_list.at(j).location = found.at(i);
          id_list.at(j).life = 0;
          id_list.at(j).old = !(id_found = true);
          j = id_list.size();
        }
      }
      if( !id_found )   
      {
        // Init a new list element
        Found_Id temp;
        temp.id = id_list.size();
        temp.location = found.at(i);
        temp.life = 0;
        temp.old = false;
        temp.kf.init(found.at(i).x, found.at(i).y);
        id_list.push_back(temp);
      }

      // Show the detected item
      cv::Rect r = found[i];
      rectangle(img_to_show, r.tl(), r.br(), cv::Scalar(0, 255, 0), 3);

    }

    // appoggio per l'output
    cv::Point pt;

    // for each list item
    for(size_t j = 0; j < id_list.size();)
    {
      bool print = true;

      // make a prediction
      id_list.at(j).kf.kalman_predict();

      // checks the age of the item, if new correct kalman filter with measurement
      if(!id_list.at(j).old) pt = id_list.at(j).kf.kalman_correct( id_list.at(j).location.x, id_list.at(j).location.y );

      //if old:
      else
      {
        // increase item's lifetime
        ++id_list.at(j).life;

        // Set the output point to previous location
        pt = cv::Point( id_list.at(j).location.x, id_list.at(j).location.y );

        // check TTL overlap, if overlapped erase it
        if( id_list.at(j).life >= TTL) 
        {
          id_list.erase(id_list.begin() + j);
          print = false;
        }
      }

      if( print )
      {
        std::stringstream ss;
        ss << "Id:" << id_list.at(j).id << " T:" << id_list.at(j).life;

        rectangle(img_to_show, pt, cv::Point(id_list.at(j).location.width + pt.x, id_list.at(j).location.height + pt.y), cv::Scalar(255, 0, 0), 2);
        putText(img_to_show, ss.str(), cv::Point( pt.x, pt.y - 4 ), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 0, 0), 1.5, 7, false );
        id_list.at(j).old = true;
        j++;
      }
    }

    //realtime output of elaborated frame
    imshow("debug", img_to_show);
    cv::waitKey(1);

  }

  return 0;
}
