#include "ruleset.h"

const Ruleset Ruleset::DEFAULT {
  -1, 4,
  1000, 300, 500,
  {1, 2000},
  10000, 5, 5000,
  4, 2, 2,
  2,
  {{1./3., 1./3., 1./6., 1./12., 1./12.},
   {1./4., 1./3., 1./4., 1./12., 1./12.},
   {1./12., 1./4., 1./3., 1./4., 1./12.},
   {1./12., 1./12., 1./4., 1./3., 1./4.},
   {1./12., 1./12., 1./6., 1./3., 1./3.}},
  {{1., 800},
   {1.5, 650},
   {2., 500},
   {2.5, 400},
   {3., 300}},
  {{3., 6500},
   {2.5, 6000},
   {2., 5500},
   {1.5, 5000},
   {1, 4500}}
};
