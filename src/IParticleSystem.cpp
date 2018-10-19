#include "IParticleSystem.h"
#include "IMathematics.h"


IParticleSystem::IParticleSystem()
 : mLightSpeed(1.0)
{

}

IParticle *IParticleSystem::CreateParticle(const Vector3 &pos, float massa, ParticleType _type)
{
    IParticle *particle = new IParticle( pos , massa , _type , mLightSpeed );
    mParticles.insert(particle);
    return particle;
}


void IParticleSystem::DeleteParticle(IParticle *particle)
{
    mParticles.erase(particle);
    delete particle;
}

void IParticleSystem::Update(float TimeStep)
{

    for( auto it = mParticles.begin(); it != mParticles.end(); ++it )
    {
        IParticle *particle = *it;

        float ownTimeStep =  TimeDilation(TimeStep , Gamma(particle->mVelocity * TimeStep)); // Own local time interval

        Matrix4 MatrixLorentzBoost = Matrix4::CreateLorentzBoostInvert( particle->mVelocity * ownTimeStep , mLightSpeed );
        particle->mPosition = (MatrixLorentzBoost * LVector4( particle->mPosition , 1.0)).GetXYZ();
    }

}


void IParticleSystem::AdvancedAngularMoment(const Vector3 &AngularMomentAxis)
{
    for( auto it = mParticles.begin(); it != mParticles.end(); ++it )
    {
        IParticle *particle = *it;

        Vector3 moment = AngularMomentAxis.Cross(particle->GetPosition());
        //Vector3 moment = -Vector3::Y  * 0.05;
        particle->mVelocity.SetToZero();
       if(!std::isnan(moment.x) ||
          !std::isnan(moment.y) ||
          !std::isnan(moment.z))
       {
           particle->ApplyImpulse(moment);
       }


    }

}
