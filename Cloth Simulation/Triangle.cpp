#include "Triangle.h"




using namespace std;



Triangle::Triangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3)
{
	this->point1 = point1;
	this->point2 = point2;
	this->point3 = point3;

	

	// n = normalize ( (p2-p1) Cross (p3-p1) )
	this->normal = glm::normalize(glm::cross( getEdge1(),getEdge2()));

	//d = - n.dot(p1)
	this->d = - glm::dot(this->point1, this->normal);


	

}

glm::vec3 Triangle::getEdge1()
{
	return ( point2 -point1);
}

glm::vec3 Triangle::getEdge2()
{
	return  (point3 -point1);
}

glm::vec3 Triangle::getEdge3()
{
	return point3 - point2;
}



bool Triangle::intersect4(glm::vec3 r1, glm::vec3 r2, glm::vec3 & Q)
{

	//calculate t = - ( n.r1 - d) / n.( r2-r1)

	double eps = std::numeric_limits<double>::epsilon();
	
	glm::vec3 diff = r2 - r1;

	//make sure the denom isnt zero <=> the segment isnt parallel to the plane of the triangle
	float denom = glm::dot(this->normal, diff);

	if (fabs(denom) < eps) {
		return false;
	}


	// find the value of the parameter t at which intersection occured along the segment from r1 to r2 and make sure its between 0 and 1 and then find the intersection point via the t parameter
	float t = -(glm::dot(r1, this->normal) + this->d) / denom;

	if ( !(t >= -5.0f && t <= 1.0f) ) {
		return false;
	}



	Q = r1 + t * diff;

	//calculate the three areas of sub triangles and compare them to the area of the whole triangle

	/*Triangle t1(Q, this->point1, this->point2);
	Triangle t2(Q, this->point1, this->point3);
	Triangle t3(Q, this->point2, this->point3);

	float area_triangle = getArea();

	float area_t1 = t1.getArea();
	float area_t2 = t2.getArea();
	float area_t3 = t3.getArea();

	float sum = area_t1 + area_t2 + area_t3;


	if ( !(fabs(sum - area_triangle) < eps) ) {
		return false;

	}*/


	glm::vec3 n21 = glm::normalize(glm::cross(this->normal, getEdge1()));
	float d21 = -glm::dot(this->point1, n21);

	if (glm::dot(n21, Q) + d21 <= 0) {

		return false;
	}

	glm::vec3 n31 = glm::normalize(glm::cross(this->normal, -getEdge2()));
	float d31 = - glm::dot(this->point3, n31);

	if (glm::dot(n31, Q) + d31 <= 0) {

		return false;
	}

	glm::vec3 n32 = glm::normalize(glm::cross(this->normal, getEdge3()));
	float d32 = -glm::dot(this->point2, n32);

	if (glm::dot(n32, Q) + d32 <= 0) {

		return false;
	}



	/*if (!pointInTriangle(Q)) {

		return false;
	}*/

	return true;
}


void Triangle::update(glm::mat4 transform /*glm::vec3 translate*/)
{
	this->point1 =  transform * glm::vec4(this->point1, 1.0f) ;
	this->point2 =   transform * glm::vec4(this->point2, 1.0f) ;
	this->point3 =  transform  * glm::vec4(this->point3, 1.0f)  ;

	this->d = -glm::dot(this->point1, this->normal);

	/*this->point1 += translate;
	this->point2 += translate;
	this->point3 += translate;
	this->d = -glm::dot(this->point1, this->normal);*/
	//this->normal = glm::normalize(glm::cross(getEdge1(), getEdge2()));

}

void Triangle::scale(float value)
{
	this->point1 = this->point1*value;
	this->point2 = this->point2*value;
	this->point3 = this->point3*value;

	this->d = -glm::dot(this->point1, this->normal);


}

void Triangle::scale(glm::mat4 mat)
{
	this->point1 = mat * glm::vec4(this->point1, 1.0f);
	this->point2 = mat * glm::vec4(this->point2, 1.0f);
	this->point3 = mat * glm::vec4(this->point3, 1.0f);

	this->d = -glm::dot(this->point1, this->normal);


}

bool Triangle::pointInTriangle(glm::vec3 p)
{
	glm::vec3 point1_t = this->point1 - p;
	glm::vec3 point2_t = this->point2 - p;
	glm::vec3 point3_t = this->point3 - p;

	float ab = glm::dot(point1_t, point2_t);
	float ac = glm::dot(point1_t, point3_t);
	float bc = glm::dot(point2_t, point3_t);
	float cc = glm::dot(point3_t, point3_t);

	if ( ( (bc*ac) - (cc*ab) ) < 0.0f) {
		return false;
	}


	float bb = glm::dot(point2_t, point2_t);

	if ( ( (ab *bc) - (ac*bb) ) < 0.0f) {
		return false;
	}

	return true;
}

float Triangle::getArea()
{
	glm::vec3 p2p1 = getEdge1();

	glm::vec3 p3p1 = getEdge2();

	glm::vec3 cross = glm::cross(p2p1, p3p1);

	return (0.5f * glm::length(cross) );
	
}




