/*
author: Warren Schweigert
*/
#ifndef FRACTALEXSPRESSIONEVALUATOR_H
#define FRACTALEXSPRESSIONEVALUATOR_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <complex>


class FractalExpressionEvaluator
{

public:

    FractalExpressionEvaluator();

    void setPreset(unsigned int);

    //if the magnitude of z is greater then this value then getValue will return how many iterations it took to get there
    unsigned int getEscapeValue() const;
    void setEscapeValue(unsigned int);

    //limits the number if times the fractal will loop, the return value of  getValue will be between 1 and this value
    unsigned int getMaximumIterations() const;
    void setMaximumIterations(unsigned int);

    //determines which julia fractal in the set of julia fractals of form e^z^3 + j
    std::complex<double> getJuliaValue() const;
    void setJuliaValue(std::complex<double>);


    //LOCATION Information
    //RefPoint1, RefPoint2, and RefSize determine the scale and position within the fractal
    //getValue(0,0) will evaluate at refpoint1 while getValue(RefSize,RefSize) will evaluate at refpoint2
    std::complex<double> getRefPoint1() const;
    void setRefPoint1(std::complex<double>);

    std::complex<double> getRefPoint2() const;
    void setRefPoint2(std::complex<double>);

    unsigned int getRefSize() const;
    void setRefSize(unsigned int);

    int getValue(double x,double y) const;

private:
    unsigned int mEscape;
    unsigned int mMaximumIterations;
    std::complex<double> mJuliaValue;

    //these variables deal with scaling and positioning
    unsigned int mRefSize;
    std::complex<double> mRefPoint1;
    std::complex<double> mRefPoint2;
    //void* functionString = [](std::complex<double> z,const std::complex<double>& c,const std::complex<double>& j)->{};

};

#endif // FRACTALEXSPRESSIONEVALUATOR_H
