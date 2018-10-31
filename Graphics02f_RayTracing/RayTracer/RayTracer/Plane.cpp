#include <cmath>
#include <iostream>

#include "Plane.h"
#include "Util.h"

float Plane::intersectionPoint(Ray ray) {
	float denominator = ray.direction.dot(this->surfaceNormal);
	if (abs(denominator) > 0.00001f) {
		Vector3 oc = this->origin - ray.origin;
		float numerator = oc.dot(this->surfaceNormal);
		/*
		if (numerator < 0.0f) {
			//std::cout << "numerator is negative" << std::endl;
		}
		if (denominator < 0.0f) {
			//std::cout << "denominator is negative" << std::endl;
		}
		*/
		return numerator / denominator;
	} else {
		std::cout << "basically a zero denominator (i.e. parallel to the plane)" << std::endl;
		return -1.0f;
	}
}

Colour Plane::calculateShading(Vector3 lightPos, Colour lightColour, Ray ray, float t) {
	//return COLOUR_CYAN;

	// calculate the point on the plane's surface
	Vector3 pointOnSurface = ray.origin + (ray.direction * t);

	// calculate the light path vector
	Vector3 lightPathVector = lightPos - pointOnSurface;

	// calculate the surface normal for the plane
	Vector3 surfaceNormal = this->surfaceNormal;
	surfaceNormal.normalize();

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
