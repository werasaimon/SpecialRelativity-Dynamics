TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


#LIBS += -lopengl32 -lglu32 -lfreeglut

#Linux
linux: {
   LIBS += -lGL -lGLU -lglut #-lGLEW
}


#Windows
win32: {
   LIBS += -lopengl32 -lfreeglut #-lglew32
}

#Windows
win64: {
   LIBS += -lopengl32 -lfreeglut #-lglew32
}

QMAKE_RPATHDIR += $ORIGIN/lib

SOURCES += \
    ../src/IParticle.cpp \
    ../src/IParticleSystem.cpp \
    ../src/main.cpp


DISTFILES += \

HEADERS += \
    ../src/IMath/IAlgebra.h \
    ../src/IMath/IComplex.h \
    ../src/IMath/IFunc.h \
    ../src/IMath/ILine3D.h \
    ../src/IMath/ILineSegment3D.h \
    ../src/IMath/ILorentzVector.h \
    ../src/IMath/IMaths.h \
    ../src/IMath/IMatrix2x2.h \
    ../src/IMath/IMatrix3x3.h \
    ../src/IMath/IMatrix4x4.h \
    ../src/IMath/IOctonion.h \
    ../src/IMath/IPlane.h \
    ../src/IMath/IQuaternion.h \
    ../src/IMath/IRay.h \
    ../src/IMath/IReal.h \
    ../src/IMath/IScalarType.h \
    ../src/IMath/ISpherical.h \
    ../src/IMath/ITransform.h \
    ../src/IMath/IVector.h \
    ../src/IMath/IVector2D.h \
    ../src/IMath/IVector3D.h \
    ../src/IMath/IVector4D.h \
    ../src/IMath/IVectorType.h \
    ../src/IMathematics.h \
    ../src/IParticle.h \
    ../src/IParticleSystem.h \
    ../src/IRelativity.h
