/*
###################################################################
#
#   Authors: Ciotti Giorgio, Zomparelli Simone, Lunetto Gaspare
#   Date: 16/09/15
#
###################################################################
*/

#include "common_defs.h"

//

enum TYPE = { PEDESTRIANS, CYCLES, CARS }; // DA TOGLIERE

class Wrapper
{
   private:
      cv::Mat _image;
      
   public:
      cv::Mat get_image() { return _image; }
      void tracker();

}

