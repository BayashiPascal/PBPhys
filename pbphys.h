// ============ PBPHYS.H ================

#ifndef PBPHYS_H
#define PBPHYS_H

// ================= Include =================

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "pberr.h"
#include "shapoid.h"

// ------------ PBPhysParticle

// ================= Define ==================

// ================= Data structure ===================

typedef struct PBPhysParticle {
  // Shapoid
  Shapoid* _shape;
  // Speed
  VecFloat* _speed;
  // User acceleration
  VecFloat* _accel;
  // System acceleration (used internally for calculation)
  VecFloat* _sysAccel;
  // Mass
  float _mass;
  // Drag per time unit
  float _drag;
  // Flag for fixed particle
  bool _fixed;
  // User data
  void* _data;
} PBPhysParticle;

// ================ Functions declaration ====================

// Create a new PBPhysParticle with dimension 'dim' and a 'shapeType'
// shapoid as shape 
// Default values: _mass = 0.0, _drag = 0.0, _fixed = false
PBPhysParticle* PBPhysParticleCreate(int dim, ShapoidType shapeType);

// Free the memory used by the particle 'that'
void PBPhysParticleFree(PBPhysParticle** that);

// Return a clone of the particle 'that'
PBPhysParticle* PBPhysParticleClone(PBPhysParticle* that);

// Print the particle 'that' on the stream 'stream'
void PBPhysParticlePrintln(PBPhysParticle* that, FILE* stream);

// Function which return the JSON encoding of 'that' 
JSONNode* PBPhysParticleEncodeAsJSON(PBPhysParticle* that);

// Function which decode from JSON encoding 'json' to 'that'
bool PBPhysParticleDecodeAsJSON(PBPhysParticle** that, JSONNode* json);

// Save the particle 'that' on the stream 'stream'
// If 'compact' equals true it saves in compact form, else it saves in 
// readable form
// Return true if we could save the particle
// Return false else
// If user data is attached to the particle it must be saved by the user
bool PBPhysParticleSave(PBPhysParticle* that, FILE* stream, 
  bool compact); 

// Load the particle 'that' from the stream 'stream'
// Return true if we could load the particle
// Return false else
// If user data is attached to the particle it must be loaded by the user
bool PBPhysParticleLoad(PBPhysParticle** that, FILE* stream); 

// Return the dimension of the particle 'that'
#if BUILDMODE != 0
inline
#endif
int PBPhysParticleGetDim(PBPhysParticle* that);

// Return the shape type of the particle 'that'
#if BUILDMODE != 0
inline
#endif
ShapoidType PBPhysParticleGetShapeType(PBPhysParticle* that);

// Return the shape of the particle 'that'
#if BUILDMODE != 0
inline
#endif
Shapoid* PBPhysParticleShape(PBPhysParticle* that);

// Return the 'iAxis'-th axis of the shape of the particle 'that'
#if BUILDMODE != 0
inline
#endif
const VecFloat* PBPhysParticleAxis(PBPhysParticle* that, int iAxis);

// Return the speed of the particle 'that'
#if BUILDMODE != 0
inline
#endif
VecFloat* PBPhysParticleSpeed(PBPhysParticle* that);

// Return the accel of the particle 'that'
#if BUILDMODE != 0
inline
#endif
VecFloat* PBPhysParticleAccel(PBPhysParticle* that);

// Return the sysAccel of the particle 'that'
#if BUILDMODE != 0
inline
#endif
VecFloat* PBPhysParticleSysAccel(PBPhysParticle* that);

// Return the position of the center of the particle 'that'
#if BUILDMODE != 0
inline
#endif
VecFloat* PBPhysParticleGetPos(PBPhysParticle* that);

// Set the speed of the particle 'that' to 'speed'
// If the particle is fixed do nothing
#if BUILDMODE != 0
inline
#endif
void _PBPhysParticleSetSpeed(PBPhysParticle* that, VecFloat* speed);

// Set the acceleration of the particle 'that' to 'accel'
// If the particle is fixed do nothing
#if BUILDMODE != 0
inline
#endif
void _PBPhysParticleSetAccel(PBPhysParticle* that, VecFloat* accel);

// Set the position of the center of the particle 'that' to 'pos'
#if BUILDMODE != 0
inline
#endif
void _PBPhysParticleSetPos(PBPhysParticle* that, VecFloat* pos);

// Return true if the particle 'that' is the same is the particle 'tho'
// Return false else
// User data is not compared
#if BUILDMODE != 0
inline
#endif
bool PBPhysParticleIsSame(PBPhysParticle* that, PBPhysParticle* tho);

// Set the shape size of the particle 'that' to 'size'
#if BUILDMODE != 0
inline
#endif
void _PBPhysParticleSetSizeVec(PBPhysParticle* that, VecFloat* size);
#if BUILDMODE != 0
inline
#endif
void _PBPhysParticleSetSizeScalar(PBPhysParticle* that, float size);

// Return the mass of the particle 'that'
#if BUILDMODE != 0
inline
#endif
float PBPhysParticleGetMass(PBPhysParticle* that);

// Set the mass of the particle 'that' to 'mass'
#if BUILDMODE != 0
inline
#endif
void PBPhysParticleSetMass(PBPhysParticle* that, float mass);

// Return the drag of the particle 'that'
#if BUILDMODE != 0
inline
#endif
float PBPhysParticleGetDrag(PBPhysParticle* that);

// Set the drag of the particle 'that' to 'drag'
#if BUILDMODE != 0
inline
#endif
void PBPhysParticleSetDrag(PBPhysParticle* that, float drag);

// Move the particle 'that' over a period of time 'dt'
// x(t+dt) = x(t) + v(t)*dt + 0.5*(a(t)-drag*v(t))*dt^2
// v(t+dt) = v(t) + (a(t)-drag*v(t))*dt
void PBPhysParticleMove(PBPhysParticle* that, float dt);

// Return true if the particle 'that' is fixed
// Return false else
#if BUILDMODE != 0
inline
#endif
bool PBPhysParticleIsFixed(PBPhysParticle* that);

// Set the fixed flag of the particle 'that' to 'fixed'
#if BUILDMODE != 0
inline
#endif
void PBPhysParticleSetFixed(PBPhysParticle* that, bool fixed);

// Set the user data of the particle 'that' to 'data'
#if BUILDMODE != 0
inline
#endif
void PBPhysParticleSetData(PBPhysParticle* that, void* data);

// Get the user data of the particle 'that'
#if BUILDMODE != 0
inline
#endif
void* PBPhysParticleData(PBPhysParticle* that);

// Correct the current speed of the two colliding particles 'that' and 
// 'tho' under the hypothesis of elastic collision
// If at least one of the particle as a null mass, do nothing
void PBPhysParticleApplyElasticCollision(PBPhysParticle* that, 
  PBPhysParticle* tho);

// Return the coefficients of the polynom describing the square of the 
// distance between particles 'that' and 'tho'
// Return a vector such as dist^2(t)=v[0]+v[1]t+v[2]t^2
VecFloat3D PBPhysParticleGetDistPoly(PBPhysParticle* that, 
  PBPhysParticle* tho);

// ------------ PBPhys

// ================= Define ==================

// units : meter, second, kilogram
#define PBPHYS_Gn 9.80665
#define PBPHYS_G 6.6740831e-11
#define PBPHYS_DELTAT 0.01

// ================= Data structure ===================

typedef struct PBPhys {
  // Dimension of space
  int _dim;
  // Set of particles
  GSetPBPhysParticle _particles;
  // Delta time used in Step()
  float _deltaT;
  // Downward gravity
  float _downGravity;
  // Gravity between particles
  float _gravity;
  // Current time
  float _curTime;
} PBPhys;

// ================ Functions declaration ====================

// Create a new PBPhys for space dimension 'dim'
// Default values: _deltaT = PBPHYS_DELTAT, _downGravity = 0.0, 
// _gravity = 0.0, _curTime = 0.0
PBPhys* PBPhysCreate(int dim);

// Free memory used by the PBPhys 'that'
void PBPhysFree(PBPhys** that);

// Return a clone of the PBPhys 'that'
PBPhys* PBPhysClone(PBPhys* that);

// Print the PBPhys 'that' on the stream 'stream'
void PBPhysPrintln(PBPhys* that, FILE* stream);

// Function which return the JSON encoding of 'that' 
JSONNode* PBPhysEncodeAsJSON(PBPhys* that);

// Function which decode from JSON encoding 'json' to 'that'
bool PBPhysDecodeAsJSON(PBPhys** that, JSONNode* json);

// Save the PBPhys 'that' on the stream 'stream'
// If 'compact' equals true it saves in compact form, else it saves in 
// readable form
// Return true if we could save the PBPhys
// Return false else
bool PBPhysSave(PBPhys* that, FILE* stream, bool compact); 

// Load the PBPhys 'that' from the stream 'stream'
// Return true if we could load the PBPhys
// Return false else
bool PBPhysLoad(PBPhys** that, FILE* stream); 

// Return the space dimension of the PBPhys 'that'
#if BUILDMODE != 0
inline
#endif
int PBPhysGetDim(PBPhys* that);

// Return the set of particles of the PBPhys 'that'
#if BUILDMODE != 0
inline
#endif
GSetPBPhysParticle* PBPhysParticles(PBPhys* that);

// Return the delta t of the PBPhys 'that'
#if BUILDMODE != 0
inline
#endif
float PBPhysGetDeltaT(PBPhys* that);

// Return the current time of the PBPhys 'that'
#if BUILDMODE != 0
inline
#endif
float PBPhysGetCurTime(PBPhys* that);

// Return the downward gravity of the PBPhys 'that'
#if BUILDMODE != 0
inline
#endif
float PBPhysGetDownGravity(PBPhys* that);

// Return the gravity coefficient between particles of the PBPhys 'that' 
#if BUILDMODE != 0
inline
#endif
float PBPhysGetGravity(PBPhys* that);

// Return true if the PBPhys 'that' is the same as PBPhys 'tho'
bool PBPhysIsSame(PBPhys* that, PBPhys* tho);

// Set the delta t of the PBPhys 'that' to 'deltaT'
#if BUILDMODE != 0
inline
#endif
void PBPhysSetDeltaT(PBPhys* that, float deltaT);

// Set the current time of the PBPhys 'that' to 't'
#if BUILDMODE != 0
inline
#endif
void PBPhysSetCurTime(PBPhys* that, float t);

// Set the downward gravity of the PBPhys 'that' to 'gravity'
#if BUILDMODE != 0
inline
#endif
void PBPhysSetDownGravity(PBPhys* that, float gravity);

// Set the gravity coefficient between particles of the PBPhys 'that'
// to 'gravity'
#if BUILDMODE != 0
inline
#endif
void PBPhysSetGravity(PBPhys* that, float gravity);

// Step the PBPhys 'that' by that->_deltaT ignoring collision
void PBPhysNext(PBPhys* that);

// Step the PBPhys 'that' by that->_deltaT managing collision(s)
void PBPhysStep(PBPhys* that);

// Step the PBPhys 'that' by that->_deltaT or until a collision occured
// If no collision occured return NULL
// If a collision occured one can check the collision time with the 
// current time that->_curTime, and the returned GSet contains the 
// particles wich have collided
GSetPBPhysParticle* PBPhysStepToCollision(PBPhys* that);

// Return the 'iParticle'-th particle of the PBPhys 'that'
#if BUILDMODE != 0
inline
#endif
PBPhysParticle* PBPhysPart(PBPhys* that, int iParticle);

// Get the number of particles of the PBPhys 'that'
#if BUILDMODE != 0
inline
#endif
int PBPhysGetNbParticle(PBPhys* that);

// Add 'nb' particles of shape 'shape' into the PBPhys 'that'
#if BUILDMODE != 0
inline
#endif
void PBPhysAddParticles(PBPhys* that, int nb, ShapoidType shape);

// ================= Polymorphism ==================

#define PBPhysParticleSetAccel(Particle, Accel) _Generic(Accel, \
  VecFloat*: _PBPhysParticleSetAccel, \
  VecFloat2D*: _PBPhysParticleSetAccel, \
  VecFloat3D*: _PBPhysParticleSetAccel, \
  default: PBErrInvalidPolymorphism)(Particle, (VecFloat*)(Accel))

#define PBPhysParticleSetSpeed(Particle, Speed) _Generic(Speed, \
  VecFloat*: _PBPhysParticleSetSpeed, \
  VecFloat2D*: _PBPhysParticleSetSpeed, \
  VecFloat3D*: _PBPhysParticleSetSpeed, \
  default: PBErrInvalidPolymorphism)(Particle, (VecFloat*)(Speed))

#define PBPhysParticleSetPos(Particle, Pos) _Generic(Pos, \
  VecFloat*: _PBPhysParticleSetPos, \
  VecFloat2D*: _PBPhysParticleSetPos, \
  VecFloat3D*: _PBPhysParticleSetPos, \
  default: PBErrInvalidPolymorphism)(Particle, (VecFloat*)(Pos))

#define PBPhysParticleSetSize(Particle, Size) _Generic(Size, \
  VecFloat*: _PBPhysParticleSetSizeVec, \
  float: _PBPhysParticleSetSizeScalar, \
  default: PBErrInvalidPolymorphism)(Particle, Size)
  
// ================ Inliner ====================

#if BUILDMODE != 0
#include "pbphys-inline.c"
#endif


#endif
