#include "IParticle.h"


#include <iostream>

Vector3 IParticle::GetPosition() const
{
    return mPosition;
}

Vector3 IParticle::GetVelocity() const
{
    return mVelocity;
}

Vector4 IParticle::GetVelocity4() const
{
  return Vector4(mVelocity,gamma_inv(mVelocity,mLightSpeed));
}

void IParticle::ApplyImpulse(const Vector3 &impulse)
{
    Vector3 impuls = impulse * mMassInverse;// /  gamma(mVelocity,mLightSpeed);

    //impuls = Vector3::Clamp( impuls , mLightSpeed - 0.01 );

    mVelocity = velocityAddition(mVelocity,impuls,gamma(mVelocity,mLightSpeed),mLightSpeed);

//    Vector4 V4(mVelocity,gamma_inv(mVelocity,mLightSpeed));
//    std::cout << " L: " <<  V4.Length()  << "  V:" << mVelocity.Length() << std::endl;

   // std::cout<< mVelocity.Length() << std::endl;

}

