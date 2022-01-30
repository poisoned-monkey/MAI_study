#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/normal.hpp>

#include "ShaderLoader.h"
#include "Camera.h"

#include "Ellipsoid.h"
#include "Cube.h"


#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void sinusToggleCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

int rotate_flat = 90;
int rotate_vert = 0;

int layer_count = 100;
int point_count = 100;

float a = 1;
float b = 1;
float c = 1;

bool sinus_light = false;

float up_factor = 0.5;
float down_factor = -0.5;

int x_angle = 90;
int y_angle = 0;
int z_angle = 0;


// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, sinusToggleCallback);

//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1,1);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("../shaders/Lighting.vert", "../shaders/Lighting.frag");
    Shader lightCubeShader("../shaders/LightCube.vert", "../shaders/LightCube.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    Ellipsoid ellipsoid(a, b, c, up_factor, down_factor, layer_count, point_count);
    std::vector<float> ellipsoid_polygons = ellipsoid.GetTriangles();
    Cube cube;
    std::vector<float> cube_polygons = cube.GetTriangles();

    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * ellipsoid_polygons.size(), ellipsoid_polygons.data(), GL_DYNAMIC_DRAW);


//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVBO, lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glGenBuffers(1, &lightCubeVBO);

    glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube_polygons.size(), cube_polygons.data(), GL_STATIC_DRAW);

    glBindVertexArray(lightCubeVAO);

    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //ellipsoid.SetParams(a,b,c);
        ellipsoid.SetPointCount(point_count);
        ellipsoid.SetLayerCount(layer_count);
        ellipsoid.SetCutFactors(up_factor, down_factor);

        // be sure to activate shader when setting uniforms/drawing objects
        if (ellipsoid.isChanged()) {
            ellipsoid_polygons = ellipsoid.GetTriangles();
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * ellipsoid_polygons.size(), ellipsoid_polygons.data(), GL_DYNAMIC_DRAW);

        }

        lightingShader.use();
        glm::vec3 lightColor = {1.f,1.f,1.f};
        if (sinus_light) {
            lightColor.x = std::sin(glfwGetTime() * 2.f);
            lightColor.y = std::sin(glfwGetTime() * .7f);
            lightColor.z = std::sin(glfwGetTime() * 1.3f);
        }

        lightingShader.setVec3("objectColor", .5f, .5f, .5f);
        lightingShader.setVec3("lightColor", lightColor);
        lightingShader.setVec3("lightPos", lightPos);
        lightingShader.setVec3("viewPos", camera.Position);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(float(x_angle)), glm::vec3(1,0,0));
        model = glm::rotate(model, glm::radians(float(y_angle)), glm::vec3(0,1,0));
        model = glm::rotate(model, glm::radians(float(z_angle)), glm::vec3(0,0,1));
        model = glm::scale(model, glm::vec3(a,b,c));
        lightingShader.setMat4("model", model);

        // render the cube
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, ellipsoid_polygons.size() / 6);



        // also draw the lamp object
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        float len = lightPos.length();
        float teta = glm::radians<float>(rotate_flat);
        float fi = glm::radians<float>(rotate_vert);
        lightPos = {len * std::sin(teta) * std::cos(fi),
                    len * std::sin(teta) * std::sin(fi),
                    len * std::cos(teta)};
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightCubeShader.setMat4("model", model);

        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, cube_polygons.size() / 6);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        //camera.ProcessKeyboard(FORWARD, deltaTime);
        camera.ProcessZoom(deltaTime * 50);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        //camera.ProcessKeyboard(BACKWARD, deltaTime);
        camera.ProcessZoom(-deltaTime * 50);
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS){
        rotate_flat += 2;
        rotate_flat %= 360;
        //std::cout << rotate_flat << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        x_angle = (x_angle + 2) % 360;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        y_angle = (y_angle + 2) % 360;
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        z_angle = (z_angle + 2) % 360;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        up_factor = std::min(up_factor + 0.01, 1.0);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        up_factor = std::max(up_factor - 0.01, -1.0);
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        down_factor = std::min(down_factor + 0.01, 1.0);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        down_factor = std::max(down_factor - 0.01, -1.0);
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        rotate_vert += 2;
        rotate_vert %= 360;
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        a = std::min(a + 0.01, 1.);
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        a = std::max(a - 0.01, 0.1);
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        b = std::min(b + 0.01, 1.);
    }
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        b = std::max(b - 0.01, 0.1);
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        c = std::min(c + 0.01, 1.);
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        c = std::max(c - 0.01, 0.1);
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        layer_count = std::min((layer_count + 30), 1000);
        std::cout << "layer count " << layer_count << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        layer_count = std::max((layer_count - 30), 20);
        std::cout << "layer count " << layer_count << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        point_count = std::min((point_count + 30), 1000);
        std::cout << "point count " << point_count << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        point_count = std::max((point_count - 30), 20);
        std::cout << "point count " << point_count << std::endl;
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void sinusToggleCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_RELEASE) {
        return;
    }
    if (key == GLFW_KEY_Q) {
        sinus_light = !sinus_light;
    }
}


