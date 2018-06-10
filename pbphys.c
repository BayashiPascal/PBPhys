// ============ PBPHYS.C ================

// ================= Include =================

#include "pbphys.h"
#if BUILDMODE == 0
#include "pbphys-inline.c"
#endif

// ------------ PBPhysParticle

// ================ Functions declaration ====================

// Return the displacement of the particle from current position to 
// the position after dt
VecFloat* PBPhysParticleGetNextDisplacement(PBPhysParticle* that, 
  float dt);

// Return the coefficients of the polynom describing the square of the 
// distance between two lines passing through 'posA' and 'posB' and 
// colinear to 'dirA' and 'dirB' respectively
// Return a vector such as dist^2(t)=v[0]+v[1]t+v[2]t^2
VecFloat3D PBPhysGetDistPoly(VecFloat* posA, VecFloat* dirA,
  VecFloat* posB, VecFloat* dirB);
  
// ================ Functions implementation ====================

// Create a new PBPhysParticle with dimension 'dim' and a 'shapeType'
// shapoid as shape 
// Default values: _mass = 0.0, _drag = 0.0, _fixed = false
PBPhysParticle* PBPhysParticleCreate(int dim, ShapoidType shapeType) {
#if BUILDMODE == 0
  if (dim <= 0) {
    PBPhysErr->_type = PBErrTypeInvalidArg;
    sprintf(PBPhysErr->_msg, "'dim' is invalid (0<%d)", dim);
    PBErrCatch(PBPhysErr);
  }
#endif
  // Allocate memory
  PBPhysParticle *that = PBErrMalloc(PBPhysErr, sizeof(PBPhysParticle));
  // Set properties
  that->_shape = ShapoidCreate(dim, shapeType);
  that->_speed = VecFloatCreate(dim);
  that->_accel = VecFloatCreate(dim);
  that->_sysAccel = VecFloatCreate(dim);
  that->_mass = 0.0;
  that->_drag = 0.0;
  that->_fixed = false;
  that->_data = NULL;
  // Return the new PBPhysParticle
  return that;
}

// Free the memory used by the particle 'that'
void PBPhysParticleFree(PBPhysParticle** that) {
  // Check arguments
  if (that == NULL || *that == NULL)
    // Nothing to do
    return;
  // Free memory
  ShapoidFree(&((*that)->_shape));
  VecFree(&((*that)->_speed));
  VecFree(&((*that)->_accel));
  VecFree(&((*that)->_sysAccel));
  free(*that);
  *that = NULL;
}

// Return a clone of the particle 'that'
PBPhysParticle* PBPhysParticleClone(PBPhysParticle* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  // Declare the clone
  PBPhysParticle* clone = PBPhysParticleCreate(
    PBPhysParticleGetDim(that), PBPhysParticleGetShapeType(that));
  // Copy properties
  PBPhysParticleSetSpeed(clone, PBPhysParticleSpeed(that));
  PBPhysParticleSetAccel(clone, PBPhysParticleAccel(that));
  PBPhysParticleSetMass(clone, PBPhysParticleGetMass(that));
  PBPhysParticleSetFixed(clone, PBPhysParticleIsFixed(that));
  PBPhysParticleSetDrag(clone, 
    PBPhysParticleGetDrag(that));
  VecFloat* center = PBPhysParticleGetPos(that);
  PBPhysParticleSetPos(clone, center);
  VecFree(&center);
  // Return the clone
  return clone;
}

// Print the particle 'that' on the stream 'stream'
void PBPhysParticlePrintln(PBPhysParticle* that, FILE* stream) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
  if (stream == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'stream' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  ShapoidPrintln(PBPhysParticleShape(that), stream);
  fprintf(stream, "speed: "); 
  VecPrint(PBPhysParticleSpeed(that), stream);
  fprintf(stream, "\n"); 
  fprintf(stream, "accel: "); 
  VecPrint(PBPhysParticleAccel(that), stream);
  fprintf(stream, "\n"); 
  fprintf(stream, "mass: %.3f\n", PBPhysParticleGetMass(that)); 
  fprintf(stream, "drag: %.3f\n", 
    PBPhysParticleGetDrag(that)); 
  if (PBPhysParticleIsFixed(that))
    fprintf(stream, "fixed\n"); 
  else
    fprintf(stream, "unfixed\n"); 
}

// Function which return the JSON encoding of 'that' 
JSONNode* PBPhysParticleEncodeAsJSON(PBPhysParticle* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Create the JSON structure
  JSONNode* json = JSONCreate();
  // Declare a buffer to convert value into string
  char val[100];
  // Encode the dim
  sprintf(val, "%d", PBPhysParticleGetDim(that));
  JSONAddProp(json, "_dim", val);
  // Encode the type
  sprintf(val, "%d", PBPhysParticleGetShapeType(that));
  JSONAddProp(json, "_type", val);
  // Encode the shape
  JSONAddProp(json, "_shape", 
    ShapoidEncodeAsJSON(PBPhysParticleShape(that)));
  // Encode the speed
  JSONAddProp(json, "_speed", 
    VecEncodeAsJSON(PBPhysParticleSpeed(that)));
  // Encode the acceleration
  JSONAddProp(json, "_accel", 
    VecEncodeAsJSON(PBPhysParticleAccel(that)));
  // Encode the mass
  sprintf(val, "%f", that->_mass);
  JSONAddProp(json, "_mass", val);
  // Encode the drag
  sprintf(val, "%f", that->_drag);
  JSONAddProp(json, "_drag", val);
  // Encode the fixed
  sprintf(val, "%d", that->_fixed);
  JSONAddProp(json, "_fixed", val);
  // Return the created JSON 
  return json;
}

// Function which decode from JSON encoding 'json' to 'that'
bool PBPhysParticleDecodeAsJSON(PBPhysParticle** that, JSONNode* json) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (json == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'json' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // If 'that' is already allocated
  if (*that != NULL)
    // Free memory
    PBPhysParticleFree(that);
  // Get the dim from the JSON
  JSONNode* prop = JSONProperty(json, "_dim");
  if (prop == NULL) {
    return false;
  }
  int dim = atoi(JSONLabel(JSONValue(prop, 0)));
  // Get the type from the JSON
  prop = JSONProperty(json, "_type");
  if (prop == NULL) {
    return false;
  }
  int type = atoi(JSONLabel(JSONValue(prop, 0)));
  // If the data is invalid
  if (dim <= 0)
    return false;
  // Allocate memory
  *that = PBPhysParticleCreate(dim, type);
  // Decode the shape
  prop = JSONProperty(json, "_shape");
  if (prop == NULL) {
    return false;
  }
  if (!ShapoidDecodeAsJSON(&((*that)->_shape), prop)) {
    return false;
  }
  // Decode the speed
  prop = JSONProperty(json, "_speed");
  if (prop == NULL) {
    return false;
  }
  if (!VecDecodeAsJSON(&((*that)->_speed), prop)) {
    return false;
  }
  // Decode the accel
  prop = JSONProperty(json, "_accel");
  if (prop == NULL) {
    return false;
  }
  if (!VecDecodeAsJSON(&((*that)->_accel), prop)) {
    return false;
  }
  // Get the mass from the JSON
  prop = JSONProperty(json, "_mass");
  if (prop == NULL) {
    return false;
  }
  (*that)->_mass = atof(JSONLabel(JSONValue(prop, 0)));
  // Get the drag from the JSON
  prop = JSONProperty(json, "_drag");
  if (prop == NULL) {
    return false;
  }
  (*that)->_drag = atof(JSONLabel(JSONValue(prop, 0)));
  // Get the fixed from the JSON
  prop = JSONProperty(json, "_fixed");
  if (prop == NULL) {
    return false;
  }
  (*that)->_fixed = atoi(JSONLabel(JSONValue(prop, 0)));
  // Return the success code
  return true;
}

// Save the particle 'that' on the stream 'stream'
// If 'compact' equals true it saves in compact form, else it saves in 
// readable form
// Return true if we could save the particle
// Return false else
// If user data is attached to the particle it must be saved by the user
bool PBPhysParticleSave(PBPhysParticle* that, FILE* stream, 
  bool compact) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
  if (stream == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'stream' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  // Get the JSON encoding
  JSONNode* json = PBPhysParticleEncodeAsJSON(that);
  // Save the JSON
  if (!JSONSave(json, stream, compact)) {
    return false;
  }
  // Free memory
  JSONFree(&json);
  // Return success code
  return true;
}

// Load the particle 'that' from the stream 'stream'
// Return true if we could load the particle
// Return false else
// If user data is attached to the particle it must be loaded by the user
bool PBPhysParticleLoad(PBPhysParticle** that, FILE* stream) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
  if (stream == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'stream' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  // Declare a json to load the encoded data
  JSONNode* json = JSONCreate();
  // Load the whole encoded data
  if (!JSONLoad(json, stream)) {
    return false;
  }
  // Decode the data from the JSON
  if (!PBPhysParticleDecodeAsJSON(that, json)) {
    return false;
  }
  // Free the memory used by the JSON
  JSONFree(&json);
  // Return the success code
  return true;
}

// Move the particle 'that' over a period of time 'dt'
// x(t+dt) = x(t) + v(t)*dt + 0.5*(a(t)-drag*v(t))*dt^2
// v(t+dt) = v(t) + (a(t)-drag*v(t))*dt
void PBPhysParticleMove(PBPhysParticle* that, float dt) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  if (!PBPhysParticleIsFixed(that)) {
    // Get the displacement
    VecFloat* disp = PBPhysParticleGetNextDisplacement(that, dt);
    // Update the position
    VecFloat* newPos = VecGetOp(
      ShapoidPos(PBPhysParticleShape(that)), 1.0, disp, 1.0);
    ShapoidSetPos(PBPhysParticleShape(that), newPos);
    VecFree(&newPos);
    // Update the speed
    VecOp(PBPhysParticleSpeed(that), 1.0, 
      PBPhysParticleSpeed(that), -dt * PBPhysParticleGetDrag(that));
    VecOp(PBPhysParticleSpeed(that), 1.0, 
      PBPhysParticleAccel(that), dt);
    VecOp(PBPhysParticleSpeed(that), 1.0, 
      PBPhysParticleSysAccel(that), dt);
    // Free memory
    VecFree(&disp);
  }
}

// Return the displacement of the particle from current position to 
// the position after dt
VecFloat* PBPhysParticleGetNextDisplacement(PBPhysParticle* that, 
  float dt) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  VecFloat* v = VecGetOp(PBPhysParticleAccel(that), 1.0, 
    PBPhysParticleSpeed(that), -1.0 * PBPhysParticleGetDrag(that));
  VecOp(v, 1.0, PBPhysParticleSysAccel(that), 1.0);
  VecOp(v, 0.5 * fsquare(dt), PBPhysParticleSpeed(that), dt);
  return v;
}

// Correct the current speed of the two colliding particles 'that' and 
// 'tho' under the hypothesis of elastic collision
// Particles' mass must not be null
void PBPhysParticleApplyElasticCollision(PBPhysParticle* that, 
  PBPhysParticle* tho) {
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
  if (fabs(PBPhysParticleGetMass(that)) < PBMATH_EPSILON) {
    PBPhysErr->_type = PBErrTypeInvalidArg;
    sprintf(PBPhysErr->_msg, "mass of 'that' is null");
    PBErrCatch(PBPhysErr);
  }
  if (fabs(PBPhysParticleGetMass(tho)) < PBMATH_EPSILON) {
    PBPhysErr->_type = PBErrTypeInvalidArg;
    sprintf(PBPhysErr->_msg, "mass of 'tho' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  // Get the center of particles
  VecFloat* posA = PBPhysParticleGetPos(that);
  VecFloat* posB = PBPhysParticleGetPos(tho);
  // Get the difference in pos
  VecFloat* v = VecGetOp(posA, 1.0, posB, -1.0);
  // Get the difference in speed
  VecFloat* w = VecGetOp(PBPhysParticleSpeed(that), 1.0, 
    PBPhysParticleSpeed(tho), -1.0);
  // Get the prod of differences
  float prod = VecDotProd(v, w);
  // Get the norm of difference in pos
  float norm = VecNorm(v);
  // Calculate a temporary value for following calculation
  float c = 2.0 * prod / 
    ((PBPhysParticleGetMass(that) + PBPhysParticleGetMass(tho)) * 
    fsquare(norm));
  // Update the speed of 'that' if it's not fixed
  if (!PBPhysParticleIsFixed(that))
    VecOp(PBPhysParticleSpeed(that), 1.0, v, 
      -1.0 * c * PBPhysParticleGetMass(tho));
  // Update the speed of 'tho' if it's not fixed
  if (!PBPhysParticleIsFixed(tho))
    VecOp(PBPhysParticleSpeed(tho), 1.0, v, 
      c * PBPhysParticleGetMass(that));
  // Free memory
  VecFree(&posA);
  VecFree(&posB);
  VecFree(&v);
  VecFree(&w);
}

// Return the coefficients of the polynom describing the square of the 
// distance between particles 'that' and 'tho'
// Return a vector such as dist^2(t)=v[0]+v[1]t+v[2]t^2
VecFloat3D PBPhysParticleGetDistPoly(PBPhysParticle* that, 
  PBPhysParticle* tho) {
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
  VecFloat* posA = PBPhysParticleGetPos(that);
  VecFloat* posB = PBPhysParticleGetPos(tho);
  VecFloat3D ret = PBPhysGetDistPoly(posA, PBPhysParticleSpeed(that), 
    posB, PBPhysParticleSpeed(tho));
  VecFree(&posA);
  VecFree(&posB);
  return ret;
}

// ------------ PBPhys

// ================ Functions declaration ====================

// Calculate the system acceleration of the particle 'part' in the 
// PBPhys 'that'
void PBPhysUpdateSysAccel(PBPhys* that, PBPhysParticle* part);

// Return the time to collision between two particles of radius 'rA' 
// and 'rB' and the polynom of the square distance between particles 
// over time 'distPoly'
float PBPhysGetTimeToHit(float rA, float rB, VecFloat3D* distPoly);

// ================ Functions implementation ====================

// Create a new PBPhys for space dimension 'dim'
// Default values: _deltaT = 0.01, _downGravity = 0.0, _gravity = 0.0,
// _curTime = 0.0
PBPhys* PBPhysCreate(int dim) {
#if BUILDMODE == 0
  if (dim <= 0) {
    PBPhysErr->_type = PBErrTypeInvalidArg;
    sprintf(PBPhysErr->_msg, "'dim' is invalid (0<%d)", dim);
    PBErrCatch(PBPhysErr);
  }
#endif
  // Allocate memory
  PBPhys* that = PBErrMalloc(PBPhysErr, sizeof(PBPhys));
  // Set properties
  *(int*)&(that->_dim) = dim;
  that->_particles = GSetPBPhysParticleCreateStatic();
  that->_deltaT = PBPHYS_DELTAT;
  that->_downGravity = 0.0; 
  that->_gravity = false;
  that->_curTime = 0.0;
  // Return the new PBPhys
  return that;
}

// Free memory used by the PBPhys 'that'
void PBPhysFree(PBPhys** that) {
  // Check argument
  if (that == NULL || *that == NULL)
    // Nothing to do
    return;
  // Free memory
  while (PBPhysGetNbParticle(*that) > 0) {
    PBPhysParticle* particle = GSetPop(PBPhysParticles(*that));
    PBPhysParticleFree(&particle);
  }
  free(*that);
  *that = NULL;
}

// Return a clone of the PBPhys 'that'
PBPhys* PBPhysClone(PBPhys* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  // Declare the clone
  PBPhys* clone = PBPhysCreate(PBPhysGetDim(that));
  // Copy the properties
  PBPhysSetGravity(clone, PBPhysGetGravity(that));
  PBPhysSetCurTime(clone, PBPhysGetCurTime(that));
  PBPhysSetDeltaT(clone, PBPhysGetDeltaT(that));
  PBPhysSetDownGravity(clone, PBPhysGetDownGravity(that));
  // Copy the particles
  if (PBPhysGetNbParticle(that) > 0) {
    GSetIterForward iter = 
      GSetIterForwardCreateStatic(PBPhysParticles(that));
    do {
      PBPhysParticle* part = GSetIterGet(&iter);
      PBPhysParticle* clonePart = PBPhysParticleClone(part);
      GSetAppend(PBPhysParticles(clone), clonePart);
    } while (GSetIterStep(&iter));
  }
  // Return the clone
  return clone;
}

// Print the PBPhys 'that' on the stream 'stream'
void PBPhysPrintln(PBPhys* that, FILE* stream) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
  if (stream == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'stream' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  fprintf(stream, "dimension: %d\n", PBPhysGetDim(that));
  fprintf(stream, "t: %f\n", PBPhysGetCurTime(that));
  fprintf(stream, "dt: %f\n", PBPhysGetDeltaT(that));
  fprintf(stream, "down gravity: %f\n", PBPhysGetDownGravity(that));
  fprintf(stream, "gravity: %f\n", PBPhysGetGravity(that));
  fprintf(stream, "nb particles: %d\n", PBPhysGetNbParticle(that));
  if (PBPhysGetNbParticle(that) > 0) {
    GSetIterForward iter = 
      GSetIterForwardCreateStatic(PBPhysParticles(that));
    int iPart = 0;
    do {
      fprintf(stream, "particle #%d:\n", iPart);
      PBPhysParticle* part = GSetIterGet(&iter);
      PBPhysParticlePrintln(part, stream);
      ++iPart;
    } while (GSetIterStep(&iter));
  }
}

// Function which return the JSON encoding of 'that' 
JSONNode* PBPhysEncodeAsJSON(PBPhys* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Create the JSON structure
  JSONNode* json = JSONCreate();
  // Declare a buffer to convert value into string
  char val[100];
  // Encode the dimension
  sprintf(val, "%d", that->_dim);
  JSONAddProp(json, "_dim", val);
  // Encode the curTime
  sprintf(val, "%f", that->_curTime);
  JSONAddProp(json, "_curTime", val);
  // Encode the deltat
  sprintf(val, "%f", that->_deltaT);
  JSONAddProp(json, "_deltaT", val);
  // Encode the downGravity
  sprintf(val, "%f", that->_downGravity);
  JSONAddProp(json, "_downGravity", val);
  // Encode the gravity
  sprintf(val, "%f", that->_gravity);
  JSONAddProp(json, "_gravity", val);
  // Encode the nbParticle
  sprintf(val, "%d", PBPhysGetNbParticle(that));
  JSONAddProp(json, "_nbParticle", val);
  // Encode the particles
  // Declare an array of structures converted to string
  JSONArrayStruct setPart = JSONArrayStructCreateStatic();
  if (PBPhysGetNbParticle(that) > 0) {
    GSetIterForward iter = 
      GSetIterForwardCreateStatic(PBPhysParticles(that));
    do {
      PBPhysParticle* part = GSetIterGet(&iter);
      JSONArrayStructAdd(&setPart, 
        PBPhysParticleEncodeAsJSON(part));

    } while (GSetIterStep(&iter));
  }
  // Add a key with the array of structures
  JSONAddProp(json, "_particles", &setPart);
  // Free memory
  JSONArrayStructFlush(&setPart);
  // Return the created JSON 
  return json;
}

// Function which decode from JSON encoding 'json' to 'that'
bool PBPhysDecodeAsJSON(PBPhys** that, JSONNode* json) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (json == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'json' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // If 'that' is already allocated
  if (*that != NULL)
    // Free memory
    PBPhysFree(that);
  // Decode the dimension
  JSONNode* prop = JSONProperty(json, "_dim");
  if (prop == NULL) {
    return false;
  }
  int dim = atoi(JSONLabel(JSONValue(prop, 0)));
  // If data is invalid
  if (dim <= 0)
    return false;
  // Allocate memory
  *that = PBPhysCreate(dim);
  // Decode the curTime
  prop = JSONProperty(json, "_curTime");
  if (prop == NULL) {
    return false;
  }
  (*that)->_curTime = atof(JSONLabel(JSONValue(prop, 0)));
  // Decode the deltaT
  prop = JSONProperty(json, "_deltaT");
  if (prop == NULL) {
    return false;
  }
  (*that)->_deltaT = atof(JSONLabel(JSONValue(prop, 0)));
  // Decode the downGravity
  prop = JSONProperty(json, "_downGravity");
  if (prop == NULL) {
    return false;
  }
  (*that)->_downGravity = atof(JSONLabel(JSONValue(prop, 0)));
  // Decode the gravity
  prop = JSONProperty(json, "_gravity");
  if (prop == NULL) {
    return false;
  }
  (*that)->_gravity = atof(JSONLabel(JSONValue(prop, 0)));
  // Decode the nbParticle
  prop = JSONProperty(json, "_nbParticle");
  if (prop == NULL) {
    return false;
  }
  int nbParticle = atoi(JSONLabel(JSONValue(prop, 0)));
  // Decode the particle
  prop = JSONProperty(json, "_particles");
  if (prop == NULL) {
    return false;
  }
  if (JSONGetNbValue(prop) != nbParticle) {
    return false;
  }
  for (int iPart = 0; iPart < nbParticle; ++iPart) {
    JSONNode* part = JSONValue(prop, iPart);
    PBPhysParticle* p = NULL;
    if (!PBPhysParticleDecodeAsJSON(&p, part))
      return false;
    GSetAppend(PBPhysParticles(*that), p);
  }
  // Return the success code
  return true;
}

// Save the PBPhys 'that' on the stream 'stream'
// If 'compact' equals true it saves in compact form, else it saves in 
// readable form
// Return true if we could save the PBPhys
// Return false else
bool PBPhysSave(PBPhys* that, FILE* stream, bool compact) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
  if (stream == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'stream' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  // Get the JSON encoding
  JSONNode* json = PBPhysEncodeAsJSON(that);
  // Save the JSON
  if (!JSONSave(json, stream, compact)) {
    return false;
  }
  // Free memory
  JSONFree(&json);
  // Return success code
  return true;
}

// Load the PBPhys 'that' from the stream 'stream'
// Return true if we could load the PBPhys
// Return false else
bool PBPhysLoad(PBPhys** that, FILE* stream) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
  if (stream == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'stream' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  // Declare a json to load the encoded data
  JSONNode* json = JSONCreate();
  // Load the whole encoded data
  if (!JSONLoad(json, stream)) {
    return false;
  }
  // Decode the data from the JSON
  if (!PBPhysDecodeAsJSON(that, json)) {
    return false;
  }
  // Free the memory used by the JSON
  JSONFree(&json);
  // Return the success code
  return true;
}

// Step the PBPhys 'that' by that->_deltaT ignoring collision
void PBPhysNext(PBPhys* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  // If there is particle
  if (PBPhysGetNbParticle(that) > 0) {
    // Loop on particles
    GSetIterForward iter = 
      GSetIterForwardCreateStatic(PBPhysParticles(that));
    do {
      PBPhysParticle* part = GSetIterGet(&iter);
      // Calculate the system acceleration of the particle
      PBPhysUpdateSysAccel(that, part);
      // Move the particle
      PBPhysParticleMove(part, PBPhysGetDeltaT(that));
    } while (GSetIterStep(&iter));
  }
  // Update current time
  PBPhysSetCurTime(that, PBPhysGetCurTime(that) + PBPhysGetDeltaT(that));
}

// Calculate the system acceleration of the particle 'part' in the 
// PBPhys 'that'
void PBPhysUpdateSysAccel(PBPhys* that, PBPhysParticle* particle) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
  if (particle == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'particle' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  // If the particle is fixed there is nothing to do
  if (PBPhysParticleIsFixed(particle))
    return;
  // Reset the system acceleration
  VecSetNull(PBPhysParticleSysAccel(particle));
  // If the down gravity is active
  if (fabs(PBPhysGetDownGravity(that)) > PBMATH_EPSILON) {
    // Substract the down gravity to the y axis of the system 
    // acceleration
    VecSet(PBPhysParticleSysAccel(particle), 1, 
      -1.0 * PBPhysGetDownGravity(that));
  }
  // If the gravity is active
  if (fabs(PBPhysGetGravity(that)) > PBMATH_EPSILON) {
    // Get the center pos of the particle
    VecFloat* centerParticle = PBPhysParticleGetPos(particle);
    // Loop on particles
    GSetIterForward iter = 
      GSetIterForwardCreateStatic(PBPhysParticles(that));
    do {
      PBPhysParticle* part = GSetIterGet(&iter);
      // If the current particle is not the particle in argument
      if (particle != part) {
        // Get the distance between the two particles
        VecFloat* centerPart = PBPhysParticleGetPos(part);
        float dist = VecDist(centerParticle, centerPart);
        if (fabs(dist) > PBMATH_EPSILON) {
          // Get the magnitude of the attraction
          float mag = PBPhysGetGravity(that) * 
            PBPhysParticleGetMass(particle) * 
            PBPhysParticleGetMass(part) / fsquare(dist);
          // Apply the attraction toward the other particle
          VecOp(centerPart, 1.0, centerParticle, -1.0);
          VecNormalise(centerPart);
          VecOp(PBPhysParticleSysAccel(particle), 1.0, centerPart, mag);
        }
        // Free memory
        VecFree(&centerPart);
      }
    } while (GSetIterStep(&iter));
    // Free memory
    VecFree(&centerParticle);
  }
}

// Step the PBPhys 'that' by that->_deltaT managing collision(s)
void PBPhysStep(PBPhys* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  // Declare a variable to memorize the goal time
  float goalT = PBPhysGetCurTime(that) + PBPhysGetDeltaT(that);
  // Declare a variable to memorize the initial deltat
  float origDeltaT = PBPhysGetDeltaT(that);
  // Loop until we reach the goal time
  while (PBPhysGetCurTime(that) < goalT) {
//printf("curt %f goalt %f\n", PBPhysGetCurTime(that), goalT);
    // Step until next collision
    GSetPBPhysParticle* set = PBPhysStepToCollision(that);
//printf("curt %f goalt %f\n", PBPhysGetCurTime(that), goalT);
    // If there has been collision
    if (set != NULL) {
//printf("hit\n");
      // Manage the collision
      PBPhysParticleApplyElasticCollision(
        GSetGet(set, 0), GSetGet(set, 1));
      // Correct the deltat to reach the initial goal time
      PBPhysSetDeltaT(that, goalT - PBPhysGetCurTime(that));
//printf("deltat %f\n", PBPhysGetDeltaT(that));
      // Free the set
      GSetFree(&set);
    }
  }
  // Reset the initial deltat
  PBPhysSetDeltaT(that, origDeltaT);
}

// Step the PBPhys 'that' for that->_deltaT or until a collision occured
// If no collision occured return NULL
// If a collision occured one can check the collision time with the 
// current time that->_curTime, and the returned GSet contains the 
// particles wich have collided
GSetPBPhysParticle* PBPhysStepToCollision(PBPhys* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  // Declare a variable to memorize the deltat until next collision
  float deltat = PBPhysGetDeltaT(that);
  // Declare a set to memorize the colliding particle
  GSetPBPhysParticle* setCollision = GSetPBPhysParticleCreate();
  // If there is particle
  if (PBPhysGetNbParticle(that) > 0) {
    // Loop on particles
    GSetIterForward iter = 
      GSetIterForwardCreateStatic(PBPhysParticles(that));
    do {
      PBPhysParticle* part = GSetIterGet(&iter);
      // Calculate the system acceleration of the particle
      PBPhysUpdateSysAccel(that, part);
    } while (GSetIterStep(&iter));
    // If there is at least two particles
    if (PBPhysGetNbParticle(that) > 1) {
      // Declare a variabe to memorize the inverse of deltat
      float invDeltaT = 1.0 / PBPhysGetDeltaT(that);
      // Loop on particles once again from the beginning
      GSetIterReset(&iter);
      do {
        PBPhysParticle* part = GSetIterGet(&iter);
        // Get the pos of the center of the particle
        VecFloat* posPart = PBPhysParticleGetPos(part);
        // Get the displacement vector for the current particle
        VecFloat* vPart = PBPhysParticleGetNextDisplacement(part, 
          PBPhysGetDeltaT(that));
        // Scale to have the displacement per time unit
        VecScale(vPart, invDeltaT);
        // Get the bounding radius of the particle
        float radPart = 
          ShapoidGetBoundingRadius(PBPhysParticleShape(part));
        // Create a new iterator to loop through following particles
        GSetIterForward iterPair = iter;
        GSetIterStep(&iterPair);
        do {
          PBPhysParticle* pair = GSetIterGet(&iterPair);
          // Get the pos of the center of the particle
          VecFloat* posPair = PBPhysParticleGetPos(pair);
          // Get the displacement vector for the current pair
          VecFloat* vPair = PBPhysParticleGetNextDisplacement(pair,
            PBPhysGetDeltaT(that));
          // Scale to have the displacement per time unit
          VecScale(vPair, invDeltaT);
          // Get the bounding radius of the pair
          float radPair = 
            ShapoidGetBoundingRadius(PBPhysParticleShape(pair));
          // Check the pair trajectory to determine at what time they
          // are at the closest and what is this closest distance
          VecFloat3D distPoly = PBPhysGetDistPoly(posPart, vPart,
            posPair, vPair);
          float tNearest = deltat;
          if (fabs(VecGet(&distPoly, 2)) > PBMATH_EPSILON)
            tNearest = -0.5 * VecGet(&distPoly, 1) / 
              VecGet(&distPoly, 2);
          float distNearest = sqrt(VecGet(&distPoly, 0) + 
            tNearest * VecGet(&distPoly, 1) +
            fsquare(tNearest) * VecGet(&distPoly, 2));
          // If there is an impact in future
          if (tNearest > 0.0 && distNearest < radPart + radPair) {
            // Get the exact time at which particles hit
            float tHit = PBPhysGetTimeToHit(radPart, radPair, &distPoly);
            // If the time at hit is sooner than current delta
            if (tHit < deltat) {
              // Remove the eventual previous colliding particles
              GSetFlush(setCollision);
              // Add the colliding particles
              GSetAppend(setCollision, part);
              GSetAppend(setCollision, pair);
              // Update the time at hit
              deltat = tHit;
            }
          }
          // Free memory
          VecFree(&vPair);
          VecFree(&posPair);
        } while (GSetIterStep(&iterPair));
        // Free memory
        VecFree(&posPart);
        VecFree(&vPart);
      } while (GSetIterStep(&iter) && !GSetIterIsLast(&iter));
    }
    // Move the particles
    GSetIterReset(&iter);
    do {
      PBPhysParticle* part = GSetIterGet(&iter);
      // Move the particle
      PBPhysParticleMove(part, deltat);
    } while (GSetIterStep(&iter));
  }
  // Update current time
  PBPhysSetCurTime(that, PBPhysGetCurTime(that) + deltat);
  // If the set of collision is empty free it
  if (GSetNbElem(setCollision) == 0)
    GSetFree(&setCollision);
  // Return the set of colliding particles
  return setCollision;
}

// Return the time to collision between two particles of radius 'rA' 
// and 'rB' and the polynom of the square distance between particles 
// over time 'distPoly'
float PBPhysGetTimeToHit(float rA, float rB, VecFloat3D* distPoly) {
  float dist = fsquare(rA + rB);
  float tHit = (-1.0 * VecGet(distPoly, 1) - 
    sqrt(fsquare(VecGet(distPoly, 1)) - 4.0 * VecGet(distPoly, 2) * 
    (VecGet(distPoly, 0) - dist))) / (2.0 * VecGet(distPoly, 2));
  return tHit;
}

// Return the coefficients of the polynom describing the square of the 
// distance between two lines passing through 'posA' and 'posB' and 
// colinear to 'dirA' and 'dirB' respectively
// Return a vector such as dist^2(t)=v[0]+v[1]t+v[2]t^2
VecFloat3D PBPhysGetDistPoly(VecFloat* posA, VecFloat* dirA,
  VecFloat* posB, VecFloat* dirB) {
#if BUILDMODE == 0
  if (posA == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'posA' is null");
    PBErrCatch(PBPhysErr);
  }
  if (posB == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'posB' is null");
    PBErrCatch(PBPhysErr);
  }
  if (dirA == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'dirA' is null");
    PBErrCatch(PBPhysErr);
  }
  if (dirB == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'dirB' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  // Declare the vector result
  VecFloat3D res = VecFloatCreateStatic3D();
  // Loop on dimensions
  for (int iDim = VecGetDim(posA); iDim--;) {
    VecSetAdd(&res, 0, 
      fsquare(VecGet(posA, iDim) - VecGet(posB, iDim)));
    VecSetAdd(&res, 1, 
      (VecGet(posA, iDim) - VecGet(posB, iDim)) *
      (VecGet(dirA, iDim) - VecGet(dirB, iDim)));
    VecSetAdd(&res, 2, 
      fsquare(VecGet(dirA, iDim) - VecGet(dirB, iDim)));
  }
  VecSet(&res, 1, VecGet(&res, 1) * 2.0);
  // Return the result
  return res;
}

// Return true if the PBPhys 'that' is the same as PBPhys 'tho'
bool PBPhysIsSame(PBPhys* that, PBPhys* tho) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBPhysErr->_type = PBErrTypeNullPointer;
    sprintf(PBPhysErr->_msg, "'that' is null");
    PBErrCatch(PBPhysErr);
  }
#endif
  if (that->_dim != tho->_dim ||
    !ISEQUALF(that->_deltaT, tho->_deltaT) ||
    !ISEQUALF(that->_curTime, tho->_curTime) ||
    !ISEQUALF(that->_downGravity, tho->_downGravity) ||
    that->_gravity != tho->_gravity ||
    PBPhysGetNbParticle(that) != PBPhysGetNbParticle(tho))
    return false;
  if (PBPhysGetNbParticle(that) > 0) {
    GSetIterForward iterA = 
      GSetIterForwardCreateStatic(PBPhysParticles(that));
    GSetIterForward iterB = 
      GSetIterForwardCreateStatic(PBPhysParticles(tho));
    do {
      PBPhysParticle* partA = GSetIterGet(&iterA);
      PBPhysParticle* partB = GSetIterGet(&iterB);
      if (!PBPhysParticleIsSame(partA, partB))
        return false;
    } while (GSetIterStep(&iterA) && GSetIterStep(&iterB));
  }
  return true;
}

