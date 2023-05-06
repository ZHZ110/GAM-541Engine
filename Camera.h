//***************************************************************************************
// Camera.h by Frank Luna (C) 2011 All Rights Reserved.
//   
// Simple first person style camera class that lets the viewer explore the 3D scene.
//   -It keeps track of the camera coordinate system relative to the world space
//    so that the view matrix can be constructed.  
//   -It keeps track of the viewing frustum of the camera so that the projection
//    matrix can be obtained.
//***************************************************************************************

#ifndef CAMERA_H
#define CAMERA_H
#include "pch.h"
namespace dx = DirectX;

class Camera
{
public:
	Camera();
	~Camera();

	void CameraStrafe(dx::XMFLOAT2 move_xy);
	void MoveCameraFrontBack(float front_back_move);

	// Get/Set world camera position.
	dx::XMVECTOR GetPositionXM()const;
	dx::XMFLOAT3 GetPosition()const;
	void SetPosition(float x, float y, float z);
	void SetPosition(const dx::XMFLOAT3& v);
	
	// Get camera basis vectors.
	dx::XMVECTOR GetRightXM()const;
	dx::XMFLOAT3 GetRight()const;
	dx::XMVECTOR GetUpXM()const;
	dx::XMFLOAT3 GetUp()const;
	dx::XMVECTOR GetLookXM()const;
	dx::XMFLOAT3 GetLook()const;

	// Get frustum properties.
	float GetNearZ()const;
	float GetFarZ()const;
	float GetAspect()const;
	float GetFovY()const;
	float GetFovX()const;

	// Get near and far plane dimensions in view space coordinates.
	float GetNearWindowWidth()const;
	float GetNearWindowHeight()const;
	float GetFarWindowWidth()const;
	float GetFarWindowHeight()const;
	
	// Set frustum.
	void SetLens(float fovY, float aspect, float zn, float zf);

	// Define camera space via LookAt parameters.
	void LookAt(dx::FXMVECTOR pos, dx::FXMVECTOR target, dx::FXMVECTOR worldUp);
	void LookAt(const dx::XMFLOAT3& pos, const dx::XMFLOAT3& target, const dx::XMFLOAT3& up);

	// Get View/Proj matrices.
	dx::XMMATRIX View()const;
	dx::XMMATRIX Proj()const;
	dx::XMMATRIX ViewProj()const;

	// Strafe/Walk the camera a distance d.
	void Strafe(float d);
	void Walk(float d);

	// Rotate the camera.
	void Pitch(float angle);
	void RotateY(float angle);

	// After modifying camera position/orientation, call to rebuild the view matrix.
	void UpdateViewMatrix();

private:

	// Camera coordinate system with coordinates relative to world space.
	dx::XMFLOAT3 mPosition;
	dx::XMFLOAT3 mRight;
	dx::XMFLOAT3 mUp;
	dx::XMFLOAT3 mLook;

	// Cache frustum properties.
	float mNearZ;
	float mFarZ;
	float mAspect;
	float mFovY;
	float mNearWindowHeight;
	float mFarWindowHeight;

	// Cache View/Proj matrices.
	dx::XMFLOAT4X4 mView;
	dx::XMFLOAT4X4 mProj;
};

#endif // CAMERA_H