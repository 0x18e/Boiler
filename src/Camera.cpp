#include "Camera.h"

//float Camera::m_CameraSpeed = 5.0f; // maybe fast or slow i think depends on dt
//glm::vec3 Camera::m_CameraVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
//

//TODO: take care of other variables that are unused here

Camera::Camera() {
	// view matrix HAS to be initialized, ALWAYS
	this->m_ViewMatrix = glm::mat4(1.0f);
	this->m_CameraSpeed = 0.05f; // will change according to dt
	this->m_UpAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	/*
	// Constructor
	this->m_ViewMatrix = glm::mat4(1.0f);
	this->m_CameraVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	// SELF NOTE: will be removed later on
	// You may be asking, why would the m_position vector have a z component of 3 instead of -3?
	// When the lookat function is used from glm it generates a transform matrix that translates in the opposite
	// direction of m_position. essentially shifting the whole world rather than actually moving the camera
	this->m_CameraSpeed = 0.05f; // will change according to dt

	
	this->m_UpAxis = glm::vec3(0.0f, 1.0f, 0.0f);

	// -1 for now cause we dont rotate, our front will always be front
	this->m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	*/
}

float Camera::GetSensitivity() {
	return this->m_CameraSpeed;
}

glm::mat4& Camera::GetViewMatrix() {
	return this->m_ViewMatrix; // Should return the view matrix as a reference to be modified
}

glm::vec3& Camera::GetFront() {
	return this->m_CameraFront;
}
glm::vec3& Camera::GetUpAxis() {
	return this->m_UpAxis;
}

// Take reference to player position and make that our position
void Camera::Update(CameraState new_state) {
	this->m_PreviousState = this->m_CurrentState;
	this->m_CurrentState = new_state;

	// Handle camera input here
	// This might change
	if (InputHandler::Get().IsPressed(GLFW_KEY_ESCAPE)) {
		WindowHandler::Get().ShowCursor(true);
	}
	if (InputHandler::Get().IsPressed(GLFW_KEY_F1)) {
		WindowHandler::Get().ShowCursor(false);
	}
	
	
	
	/*
	* this is interesting.... maybe do it this way later but account for the direction as well.
	m_Position = playerPosition + state.baseEyeOffset + state.viewPunchOffset + state.deathOffset + state.externalOffset;

    m_ViewMatrix = glm::lookAt(m_Position, playerPosition + state.viewPunchOffset, glm::vec3(0, 1, 0));
	*/


	// first argument is the camera position
	
	this->m_ViewMatrix = glm::lookAt(this->m_CurrentState.position, this->m_CurrentState.position + this->m_CurrentState.forward, this->m_UpAxis);
	//LOGVEC(m_CurrentState.position.x, m_CurrentState.position.y, m_CurrentState.position.z, "m_Position");
}

Camera::~Camera() {

}

void Camera::SetCameraPosition(const glm::vec3& position) {
	this->m_CameraPosition = position;
}

void Camera::SetCameraVelocity(const glm::vec3& velocity) {
	this->m_CameraVelocity = velocity;
}

void Camera::SetCameraSpeed(const float& speed) {
	this->m_CameraSpeed = speed;
}


