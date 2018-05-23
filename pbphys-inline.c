// ============ PBPHYS-INLINE.C ================

// ------------ PBPhysParticle

// ================ Functions implementation ====================

// Return the dimension of the particle 'that'
#if BUILDMODE != 0
inline
#endif
int PBPhysParticleGetDim(PBPhysParticle* that) {
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
ShapoidType PBPhysParticleGetShapeType(PBPhysParticle* that) {
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
Shapoid* PBPhysParticleShape(PBPhysParticle* that) {
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
const VecFloat* PBPhysParticleAxis(PBPhysParticle* that, int iAxis) {
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
VecFloat* PBPhysParticleSpeed(PBPhysParticle* that) {
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
VecFloat* PBPhysParticleAccel(PBPhysParticle* that) {
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
VecFloat* PBPhysParticleSysAccel(PBPhysParticle* that) {
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
VecFloat* PBPhysParticleGetPos(PBPhysParticle* that) {
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
void _PBPhysParticleSetSpeed(PBPhysParticle* that, VecFloat* speed) {
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

// Set the acceleration of the particle 'that' to 'accel'
// If the particle is fixed do nothing
#if BUILDMODE != 0
inline
#endif
void _PBPhysParticleSetAccel(PBPhysParticle* that, VecFloat* accel) {
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

// Set the position of the center of the particle 'that' to 'pos'
#if BUILDMODE != 0
inline
#endif
void _PBPhysParticleSetPos(PBPhysParticle* that, VecFloat* pos) {
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
  ShapoidSetCenterPos(PBPhysParticleShape(that), pos);
}

// Return true if the particle 'that' is the same is the particle 'tho'
// Return false else
// User data is not compared
#if BUILDMODE != 0
inline
#endif
bool PBPhysParticleIsSame(PBPhysParticle* that, PBPhysParticle* tho) {
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
void _PBPhysParticleSetSizeVec(PBPhysParticle* that, VecFloat* size) {
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
    ShapoidAxisScale(PBPhysParticleShape(that), iAxis, scale);
  }
}

#if BUILDMODE != 0
inline
#endif
void _PBPhysParticleSetSizeScalar(PBPhysParticle* that, float size) {
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
    ShapoidAxisScale(PBPhysParticleShape(that), iAxis, scale);
  }
}

// Return the mass of the particle 'that'
#if BUILDMODE != 0
inline
#endif
float PBPhysParticleGetMass(PBPhysParticle* that) {
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
void PBPhysParticleSetMass(PBPhysParticle* that, float mass) {
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
float PBPhysParticleGetDrag(PBPhysParticle* that) {
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
void PBPhysParticleSetDrag(PBPhysParticle* that, float drag) {
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
bool PBPhysParticleIsFixed(PBPhysParticle* that) {
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
void PBPhysParticleSetFixed(PBPhysParticle* that, bool fixed) {
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
void PBPhysParticleSetData(PBPhysParticle* that, void* data) {
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
void* PBPhysParticleData(PBPhysParticle* that) {
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
int PBPhysGetDim(PBPhys* that) {
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
GSetPBPhysParticle* PBPhysParticles(PBPhys* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  return &(that->_particles);
}

// Return the delta t of the PBPhys 'that'
#if BUILDMODE != 0
inline
#endif
float PBPhysGetDeltaT(PBPhys* that) {
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
float PBPhysGetCurTime(PBPhys* that) {
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
float PBPhysGetDownGravity(PBPhys* that) {
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
float PBPhysGetGravity(PBPhys* that) {
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
void PBPhysSetDeltaT(PBPhys* that, float deltaT) {
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
void PBPhysSetCurTime(PBPhys* that, float t) {
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
void PBPhysSetDownGravity(PBPhys* that, float gravity) {
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
void PBPhysSetGravity(PBPhys* that, float gravity) {
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
PBPhysParticle* PBPhysPart(PBPhys* that, int iParticle) {
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
int PBPhysGetNbParticle(PBPhys* that) {
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
void PBPhysAddParticles(PBPhys* that, int nb, ShapoidType shape) {
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
