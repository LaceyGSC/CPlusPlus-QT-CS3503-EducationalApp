#include "FractalExspressionEvaluator.h"

FractalExspressionEvaluator::FractalExspressionEvaluator():
    mEscape(500),
    mMaxIters(512),
    mJuliaValue(-.621,0),
    mRefSize(512),
    mRefPoit1(-.375,.5),
    mRefPoit2(-.125,.25)
{

}

unsigned int FractalExspressionEvaluator::getEscapeValue(){return mEscape;}
void FractalExspressionEvaluator::setEscapeValue(unsigned int Escape){mEscape=Escape;}

unsigned int FractalExspressionEvaluator::getMaxIters(){return mMaxIters;}
void FractalExspressionEvaluator::setMaxIters(unsigned int MaxIters){mMaxIters=MaxIters;}

unsigned int FractalExspressionEvaluator::GetRefSize(){return mRefSize;}
void FractalExspressionEvaluator::setRefSize(unsigned int RefSize){mRefSize=RefSize;}

std::complex<double> FractalExspressionEvaluator::getJuliaValue(){return mJuliaValue;}
void FractalExspressionEvaluator::setJuliaValue(std::complex<double> JuliaValue){mJuliaValue=JuliaValue;}

std::complex<double> FractalExspressionEvaluator::getRefPoit1(){return mRefPoit1;}
void FractalExspressionEvaluator::setRefPoit1(std::complex<double> RefPoit1){mRefPoit1=RefPoit1;}

std::complex<double> FractalExspressionEvaluator::getRefPoit2(){return mRefPoit2;}
void FractalExspressionEvaluator::setRefPoit2(std::complex<double> RefPoit2){mRefPoit2=RefPoit2;}


int FractalExspressionEvaluator::getValue(double x,double y)
{

    //correct for position
    x = mRefPoit1.real() + x*(mRefPoit2.real() - mRefPoit1.real())/mRefSize;
    y = mRefPoit1.imag() + y*(mRefPoit2.imag() - mRefPoit1.imag())/mRefSize;

    std::complex<double> c(x,y);
    std::complex<double> z = c;

    unsigned int i(0);
    for(i = 0; i<mMaxIters || std::norm(z)>=mEscape;i++)
    {
        z=pow(M_E,pow(z,3))+mJuliaValue;
    }
    return i;
}
