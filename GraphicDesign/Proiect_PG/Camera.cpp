#include "Camera.hpp"

namespace gps {

    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        //TODO
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraUpDirection = cameraUp;
        
    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        //TODO

        return glm::lookAt(cameraPosition, cameraTarget, this->cameraUpDirection);
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {
        //TODO
        glm::vec3 cameraFront = glm::normalize(cameraTarget - cameraPosition);
        glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUpDirection, cameraFront));
        glm::vec3 cameraUp = glm::cross(cameraFront, cameraRight);
        // Move the camera based on the specified direction
        switch (direction) {
        case MOVE_FORWARD:
            cameraPosition += cameraFront * speed;
            cameraTarget += cameraFront * speed;
            break;
        case MOVE_BACKWARD:
            cameraPosition -= cameraFront * speed;
            cameraTarget -= cameraFront * speed;
            break;
        case MOVE_LEFT:
            cameraPosition += cameraRight * speed;
            cameraTarget += cameraRight * speed;
            break;
        case MOVE_RIGHT:
            cameraPosition -= cameraRight * speed;
            cameraTarget -= cameraRight * speed;
            break;
        case MOVE_UP:
            cameraPosition += cameraUp * speed;
            cameraTarget += cameraUp * speed;
            break;
        case MOVE_DOWN:
            cameraPosition -= cameraUp * speed;
            cameraTarget -= cameraUp * speed;
            break;
        
        }
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw) {
        //TODO
        glm::vec3 cameraFront = glm::normalize(cameraTarget - cameraPosition);

        // Update yaw (around y-axis)
        glm::mat4 yawRotation = glm::rotate(glm::mat4(1.0f), glm::radians(yaw), cameraUpDirection);
        glm::mat3 yawRotationMatrix = glm::mat3(yawRotation);
        cameraFront = glm::normalize(yawRotationMatrix * cameraFront);

        // Update pitch (around x-axis)
        glm::vec3 rightAxis = glm::normalize(glm::cross(cameraFront, cameraUpDirection));
        glm::mat4 pitchRotation = glm::rotate(glm::mat4(1.0f), glm::radians(pitch), rightAxis);
        glm::mat3 pitchRotationMatrix = glm::mat3(pitchRotation);
        cameraFront = glm::normalize(pitchRotationMatrix * cameraFront);

        cameraTarget = cameraPosition + cameraFront;
    }
}
