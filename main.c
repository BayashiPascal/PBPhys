#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include "pberr.h"
#include "pbphys.h"

#define RANDOMSEED 0

void UnitTestPBPhysParticleCreateFreePrint() {
  PBPhysParticle* particle = PBPhysParticleCreate(2, 
    ShapoidTypeSpheroid);
  if (particle == NULL ||
    particle->_shape == NULL ||
    particle->_speed == NULL ||
    particle->_accel == NULL ||
    particle->_fixed == true ||
    ISEQUALF(particle->_mass, 0.0) == false ||
    ISEQUALF(particle->_drag, 0.0) == false ||
    VecGetDim(particle->_speed) != 2 ||
    VecGetDim(particle->_accel) != 2 ||
    ShapoidGetDim(particle->_shape) != 2 ||
    ShapoidGetType(particle->_shape) != ShapoidTypeSpheroid) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleCreate failed");
    PBErrCatch(PBPhysErr);
  }
  PBPhysParticlePrintln(particle, stdout);
  PBPhysParticleFree(&particle);
  if (particle != NULL) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleFree failed");
    PBErrCatch(PBPhysErr);
  }
  printf("UnitTestPBPhysParticleCreateFreePrint OK\n");
}

void UnitTestPBPhysParticleGetSet() {
  int dim = 2;
  ShapoidType type = ShapoidTypeSpheroid;
  PBPhysParticle* particle = PBPhysParticleCreate(dim, type);
  if (PBPhysParticleGetDim(particle) != dim) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleGetDim failed");
    PBErrCatch(PBPhysErr);
  }
  if (PBPhysParticleGetShapeType(particle) != type) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleGetShapeType failed");
    PBErrCatch(PBPhysErr);
  }
  if (PBPhysParticleShape(particle) != particle->_shape) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleShape failed");
    PBErrCatch(PBPhysErr);
  }
  if (PBPhysParticleSpeed(particle) != particle->_speed) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleSpeed failed");
    PBErrCatch(PBPhysErr);
  }
  if (PBPhysParticleAccel(particle) != particle->_accel) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleAccel failed");
    PBErrCatch(PBPhysErr);
  }
  if (PBPhysParticleIsFixed(particle) != particle->_fixed) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleIsFixed failed");
    PBErrCatch(PBPhysErr);
  }
  VecFloat2D v = VecFloatCreateStatic2D();
  VecSet(&v, 0, 2.0); VecSet(&v, 1, 3.0);
  PBPhysParticleSetSpeed(particle, &v);
  if (VecIsEqual(PBPhysParticleSpeed(particle), &v) == false) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleSetSpeed failed");
    PBErrCatch(PBPhysErr);
  }
  VecSet(&v, 0, 4.0); VecSet(&v, 1, 5.0);
  PBPhysParticleSetPos(particle, &v);
  VecFloat* pos = PBPhysParticleGetPos(particle);
  if (VecIsEqual(pos, &v) == false) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleSetPos failed");
    PBErrCatch(PBPhysErr);
  }
  VecFree(&pos);
  VecSet(&v, 0, 6.0); VecSet(&v, 1, 7.0);
  PBPhysParticleSetAccel(particle, &v);
  if (VecIsEqual(PBPhysParticleAccel(particle), &v) == false) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleSetAccel failed");
    PBErrCatch(PBPhysErr);
  }
  for (int iAxis = dim; iAxis--;)
    if (PBPhysParticleAxis(particle, iAxis) != 
      ShapoidAxis(PBPhysParticleShape(particle), iAxis)) {
      PBPhysErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBPhysErr->_msg, "PBPhysParticleAxis failed");
      PBErrCatch(PBPhysErr);
    }
  PBPhysParticleSetSize(particle, (VecFloat*)&v);
  for (int iAxis = dim; iAxis--;)
    if (!ISEQUALF(VecNorm(PBPhysParticleAxis(particle, iAxis)), 
      VecGet(&v, iAxis))) {
      PBPhysErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBPhysErr->_msg, "PBPhysParticleSetSize failed");
      PBErrCatch(PBPhysErr);
    }
  float size = 0.5;
  PBPhysParticleSetSize(particle, size);
  for (int iAxis = dim; iAxis--;)
    if (!ISEQUALF(VecNorm(PBPhysParticleAxis(particle, iAxis)), size)) {
      PBPhysErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBPhysErr->_msg, "PBPhysParticleSetSize failed");
      PBErrCatch(PBPhysErr);
    }
  float mass = 0.1;
  PBPhysParticleSetMass(particle, mass);
  if (!ISEQUALF(particle->_mass, mass)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleSetMass failed");
    PBErrCatch(PBPhysErr);
  }
  if (!ISEQUALF(PBPhysParticleGetMass(particle), mass)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleGetMass failed");
    PBErrCatch(PBPhysErr);
  }
  float drag = 0.2;
  PBPhysParticleSetDrag(particle, drag);
  if (!ISEQUALF(particle->_drag, drag)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleSetDrag failed");
    PBErrCatch(PBPhysErr);
  }
  if (!ISEQUALF(PBPhysParticleGetDrag(particle), drag)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleGetDrag failed");
    PBErrCatch(PBPhysErr);
  }
  PBPhysParticleSetFixed(particle, true);
  if (PBPhysParticleIsFixed(particle) != true) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleSetFixed failed");
    PBErrCatch(PBPhysErr);
  }
  char data[2];
  particle->_data = data;
  if (PBPhysParticleData(particle) != data) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleData failed");
    PBErrCatch(PBPhysErr);
  }
  PBPhysParticleSetData(particle, data + 1);
  if (PBPhysParticleData(particle) != data + 1) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleSetData failed");
    PBErrCatch(PBPhysErr);
  }
  PBPhysParticleFree(&particle);
  printf("UnitTestPBPhysParticleGetSet OK\n");
}

void UnitTestPBPhysParticleCloneIsSame() {
  PBPhysParticle* particle = PBPhysParticleCreate(2, 
    ShapoidTypeSpheroid);
  VecFloat2D v = VecFloatCreateStatic2D();
  VecSet(&v, 0, 2.0); VecSet(&v, 1, 3.0);
  PBPhysParticleSetPos(particle, &v);
  VecFloat2D w = VecFloatCreateStatic2D();
  VecSet(&w, 0, 4.0); VecSet(&w, 1, 5.0);
  PBPhysParticleSetSpeed(particle, &w);
  VecSet(&w, 0, 6.0); VecSet(&w, 1, 7.0);
  PBPhysParticleSetAccel(particle, &w);
  PBPhysParticle* clone = PBPhysParticleClone(particle);
  if (PBPhysParticleIsSame(clone, particle) == false) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleClone failed");
    PBErrCatch(PBPhysErr);
  }
  VecSet(&w, 0, 1.0); VecSet(&w, 1, 5.0);
  PBPhysParticleSetSpeed(particle, &w);
  if (PBPhysParticleIsSame(clone, particle) == true) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleIsSame failed");
    PBErrCatch(PBPhysErr);
  }
  PBPhysParticleFree(&particle);
  PBPhysParticleFree(&clone);
  printf("UnitTestPBPhysParticleCloneIsSame OK\n");
}

void UnitTestPBPhysParticleLoadSave() {
  PBPhysParticle* particle = PBPhysParticleCreate(2, 
    ShapoidTypeSpheroid);
  VecFloat2D v = VecFloatCreateStatic2D();
  VecSet(&v, 0, 2.0); VecSet(&v, 1, 3.0);
  PBPhysParticleSetPos(particle, &v);
  VecFloat2D w = VecFloatCreateStatic2D();
  VecSet(&w, 0, 4.0); VecSet(&w, 1, 5.0);
  PBPhysParticleSetSpeed(particle, &w);
  VecSet(&w, 0, 6.0); VecSet(&w, 1, 7.0);
  PBPhysParticleSetAccel(particle, &w);
  PBPhysParticleSetMass(particle, 8.0);
  FILE* fd = fopen("./particle.txt", "w");
  if (PBPhysParticleSave(particle, fd, false) == false) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleSave failed");
    PBErrCatch(PBPhysErr);
  }
  fclose(fd);
  fd = fopen("./particle.txt", "r");
  PBPhysParticle* loaded = PBPhysParticleCreate(2, 
    ShapoidTypeSpheroid);
  if (PBPhysParticleLoad(&loaded, fd) == false ||
    PBPhysParticleIsSame(loaded, particle) == false) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticleLoad failed");
    PBErrCatch(PBPhysErr);
  }
  fclose(fd);
  PBPhysParticleFree(&loaded);
  PBPhysParticleFree(&particle);
  printf("UnitTestPBPhysParticleLoadSave OK\n");
}

void UnitTestPBPhysParticleAccelMove() {
  PBPhysParticle* particle = PBPhysParticleCreate(2, 
    ShapoidTypeSpheroid);
  VecFloat2D v = VecFloatCreateStatic2D();
  VecSet(&v, 0, 1.0); VecSet(&v, 1, -0.5);
  PBPhysParticleSetAccel(particle, &v);
  float dt = 0.1;
  float checkA[20] = {
    0.005000,-0.002500,0.020000,-0.010000,0.045000,-0.022500,0.080000,
    -0.040000,0.125000,-0.062500,0.180000,-0.090000,0.245000,-0.122500,
    0.320000,-0.160000,0.405000,-0.202500,0.500000,-0.250000};
  const VecFloat* pos = ShapoidPos(PBPhysParticleShape(particle));
  for (int i = 0; i < 10; ++i) {
    PBPhysParticleMove(particle, dt);
    if (ISEQUALF(VecGet(PBPhysParticleSpeed(particle), 0), 
      (float)(i + 1) * dt) == false ||
      ISEQUALF(VecGet(PBPhysParticleSpeed(particle), 1), 
      (float)(i + 1) * dt * -0.5) == false) {
      PBPhysErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBPhysErr->_msg, "PBPhysParticleMove failed");
      PBErrCatch(PBPhysErr);
    }
    if (ISEQUALF(VecGet(pos, 0), checkA[2 * i]) == false ||
      ISEQUALF(VecGet(pos, 1), checkA[2 * i + 1]) == false) {
      PBPhysErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBPhysErr->_msg, "PBPhysParticleMove failed");
      PBErrCatch(PBPhysErr);
    }
  }
  float drag = 0.1;
  PBPhysParticleSetDrag(particle, drag);
  VecFloat2D vecNull = VecFloatCreateStatic2D();
  ShapoidSetPos(PBPhysParticleShape(particle), &vecNull);
  VecSetNull(PBPhysParticleSpeed(particle));
  float checkC[20] = {
    0.100000,-0.050000,0.199000,-0.099500,0.297010,-0.148505,0.394040,
    -0.197020,0.490099,-0.245050,0.585199,-0.292599,0.679347,-0.339673,
    0.772553,-0.386277,0.864828,-0.432414,0.956179,-0.478090};
  float checkD[20] = {
    0.005000,-0.002500,0.019950,-0.009975,0.044751,-0.022375,0.079303,
    -0.039651,0.123510,-0.061755,0.177275,-0.088637,0.240502,-0.120251,
    0.313097,-0.156549,0.394966,-0.197483,0.486017,-0.243008};
  for (int i = 0; i < 10; ++i) {
    PBPhysParticleMove(particle, dt);
    if (ISEQUALF(VecGet(PBPhysParticleSpeed(particle), 0), 
      checkC[2 * i]) == false ||
      ISEQUALF(VecGet(PBPhysParticleSpeed(particle), 1), 
      checkC[2 * i + 1]) == false) {
      PBPhysErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBPhysErr->_msg, "PBPhysParticleMove failed");
      PBErrCatch(PBPhysErr);
    }
    if (ISEQUALF(VecGet(pos, 0), checkD[2 * i]) == false ||
      ISEQUALF(VecGet(pos, 1), checkD[2 * i + 1]) == false) {
      PBPhysErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBPhysErr->_msg, "PBPhysParticleMove failed");
      PBErrCatch(PBPhysErr);
    }
  }
  PBPhysParticleFree(&particle);
  printf("UnitTestPBPhysParticleAccelMove OK\n");
}

void UnitTestPBPhysParticleTestTrajectory() {
  PBPhysParticle* am = PBPhysParticleCreate(2, 
    ShapoidTypeSpheroid);
  PBPhysParticle* amd = PBPhysParticleCreate(2, 
    ShapoidTypeSpheroid);
  VecFloat2D accel = VecFloatCreateStatic2D();
  VecSet(&accel, 0, 4.0); VecSet(&accel, 1, 4.0);
  PBPhysParticleSetSpeed(am, &accel);
  PBPhysParticleSetSpeed(amd, &accel);
  VecSet(&accel, 0, 0.0); VecSet(&accel, 1, -1.0 * PBPHYS_Gn);
  PBPhysParticleSetAccel(am, &accel);
  PBPhysParticleSetAccel(amd, &accel);
  float drag = 0.2;
  PBPhysParticleSetDrag(amd, drag);
  float dt = 0.01;
  float t = 0.0;
  FILE* fd = fopen("./traj.txt", "w");
  const VecFloat* posam = ShapoidPos(PBPhysParticleShape(am));
  const VecFloat* posamd = ShapoidPos(PBPhysParticleShape(amd));
  for (int i = 0; i < 100; ++i) {
    PBPhysParticleMove(am, dt);
    PBPhysParticleMove(amd, dt);
    t += dt;
    fprintf(fd, "%f %f %f %f %f\n", t, 
      VecGet(posam, 0), VecGet(posam, 1),
      VecGet(posamd, 0), VecGet(posamd, 1));
  }
  fclose(fd);
  PBPhysParticleFree(&am);
  PBPhysParticleFree(&amd);
  printf("UnitTestPBPhysParticleTestTrajectory OK\n");
}

void UnitTestPBPhysParticle() {
  UnitTestPBPhysParticleCreateFreePrint();
  UnitTestPBPhysParticleGetSet();
  UnitTestPBPhysParticleCloneIsSame();
  UnitTestPBPhysParticleLoadSave();
  UnitTestPBPhysParticleAccelMove();
  UnitTestPBPhysParticleTestTrajectory();
  printf("UnitTestPBPhysParticle OK\n");
}

void UnitTestPBPhysCreateFreePrint() {
  int dim = 2;
  PBPhys* phys = PBPhysCreate(dim);
  if (phys == NULL ||
    phys->_dim != 2 ||
    !ISEQUALF(phys->_deltaT, PBPHYS_DELTAT) ||
    !ISEQUALF(phys->_downGravity, 0.0) ||
    !ISEQUALF(phys->_curTime, 0.0) ||
    phys->_gravity != 0 ||
    GSetNbElem(PBPhysParticles(phys)) != 0) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysCreate failed");
    PBErrCatch(PBPhysErr);
  }
  PBPhysAddParticles(phys, 2, ShapoidTypeSpheroid);
  PBPhysParticleSetMass(PBPhysPart(phys, 1), 1.0);
  PBPhysPrintln(phys, stdout);
  PBPhysFree(&phys);
  if (phys != NULL) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysFree failed");
    PBErrCatch(PBPhysErr);
  }
  printf("UnitTestPBPhysCreateFreePrint OK\n");
}

void UnitTestPBPhysGetSetAdd() {
  int dim = 2;
  PBPhys* phys = PBPhysCreate(dim);
  if (PBPhysGetDim(phys) != dim) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysGetDim failed");
    PBErrCatch(PBPhysErr);
  }
  phys->_curTime = 0.1;
  if (!ISEQUALF(PBPhysGetCurTime(phys), phys->_curTime)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysGetCurTime failed");
    PBErrCatch(PBPhysErr);
  }
  if (!ISEQUALF(PBPhysGetDeltaT(phys), PBPHYS_DELTAT)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysGetDeltaT failed");
    PBErrCatch(PBPhysErr);
  }
  phys->_downGravity = 0.2;
  if (!ISEQUALF(PBPhysGetDownGravity(phys), phys->_downGravity)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysGetDownGravity failed");
    PBErrCatch(PBPhysErr);
  }
  phys->_gravity = 0.3;
  if (!ISEQUALF(PBPhysGetGravity(phys), phys->_gravity)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysGetGravity failed");
    PBErrCatch(PBPhysErr);
  }
  PBPhysSetCurTime(phys, 0.2);
  if (!ISEQUALF(PBPhysGetCurTime(phys), phys->_curTime)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysSetCurTime failed");
    PBErrCatch(PBPhysErr);
  }
  PBPhysSetDeltaT(phys, 0.3);
  if (!ISEQUALF(PBPhysGetDeltaT(phys), phys->_deltaT)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysSetDeltaT failed");
    PBErrCatch(PBPhysErr);
  }
  PBPhysSetDownGravity(phys, 0.4);
  if (!ISEQUALF(PBPhysGetDownGravity(phys), phys->_downGravity)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysSetDownGravity failed");
    PBErrCatch(PBPhysErr);
  }
  PBPhysSetGravity(phys, 0.5);
  if (!ISEQUALF(PBPhysGetGravity(phys), phys->_gravity)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysSetGravity failed");
    PBErrCatch(PBPhysErr);
  }
  if (PBPhysParticles(phys) != &(phys->_particles)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysParticles failed");
    PBErrCatch(PBPhysErr);
  }
  if (PBPhysGetNbParticle(phys) != 0) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysGetNbParticle failed");
    PBErrCatch(PBPhysErr);
  }
  PBPhysAddParticles(phys, 2, ShapoidTypeSpheroid);
  if (GSetNbElem(PBPhysParticles(phys)) != 2) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysAddParticles failed");
    PBErrCatch(PBPhysErr);
  }
  if (PBPhysGetNbParticle(phys) != 2) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysGetNbParticle failed");
    PBErrCatch(PBPhysErr);
  }
  if (GSetGet(PBPhysParticles(phys), 0) != PBPhysPart(phys, 0) ||
    GSetGet(PBPhysParticles(phys), 1) != PBPhysPart(phys, 1)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysPart failed");
    PBErrCatch(PBPhysErr);
  }
  PBPhysFree(&phys);
  printf("UnitTestPBPhysGetSetAdd OK\n");
}

void UnitTestPBPhysCloneIsSame() {
  int dim = 2;
  PBPhys* phys = PBPhysCreate(dim);
  PBPhysAddParticles(phys, 2, ShapoidTypeSpheroid);
  PBPhysParticleSetMass(PBPhysPart(phys, 1), 1.0);
  PBPhys* clone = PBPhysClone(phys);
  if (!PBPhysIsSame(clone, phys)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysClone failed");
    PBErrCatch(PBPhysErr);
  }
  PBPhysParticleSetMass(PBPhysPart(clone, 1), 2.0);
  if (PBPhysIsSame(clone, phys)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysIsSame failed");
    PBErrCatch(PBPhysErr);
  }
  PBPhysFree(&phys);
  PBPhysFree(&clone);
  printf("UnitTestPBPhysCloneIsSame OK\n");
}

void UnitTestPBPhysLoadSave() {
  int dim = 2;
  PBPhys* phys = PBPhysCreate(dim);
  PBPhysAddParticles(phys, 2, ShapoidTypeSpheroid);
  PBPhysParticleSetMass(PBPhysPart(phys, 1), 1.0);
  FILE* fd = fopen("./phys.txt", "w");
  if (!PBPhysSave(phys, fd, false)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysSave failed");
    PBErrCatch(PBPhysErr);
  }
  fclose(fd);
  PBPhys* loaded = PBPhysCreate(dim);
  fd = fopen("./phys.txt", "r");
  if (!PBPhysLoad(&loaded, fd) ||
    !PBPhysIsSame(phys, loaded)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysLoad failed");
    PBErrCatch(PBPhysErr);
  }
  fclose(fd);
  PBPhysFree(&phys);
  PBPhysFree(&loaded);
  printf("UnitTestPBPhysLoadSave OK\n");
}

void UnitTestPBPhysStepFree() {
  int dim = 2;
  PBPhys* phys = PBPhysCreate(dim);
  PBPhysAddParticles(phys, 1, ShapoidTypeSpheroid);
  VecFloat2D v = VecFloatCreateStatic2D();
  VecSet(&v, 0, 1.0); VecSet(&v, 1, 0.5);
  PBPhysParticleSetSpeed(PBPhysPart(phys, 0), &v);
  float check[20] = {
    0.010000,0.005000,0.020000,0.010000,0.030000,0.015000,0.040000,
    0.020000,0.050000,0.025000,0.060000,0.030000,0.070000,0.035000,
    0.080000,0.040000,0.090000,0.045000,.100000,0.050000};
  for (int i = 0; i < 10; ++i) {
    PBPhysNext(phys);
    VecSet(&v, 0, check[2 * i]); VecSet(&v, 1, check[2 * i + 1]);
    if (!VecIsEqual(
      ShapoidPos(PBPhysParticleShape(PBPhysPart(phys, 0))),
      &v)) {
      PBPhysErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBPhysErr->_msg, "PBPhysStep failed");
      PBErrCatch(PBPhysErr);
    }
  }
  PBPhysFree(&phys);
  printf("UnitTestPBPhysStepFree OK\n");
}

void UnitTestPBPhysStepDownGravity() {
  int dim = 2;
  PBPhys* phys = PBPhysCreate(dim);
  PBPhysSetDownGravity(phys, PBPHYS_Gn);
  PBPhysAddParticles(phys, 1, ShapoidTypeSpheroid);
  VecFloat2D v = VecFloatCreateStatic2D();
  VecSet(&v, 0, 1.0); VecSet(&v, 1, 0.5);
  PBPhysParticleSetSpeed(PBPhysPart(phys, 0), &v);
  float check[20] = {
    0.010000,0.004510,0.020000,0.008039,0.030000,0.010587,0.040000,
    0.012155,0.050000,0.012742,0.060000,0.012348,0.070000,0.010974,
    0.080000,0.008619,0.090000,0.005283,0.100000,0.000967};
  for (int i = 0; i < 10; ++i) {
    PBPhysNext(phys);
    VecSet(&v, 0, check[2 * i]); VecSet(&v, 1, check[2 * i + 1]);
    if (!VecIsEqual(
      ShapoidPos(PBPhysParticleShape(PBPhysPart(phys, 0))),
      &v)) {
      PBPhysErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBPhysErr->_msg, "PBPhysStep failed");
      PBErrCatch(PBPhysErr);
    }
  }
  PBPhysFree(&phys);
  printf("UnitTestPBPhysStepDownGravity OK\n");
}

void UnitTestPBPhysStepGravity() {
  int dim = 2;
  PBPhys* phys = PBPhysCreate(dim);
  PBPhysSetGravity(phys, 1.0);
  PBPhysAddParticles(phys, 2, ShapoidTypeSpheroid);
  VecFloat2D v = VecFloatCreateStatic2D();
  VecSet(&v, 0, 1.0); VecSet(&v, 1, 0.5);
  PBPhysParticleSetSpeed(PBPhysPart(phys, 0), &v);
  PBPhysParticleSetMass(PBPhysPart(phys, 0), 1.0);
  VecSet(&v, 0, 1.0); VecSet(&v, 1, 1.0);
  PBPhysParticleSetPos(PBPhysPart(phys, 1), &v);
  PBPhysParticleSetMass(PBPhysPart(phys, 1), 1.0);
  PBPhysParticleSetFixed(PBPhysPart(phys, 1), true);
  float check[20] = {
    0.010018,0.005018,0.020071,0.010071,0.030160,0.015161,0.040286,
    0.020287,0.050449,0.025452,0.060649,0.030654,0.070887,0.035896,
    0.081164,0.041177,0.091479,0.046499,.101834,0.051862};
  for (int i = 0; i < 10; ++i) {
    PBPhysNext(phys);
    VecSet(&v, 0, check[2 * i]); VecSet(&v, 1, check[2 * i + 1]);
    if (!VecIsEqual(
      ShapoidPos(PBPhysParticleShape(PBPhysPart(phys, 0))),
      &v)) {
      PBPhysErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBPhysErr->_msg, "PBPhysStep failed");
      PBErrCatch(PBPhysErr);
    }
//VecFloatPrint(ShapoidPos(PBPhysParticleShape(PBPhysPart(phys, 0))), stdout, 6);printf("\n");
  }
  PBPhysFree(&phys);
  printf("UnitTestPBPhysStepDownGravity OK\n");
  printf("UnitTestPBPhysStepGravity OK\n");
}

void UnitTestPBPhysStepToCollisionApplyElasticCollision() {
  int dim = 2;
  PBPhys* phys = PBPhysCreate(dim);
  PBPhysAddParticles(phys, 3, ShapoidTypeSpheroid);
  VecFloat2D v = VecFloatCreateStatic2D();
  VecSet(&v, 0, 1.0); VecSet(&v, 1, 1.0);
  PBPhysParticleSetSpeed(PBPhysPart(phys, 0), &v);
  PBPhysParticleSetMass(PBPhysPart(phys, 0), 1.0);
  VecSet(&v, 0, 0.0); VecSet(&v, 1, 2.0);
  PBPhysParticleSetPos(PBPhysPart(phys, 1), &v);
  VecSet(&v, 0, 0.5); VecSet(&v, 1, -0.5);
  PBPhysParticleSetSpeed(PBPhysPart(phys, 1), &v);
  PBPhysParticleSetMass(PBPhysPart(phys, 1), 1.0);
  VecSet(&v, 0, 2.0); VecSet(&v, 1, 2.0);
  PBPhysParticleSetPos(PBPhysPart(phys, 2), &v);
  VecSet(&v, 0, -1.0); VecSet(&v, 1, -1.0);
  PBPhysParticleSetSpeed(PBPhysPart(phys, 2), &v);
  PBPhysParticleSetMass(PBPhysPart(phys, 2), 2.0);
  PBPhysSetDeltaT(phys, 2.0);
  GSetPBPhysParticle* set = PBPhysStepToCollision(phys);
  if (!ISEQUALF(PBPhysGetCurTime(phys), 0.646447) ||
    !ISEQUALF(PBPhysPart(phys,0)->_shape->_pos->_val[0], 0.646447) ||
    !ISEQUALF(PBPhysPart(phys,0)->_shape->_pos->_val[1], 0.646447) ||
    !ISEQUALF(PBPhysPart(phys,1)->_shape->_pos->_val[0], 0.323223) ||
    !ISEQUALF(PBPhysPart(phys,1)->_shape->_pos->_val[1], 1.676777) ||
    !ISEQUALF(PBPhysPart(phys,2)->_shape->_pos->_val[0], 1.353553) ||
    !ISEQUALF(PBPhysPart(phys,2)->_shape->_pos->_val[1], 1.353553) ||
    GSetNbElem(set) != 2 ||
    GSetGet(set, 0) != PBPhysPart(phys,0) ||
    GSetGet(set, 1) != PBPhysPart(phys,2)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysStepToCollision failed");
    PBErrCatch(PBPhysErr);
  }
  PBPhysParticleApplyElasticCollision(GSetGet(set, 0), GSetGet(set, 1));
  if (!ISEQUALF(PBPhysPart(phys,0)->_speed->_val[0], -1.666667) ||
    !ISEQUALF(PBPhysPart(phys,0)->_speed->_val[1], -1.666667) ||
    !ISEQUALF(PBPhysPart(phys,2)->_speed->_val[0], 0.333334) ||
    !ISEQUALF(PBPhysPart(phys,2)->_speed->_val[1], 0.333334)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, 
      "PBPhysParticleApplyElasticCollision failed");
    PBErrCatch(PBPhysErr);
  }
  GSetFree(&set);
  set = PBPhysStepToCollision(phys);
  if (!ISEQUALF(PBPhysGetCurTime(phys), 0.878937) ||
    !ISEQUALF(PBPhysPart(phys,0)->_shape->_pos->_val[0], 0.258963) ||
    !ISEQUALF(PBPhysPart(phys,0)->_shape->_pos->_val[1], 0.258963) ||
    !ISEQUALF(PBPhysPart(phys,1)->_shape->_pos->_val[0], 0.439468) ||
    !ISEQUALF(PBPhysPart(phys,1)->_shape->_pos->_val[1], 1.560532) ||
    !ISEQUALF(PBPhysPart(phys,2)->_shape->_pos->_val[0], 1.431050) ||
    !ISEQUALF(PBPhysPart(phys,2)->_shape->_pos->_val[1], 1.431050) ||
    GSetNbElem(set) != 2 ||
    GSetGet(set, 0) != PBPhysPart(phys,1) ||
    GSetGet(set, 1) != PBPhysPart(phys,2)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, "PBPhysStepToCollision failed");
    PBErrCatch(PBPhysErr);
  }
  PBPhysParticleApplyElasticCollision(GSetGet(set, 0), GSetGet(set, 1));
  if (!ISEQUALF(PBPhysPart(phys,1)->_speed->_val[0], 0.138846) ||
    !ISEQUALF(PBPhysPart(phys,1)->_speed->_val[1], -0.452840) ||
    !ISEQUALF(PBPhysPart(phys,2)->_speed->_val[0], 0.513910) ||
    !ISEQUALF(PBPhysPart(phys,2)->_speed->_val[1], 0.309754)) {
    PBPhysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBPhysErr->_msg, 
      "PBPhysParticleApplyElasticCollision failed");
    PBErrCatch(PBPhysErr);
  }
  GSetFree(&set);
  VecSet(&v, 0, 0.0); VecSet(&v, 1, 0.0);
  PBPhysParticleSetPos(PBPhysPart(phys, 0), &v);
  VecSet(&v, 0, 1.0); VecSet(&v, 1, 1.0);
  PBPhysParticleSetSpeed(PBPhysPart(phys, 0), &v);
  VecSet(&v, 0, 0.0); VecSet(&v, 1, 2.0);
  PBPhysParticleSetPos(PBPhysPart(phys, 1), &v);
  VecSet(&v, 0, 0.5); VecSet(&v, 1, -0.5);
  PBPhysParticleSetSpeed(PBPhysPart(phys, 1), &v);
  VecSet(&v, 0, 2.0); VecSet(&v, 1, 2.0);
  PBPhysParticleSetPos(PBPhysPart(phys, 2), &v);
  VecSet(&v, 0, -1.0); VecSet(&v, 1, -1.0);
  PBPhysParticleSetSpeed(PBPhysPart(phys, 2), &v);
  ShapoidScale(PBPhysParticleShape(PBPhysPart(phys, 2)), (float)2.0);
  PBPhysSetDeltaT(phys, 0.05);
  PBPhysSetCurTime(phys, 0.0);
  FILE* fd = fopen("./collision.txt", "w");
  for (int i = 0; i < 20; ++i) {
    PBPhysStep(phys);
    fprintf(fd, "%f %f %f %f %f %f %f\n", PBPhysGetCurTime(phys), 
      PBPhysPart(phys,0)->_shape->_pos->_val[0],
      PBPhysPart(phys,0)->_shape->_pos->_val[1],
      PBPhysPart(phys,1)->_shape->_pos->_val[0],
      PBPhysPart(phys,1)->_shape->_pos->_val[1],
      PBPhysPart(phys,2)->_shape->_pos->_val[0],
      PBPhysPart(phys,2)->_shape->_pos->_val[1]);
  }
  fclose(fd);
  PBPhysFree(&phys);
  printf("UnitTestPBPhysStepToCollisionApplyElasticCollision OK\n");
}

void UnitTestPBPhysNext() {
  UnitTestPBPhysStepFree();
  UnitTestPBPhysStepDownGravity();
  UnitTestPBPhysStepGravity();
  UnitTestPBPhysStepToCollisionApplyElasticCollision();
  printf("UnitTestPBPhysStep OK\n");
}

void UnitTestPBPhys() {
  UnitTestPBPhysCreateFreePrint();
  UnitTestPBPhysGetSetAdd();
  UnitTestPBPhysCloneIsSame();
  UnitTestPBPhysLoadSave();
  UnitTestPBPhysNext();

  printf("UnitTestPBPhys OK\n");
}

void UnitTestAll() {
  UnitTestPBPhysParticle();
  UnitTestPBPhys();
  printf("UnitTestAll OK\n");
}

int main() {
  UnitTestAll();
  // Return success code
  return 0;
}

