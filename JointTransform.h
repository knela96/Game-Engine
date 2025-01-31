#ifndef JOINTTRANSFORM_H_
#define JOINTTRANSFORM_H_


#include "Globals.h"
#include "Application.h"


class JointTransform
{
public:
	JointTransform() {};
	JointTransform(vec3 Position_, Quat Rotation_,vec3 Scale_) :Position(Position_), Rotation(Rotation_),Scale(Scale_) {};
	~JointTransform() {};

	vec3 Position ;
	Quat Rotation;
	vec3 Scale;

public:

	mat4x4 GetLocalTransform();

	JointTransform Interpolate(JointTransform* PointA, JointTransform* PointB, float Progression);
	vec3 Interpolate(vec3 start, vec3 end, float progression);
	Quat Interpolate(Quat qa, Quat qb, float blend);
};

#endif


