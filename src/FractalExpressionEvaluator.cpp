#include "FractalExpressionEvaluator.h"

FractalExpressionEvaluator::FractalExpressionEvaluator():
    mEscape(500),
    mMaximumIterations(512),
    mJuliaValue(-.621,0),
    mRefSize(512),
    mRefPoint1(-.375,.5),
    mRefPoint2(-.125,.25)
{

}

unsigned int FractalExpressionEvaluator::getEscapeValue() const
{
    return mEscape;
}
void FractalExpressionEvaluator::setEscapeValue(unsigned int Escape)
{
    mEscape=Escape;
}

unsigned int FractalExpressionEvaluator::getMaximumIterations() const
{
    return mMaximumIterations;
}
void FractalExpressionEvaluator::setMaximumIterations(unsigned int MaxIters)
{
    mMaximumIterations=MaxIters;
}

unsigned int FractalExpressionEvaluator::getRefSize() const
{
    return mRefSize;
}
void FractalExpressionEvaluator::setRefSize(unsigned int RefSize){mRefSize=RefSize;}

std::complex<double> FractalExpressionEvaluator::getJuliaValue() const
{
    return mJuliaValue;
}
void FractalExpressionEvaluator::setJuliaValue(std::complex<double> JuliaValue)
{
    mJuliaValue=JuliaValue;
}

std::complex<double> FractalExpressionEvaluator::getRefPoint1() const
{
    return mRefPoint1;
}
void FractalExpressionEvaluator::setRefPoint1(std::complex<double> RefPoit1)
{
    mRefPoint1=RefPoit1;
}

std::complex<double> FractalExpressionEvaluator::getRefPoint2() const
{
    return mRefPoint2;
}
void FractalExpressionEvaluator::setRefPoint2(std::complex<double> RefPoit2)
{
    mRefPoint2=RefPoit2;
}


int FractalExpressionEvaluator::getValue(double x,double y) const
{
    //correct for position and scale
    x = mRefPoint1.real() + x*(mRefPoint2.real() - mRefPoint1.real())/mRefSize;
    y = mRefPoint1.imag() + y*(mRefPoint2.imag() - mRefPoint1.imag())/mRefSize;

    std::complex<double> c(x,y);
    std::complex<double> z = c;

    unsigned int i(0);
    while(i < mMaximumIterations && std::norm(z)<=mEscape)
    {
        z=pow(M_E,pow(z,3))+mJuliaValue;
        i+=1;
    }
    return i;
}
