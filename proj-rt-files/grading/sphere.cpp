#include "sphere.h"
#include "ray.h"

//quadratic function that returns smaller of roots, or -1 if it doesn't exist
double Sphere::minQuadratic(double a, double b, double c) const {
	if(pow(b,2) - 4*a*c < 0)
		return -1;
	double ans = (-b - sqrt(pow(b,2) - 4*a*c)) / (2*a);
	double ans2 = (-b + sqrt(pow(b,2) - 4*a*c)) / (2*a);
	if(ans < small_t && ans2 < small_t)
		return -1;
	return ans < small_t ? ans2 : ans;
	
}

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
	//TODO
	Hit h;
    double a = pow(ray.direction[0], 2) + pow(ray.direction[1], 2) + pow(ray.direction[2], 2);
    double b = 2*ray.direction[0]*(ray.endpoint[0] - center[0]) + 2*ray.direction[1]*(ray.endpoint[1] - center[1]) + 2*ray.direction[2]*(ray.endpoint[2] - center[2]);
    double c = pow(ray.endpoint[0] - center[0], 2) + pow(ray.endpoint[1] - center[1], 2) + pow(ray.endpoint[2] - center[2], 2) - pow(radius, 2);
    h.dist = minQuadratic(a,b,c);
    if(h.dist < small_t)
		h.object = nullptr;
	else
		h.object = this;
	//h.part = part; //idk
	return h;
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    //TODO; // compute the normal direction
    normal = point - center;
    return normal.normalized();
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
