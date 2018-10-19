#ifndef PARTICLE_H
#define PARTICLE_H

#include "IRelativity.h"
#include "IMathematics.h"


enum ParticleType {STATIC , DYNAMIC};

class IParticle
{

    private:

       ParticleType mType;

       //------------------//

        Vector3 mPosition;
        Vector3 mVelocity;

        float   mMassInverse;

       //------------------//

       const float mLightSpeed;

    public:

       //-------------------[ constructors ]--------------------//
       IParticle( const Vector3& _pos , float _massa , ParticleType _type , const float _LightSpeed)
       : mType(_type),
         mPosition(_pos),
         mMassInverse(float(1.0/_massa)),
         mLightSpeed(_LightSpeed)
       {
       }

       //-------------------------------------------------------//

       void ApplyImpulse(const Vector3& impulse);

       //-------------------------------------------------------//

       Vector3 GetPosition() const;
       Vector3 GetVelocity() const;
       Vector4 GetVelocity4() const;

       //------------------[ friend classes ]-------------------//
       friend class IParticleSystem;



};

#endif // PARTICLE_H
