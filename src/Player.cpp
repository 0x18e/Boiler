#include "Player.h"



Player::Player() {
	this->Spawn();
}
Player::~Player() {

}
void Player::Spawn() {
	this->m_fFov = 75.0f;
	this->m_fMass = 49.0f;
	this->m_fSpeed = 15.0f;
	this->m_Position = glm::vec3(0.0f, 0.0f, 3.0f);
	this->m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_bIsGrounded = true;
}

//TODO work on player movement, aceleration, velocity, position gets updated, so does camera position as well.
void Player::Move(const float& dt) {
	glm::vec3 flatForward = glm::vec3(
		m_PlayerCameraState.forward.x,
		0.0f,
		m_PlayerCameraState.forward.z
	);
	// as bad as this is i want to keep it at a point where i can just delete it all later.
	if (InputHandler::Get().IsPressed(GLFW_KEY_W)) {
		// move forward
		//this->m_CameraPosition += this->m_CameraSpeed * m_CameraFront;
		this->m_Velocity += m_fSpeed * glm::normalize(flatForward);
		//this->m_Velocity += this->m_fSpeed * this->m_PlayerCameraState.forward;
	}
	if (InputHandler::Get().IsPressed(GLFW_KEY_S)) {
		//move backwards without having to ascend when looking down and walking backwards
		
		this->m_Velocity -= this->m_fSpeed * glm::normalize(flatForward);//this->m_PlayerCameraState.forward;
	}
	if (InputHandler::Get().IsPressed(GLFW_KEY_D)) {
		// move right
		this->m_Velocity += glm::normalize(
			glm::cross(this->m_PlayerCameraState.forward, this->m_Camera.GetUpAxis())) * this->m_fSpeed;
	}
	if (InputHandler::Get().IsPressed(GLFW_KEY_A)) {
		// move back
		this->m_Velocity -= glm::normalize(
			glm::cross(this->m_PlayerCameraState.forward, this->m_Camera.GetUpAxis())) * this->m_fSpeed;
	}

	if (InputHandler::Get().IsPressed(GLFW_KEY_SPACE)) {
		// go up
		// impact velocity!!
		this->Jump();
	}

	if (InputHandler::Get().IsPressed(GLFW_KEY_F)) {
		
		if (this->m_fFov <= 24.0f) {
			this->m_fFov = 24.0f;
		}
		else {
			this->m_fFov -= 0.9f;
		}
	}
	else {
		if (this->m_fFov >= 75.0f) {
			this->m_fFov = 75.0f;
		}
		else {
			this->m_fFov += 0.9f;
		}
	}
	
	if (InputHandler::Get().IsPressed(GLFW_KEY_R)) {
		//AudioHandler::Get().PlaySound("wpn_hudoff");
	}

	/*
	if (InputHandler::Get().IsPressed(GLFW_KEY_LEFT_CONTROL)) {
		// go down
		this->m_CameraPosition.y -= m_CameraSpeed;
	}
	*/
	//this->m_CameraPosition.y = 0.0f;
	const float gravity = 9.81f; 
	// Apply gravity if not grounded
	if (!m_bIsGrounded) {
		m_Velocity.y -= gravity;
		LOG(m_Velocity.y);
	}
	this->m_Position += m_Velocity * dt;
	if (m_Position.y <= 0.0f) {
		m_Position.y = 0.0f;
		m_Velocity.y = 0.0f;
		m_bIsGrounded = true;
	}
	// friction
	m_Velocity.x *= this->m_fFrictionConstant * dt;
	m_Velocity.z *= this->m_fFrictionConstant * dt;

}
void Player::Jump() {
	// this should be an impulse jump
	m_bIsGrounded = false;
	this->m_Velocity.y = 30.0f;
	
}
void Player::PlayerBoundaryCheck(){
    if (this->m_Position.x > 50.0f){
        this->m_Position.x = 49.0f;
    }else if (this->m_Position.x < -50.0f){
        this->m_Position.x = -49.0f;
    }
    if (this->m_Position.z > 50.0f){
        this->m_Position.z = 49.0f;
    } else if (this->m_Position.z < -50.0f){
        this->m_Position.z = -50.0f;
    }
}
glm::vec3 Player::GetPlayerPos(){
    return this->m_Position;
}
void Player::UpdateCamera() {
	// Maybe pass in our change in position as reference to update?
	this->m_Camera.Update(this->BuildCamera());
}

glm::mat4& Player::GetViewMatrix() {
	return this->m_Camera.GetViewMatrix();
}

glm::vec3 Player::GetForwardVector() {
	glm::vec3 direction;
	// Rotation input would be here.
	direction.x = cos(glm::radians(InputHandler::Get().GetYaw())) * cos(glm::radians(InputHandler::Get().GetPitch()));
	direction.y = sin(glm::radians(InputHandler::Get().GetPitch()));
	direction.z = sin(glm::radians(InputHandler::Get().GetYaw())) * cos(glm::radians(InputHandler::Get().GetPitch()));
	return glm::normalize(direction);
}
CameraState Player::BuildCamera() {
	CameraState state;
	state.eyeOffset = glm::vec3(0.0f, 1.5f, 0.0f);
	state.fov = this->m_fFov;
	state.position = this->m_Position; // maybe add eyeOffset to this?
	state.viewPunchAngles = this->m_LocalViewPunch;
	state.forward = this->GetForwardVector();
	this->m_PlayerCameraState = state;
	return this->m_PlayerCameraState;
}
