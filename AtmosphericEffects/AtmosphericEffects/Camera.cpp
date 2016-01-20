#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>

void Camera::create(vec3 t, float r, vec3 c, float y, float p)
{
	speed = Speed;
	moveSensitivity = MoveSensitivity;
	scrollSensitivity = ScrollSensitivity;
	zoom = 1.0f;
	target = t;
	radius = r;
	center = c;
	yaw = y;
	pitch = p;

	calculate();
	toggled = false;
}

void Camera::onEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		lastX = event.mouseButton.x;
		lastY = event.mouseButton.y;

		// std::cout << lastX << ", " << lastY << std::endl;

		toggled = true;
	}
	if (event.type == sf::Event::MouseButtonReleased)
	{
		lastX = event.mouseButton.x;
		lastY = event.mouseButton.y;

		toggled = false;
	}
	if (event.type == sf::Event::MouseMoved)
	{
		float mx = event.mouseMove.x;
		float my = event.mouseMove.y;

		if (toggled)
		{
			onMouseMove(lastX - mx, lastY - my);
			// std::cout << "Mouse Move" << std::endl;
		}

		lastX = mx;
		lastY = my;
	}
	if (event.type == sf::Event::MouseWheelScrolled)
	{
		onMouseWheel(event.mouseWheelScroll.delta);
	}
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::W:
			center.y += 0.1f;
			break;
		case sf::Keyboard::S:
			center.y -= 0.1f;
			break;
		case sf::Keyboard::A:
			center.x -= 0.1f;
			break;
		case sf::Keyboard::D:
			center.x += 0.1f;
			break;
		}

		calculate();
	}
}

mat4 Camera::getView()
{
	return glm::lookAt(position + center, target + center, up);
}

void Camera::onMouseMove(int xoffset, int yoffset)
{
	yaw += moveSensitivity * (float)xoffset;
	pitch += moveSensitivity * (float)yoffset;

	glm::clamp(pitch, -glm::half_pi<float>(), glm::half_pi<float>());

	calculate();
}

void Camera::onMouseWheel(float delta)
{
	zoom += scrollSensitivity * delta;

	calculate();
}

void Camera::calculate()
{
	position.x = (zoom * radius) * cos(pitch) * sin(yaw);
	position.y = (zoom * radius) * sin(pitch);
	position.z = (zoom * radius) * cos(pitch) * cos(yaw);

	vec3 front = normalize(position - target);

	vec3 right = normalize(cross(front, vec3(0.0f, 1.0f, 0.0f)));
	up = normalize(cross(right, front));
}