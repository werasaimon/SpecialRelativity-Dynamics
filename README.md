# SpecialRelativity-Particles

  Windows (OpenGL-GLUT)
  ------------
https://drive.google.com/file/d/0Bx_LsIsmyGthQzV0OFozdkt5a2c/view?usp=sharing

<div                                             id="/installation">&nbsp;</div>

  Installation-Linux (OpenGL-GLUT)
  ------------

```sh
$ sudo apt-get install libglut3-dev
```






#  Demo Spin Galaxy 

![title](https://j.gifs.com/yrqlmW.gif)




   Velocity Addtion Formula Decomposition
   ------------

https://en.wikipedia.org/wiki/Wigner_rotation

![title](https://wikimedia.org/api/rest_v1/media/math/render/svg/e32cd3766d5a81eada5e712aa95a4047ffced308)

```c++
/**
* Two general boosts Wigner https://en.wikipedia.org/wiki/Wigner_rotation
* Relativistically adds two velocities, v and u, and returns their sum, w;
* each velocity is expressed as a 3-vector in the form (x,y,z),(x,y,z);
* treats v as the velocity of a relativistic reference frame and u as the
* velocity of something within that frame
**/
static Vector3 VelocityAddition(const Vector3 &vComp,
                                const Vector3 &uComp,
                                const float &gamma_u,
                                const float &c)
{

    float dot_VU = std::abs((uComp).Dot(vComp))/(c*c);


    /**
    * using the values calculated above general boosts Wigner , calculates one component at a time of
    * the velocity resulting from the relativistic addition of v and u
    * ------------------------------------------------------------------
    * if the relativistical velocity sum is w:
    *         1                            gamma_u
    * w = -------- * [ vComp * ( 1+dot_UV*--------- ) + uComp/gamma_u ]
    *     1+dot_UV                         1+gamma_u
    **/

    return (1.0/(1.0+dot_VU)) * (uComp * (1.f+dot_VU*(gamma_u/(1.f+gamma_u))) + (vComp/gamma_u));
}
```



========================================================================================





  The Lorentz boost matrix4x4 is
  ------------

![title](https://wikimedia.org/api/rest_v1/media/math/render/svg/c08a87bdc969fdcbfbd9d443af3e457966de9e1a)

```c++
     /**
      * class TLorentzRotation
             \ingroup Physics
         The TLorentzRotation class describes Lorentz transformations including
         Lorentz boosts and rotations (see TRotation)
         ~~~
                     | xx  xy  xz  xt |
                     |                |
                     | yx  yy  yz  yt |
            lambda = |                |
                     | zx  zy  zz  zt |
                     |                |
                     | tx  ty  tz  tt |
         
      **/
  static SIMD_INLINE IMatrix4x4<T> CreateLorentzBoost( T gamma , const IVector3D<T> vel ,  const T &_LightSpeed = DEFAUL_LIGHT_MAX_VELOCITY_C )
     {
          static IMatrix4x4<T> M = IMatrix4x4<T>::IDENTITY;

         const IVector3D<T> n = vel.GetUnit();
         const T             v = vel.Length();

          //T bgamma = gamma * gamma / (1.0 + gamma);
          T bgamma = (gamma - 1.0);

         const T c = _LightSpeed;

         M[0][0] = 1.0+((bgamma)*((n.x * n.x)));
    	 M[1][0] =     ((bgamma)*((n.y * n.x)));
    	 M[2][0] =     ((bgamma)*((n.z * n.x)));
         M[3][0] = (v*n.x*gamma);

    	 M[0][1] =     ((bgamma)*((n.x * n.y)));
    	 M[1][1] = 1.0+((bgamma)*((n.y * n.y)));
    	 M[2][1] =     ((bgamma)*((n.z * n.y)));
         M[3][1] = (v*n.y*gamma);

    	 M[0][2] =      ((bgamma)*((n.x * n.z)));
    	 M[1][2] =      ((bgamma)*((n.y * n.z)));
    	 M[2][2] =  1.0+((bgamma)*((n.z * n.z)));
         M[3][2] = (v*n.z*gamma);

         M[0][3] =  v*n.x*gamma/(c*c);
         M[1][3] =  v*n.y*gamma/(c*c);
         M[2][3] =  v*n.z*gamma/(c*c);
         M[3][3] =  gamma;
     }
     ```




