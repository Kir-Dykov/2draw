#pragma once

//returns number that is on margin of double precision to number d
//that is, d+=epsilon(d) changes actual value of d, but d+=0.5*epsilon(d) already doesn't
//if number is too close to zero, (such that it's precision limit 
//cannot be expessed using doubles), functions returns the smalest positive double
double epsilon(const double& d);