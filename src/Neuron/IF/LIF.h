#ifndef LIF_H
#define LIF_H

#include <string>

#include "IF.h"

class LIF : public IF {
public:
  LIF(double mu, double D);
  explicit LIF(const std::string &input_file);

  [[nodiscard]] double drift(double v) const override;
};

#endif // LIF_H
