#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
	//TODO; //determine the color
    vec3 color, colorA, colorD, colorS;
    //ambient
    colorA = this->world.ambient_color * this->world.ambient_intensity * color_ambient;
    //end ambient
    
    for(unsigned i = 0; i < this->world.lights.size(); i++) {
		vec3 l = this->world.lights[i]->position - intersection_point;
		vec3 LS = this->world.lights[i]->Emitted_Light(l);
		
		if(world.enable_shadows) { //shadows begin
			Ray shadow;
			shadow.endpoint = intersection_point;
			shadow.direction = l.normalized();
			Hit h = this->world.Closest_Intersection(shadow);
			if(h.object && h.dist < l.magnitude())
				continue;
		} //shadows end
		
		//LS /= (l).magnitude_squared(); //decay?
		l = l.normalized();	
		//normal.normalized();
		
		//Diffuse
		double d_intensity = 0;
		if(dot(normal,l) > 0)
			d_intensity = dot(normal,l);
		colorD += color_diffuse*LS*d_intensity;
		//end diffuse	
		
		//Specular
		vec3 r = l - 2*dot(l, normal)*normal;
		r = r.normalized();
		vec3 c = intersection_point - ray.endpoint;
		c = c.normalized();
		double s_intensity = 0;
		if(dot(r,c) > 0)
			s_intensity = pow(dot(r,c), specular_power);
		colorS += color_specular*LS*s_intensity;	
		//end Specular
		
	}
    
    color = colorA + colorD + colorS;
    return color;
}
