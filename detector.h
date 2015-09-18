/*
###################################################################
#
#   Authors: Ciotti Giorgio, Zomparelli Simone
#   Date: 17/09/15
#
###################################################################
*/

#include "common_defs.h"
// 
/**/

struct Detected
{
   std::vector<cv::Rect>     pedestrians_found;
   std::vector<cv::Rect>     cycles_found;
   std::vector<cv::Rect>     cars_found;
};

class Detector
{
   private:
      bool _pedestrians;
      bool _cycles;
      bool _cars;
      cv::HOGDescriptor _hog_pedestrians;
      cv::HOGDescriptor _hog_cycles;
      cv::HOGDescriptor _hog_cars;

   public:
      /* Constructors */
      Detector () : _hog_pedestrians (cv::Size(48, 96), cv::Size(16, 16), cv::Size(8, 8), cv::Size(8, 8), 9, 1, -1, cv::HOGDescriptor::L2Hys, 0.2, true, cv::HOGDescriptor::DEFAULT_NLEVELS),
                    _hog_cycles (cv::Size(48, 96), cv::Size(16, 16), cv::Size(8, 8), cv::Size(8, 8), 9, 1, -1, cv::HOGDescriptor::L2Hys, 0.2, true, cv::HOGDescriptor::DEFAULT_NLEVELS),
                    _hog_cars (cv::Size(48, 96), cv::Size(16, 16), cv::Size(8, 8), cv::Size(8, 8), 9, 1, -1, cv::HOGDescriptor::L2Hys, 0.2, true, cv::HOGDescriptor::DEFAULT_NLEVELS)
      {
         _pedestrians = true;
         _cycles = false;
         _cars = false;
         _hog_pedestrians.setSVMDetector ( cv::HOGDescriptor::getDaimlerPeopleDetector() );
         //_hog_cycles.setSVMDetector (  );
         //_hog_cars.setSVMDetector (  );
      }

      /* Other methods, needed in order to elaborate the image */
      Detected detect (cv::UMat input)
      {
         Detected output;

         if(_pedestrians) _hog_pedestrians.detectMultiScale(input.getMat(cv::ACCESS_READ), output.pedestrians_found, 1.4, cv::Size(8, 8), cv::Size(0, 0), 1.05, 8);
         //if(_cycles) _hog_cycles.detectMultiScale(input.getMat(cv::ACCESS_READ), output.cycles_found, 1.4, cv::Size(8, 8), cv::Size(0, 0), 1.05, 8);
         //if(_cars) _hog_cars.detectMultiScale(input.getMat(cv::ACCESS_READ), output.cars_found, 1.4, cv::Size(8, 8), cv::Size(0, 0), 1.05, 8);

         return output;
      }

      void set_pedestrians(bool status)  {  _pedestrians = status;  }
      void set_cycles(bool status)  {  _cycles = status;  }
      void set_cars(bool status)  {  _cars = status;  }

      bool get_pedestrians { return _pedestrian;  }
      bool get_cycles { return _cycles;  }
      bool get_cars { return _cars;  }

};
