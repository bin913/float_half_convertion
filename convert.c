#include <stdio.h>
#include <CL/cl.h>

cl_half float_to_half(float *f)
{
  int hs, he, hm, *ptr;
  short rlt;

  ptr = (int *)f;
  hs = ((*ptr)&0x80000000) >> 16;

  he = ((*ptr)&0x7f800000) >> 23;
  he = he - 0x70;
  he = he << 10;

  hm = ((*ptr)&0x007fffff) >> 13;

  rlt = hs | he | hm;

  return *((cl_half *)&rlt);
}

float half_to_float(cl_half *h)
{
  short *ptr;
  int fs, fe, fm, rlt;

  ptr = (short *)h;

  fs = ((*ptr)&0x8000) << 16;

  fe = ((*ptr)&0x7c00) >> 10;
  fe = fe + 0x70;
  fe = fe << 23;

  fm = ((*ptr)&0x03ff) << 13;

  rlt = fs | fe | fm;
  return *((float *)&rlt);
}

int main(int argc, char **argv)
{
  cl_half h0;
  float f0;

  f0 = 76.2f;
  h0 = float_to_half(&f0);
  f0 = half_to_float(&h0);

  printf("the value %f.\n", f0);
}
