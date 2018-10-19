#include "IParticle.h"

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
  return Vector4(mVelocity,GammaInv(mVelocity/mLightSpeed));
}


void IParticle::ApplyImpulse(const Vector3 &impulse)
{
    Vector3 impuls = impulse * mMassInverse;//  Gamma(mVelocity,mLightSpeed);
    mVelocity = VelocityAddition(mVelocity,impuls,Gamma(mVelocity/mLightSpeed),mLightSpeed);

}

