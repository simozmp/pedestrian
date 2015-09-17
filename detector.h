/*
###################################################################
#
#   Authors: Ciotti Giorgio, Lunetto Gaspare
#   Date: 16/09/15
#
###################################################################
*/

#include "common_defs.h"

/**/

class Detector
{
   private:
      cv::HOGDescriptor _hog;

   public:
      /* Constructors */
      Detector (enum TYPES a) : _hog(cv::Size(48, 96), cv::Size(16, 16), cv::Size(8, 8), cv::Size(8, 8), 9, 1, -1, cv::HOGDescriptor::L2Hys, 0.2, true, cv::HOGDescriptor::DEFAULT_NLEVELS)
      {
         switch (a)
         {
            case PEDESTRIANS:
               _hog.setSVMDetector ( cv::HOGDescriptor::getDaimlerPeopleDetector() );
               break;

            case CARS:
               break;

            case CYCLES:
               break;

            default:
               exit (1);
         }
      }

      /* Other methods, needed in order to elaborate the image */
      std::vector<cv::Rect> detect (cv::UMat input)
      {
         std::vector<cv::Rect> output;

         _hog.detectMultiScale(input.getMat(cv::ACCESS_READ), output, 1.4, cv::Size(8, 8), cv::Size(0, 0), 1.05, 8);

         return output;
      }
};
