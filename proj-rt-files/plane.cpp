#include "plane.h"
#include "ray.h"
#include <cfloat>
#include <limits>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
Hit Plane::Intersection(const Ray& ray, int part) const
{
    //TODO;
    Hit h;
    
    double c1 = normal[0] * ray.direction[0] + normal[1] * ray.direction[1] + normal[2] * ray.direction[2];
    double c2 = normal[0] * (ray.endpoint[0] - x1[0]) + normal[1] * (ray.endpoint[1] - x1[1])  + normal[2] * (ray.endpoint[2] - x1[2]);
    h.dist = -c2/c1;
    
    if(h.dist < small_t)
		h.object = nullptr;
	else
		h.object = this;
	h.part = part;
	return h;
}

vec3 Plane::Normal(const vec3& point, int part) const
{
    return normal;
}

// There is not a good answer for the bounding box of an infinite object.
// The safe thing to do is to return a box that contains everything.
Box Plane::Bounding_Box(int part) const
{
    Box b;
    b.hi.fill(std::numeric_limits<double>::max());
    b.lo=-b.hi;
    return b;
}
