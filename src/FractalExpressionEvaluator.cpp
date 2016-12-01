#include "FractalExpressionEvaluator.h"

FractalExpressionEvaluator::FractalExpressionEvaluator():
    mEscape(500),
    mMaxIters(512),
    mJuliaValue(-.621,0),
    mRefSize(512),
    mRefPoit1(-.375,.5),
    mRefPoit2(-.125,.25)
{

}

unsigned int FractalExpressionEvaluator::getEscapeValue(){return mEscape;}
void FractalExpressionEvaluator::setEscapeValue(unsigned int Escape){mEscape=Escape;}

unsigned int FractalExpressionEvaluator::getMaxIters(){return mMaxIters;}
void FractalExpressionEvaluator::setMaxIters(unsigned int MaxIters){mMaxIters=MaxIters;}

unsigned int FractalExpressionEvaluator::GetRefSize(){return mRefSize;}
void FractalExpressionEvaluator::setRefSize(unsigned int RefSize){mRefSize=RefSize;}

std::complex<double> FractalExpressionEvaluator::getJuliaValue(){return mJuliaValue;}
void FractalExpressionEvaluator::setJuliaValue(std::complex<double> JuliaValue){mJuliaValue=JuliaValue;}

std::complex<double> FractalExpressionEvaluator::getRefPoit1(){return mRefPoit1;}
void FractalExpressionEvaluator::setRefPoit1(std::complex<double> RefPoit1){mRefPoit1=RefPoit1;}

std::complex<double> FractalExpressionEvaluator::getRefPoit2(){return mRefPoit2;}
void FractalExpressionEvaluator::setRefPoit2(std::complex<double> RefPoit2){mRefPoit2=RefPoit2;}


int FractalExpressionEvaluator::getValue(double x,double y)
{
    //correct for position
    x = mRefPoit1.real() + x*(mRefPoit2.real() - mRefPoit1.real())/mRefSize;
    y = mRefPoit1.imag() + y*(mRefPoit2.imag() - mRefPoit1.imag())/mRefSize;

    std::complex<double> c(x,y);
    std::complex<double> z = c;

    unsigned int i(0);
    while(i < mMaxIters && std::norm(z)<=mEscape)
    {
        z=pow(M_E,pow(z,3))+mJuliaValue;
        i+=1;
    }
    return i;
}
