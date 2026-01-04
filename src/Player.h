#pragma once
#include "tools.h"
#include "Camera.h"
#include "AudioEngine.h"


/* Notes & questions for not tired me
* Determine whether its better to just pack the forward vector into the camera state or just calculate when needed
* Should we change the BuildCamera function to permanently just change a single CameraState thats a member?
* 
*/


class Player {

public:
	Player();
	~Player();
	void Move(const float& dt);
	void Spawn();
	void UpdateCamera(); // This should update at the end of our move function
	glm::mat4& GetViewMatrix();
	glm::vec3 GetForwardVector();
	
	float GetFov() { return this->m_fFov; }
private:
	CameraState BuildCamera(); // runs per frame or will eventually get cached for interpolation
	void Jump();
	glm::vec3 m_Position;
	glm::vec3 m_Velocity;
	glm::vec3 m_EyeOffset;
	glm::vec3 m_LocalViewPunch;
	glm::vec3 m_CrouchOffset;
	glm::vec3 m_DeadOffset;
	

	float m_fSpeed;
	float m_fMass;
	float m_fFov;
	bool m_bIsGrounded;

	// player should not own any part of the camera's internals
	Camera m_Camera;
	CameraState m_PlayerCameraState; // should be equal to whatever we do to the camera
};