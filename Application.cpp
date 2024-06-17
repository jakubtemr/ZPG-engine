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

void Application::LinearMoveObject()
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
	glm::vec3 currentPosition = this->mainScene->objects[this->mainScene->objectIndex(this->selectedObjectIndex)]->getPos();
	this->mainScene->objects[this->mainScene->objectIndex(this->selectedObjectIndex)]->addLineMove(currentPosition, pos, 0.3f);
	this->moveObject = false;
	this->selectedObjectIndex = 0;
}
void Application::CurveMoveObject()
{
	if (this->controlCurve==0&&this->selectedObjectIndex == 0)
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
	if (this->controlCurve == 0) {
		this->startCurve = this->mainScene->objects[this->mainScene->objectIndex(this->selectedObjectIndex)]->getPos();
		this->objectCurveIndex = this->mainScene->objectIndex(this->selectedObjectIndex);
	}
	if (this->controlCurve == 1) {
		this->control1 = pos;
	}
	if (this->controlCurve == 2) {
		this->control2 = pos;
	}
	if (controlCurve == 3) {
		this->mainScene->objects[objectCurveIndex]->addCurveMove(this->startCurve, pos,this->control1,this->control2, 0.001f);
		this->moveCurveObject = false;
		this->selectedObjectIndex = 0;
		this->controlCurve = 0;
		return;
	}
	this->controlCurve++;
	
}

void Application::cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY) {
	//printf("cursor_pos_callback %d, %d;\n", (int)mouseX, (int)mouseY);
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
	if (key == GLFW_KEY_L && action == GLFW_PRESS) { this->moveObject = true; 
	this->selectedObjectIndex = 0;
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		this->moveCurveObject = true;
		this->selectedObjectIndex = 0;
	}
	if (key == GLFW_KEY_W && action == GLFW_RELEASE) this->mainScene->camera->setFrontMoveState(0);
	if (key == GLFW_KEY_S && action == GLFW_RELEASE) this->mainScene->camera->setFrontMoveState(0);
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) this->mainScene->camera->setSideMoveState(0);
	if (key == GLFW_KEY_D && action == GLFW_RELEASE) this->mainScene->camera->setSideMoveState(0);

}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		this->mainScene->camera->setMouseMoveState(true);
		if (moveObject) {
			this->LinearMoveObject();
		}
		if (moveCurveObject) {
			this->CurveMoveObject();
		}
		this->identifyObject();
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) this->mainScene->camera->setMouseMoveState(false);

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) this->pushObject();
}

void Application::window_focus_callback(GLFWwindow* window, int focused) {
	//printf("window_focus_callback \n");
}

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
	this->mainScene->camera->setAspectRatio((float)width ,(float)height);
}

void Application::window_iconify_callback(GLFWwindow* window, int iconified) {
	//printf("window_iconify_callback \n");
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
	/*
	sceneBuilder.addObject("sun", "phong");
	sceneBuilder.addObject("mercury", "blinn");
	sceneBuilder.addObject("venus", "blinn");
	sceneBuilder.addObject("earth", "blinn");
	sceneBuilder.addObject("mars", "blinn");
	sceneBuilder.addObject("jupiter", "blinn");
	sceneBuilder.addObject("saturn", "blinn");
	sceneBuilder.addObject("uranus", "blinn");
	sceneBuilder.addObject("neptune", "blinn");
	sceneBuilder.addObject("moon", "blinn");
	//sceneBuilder.addObject("ceres", "blinn");
	
	//sceneBuilder.addObject("moon", "phong");
	*/
	//sceneBuilder.addObject("moon", "phongControl");
	
	/*sceneBuilder.addObject("moon", "phong");
	sceneBuilder.addObject("moon", "phong");
	sceneBuilder.addObject("moon", "phong");
	sceneBuilder.addObject("moon", "phong");
	*/

	//scene ONE
	///*
	sceneBuilder.addObject("house", "phong");
	sceneBuilder.addObject("zombie", "blinn");
	sceneBuilder.addObject("zombie", "blinn");
	sceneBuilder.addObject("tree", "blinn");
	sceneBuilder.addObject("zed", "blinn");
	sceneBuilder.addObject("teren", "blinn");
	//*/
	sceneBuilder.addSkyBox(std::vector<std::string>{"../final/models/negx.jpg", "../final/models/posx.jpg", "../final/models/posy.jpg", "../final/models/negy.jpg", "../final/models/negz.jpg", "../final/models/posz.jpg"});
	
	
	
	//scene TWO
	/*
	for (int i = 0; i < 20; i++) {
		sceneBuilder.addObject("zombie", "phong");
		sceneBuilder.addObject("tree", "phong");
		sceneBuilder.addObject("zed", "phong");
		//sceneBuilder.addObject("house", "phong");

	}
	
	*/
	

	sceneBuilder.addCamera(glm::vec3(0.f, 0.f, 10.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.0f, 0.0f));
	//sceneBuilder.addPointLight(glm::vec3(0.f, 8.f, 0.f), glm::vec3(1.f, 1.f, 1.f));
	
	//SCENE 1
	sceneBuilder.addPointLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	//SCENE 2
	//sceneBuilder.addSpotLight(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 1.f, 1.f), glm::radians(45.0f));

	//sceneBuilder.addPointLight(glm::vec3(26.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	//sceneBuilder.addDirLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	this->mainScene = sceneBuilder.build();

	for (int i = 0; i < this->mainScene->lights.size(); i++) {
		this->mainScene->lights[i]->addLightObserver(&ShaderManager::getInstance()->getShader("phong"));
		this->mainScene->lights[i]->addLightObserver(&ShaderManager::getInstance()->getShader("phongControl"));
		this->mainScene->lights[i]->addLightObserver(&ShaderManager::getInstance()->getShader("blinn"));

	}

	for (int i = 0; i < this->mainScene->lights.size(); i++) {
		this->mainScene->lights[i]->notifyLightObservers();
	}

	this->mainScene->camera->addCameraObserver(&ShaderManager::getInstance()->getShader("phong"));
	this->mainScene->camera->addCameraObserver(&ShaderManager::getInstance()->getShader("phongControl"));
	this->mainScene->camera->addCameraObserver(&ShaderManager::getInstance()->getShader("blinn"));
	this->mainScene->camera->addCameraObserver(&ShaderManager::getInstance()->getShader("skybox"));
	this->mainScene->camera->notifyCameraObservers();
	
	//scene ONE
	///*
	this->mainScene->objects[1]->translate(glm::vec3(0.f, 0.f, 14.f));
	this->mainScene->objects[2]->translate(glm::vec3(2.f, 0.f, 15.f));
	this->mainScene->objects[3]->translate(glm::vec3(5.f, 0.f, 15.f));
	this->mainScene->objects[4]->translate(glm::vec3(10.f, 0.f, 15.f));
	//this->mainScene->objects[5]->scale(glm::vec3(1.0f, 1.0f, 1.0f));

	//*/
	//this->mainScene->objects[2]->rotate(M_PI_2, glm::vec3(0.f, 0.5f, 0.f));

	//this->mainScene->objects[1]->addCircleMove(glm::vec3(1.f, 0.f, 0.f), 6, 1.0f)
	
	//scene TWO
	/*
	srand(time(NULL));
	int x=20;
	int y=20;
	for (int i = 0; i < 20; i++) {
		int size = rand() % 5;

			this->mainScene->objects[i]->translate(glm::vec3(x, 0.f, y));
			
			//this->mainScene->objects[i]->addCircleMove(glm::vec3(1.f, 0.f, 0.f), size, 1.0f);
			this->mainScene->objects[i]->scale(glm::vec3(size, size, size));
			x -= 4;
			y -= 2;
			if (y < 0) {
				y = 20;
			}
	}
	*/
	
	//this->mainScene->objects[100]->scale(glm::vec3(200.f, 0.f, 200.f));
	

	/*
	// Slunce 
	this->mainScene->objects[0]->scale(glm::vec3(5.0f, 5.0f, 5.0f)); 

	// Merkur
	this->mainScene->objects[1]->addCircleMove(glm::vec3(1.f, 0.f, 0.f), 6, 1.0f); 
	this->mainScene->objects[1]->scale(glm::vec3(0.4f, 0.4f, 0.4f));

	// Venuše 
	this->mainScene->objects[2]->addCircleMove(glm::vec3(1.f, 0.f, 0.f), 8, 0.8f);
	this->mainScene->objects[2]->scale(glm::vec3(0.6f, 0.6f, 0.6f));

	// Zemì 
	this->mainScene->objects[3]->addCircleMove(glm::vec3(1.f, 0.f, 0.f), 12, 0.1f); 
	this->mainScene->objects[3]->scale(glm::vec3(0.7f, 0.7f, 0.7f));

	// Mars
	this->mainScene->objects[4]->addCircleMove(glm::vec3(1.f, 0.f, 0.f), 15, 0.5f); 
	this->mainScene->objects[4]->scale(glm::vec3(0.6f, 0.6f, 0.6f));

	// Jupiter
	this->mainScene->objects[5]->addCircleMove(glm::vec3(1.f, 0.f, 0.f), 19, 0.3f); 
	this->mainScene->objects[5]->scale(glm::vec3(2.5f, 2.5f, 2.5f));

	// Saturn
	this->mainScene->objects[6]->addCircleMove(glm::vec3(1.f, 0.f, 0.f), 25, 0.2f);
	this->mainScene->objects[6]->scale(glm::vec3(2.0f, 2.0f, 2.0f));

	// Uran
	this->mainScene->objects[7]->addCircleMove(glm::vec3(1.f, 0.f, 0.f), 28, 0.15f);
	this->mainScene->objects[7]->scale(glm::vec3(1.8f, 1.8f, 1.8f));

	// Neptun
	this->mainScene->objects[8]->addCircleMove(glm::vec3(1.f, 0.f, 0.f), 32, 0.1f);
	this->mainScene->objects[8]->scale(glm::vec3(1.7f, 1.7f, 1.7f));

	this->mainScene->objects[9]->setParent(this->mainScene->objects[3]);
	this->mainScene->objects[9]->addCircleMove(glm::vec3(0.f, 0.f, 0.f), 2, 1.9f); 
	this->mainScene->objects[9]->scale(glm::vec3(0.3f, 0.3f, 0.3f));
	*/
	
	/*
	this->mainScene->objects[0]->translate(glm::vec3(-2.f, 0.f, 0.f));
	this->mainScene->objects[1]->translate(glm::vec3(2.f, 0.f, 0.f));
	this->mainScene->objects[2]->translate(glm::vec3(0.f, 2.f, 0.f));
	this->mainScene->objects[3]->translate(glm::vec3(0.f, -2.f, 0.f));
	*/

	//this->mainScene->objects[0]->translate(glm::vec3(10.f, 5.f, 50.f));
	//this->mainScene->objects[0]->scale(glm::vec3(3.f, 3.f, 3.f));
	//this->mainScene->objects[0]->rotate(M_PI_2, glm::vec3(0.f, 1.f, 0.f));
	
	//this->mainScene->objects[3]->addCircleMove(glm::vec3(0.f, 20.f, -30.f), 15);
	//this->mainScene->objects[0]->addLineMove(glm::vec3(0.f, 0.f, 0.f), glm::vec3(10.f, 12.f, 15.f),1.f);

	

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->mainScene->skybox->draw();
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

