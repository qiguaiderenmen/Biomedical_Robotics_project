#include "NeuroKinematics/NeuroKinematics.hpp"
#include <iostream>
#include <string>
#include <math.h> /* isnan, sqrt */
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

// Initializing the joint variables for use in the FK function
double AxialHeadTranslation{0.0};
double AxialFeetTranslation{0.0};
double LateralTranslation{0.0};
double PitchRotation{0.0};
double YawRotation{0.0};
double ProbeInsertion{0.0};
double ProbeRotation{0.0};
// A is treatment to tip, where treatment is the piezoelectric element,// A = 10mm
// B is robot to entry, this allows us to specify how close to the patient the physical robot can be,// B = 5mm
// C is cannula to treatment, we define this so the robot can compute the cannula length,// C = 5mm
// D is the robot to treatment distance,// D = 41mm
// Creating an object called Forward for FK
double _cannulaToTreatment{5.0};
double _treatmentToTip{10.0};
double _robotToEntry{5.0};
double _robotToTreatmentAtHome{41.0};
Probe probe_init = {
    _cannulaToTreatment,
    _treatmentToTip,
    _robotToEntry,
    _robotToTreatmentAtHome};

// std::cout << Forward._lengthOfAxialTrapezoidSideLink << std::endl;
// std::cout << Forward._widthTrapezoidTop << std::endl;
// std::cout << Forward._initialAxialSeperation << std::endl;
// std::cout << Forward._xInitialRCM << std::endl;
// std::cout << Forward._yInitialRCM << std::endl;
// std::cout << Forward._zInitialRCM << std::endl;
// std::cout << Forward._robotToRCMOffset << std::endl;
// std::cout << Forward._probe->_treatmentToTip << std::endl;
// std::cout << "the code built successfully" << std::endl;
// std::cout << ProbeRotation << std::endl;
// std::cout << "The probe cannula to treatment is:" << probe_init._cannulaToTreatment << std::endl;

int main()
{
  Probe *probe1{&probe_init}; // Creating a pointer Probe1 of type Probe that points to the address of probe_init
  NeuroKinematics Forward(probe1);
  // Yaw rotation range : -1.54 - +0.01
  // Probe Rotation range : -6.28 - +6.28
  // Pitch Rotation range : -0.46 - 0.65
  // Probe Insertion range : 0.00 - 34.93
  // Lateral Translation range : -49.47 - 0.00
  // Axial Head Translation range : -145.01 - 0.00
  // Axial Feet Translation range : -70.00 - 75.01 -> Experimental range from -7 to 233 inclusive
  Neuro_FK_outputs FK{};
  // FK = Forward.ForwardKinematics(AxialHeadTranslation, AxialFeetTranslation,
  //                                LateralTranslation, ProbeInsertion,
  //                                ProbeRotation, PitchRotation, YawRotation);
  // std::cout << "Z Position :\n"
  //           << FK.zFrameToTreatment << std::endl;
  // AxialHeadTranslation = -70;
  // FK = Forward.ForwardKinematics(AxialHeadTranslation, AxialFeetTranslation,
  //                                LateralTranslation, ProbeInsertion,
  //                                ProbeRotation, PitchRotation, YawRotation);
  // std::cout << "Z Position :\n"
  //           << FK.zFrameToTreatment << std::endl;
  // AxialHeadTranslation = -60;
  // FK = Forward.ForwardKinematics(AxialHeadTranslation, AxialFeetTranslation,
  //                                LateralTranslation, ProbeInsertion,
  //                                ProbeRotation, PitchRotation, YawRotation);
  // std::cout << "Z Position :\n"
  //           << FK.zFrameToTreatment << std::endl;
  // Max allowed seperation  146mm
  // Min allowed seperation 75mm
  double i{}, j{}, k{}, l{};

  for (i = 0, j = 0; i < 87; ++i, ++j) //75
  {
    AxialFeetTranslation = i;
    AxialHeadTranslation = j;
    for (k = 0; k <= 37.5; k += 0.5)
    {
      LateralTranslation = k;
      FK = Forward.ForwardKinematics(AxialHeadTranslation, AxialFeetTranslation,
                                     LateralTranslation, ProbeInsertion,
                                     ProbeRotation, PitchRotation, YawRotation);
      if (isnan(FK.zFrameToTreatment(1, 3)))
      {
        std::cout << "Y is out of range!\n";
        break;
      }
      if (i == 0 | i == 86)
      {
        std::cout << "\ni is :" << i << " ,";
        std::cout << "j is :" << j << " ,";
        std::cout << "k is :" << k << std::endl;
        std::cout << "X Position :" << FK.zFrameToTreatment(0, 3) << std::endl;
        std::cout << "Y Position :" << FK.zFrameToTreatment(1, 3) << std::endl;
        std::cout << "Z Position :" << FK.zFrameToTreatment(2, 3) << std::endl;
      }
    }
  }

  return 0;
}