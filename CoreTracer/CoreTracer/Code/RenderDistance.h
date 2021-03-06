#pragma once

#include "RenderObject.h"

class DDistFunc;

class DRenderDistance : public DRenderObject
{
public:
	DRenderDistance() : mMinimumDistance(0.001f), mDEScale(1.f), mDEOffset(0.0f,0.f,0.f), mDEIterations(200), mDEExtents(1.f,1.f,1.f), mStepSize(0.7f)	
	{
		mAABoundingBox = DAABoundingBox(mCentre, mDEExtents[0]*mScale[0], mDEExtents[1]*mScale[1], mDEExtents[2]*mScale[2]);
		mAABoundingBox.TransformBy(mRotation);
	}

	virtual DRenderObject* InternalClone()
	{
		DRenderDistance* ret = new DRenderDistance();
		return ret;
	}
	virtual void PostLoad()
	{
		mAABoundingBox = DAABoundingBox(mCentre, mDEExtents[0]*mScale[0], mDEExtents[1]*mScale[1], mDEExtents[2]*mScale[2]);
		mAABoundingBox.TransformBy(mRotation);
	}
	virtual float DistanceEstimator(const DVector3& pos) const;

protected:
	virtual bool InternalIntersect(const DRayContext& rRayContext, DCollisionResponse& out_Response) const;
	virtual void InternalRead(TiXmlElement* element);
	virtual bool InternalContains(const DVector3& position) const;
	virtual DColour DEColour(const DVector3& pos) const {return DColour(1,1,1);}

	float mMinimumDistance;	
	float mDEScale;
	DVector3 mDEOffset;
	int mDEIterations;
	DVector3 mDEExtents;
	float mStepSize;

private:
	bool GetCollisionPoint(const DRayContext& rRayContext, DVector3 &out_Point, const DVector3& start, const DVector3& end, const DVector3& direction) const;
	bool GetBackfaceCollisionPoint(const DRayContext& rRayContext, DVector3 &out_Point, const DVector3& start, const DVector3& end, const DVector3& direction) const;
	DVector3 GetNormal(const DVector3& position, const DVector3& direction, const float minimumDistance) const;
	void Nudge(DVector3& out_Position, const DVector3& normal, const float minimumDistance) const;
	void DeNudge(DVector3& out_Position, const DVector3& normal, const float minimumDistance) const;

	DProgram mDistanceProgram;
};
