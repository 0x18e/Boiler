#pragma once
#include<glm/vec3.hpp>
#include<glm/mat3x3.hpp>
#include<glm/ext/matrix_transform.hpp>
#include "InputHandler.h"
#include "WindowHandler.h"


struct CameraState {
	float fov;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 viewPunchAngles;
	glm::vec3 eyeOffset;
};

class Camera {

public:
	Camera();
	~Camera();
	void SetCameraPosition(const glm::vec3& position);
	void SetCameraVelocity(const glm::vec3& velocity);
	void SetCameraSpeed(const float& speed);
	glm::mat4& GetViewMatrix();
	glm::vec3& GetFront();
	glm::vec3& GetUpAxis();
	void Update(CameraState new_state);
	float GetSensitivity();
	
private:

	// Interpolation activities
	CameraState m_PreviousState;
	CameraState m_CurrentState;

	// Camera class
	// A lot of these static variables are actually very stupid, no need to have them as static.
	float m_CameraSpeed;
	glm::vec3 m_CameraVelocity; // Might just need to be changed or removed depending on how i want the camera

	// 3 important variables
	// 1. camera's position
	glm::vec3 m_CameraPosition;
	// 2. the up axis relative to the camera
	glm::vec3 m_UpAxis;
	// 3. the direction vector we want to face, this would be what we're looking at i think.
	glm::vec3 m_CameraFront; // maybe a better name?

	glm::vec3 m_ViewPunchAngles;

	// need a view matrix
	glm::mat4 m_ViewMatrix;
};

