/*
 * transmitter22a.cpp
 *
 * Code generation for model "transmitter22a".
 *
 * Model version              : 1.0
 * Simulink Coder version : 9.7 (R2022a) 13-Nov-2021
 * C++ source code generated on : Mon May 27 21:23:58 2024
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#include "transmitter22a.h"
#include <cmath>
#include "transmitter22a_private.h"

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
void transmitter22a::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3]{
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3]{
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t { rtsiGetT(si) };

  time_T tnew { rtsiGetSolverStopTime(si) };

  time_T h { rtsiGetStepSize(si) };

  real_T *x { rtsiGetContStates(si) };

  ODE3_IntgData *id { static_cast<ODE3_IntgData *>(rtsiGetSolverData(si)) };

  real_T *y { id->y };

  real_T *f0 { id->f[0] };

  real_T *f1 { id->f[1] };

  real_T *f2 { id->f[2] };

  real_T hB[3];
  int_T i;
  int_T nXc { 3 };

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) std::memcpy(y, x,
                     static_cast<uint_T>(nXc)*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  transmitter22a_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  transmitter22a_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  this->step();
  transmitter22a_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void transmitter22a::step()
{
  if (rtmIsMajorTimeStep((&transmitter22a_M))) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&(&transmitter22a_M)->solverInfo,(((&transmitter22a_M
      )->Timing.clockTick0+1)*(&transmitter22a_M)->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&transmitter22a_M))) {
    (&transmitter22a_M)->Timing.t[0] = rtsiGetT(&(&transmitter22a_M)->solverInfo);
  }

  /* Integrator: '<S1>/Integrator' */
  if (transmitter22a_DW.Integrator_IWORK != 0) {
    transmitter22a_X.Integrator_CSTATE[0] = 1.0;
    transmitter22a_X.Integrator_CSTATE[1] = -1.0;
    transmitter22a_X.Integrator_CSTATE[2] = -1.0;
  }

  /* Outport: '<Root>/x' incorporates:
   *  Integrator: '<S1>/Integrator'
   */
  transmitter22a_Y.x[0] = transmitter22a_X.Integrator_CSTATE[0];
  transmitter22a_Y.x[1] = transmitter22a_X.Integrator_CSTATE[1];
  transmitter22a_Y.x[2] = transmitter22a_X.Integrator_CSTATE[2];

  /* MATLAB Function: '<S1>/chua' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant3'
   *  Inport: '<Root>/payload'
   *  Integrator: '<S1>/Integrator'
   *  Sum: '<S1>/Sum'
   */
  transmitter22a_B.dxdt[0] = ((transmitter22a_X.Integrator_CSTATE[1] -
    0.2857142857142857 * transmitter22a_X.Integrator_CSTATE[0]) - (std::abs
    (transmitter22a_X.Integrator_CSTATE[0] + 1.0) - std::abs
    (transmitter22a_X.Integrator_CSTATE[0] - 1.0)) * -0.21428571428571427) *
    9.35;
  transmitter22a_B.dxdt[1] = (transmitter22a_X.Integrator_CSTATE[0] -
    transmitter22a_X.Integrator_CSTATE[1]) + transmitter22a_X.Integrator_CSTATE
    [2];
  transmitter22a_B.dxdt[2] = -(transmitter22a_U.payload + 14.35) *
    transmitter22a_X.Integrator_CSTATE[1];
  if (rtmIsMajorTimeStep((&transmitter22a_M))) {
    /* Update for Integrator: '<S1>/Integrator' */
    transmitter22a_DW.Integrator_IWORK = 0;
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&transmitter22a_M))) {
    rt_ertODEUpdateContinuousStates(&(&transmitter22a_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++(&transmitter22a_M)->Timing.clockTick0;
    (&transmitter22a_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&transmitter22a_M)
      ->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      (&transmitter22a_M)->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void transmitter22a::transmitter22a_derivatives()
{
  XDot_transmitter22a_T *_rtXdot;
  _rtXdot = ((XDot_transmitter22a_T *) (&transmitter22a_M)->derivs);

  /* Derivatives for Integrator: '<S1>/Integrator' */
  _rtXdot->Integrator_CSTATE[0] = transmitter22a_B.dxdt[0];
  _rtXdot->Integrator_CSTATE[1] = transmitter22a_B.dxdt[1];
  _rtXdot->Integrator_CSTATE[2] = transmitter22a_B.dxdt[2];
}

/* Model initialize function */
void transmitter22a::initialize()
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&transmitter22a_M)->solverInfo, &(&transmitter22a_M
                          )->Timing.simTimeStep);
    rtsiSetTPtr(&(&transmitter22a_M)->solverInfo, &rtmGetTPtr((&transmitter22a_M)));
    rtsiSetStepSizePtr(&(&transmitter22a_M)->solverInfo, &(&transmitter22a_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&transmitter22a_M)->solverInfo, &(&transmitter22a_M)->derivs);
    rtsiSetContStatesPtr(&(&transmitter22a_M)->solverInfo, (real_T **)
                         &(&transmitter22a_M)->contStates);
    rtsiSetNumContStatesPtr(&(&transmitter22a_M)->solverInfo,
      &(&transmitter22a_M)->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&transmitter22a_M)->solverInfo,
      &(&transmitter22a_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&transmitter22a_M)->solverInfo,
      &(&transmitter22a_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&transmitter22a_M)->solverInfo,
      &(&transmitter22a_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&transmitter22a_M)->solverInfo, (&rtmGetErrorStatus
      ((&transmitter22a_M))));
    rtsiSetRTModelPtr(&(&transmitter22a_M)->solverInfo, (&transmitter22a_M));
  }

  rtsiSetSimTimeStep(&(&transmitter22a_M)->solverInfo, MAJOR_TIME_STEP);
  (&transmitter22a_M)->intgData.y = (&transmitter22a_M)->odeY;
  (&transmitter22a_M)->intgData.f[0] = (&transmitter22a_M)->odeF[0];
  (&transmitter22a_M)->intgData.f[1] = (&transmitter22a_M)->odeF[1];
  (&transmitter22a_M)->intgData.f[2] = (&transmitter22a_M)->odeF[2];
  (&transmitter22a_M)->contStates = ((X_transmitter22a_T *) &transmitter22a_X);
  rtsiSetSolverData(&(&transmitter22a_M)->solverInfo, static_cast<void *>
                    (&(&transmitter22a_M)->intgData));
  rtsiSetIsMinorTimeStepWithModeChange(&(&transmitter22a_M)->solverInfo, false);
  rtsiSetSolverName(&(&transmitter22a_M)->solverInfo,"ode3");
  rtmSetTPtr((&transmitter22a_M), &(&transmitter22a_M)->Timing.tArray[0]);
  (&transmitter22a_M)->Timing.stepSize0 = 0.01;
  rtmSetFirstInitCond((&transmitter22a_M), 1);

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  if (rtmIsFirstInitCond((&transmitter22a_M))) {
    transmitter22a_X.Integrator_CSTATE[0] = 1.0;
    transmitter22a_X.Integrator_CSTATE[1] = -1.0;
    transmitter22a_X.Integrator_CSTATE[2] = -1.0;
  }

  transmitter22a_DW.Integrator_IWORK = 1;

  /* End of InitializeConditions for Integrator: '<S1>/Integrator' */

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond((&transmitter22a_M))) {
    rtmSetFirstInitCond((&transmitter22a_M), 0);
  }
}

/* Model terminate function */
void transmitter22a::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
transmitter22a::transmitter22a() :
  transmitter22a_U(),
  transmitter22a_Y(),
  transmitter22a_B(),
  transmitter22a_DW(),
  transmitter22a_X(),
  transmitter22a_M()
{
  /* Currently there is no constructor body generated.*/
}

/* Destructor */
transmitter22a::~transmitter22a()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_transmitter22a_T * transmitter22a::getRTM()
{
  return (&transmitter22a_M);
}
