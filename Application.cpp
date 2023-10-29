#include "Application.h"

Application* Application::instance = nullptr;
Application* Application::getInstance() {
	if (!instance) {
		instance = new Application();
	}
	return instance;
}
Application::Application() {
}

void Application::identifyObject()
{
	GLbyte color[4];
	GLfloat depth;

	GLint x = (GLint)this->mouseX;
	GLint y = (GLint)this->mouseY;

	int newy = this->height - y;

	glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &this->selectedObjectIndex);

	printf("Clicked on pixel %d, %d, color %02hhx %02hhx %02hhx %02hhx, depth %f, stencil index %u \n"
		, x, y, color[0], color[1], color[2], color[3], depth, this->selectedObjectIndex);
}

void Application::pushObject()
{
	if (this->selectedObjectIndex == 0)
		return;

	GLint x = (GLint)this->mouseX;
	GLint y = (GLint)this->mouseY;
	int newy = this->height - y;
	GLfloat depth;

	glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

	glm::vec3 screenX = glm::vec3(x, newy, depth);
	glm::mat4 view = this->mainScene->camera->getCamera();
	glm::vec4 viewPort = glm::vec4(0, 0, this->width, this->height);
	glm::vec3 pos = glm::unProject(screenX, view, this->mainScene->camera->getProjectionMatrix(), viewPort);
	Object* o = new Object(*this->mainScene->objects[this->mainScene->objectIndex(this->selectedObjectIndex)]);
	o->setPos(pos);
	this->mainScene->objects.push_back(o);
}
void Application::cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY) {
	printf("cursor_pos_callback %d, %d;\n", (int)mouseX, (int)mouseY);
	this->mainScene->camera->setMousePos((int)mouseX, (int)mouseY);
	this->mouseX = (int)mouseX;
	this->mouseY = (int)mouseY;
}

void Application::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

	if (key == GLFW_KEY_W && action == GLFW_PRESS) this->mainScene->camera->setFrontMoveState(1);
	if (key == GLFW_KEY_S && action == GLFW_PRESS) this->mainScene->camera->setFrontMoveState(-1);
	if (key == GLFW_KEY_A && action == GLFW_PRESS) this->mainScene->camera->setSideMoveState(1);
	if (key == GLFW_KEY_D && action == GLFW_PRESS) this->mainScene->camera->setSideMoveState(-1);

	if (key == GLFW_KEY_W && action == GLFW_RELEASE) this->mainScene->camera->setFrontMoveState(0);
	if (key == GLFW_KEY_S && action == GLFW_RELEASE) this->mainScene->camera->setFrontMoveState(0);
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) this->mainScene->camera->setSideMoveState(0);
	if (key == GLFW_KEY_D && action == GLFW_RELEASE) this->mainScene->camera->setSideMoveState(0);

}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
	//if (button == GLFW_MOUSE_BUTTON_LEFT) 
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		this->mainScene->camera->setMouseMoveState(true);
		this->identifyObject();
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) this->mainScene->camera->setMouseMoveState(false);

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) this->pushObject();
}

void Application::window_focus_callback(GLFWwindow* window, int focused) {
	printf("window_focus_callback \n");
}

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::window_iconify_callback(GLFWwindow* window, int iconified) {
	printf("window_iconify_callback \n");
}

void Application::error_callback(int error, const char* description) {
	fputs(description, stderr);
}
void Application::run()
{
	GLFWwindow* window;
	glfwSetErrorCallback([](int error, const char* description) -> void {instance->error_callback(error, description); });
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(640, 480, "TEM0017", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	glewInit();
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		-> void {instance->KeyCallback(window, key, scancode, action, mods); });

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos, double mouseYPos)
		-> void {instance->cursor_pos_callback(window, mouseXPos, mouseYPos); });

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mode)
		-> void {instance->button_callback(window, button, action, mode); });

	glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused)
		-> void {instance->window_focus_callback(window, focused); });

	glfwSetWindowIconifyCallback(window, [](GLFWwindow* window, int iconified)
		-> void {instance->window_iconify_callback(window, iconified); });

	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		-> void {instance->window_size_callback(window, width, height); });

	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	glfwGetFramebufferSize(window, &this->width, &this->height);
	float ratio = this->width / (float)this->height;
	glViewport(0, 0, this->width, this->height);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	Scene::Builder sceneBuilder;
	
	sceneBuilder.addObject("sphere", "phong");
	sceneBuilder.addObject("tree", "phong");
	
	
	sceneBuilder.addCamera(glm::vec3(-5.f, 20.f, 20.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.0f, 0.0f));

	//sceneBuilder.addPointLight(glm::vec3(0.f, 8.f, 0.f), glm::vec3(1.f, 1.f, 1.f));
	//sceneBuilder.addDirLight(glm::vec3(-3.f, -10.f, -1.f), glm::vec3(1.f, 1.f, 1.f));
	sceneBuilder.addDirLight(glm::vec3(5.f, -20.f, -5.f), glm::vec3(1.f, 1.f, 1.f));
	// Šptaný lightDir!!
	sceneBuilder.addSpotLight(glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 1.f, 0.f), glm::vec3(1.f, 1.f, 1.f), glm::radians(45.0f));

	this->mainScene = sceneBuilder.build();

	for (int i = 0; i < this->mainScene->lights.size(); i++) {
		this->mainScene->lights[i]->addLightObserver(&ShaderManager::getInstance()->getShader("phong"));

	}

	for (int i = 0; i < this->mainScene->lights.size(); i++) {
		this->mainScene->lights[i]->notifyLightObservers();
	}

	//this->mainScene->camera->addCameraObserver(&ShaderManager::getInstance()->getShader("constant"));
	//this->mainScene->camera->addCameraObserver(&ShaderManager::getInstance()->getShader("lambert"));
	this->mainScene->camera->addCameraObserver(&ShaderManager::getInstance()->getShader("phong"));
	
	this->mainScene->camera->notifyCameraObservers();
	this->mainScene->objects[0]->addCircleMove(glm::vec3(1.f, 0.f, 0.f),2);
	//this->mainScene->objects[0]->translate(glm::vec3(1.f, 0.f, 0.f));
	//this->mainScene->objects[0]->rotate(-M_PI_2, glm::vec3(1.f, 0.f, 0.f));
	//this->mainScene->objects[0]->scale(glm::vec3(0.5f, 0.5f, 0.5f));
	//this->mainScene->objects[0]->translate(glm::vec3(10.f, 5.f, 50.f));
	//this->mainScene->objects[0]->scale(glm::vec3(3.f, 3.f, 3.f));
	//this->mainScene->objects[0]->rotate(M_PI_2, glm::vec3(0.f, 1.f, 0.f));
	//this->mainScene->objects[1]->translate(glm::vec3(13.f, 4.35f, -12.f));
	//this->mainScene->objects[2]->translate(glm::vec3(1.f, 2.f, 0.f));
	//this->mainScene->objects[3]->translate(glm::vec3(0.f, 8.f, 6.f));

	//this->mainScene->objects[3]->addCircleMove(glm::vec3(0.f, 20.f, -30.f), 15);
	//this->mainScene->objects[4]->addLineMove(glm::vec3(2.f, 12.f, 0.f), glm::vec3(2.f, 12.f, -80.f));
	//this->mainScene->objects[1]->setColor(glm::vec3(1.0, 0.0, 0.0));

	//this->mainScene->objects[5]->translate(glm::vec3(0.f, 7.5f, 0.f));
	//this->mainScene->objects[5]->scale(glm::vec3(2.f, 2.f, 2.f));
	//this->mainScene->objects[5]->rotate(-M_PI_2, glm::vec3(1.f, 0.f, 0.f));

	//this->mainScene->objects[6]->translate(glm::vec3(0.f, 10.f, 0.f));
	//this->mainScene->objects[6]->scale(glm::vec3(2.f, 2.f, 2.f));

	

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->mainScene->camera->update();

		for (int i = 0; i < this->mainScene->objects.size(); i++) {
			this->mainScene->objects[i]->update();
			this->mainScene->objects[i]->draw();
		}
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

