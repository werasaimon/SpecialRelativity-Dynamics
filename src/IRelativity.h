#ifndef RELATIVITY_H
#define RELATIVITY_H

#include "IMathematics.h"


/**
* Relativistically adds two velocities, v and u, and returns their sum, w;
* each velocity is expressed as a 3-vector in the form (x,y,z),(x,y,z);
* treats v as the velocity of a relativistic reference frame and u as the
* velocity of something within that frame
**/
static Vector3 VelocityAddition(const Vector3 &vComp,
                                const Vector3 &uComp,
                                const float &gamma_v,
                                const float &c)
{

    float dot_VU = std::abs((vComp).Dot(uComp))/(c*c);

    /**
    * using the values calculated above, calculates one component at a time of
    * the velocity resulting from the relativistic addition of v and u
    * ------------------------------------------------------------------
    * if the relativistical velocity sum is w:
    *         1                            gamma_v
    * w = -------- * [ vComp * ( 1+dot_VU*--------- ) + uComp/gamma_v ]
    *     1+dot_VU                         1+gamma_v
    **/

    return (1.0/(1.0+dot_VU)) * (vComp * (1.f+dot_VU*(gamma_v/(1.f+gamma_v))) + (uComp/gamma_v));
}

/**
*calculates gamma for two reference frames moving relative to eachother with
* speed equal to the 3-vector v; gamma is a unitless relativistic factor which
* determines the magnitude of many relativistic effects, such as time
* dilation and Lorentz contraction (shortening of moving objects)
**/
static float Gamma(const Vector3 &beta)
{
    float gamma = 1.f/sqrt(1.f - IMath::Clamp(Dot(beta,beta),0.f,0.9999f)); //definition of gamma
    return gamma;
}

/**
*calculates gamma for two reference frames moving relative to eachother with
* speed equal to the 3-vector v; gamma is a unitless relativistic factor which
* determines the magnitude of many relativistic effects, such as time
* dilation and Lorentz contraction invert (shortening of moving objects)
**/
static float GammaInv(const Vector3 &beta)
{
    float gamma = sqrt(1.f - IMath::Clamp(Dot(beta,beta),0.f,0.9999f)); //definition of gamma
    return gamma;
}

/**
* objects moving quickly relative to a stationary observer will have the
* frequency of the light leaving them shifted based on the relativistic factor
* beta. as a result, their color will change -- this is the origin for the terms
* "redshift" and "blueshift"
**/
static float DopplerShift(float properFreq, float beta)
{
   float newFreq = properFreq * sqrt(1-beta)/sqrt(1+beta);
   return newFreq;
}

/**
* an observer will see the progression of time in a relatively moving frame of
* reference slow down by a factor of gamma (a relativistic factor)
* **/
static float TimeDilation(float time, float gamma)
{
   return time/gamma;
}


#endif // RELATIVITY_H
