#include <cmath>
#include <iostream>

#include "Sphere.h"
#include "Util.h"

float Sphere::intersectionPoint(Ray ray) {
	Vector3 oc = ray.origin - this->centre;
	float a = ray.direction.dot(ray.direction);
	float b = 2 * ray.direction.dot(oc);
	float c = oc.dot(oc) - (this->radius * this->radius);

	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0) {
		// ray does not hit the sphere
		return NAN;
	} else {
		return (-b - sqrt(discriminant)) / (2 * a);
	}
}

Colour Sphere::calculateShading(Vector3 lightPos, Colour lightColour, Ray ray, float t) {
	// calculate the point on the sphere's surface
	Vector3 pointOnSurface = ray.origin + (ray.direction * t);

	// calculate the surface normal for the sphere
	Vector3 surfaceNormal = pointOnSurface - this->centre;
	surfaceNormal.normalize();

	// calculate the light path vector
	Vector3 lightPathVector = lightPos - pointOnSurface;
	lightPathVector.normalize();

	// calculate the eye path vector
	Vector3 eyePathVector = ray.origin - pointOnSurface;
	eyePathVector.normalize();

	// calculate the diffuse contribution using the Lambertian model
	float diffuseCoefficient = clamp(surfaceNormal.dot(lightPathVector));
	Colour diffuseColour = this->material.colour * diffuseCoefficient;

	// calculate the light reflection vector
	Vector3 lightReflectionVector = lightPathVector + surfaceNormal * -2 * surfaceNormal.dot(lightPathVector);
	lightReflectionVector.normalize();
	Vector3 r = lightPathVector - (surfaceNormal * (2 * surfaceNormal.dot(lightPathVector)));

	// calculate the specular contribution using the Blinn-Phong model
	Vector3 h = lightPathVector + eyePathVector;
	h.normalize();
	float z = max(0, h.dot(surfaceNormal));
	float specFactor = (8 + this->material.shininess) / (8 * PI);
	Colour specularColour = lightColour * this->material.specularCoefficient * specFactor * pow(z, this->material.shininess);

	// calculate the ambient colour
	Colour ambientColour = this->material.colour * ambientCoefficient;

	// combine specular, diffuse, and ambient lighting contributions
	return ambientColour + diffuseColour + specularColour;
}
