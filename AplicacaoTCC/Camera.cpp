#include "Camera.h"

Camera::~Camera()
{
}

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	this->Position = position;
	this->WorldUp = up;
	this->Yaw = yaw;
	this->Pitch = pitch;
	this->updateCameraVectors();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	this->Position = glm::vec3(posX, posY, posZ);
	this->WorldUp = glm::vec3(upX, upY, upZ);
	this->Yaw = yaw;
	this->Pitch = pitch;
	this->updateCameraVectors();
}

// Retorna a matriz LookAt
glm::mat4 Camera::GetViewMatrix()
{
	//static int delay = 0;
	//if (delay >= 30)
	//{
	//	gotoxy(0, 8);
	//	showMessage("Posição     x " + std::to_string(this->Position.x) + "     y " + std::to_string(this->Position.y) + "     z " + std::to_string(this->Position.z));
	//	gotoxy(0, 9);
	//	showMessage("Posição     x " + std::to_string(this->Position.x + this->Front.x) + "     y " + std::to_string(this->Position.y + this->Front.y) + "     z " + std::to_string(this->Position.z + this->Front.z));
	//	delay = 0;
	//}
	//else
	//{
	//	delay++;
	//}
	return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}

// Executa as chamadas do teclado
void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
	GLfloat velocity = this->MovementSpeed * deltaTime;
	if (direction == FORWARD)
	{
		this->Position += this->Front * velocity;
	}
	if (direction == BACKWARD)
	{
		this->Position -= this->Front * velocity;
	}
	if (direction == LEFT)
	{
		this->Position -= this->Right * velocity;
	}
	if (direction == RIGHT) 
	{
		this->Position += this->Right * velocity;
	}
}

// Executa as chamadas do mouse (motion)
void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
	xoffset *= this->MouseSensitivity;
	yoffset *= this->MouseSensitivity;

	this->Yaw += xoffset;
	this->Pitch += yoffset;
	
	if (constrainPitch)
	{
		if (this->Pitch > 89.0f)
			this->Pitch = 89.0f;
		if (this->Pitch < -89.0f)
			this->Pitch = -89.0f;
	}

	this->updateCameraVectors();
}

// Executa as chamadas do scroll do mouse
void Camera::ProcessMouseScroll(GLfloat yoffset)
{
	yoffset /= 4;
	if (this->Zoom >= 1.0f && this->Zoom <= 45.0f)
		this->Zoom -= yoffset;
	if (this->Zoom <= 1.0f)
		this->Zoom = 1.0f;
	if (this->Zoom >= 45.0f)
		this->Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	front.y = sin(glm::radians(this->Pitch));
	front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	this->Front = glm::normalize(front);

	this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp)); 
	this->Up = glm::normalize(glm::cross(this->Right, this->Front));
}
