#pragma once

#include "math.hpp"

t_mat4  lookAt(t_vec3  const & eye, t_vec3  const & center, t_vec3  const & up);
double	degree_to_radian(double degree_angle);

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  10.5f;
const float SENSITIVITY =  0.03f;
const float FOV        =  45.0f;


class Camera
{
public:
    t_vec3 Position;
    t_vec3 Front;
    t_vec3 Up;
    t_vec3 Right;
    t_vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Fov;

    Camera(t_vec3 position = create_vec3(0.0f, 0.0f, 0.0f), t_vec3 up = create_vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(create_vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Fov(FOV)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    t_mat4 GetViewMatrix()
    {
        return lookAt(Position, vec3_add(Position, Front), Up);
    }

    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position = vec3_add(Position, vec3_mul(Front, velocity));
        if (direction == BACKWARD)
            Position = vec3_sub(Position, vec3_mul(Front, velocity));
        if (direction == LEFT)
            Position = vec3_sub(Position, vec3_mul(Right, velocity));
        if (direction == RIGHT)
            Position = vec3_add(Position, vec3_mul(Right, velocity));
    }

    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        updateCameraVectors();
    }

    void ProcessMouseScroll(float yoffset)
    {
        Fov -= (float)yoffset;
        if (Fov < 1.0f)
            Fov = 1.0f;
        if (Fov > 45.0f)
            Fov = 45.0f; 
    }

private:
    void updateCameraVectors()
    {
        t_vec3 front;
        front.x = cos(degree_to_radian(Yaw)) * cos(degree_to_radian(Pitch));
        front.y = sin(degree_to_radian(Pitch));
        front.z = sin(degree_to_radian(Yaw)) * cos(degree_to_radian(Pitch));
        Front = my_normalize(front);

        Right = my_normalize(my_cross(Front, WorldUp));
        Up    = my_normalize(my_cross(Right, Front));
    }
};
