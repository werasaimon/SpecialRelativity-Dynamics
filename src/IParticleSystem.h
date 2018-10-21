#ifndef IPARTICLESYSTEM_H
#define IPARTICLESYSTEM_H

#include "IParticle.h"



#include "IMathematics.h"
#include <vector>
#include <set>




class IParticleSystem
{
    protected:

        std::set<IParticle*> mParticles;
        Vector3              mGravityPoint;
        const float          mLightSpeed;

    public:

        IParticleSystem();

        //--------------------------------------------//

        IParticle *CreateParticle(const Vector3 &pos , float massa , ParticleType _type );


        void  DeleteParticle( IParticle *particle );

        //--------------------------------------------//

        void  Update(float TimeStep);

        //--------------------------------------------//

        void AdvancedAngularMoment( const Vector3& AngularMomentAxis );
};

#endif // IPARTICLESYSTEM_H
