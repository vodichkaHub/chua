/*
 * receiver22a.cpp
 *
 * Code generation for model "receiver22a".
 *
 * Model version              : 1.1
 * Simulink Coder version : 9.7 (R2022a) 13-Nov-2021
 * C++ source code generated on : Mon May 27 21:15:03 2024
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#include "receiver22a.h"
#include "rtwtypes.h"
#include "receiver22a_private.h"
#include <cmath>

extern "C" {

#include "rt_nonfinite.h"

}
/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
  void receiver22a::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
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
  int_T nXc { 1 };

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) std::memcpy(y, x,
                     static_cast<uint_T>(nXc)*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  receiver22a_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  receiver22a_derivatives();

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
  receiver22a_derivatives();

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

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = (rtNaN);
  } else {
    real_T tmp;
    real_T tmp_0;
    tmp = std::abs(u0);
    tmp_0 = std::abs(u1);
    if (std::isinf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = (rtNaN);
    } else {
      y = std::pow(u0, u1);
    }
  }

  return y;
}

/* Model step function */
void receiver22a::step()
{
  if (rtmIsMajorTimeStep((&receiver22a_M))) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&(&receiver22a_M)->solverInfo,(((&receiver22a_M)
      ->Timing.clockTick0+1)*(&receiver22a_M)->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&receiver22a_M))) {
    (&receiver22a_M)->Timing.t[0] = rtsiGetT(&(&receiver22a_M)->solverInfo);
  }

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Constant: '<Root>/Constant'
   *  Inport: '<Root>/x'
   *  Integrator: '<S1>/Integrator1'
   */
  receiver22a_B.dvdt = (((-receiver22a_U.x[2] * receiver22a_U.x[1] +
    receiver22a_U.x[0] * receiver22a_U.x[2]) + receiver22a_U.x[2] *
    receiver22a_U.x[2]) * 22.0 + 484.0 * rt_powd_snf(receiver22a_U.x[1], 3.0) *
                        receiver22a_U.x[2]) - receiver22a_U.x[1] *
    receiver22a_U.x[1] * 22.0 * receiver22a_X.Integrator1_CSTATE;

  /* Outport: '<Root>/payload_estimation' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant1'
   *  Inport: '<Root>/x'
   *  Integrator: '<S1>/Integrator1'
   *  MATLAB Function: '<S1>/MATLAB Function'
   *  Sum: '<S1>/Sum'
   */
  receiver22a_Y.payload_estimation = (-22.0 * receiver22a_U.x[1] *
    receiver22a_U.x[2] + receiver22a_X.Integrator1_CSTATE) - 14.35;
  if (rtmIsMajorTimeStep((&receiver22a_M))) {
    rt_ertODEUpdateContinuousStates(&(&receiver22a_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++(&receiver22a_M)->Timing.clockTick0;
    (&receiver22a_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&receiver22a_M)
      ->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      (&receiver22a_M)->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void receiver22a::receiver22a_derivatives()
{
  XDot_receiver22a_T *_rtXdot;
  _rtXdot = ((XDot_receiver22a_T *) (&receiver22a_M)->derivs);

  /* Derivatives for Integrator: '<S1>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = receiver22a_B.dvdt;
}

/* Model initialize function */
void receiver22a::initialize()
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&receiver22a_M)->solverInfo, &(&receiver22a_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&receiver22a_M)->solverInfo, &rtmGetTPtr((&receiver22a_M)));
    rtsiSetStepSizePtr(&(&receiver22a_M)->solverInfo, &(&receiver22a_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&receiver22a_M)->solverInfo, &(&receiver22a_M)->derivs);
    rtsiSetContStatesPtr(&(&receiver22a_M)->solverInfo, (real_T **)
                         &(&receiver22a_M)->contStates);
    rtsiSetNumContStatesPtr(&(&receiver22a_M)->solverInfo, &(&receiver22a_M)
      ->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&receiver22a_M)->solverInfo,
      &(&receiver22a_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&receiver22a_M)->solverInfo,
      &(&receiver22a_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&receiver22a_M)->solverInfo,
      &(&receiver22a_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&receiver22a_M)->solverInfo, (&rtmGetErrorStatus
      ((&receiver22a_M))));
    rtsiSetRTModelPtr(&(&receiver22a_M)->solverInfo, (&receiver22a_M));
  }

  rtsiSetSimTimeStep(&(&receiver22a_M)->solverInfo, MAJOR_TIME_STEP);
  (&receiver22a_M)->intgData.y = (&receiver22a_M)->odeY;
  (&receiver22a_M)->intgData.f[0] = (&receiver22a_M)->odeF[0];
  (&receiver22a_M)->intgData.f[1] = (&receiver22a_M)->odeF[1];
  (&receiver22a_M)->intgData.f[2] = (&receiver22a_M)->odeF[2];
  (&receiver22a_M)->contStates = ((X_receiver22a_T *) &receiver22a_X);
  rtsiSetSolverData(&(&receiver22a_M)->solverInfo, static_cast<void *>
                    (&(&receiver22a_M)->intgData));
  rtsiSetIsMinorTimeStepWithModeChange(&(&receiver22a_M)->solverInfo, false);
  rtsiSetSolverName(&(&receiver22a_M)->solverInfo,"ode3");
  rtmSetTPtr((&receiver22a_M), &(&receiver22a_M)->Timing.tArray[0]);
  (&receiver22a_M)->Timing.stepSize0 = 0.01;

  /* InitializeConditions for Integrator: '<S1>/Integrator1' */
  receiver22a_X.Integrator1_CSTATE = 0.0;
}

/* Model terminate function */
void receiver22a::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
receiver22a::receiver22a() :
  receiver22a_U(),
  receiver22a_Y(),
  receiver22a_B(),
  receiver22a_X(),
  receiver22a_M()
{
  /* Currently there is no constructor body generated.*/
}

/* Destructor */
receiver22a::~receiver22a()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_receiver22a_T * receiver22a::getRTM()
{
  return (&receiver22a_M);
}
