#include "scop.h"
#include "scop_math.h"

static void move_forward(t_camera *cam, float speed)
{
    ft_vec3_scale(cam->cameraFront, speed, cam->moveForward);
    ft_vec3_add(cam->cameraPos, cam->moveForward, cam->cameraPos);
}

static void move_backward(t_camera *cam, float speed)
{
    ft_vec3_scale(cam->cameraFront, speed, cam->moveForward);
    ft_vec3_sub(cam->cameraPos, cam->moveForward, cam->cameraPos);
}

static void strafe_right(t_camera *cam, float speed)
{
    glm_cross(cam->cameraFront, cam->cameraUp, cam->moveStrafe);
    ft_vec3_normalize(cam->moveStrafe);
    ft_vec3_scale(cam->moveStrafe, speed, cam->moveStrafe);
    ft_vec3_add(cam->cameraPos, cam->moveStrafe, cam->cameraPos);
}

static void strafe_left(t_camera *cam, float speed)
{
    glm_cross(cam->cameraFront, cam->cameraUp, cam->moveStrafe);
    ft_vec3_normalize(cam->moveStrafe);
    ft_vec3_scale(cam->moveStrafe, speed, cam->moveStrafe);
    ft_vec3_sub(cam->cameraPos, cam->moveStrafe, cam->cameraPos);
}

void	    process_input(GLFWwindow *window, t_camera *cam)
{
	float speed;

    speed = 2.5f * cam->deltaTime;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, TRUE);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	    move_forward(cam, speed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	    move_backward(cam, speed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	    strafe_left(cam, speed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	    strafe_right(cam, speed);
}