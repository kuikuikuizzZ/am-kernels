#include "trap.h"

#define N 10
int a[N];

int b[] = {-2147483648,-2147483647}; 
 

int main() {
  int i, j;
  for(i = 0; i < N; i ++)
    a[i] = i;
  for(i = 0; i < N; i ++)
    for(j = 1; j < N + 1; j ++)
      a[i] *= j;
  for(i = 0; i < N; i ++)
    for(j = 1; j < N + 1; j ++)
      a[i] /= j;

  for(i = 0; i < N; i ++)
    check(a[i] == i);

  check(b[0]/b[1]==1 );
  check(b[1]/b[0]==0 );
  return 0;
}
