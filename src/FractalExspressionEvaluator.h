#ifndef FRACTALEXSPRESSIONEVALUATOR_H
#define FRACTALEXSPRESSIONEVALUATOR_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <complex>


class FractalExspressionEvaluator
{

public:

    FractalExspressionEvaluator();

    void setPreset(unsigned int);

    unsigned int GetRefSize();
    void setRefSize(unsigned int);

    unsigned int getEscapeValue();
    void setEscapeValue(unsigned int);

    unsigned int getMaxIters();
    void setMaxIters(unsigned int);

    std::complex<double> getJuliaValue();
    void setJuliaValue(std::complex<double>);

    std::complex<double> getRefPoit1();
    void setRefPoit1(std::complex<double>);

    std::complex<double> getRefPoit2();
    void setRefPoit2(std::complex<double>);



    int getValue(double x,double y);

private:
    unsigned int mEscape;
    unsigned int mMaxIters;
    std::complex<double> mJuliaValue;

    //these variables deal with scaling and positioning
    unsigned int mRefSize;
    std::complex<double> mRefPoit1;
    std::complex<double> mRefPoit2;
    //void* functionString = [](std::complex<double> z,const std::complex<double>& c,const std::complex<double>& j)->{};

};

#endif // FRACTALEXSPRESSIONEVALUATOR_H
