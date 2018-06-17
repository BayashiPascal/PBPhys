// ============ PBPHYS-INLINE.C ================

// ------------ PBPhysParticle

// ================ Functions implementation ====================

// Return the dimension of the particle 'that'
#if BUILDMODE != 0
inline
#endif
int PBPhysParticleGetDim(const PBPhysParticle* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  return ShapoidGetDim(that->_shape);
}

// Return the shape type of the particle 'that'
#if BUILDMODE != 0
inline
#endif
ShapoidType PBPhysParticleGetShapeType(const PBPhysParticle* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  return ShapoidGetType(that->_shape);
}

// Return the shape of the particle 'that'
#if BUILDMODE != 0
inline
#endif
const Shapoid* PBPhysParticleShape(const PBPhysParticle* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  return that->_shape;
}

// Return the 'iAxis'-th axis of the shape of the particle 'that'
#if BUILDMODE != 0
inline
#endif
const VecFloat* PBPhysParticleAxis(const PBPhysParticle* const that, const int iAxis) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
  if (iAxis < 0 || iAxis >= PBPhysParticleGetDim(that)) {
    PBPhysErr->_type = PBErrTypeInvalidArg;
    sprintf(PBPhysErr->_msg, "'iAxis' is invalid (0<=%d<%d)",
      iAxis, PBPhysParticleGetDim(that));
    PBErrCatch(PBPhysErr);
  }
#endif
  return ShapoidAxis(PBPhysParticleShape(that), iAxis);
}

// Return the speed of the particle 'that'
#if BUILDMODE != 0
inline
#endif
const VecFloat* PBPhysParticleSpeed(const PBPhysParticle* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  return that->_speed;
}

// Return the acceleration of the particle 'that'
#if BUILDMODE != 0
inline
#endif
const VecFloat* PBPhysParticleAccel(const PBPhysParticle* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  return that->_accel;
}

// Return the sysAccel of the particle 'that'
#if BUILDMODE != 0
inline
#endif
const VecFloat* PBPhysParticleSysAccel(const PBPhysParticle* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  return that->_sysAccel;
}

// Return the position of the center of the particle 'that'
#if BUILDMODE != 0
inline
#endif
VecFloat* PBPhysParticleGetPos(const PBPhysParticle* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  return ShapoidGetCenter(that->_shape);
}

// Set the speed of the particle 'that' to 'speed'
// If the particle is fixed do nothing
#if BUILDMODE != 0
inline
#endif
void _PBPhysParticleSetSpeed(const PBPhysParticle* const that, const VecFloat* const speed) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
  if (speed == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'speed' is null");
    PBErrCatch(PBPhysErr);
  }
  if (VecGetDim(speed) != PBPhysParticleGetDim(that)) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'speed' 's dimension is invalid (%d=%d)",
      VecGetDim(speed), PBPhysParticleGetDim(that));
    PBErrCatch(PBPhysErr);
  }
#endif
  if (!PBPhysParticleIsFixed(that))
    VecCopy(that->_speed, speed);
}

// Add to the speed of the particle 'that' the vector 'v' multiplied 
// by 'c'
// If the particle is fixed do nothing
#if BUILDMODE != 0
inline
#endif
void _PBPhysParticleAddSpeed(const PBPhysParticle* const that, const VecFloat* const v, const float c) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
  if (v == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'v' is null");
    PBErrCatch(PBPhysErr);
  }
  if (VecGetDim(v) != PBPhysParticleGetDim(that)) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'v' 's dimension is invalid (%d=%d)",
      VecGetDim(v), PBPhysParticleGetDim(that));
    PBErrCatch(PBPhysErr);
  }
#endif
  if (!PBPhysParticleIsFixed(that))
    VecOp(that->_speed, 1.0, v, c);
}

// Add to the system accel of the particle 'that' the vector 'v' 
// multiplied by 'c'
// If the particle is fixed do nothing
#if BUILDMODE != 0
inline
#endif
void _PBPhysParticleAddSysAccel(const PBPhysParticle* const that, const VecFloat* const v, const float c) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
  if (v == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'v' is null");
    PBErrCatch(PBPhysErr);
  }
  if (VecGetDim(v) != PBPhysParticleGetDim(that)) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'v' 's dimension is invalid (%d=%d)",
      VecGetDim(v), PBPhysParticleGetDim(that));
    PBErrCatch(PBPhysErr);
  }
#endif
  if (!PBPhysParticleIsFixed(that))
    VecOp(that->_sysAccel, 1.0, v, c);
}



// Set the acceleration of the particle 'that' to 'accel'
// If the particle is fixed do nothing
#if BUILDMODE != 0
inline
#endif
void _PBPhysParticleSetAccel(PBPhysParticle* const that, const VecFloat* const accel) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
  if (accel == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'accel' is null");
    PBErrCatch(PBPhysErr);
  }
  if (VecGetDim(accel) != PBPhysParticleGetDim(that)) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'accel' 's dimension is invalid (%d=%d)",
      VecGetDim(accel), PBPhysParticleGetDim(that));
    PBErrCatch(PBPhysErr);
  }
#endif
  if (!PBPhysParticleIsFixed(that))
    VecCopy(that->_accel, accel);
}

// Reset the system acceleration of the particle 'that'
#if BUILDMODE != 0
inline
#endif
void PBPhysParticleResetSysAccel(PBPhysParticle* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  VecSetNull(that->_accel);
}

// Add the gravity force 'gravity' to the system acceleration of the 
// particle 'that' (substract 'gravity' to the axis y)
// If the particle is fixed do nothing
#if BUILDMODE != 0
inline
#endif
void PBPhysParticleApplyGravity(PBPhysParticle* const that, float gravity) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  if (!PBPhysParticleIsFixed(that))
    VecSetAdd(that->_accel, 1, -1.0 * gravity);
}

// Set the position of the center of the particle 'that' to 'pos'
#if BUILDMODE != 0
inline
#endif
void _PBPhysParticleSetPos(PBPhysParticle* const that, const VecFloat* const pos) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
  if (pos == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'pos' is null");
    PBErrCatch(PBPhysErr);
  }
  if (VecGetDim(pos) != PBPhysParticleGetDim(that)) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'pos' 's dimension is invalid (%d=%d)",
      VecGetDim(pos), PBPhysParticleGetDim(that));
    PBErrCatch(PBPhysErr);
  }
#endif
  ShapoidSetCenterPos(that->_shape, pos);
}

// Add to the position of the center of the particle 'that' the vector 'v' multiplied by 'c'
#if BUILDMODE != 0
inline
#endif
void _PBPhysParticleAddPos(PBPhysParticle* const that, const VecFloat* const v, const float c) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
  if (v == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'v' is null");
    PBErrCatch(PBPhysErr);
  }
  if (VecGetDim(v) != PBPhysParticleGetDim(that)) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'v' 's dimension is invalid (%d=%d)",
      VecGetDim(v), PBPhysParticleGetDim(that));
    PBErrCatch(PBPhysErr);
  }
#endif
  VecFloat* pos = ShapoidGetCenter(PBPhysParticleShape(that));
  VecOp(pos, 1.0, v, c);
  ShapoidSetCenterPos(that->_shape, pos);
  VecFree(&pos);
}

// Return true if the particle 'that' is the same is the particle 'tho'
// Return false else
// User data is not compared
#if BUILDMODE != 0
inline
#endif
bool PBPhysParticleIsSame(const PBPhysParticle* const that, const PBPhysParticle* const tho) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
  if (tho == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'tho' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  if (!ShapoidIsEqual(PBPhysParticleShape(that), 
    PBPhysParticleShape(tho)) ||
    !VecIsEqual(PBPhysParticleSpeed(that), PBPhysParticleSpeed(tho)) ||
    !VecIsEqual(PBPhysParticleAccel(that), PBPhysParticleAccel(tho)) ||
    !ISEQUALF(PBPhysParticleGetMass(that), PBPhysParticleGetMass(tho)) ||
    PBPhysParticleIsFixed(that) != PBPhysParticleIsFixed(tho))
    return false;
  return true;
}

// Set the shape size of the particle 'that' to 'size'
#if BUILDMODE != 0
inline
#endif
void _PBPhysParticleSetSizeVec(PBPhysParticle* const that, const VecFloat* const size) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
  if (size == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'size' is null");
    PBErrCatch(PBPhysErr);
  }
  if (VecGetDim(size) != PBPhysParticleGetDim(that)) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'size' 's dimension is invalid (%d=%d)",
      VecGetDim(size), PBPhysParticleGetDim(that));
    PBErrCatch(PBPhysErr);
  }
#endif
  for (int iAxis = PBPhysParticleGetDim(that); iAxis--;) {
    float scale = VecGet(size, iAxis) / 
      VecNorm(ShapoidAxis(PBPhysParticleShape(that), iAxis));
    ShapoidAxisScale(that->_shape, iAxis, scale);
  }
}

#if BUILDMODE != 0
inline
#endif
void _PBPhysParticleSetSizeScalar(PBPhysParticle* const that, const float size) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  for (int iAxis = PBPhysParticleGetDim(that); iAxis--;) {
    float scale = size / 
      VecNorm(ShapoidAxis(PBPhysParticleShape(that), iAxis));
    ShapoidAxisScale(that->_shape, iAxis, scale);
  }
}

// Return the mass of the particle 'that'
#if BUILDMODE != 0
inline
#endif
float PBPhysParticleGetMass(const PBPhysParticle* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  return that->_mass;
}

// Set the mass of the particle 'that' to 'mass'
#if BUILDMODE != 0
inline
#endif
void PBPhysParticleSetMass(PBPhysParticle* const that, const float mass) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  that->_mass = mass;
}

// Return the drag of the particle 'that'
#if BUILDMODE != 0
inline
#endif
float PBPhysParticleGetDrag(const PBPhysParticle* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  return that->_drag;
}

// Set the drag of the particle 'that' to 'drag'
#if BUILDMODE != 0
inline
#endif
void PBPhysParticleSetDrag(PBPhysParticle* const that, const float drag) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  that->_drag = drag;
}

// Return true if the particle 'that' is fixed
// Return false else
#if BUILDMODE != 0
inline
#endif
bool PBPhysParticleIsFixed(const PBPhysParticle* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  return that->_fixed;
}

// Set the fixed flag of the particle 'that' to 'fixed'
#if BUILDMODE != 0
inline
#endif
void PBPhysParticleSetFixed(PBPhysParticle* const that, const bool fixed) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  that->_fixed = fixed;
  if (fixed) {
    VecSetNull(that->_speed);
    VecSetNull(that->_accel);
  }
}

// Set the user data of the particle 'that' to 'data'
#if BUILDMODE != 0
inline
#endif
void PBPhysParticleSetData(PBPhysParticle* const that, void* const data) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  that->_data = data;
}

// Get the user data of the particle 'that'
#if BUILDMODE != 0
inline
#endif
void* PBPhysParticleData(const PBPhysParticle* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  return that->_data;
}

// ------------ PBPhys

// ================ Functions implementation ====================

// Return the space dimension of the PBPhys 'that'
#if BUILDMODE != 0
inline
#endif
int PBPhysGetDim(const PBPhys* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  return that->_dim;
}

// Return the set of particles of the PBPhys 'that'
#if BUILDMODE != 0
inline
#endif
GSetPBPhysParticle* PBPhysParticles(const PBPhys* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  return (GSetPBPhysParticle*)&(that->_particles);
}

// Return the delta t of the PBPhys 'that'
#if BUILDMODE != 0
inline
#endif
float PBPhysGetDeltaT(const PBPhys* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  return that->_deltaT;
}

// Return the current time of the PBPhys 'that'
#if BUILDMODE != 0
inline
#endif
float PBPhysGetCurTime(const PBPhys* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  return that->_curTime;
}

// Return the downward gravity of the PBPhys 'that'
#if BUILDMODE != 0
inline
#endif
float PBPhysGetDownGravity(const PBPhys* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  return that->_downGravity;
}

// Return the gravity coefficient between particles of the PBPhys 'that' 
#if BUILDMODE != 0
inline
#endif
float PBPhysGetGravity(const PBPhys* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  return that->_gravity;
}

// Set the delta t of the PBPhys 'that' to 'deltaT'
#if BUILDMODE != 0
inline
#endif
void PBPhysSetDeltaT(PBPhys* const that, const float deltaT) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  that->_deltaT = deltaT;
}

// Set the current time of the PBPhys 'that' to 't'
#if BUILDMODE != 0
inline
#endif
void PBPhysSetCurTime(PBPhys* const that, const float t) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  that->_curTime = t;
}

// Set the downward gravity of the PBPhys 'that' to 'gravity'
#if BUILDMODE != 0
inline
#endif
void PBPhysSetDownGravity(PBPhys* const that, float gravity) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  that->_downGravity = gravity;
}

// Set the gravity coefficient between particles of the PBPhys 'that'
// to 'gravity'
#if BUILDMODE != 0
inline
#endif
void PBPhysSetGravity(PBPhys* const that, float gravity) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  that->_gravity = gravity;
}

// Return the 'iParticle'-th particle of the PBPhys 'that'
#if BUILDMODE != 0
inline
#endif
PBPhysParticle* PBPhysPart(const PBPhys* const that, const int iParticle) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
  if (iParticle < 0 || iParticle >= PBPhysGetNbParticle(that)) {
    PBPhysErr->_type = PBErrTypeInvalidArg;
    sprintf(PBPhysErr->_msg, "'iParticle' is invalid (0<=%d<%d)", 
      iParticle, PBPhysGetNbParticle(that));
    PBErrCatch(PBPhysErr);
  }
#endif
  return GSetGet(&(that->_particles), iParticle);
}

// Get the number of particles of the PBPhys 'that'
#if BUILDMODE != 0
inline
#endif
int PBPhysGetNbParticle(const PBPhys* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  return GSetNbElem(&(that->_particles));
}

// Add 'nb' particles of shape 'shape' into the PBPhys 'that'
#if BUILDMODE != 0
inline
#endif
void PBPhysAddParticles(PBPhys* const that, const int nb, const ShapoidType shape) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
  if (nb <= 0) {
    PBPhysErr->_type = PBErrTypeInvalidArg;
    sprintf(PBPhysErr->_msg, "'nb' is invalid (0<%d)", nb);
    PBErrCatch(PBPhysErr);
  }
#endif
  for (int iParticle = nb; iParticle--;) {
    PBPhysParticle* particle = 
      PBPhysParticleCreate(PBPhysGetDim(that), shape);
    GSetAppend(&(that->_particles), particle);
  }
}
