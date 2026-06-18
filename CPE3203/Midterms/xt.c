#include <math.h>


double u(double t)
{

  return (t >= 0 ? 1 : 0);

}


double x(double t){
	if (-3.0 <= t && t <= -2.0)
		return t + 3.0;
	else if (0.0 <= t && t <= 1.0)
		return -3.0;
	else if (3.0 <= t && t <= 4.0)
		return (-2.0 * t) + 8.0;
	else
		return 0;
}

