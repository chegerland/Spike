#ifndef TIMEFRAME_H
#define TIMEFRAME_H

#include <string>

//! A time frame struct
class Timeframe
{
public:
  
  /*! start time */
  double t_0;
  /*! end time */
  double t_end;
  /*! time step */
  double dt;

  Timeframe(std::string input_file);
};

#endif // TIMEFRAME_H
