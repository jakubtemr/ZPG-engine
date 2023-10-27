#include "Scene.h"
#include "CallbackHandler.h"

Scene::Scene() {
    app = Application();

    window = app.DrawWindow();
    CallbackHandler::SetCallbacks(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Scene::AddModel(GLuint model, ShaderApp* shader, GLsizei vertexCount) {
    ModelShaderPair pair = { model, shader,vertexCount };
    modelShaderPairs.push_back(pair);
}

void Scene::Render() {
   /* glm::mat4 M = glm::mat4(1.0f);
    glm::vec3 axis(0.0f, 1.0f, 0.0f); // Otoèení kolem osy Y
    M = glm::rotate(M, 45.0f, axis);
    glm::vec3 translation(0.0f, 0.0f, -5.0f); // Posunutí 5 jednotek dozadu
    M = glm::translate(M, translation);
    glm::vec3 scale(0.5f, 0.5f, 0.5f); // Zmenšení na polovinu
    M = glm::scale(M, scale);
    */
    Camera camera;

    float rotationAngle = 0.0f;
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 translation(0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
               scale += glm::vec3(0.01f, 0.01f, 0.01f);
        }
        else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
               scale -= glm::vec3(0.01f, 0.01f, 0.01f);
        }
        if (scale.x < 0.1f || scale.y < 0.1f || scale.z < 0.1f) {
            scale.x = 0.1f;
            scale.y = 0.1f;
            scale.z = 0.1f;
        }
        else if (scale.x > 2 || scale.y > 2 || scale.z > 2) {
			scale.x = 2;
			scale.y = 2;
			scale.z = 2;
		}
    
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
           
            translation.x += 0.05f;
        }
        else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            translation.x -= 0.05f;
        }
        //camera
        glm::mat4 view = camera.getCamera();
        //glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
        float cameraSpeed = 0.05f;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            camera.eye += cameraSpeed * camera.target;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            camera.eye -= cameraSpeed * camera.target;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            camera.eye -= glm::normalize(glm::cross(camera.target, camera.up)) * cameraSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            camera.eye += glm::normalize(glm::cross(camera.target, camera.up)) * cameraSpeed;
        }

        // Aktualizace úhlu rotace
        rotationAngle += 0.005f; 
        if (rotationAngle > 2 * M_PI) {
            rotationAngle -= 2 * M_PI;
        }

        for (ModelShaderPair& pair : modelShaderPairs) {

            glm::mat4 M = glm::mat4(1.0f);
            glm::vec3 axis(1.0f, 1.0f, 0.0f);

            //M = glm::rotate(M, rotationAngle, axis);
            M = glm::scale(M, scale);
            M = glm::translate(M, translation);
           // camera.rotate(0.01f, 0.01f);
            pair.shader->UseShader();
            pair.shader->SetTransformationMatrix(M);
            pair.shader->SetViewMatrix(view);
            pair.shader->SetProjectionMatrix(projection);
            glBindVertexArray(pair.model);
            glDrawArrays(GL_TRIANGLES, 0, pair.vertexCount);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

Scene::~Scene() {
    app.DestroyWindow(window);
}
