// CPE 3103 - FUNDAMENTALS OF MIXED SIGNALS AND SENSORS
// GROUP 1	Mon Wed 10:30AM- 1:30PM LBCEAC2 TC
// Sarcol, Joshua S	BS CPE - 3		2025/11/17
// Midterm Exam

extern double dt;
extern double Inf;

//Do not edit this function.
//This is the function for a unit step
double u(t)
{

  if (t >= 0)
    return 1.0;
  else
    return 0.0;
}

//Do not edit this function.
//This is the function for a unit Impulse 
double d(t)
{

  if (t > -dt && t < dt) 
    return Inf;
  else
    return 0.0;
}


//Edit this function as needed but keep the function prototype
double x(double t)
{
	if (1 <= t && t < 2)
		return -3 * (t - 4/3);			// C DATA TYPES WARNING
	else if (2 <= t && t < 4)			// int/int = int, not float
		return t - 4;					// should be 4.0/3.0 to produce 1.33 as expected
	else if (4 <= t && t < 5)
		return -(t - 3);
	else
		return 0.0;
}


//Edit this function as needed but keep the function prototype
double y(double t)
{
  	if (0 < t && t <= 1)
		return 3*t - 2;
	else if (-2 < t && t <= 0)
		return -t - 2;
	else if (-3 < t && t <= -2)
		return t + 1;
	else
		return 0.0;
}

//Edit this function as needed but keep the function prototype
double z(double t)
{
  return	-2 * u(t+3) + (t+3) * u(t+3)
		+ u(t+2) -2 * (t+2) * u(t+2)
		+ 4 * t * u(t)
		-3 * (t-1) * u(t-1) - u(t-1);
}

//Edit this function as needed but keep the function prototype
double r(double t)
{
  	if (t < 1)
		return 0.0;
	else if (t == 1)					// FLOATING POINT PRECISION WARNING
		return Inf;						// Cannot just use equalities as-is when the data type to be compared are floats
	else if (1 < t && t < 2)			// Use epsilon inequality logic instead:
		return -3.0;					// if abs(t - 1) < dt
	else if (2 <= t && t < 4)
		return 1.0;
	else if (t == 4)
		return -Inf;
	else if (4 < t && t < 5)
		return -1.0;
	else if (t == 5)
		return 2*Inf;
	else if (5 < t)
		return 0.0;
}








