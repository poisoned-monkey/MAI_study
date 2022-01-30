#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderLoader.h"
#include "Surface.h"
#include "figures/Cube.h"

enum ImGuiScheme {
    IMGUI_LIGHT_SCHEME,
    IMGUI_DARK_SCHEME,
    IMGUI_CLASSIC_SCHEME
};

bool glad_initialized = false;
const char* GLSL_version = "#version 460";
int curImguiScheme = ImGuiScheme::IMGUI_CLASSIC_SCHEME;


glm::vec3 imVec4toVec3(ImVec4 v) {
    return glm::vec3{v.x, v.y, v.z};
}

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void InitImGui(GLFWwindow* glfw_window);
GLFWwindow* CreateWindow(int width, int height,
                         int xpos, int ypos,
                         const char* title);

// settings
const unsigned int main_width = 800;
const unsigned int main_height = 600;
const unsigned int settings_width = 400;
const unsigned int settings_height = 600;
const unsigned int start_xpos = 150;
const unsigned int start_ypos = 150;
float fov = 60.f;
float scale = 0.5f;

float rot_x = 0.f;
float rot_y = 0.f;
float rot_z = 0.f;

int precision = 10;

glm::vec3 camera_pos{4.f, 0.f, 4.f};
glm::vec3 camera_front{-1.f, 0.f, -1.f};
glm::vec3 camera_up{0.f, 0.f, 1.f};

glm::vec3 light_pos{2.f, 0.f, .5f};
glm::vec3 light_color{1.f, 1.f, 1.f};

glm::vec3 clear_color{.5f, .5f, .5f};

bool fill = true;
bool grid = true;



Material surface_material{
    .ambient = {0.f,.1f,.06f},
    .diffuse = {0.f, .509f, .509f},
    .specular = {.501f, .501f, 0.501f},
    .shininess = 0.25
};



glm::vec3 grid_color{0.,0.f,0.f};
ImVec4 first_bezier_color{.8f, .8f, .2f, 1.f};
ImVec4 second_bezier_color{.2f, .8f, .8f, 1.f};


int main()
{
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return EXIT_FAILURE;
    }

    GLFWwindow* main_window = CreateWindow(main_width, main_height, start_xpos, start_ypos, "Surface Viewer");
    GLFWwindow* settings_window = CreateWindow(settings_width, settings_height, start_xpos + main_width, start_ypos, "Settings");

    glfwMakeContextCurrent(main_window);

    Cube lightCube;
    std::vector<float> cube_vertices = lightCube.GetTriangles();
    Surface surface({{2.f,-2.f,0.f},{0.f,-2.f,1.f},{0.f,-2.f,2.f},{2.f,-2.f,3.f}},
                    {{0.f,2.f,0.f},{2.f,2.f,1.f},{0.f,2.f,3.f},{2.f,2.f,3.f}});
    surface.SetPrecision(precision);
    std::vector<float> surface_vertices = surface.GetTriangles();

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, surface_vertices.size() * sizeof(float), surface_vertices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    GLuint lightVAO, lightVBO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glGenBuffers(1, &lightVBO);

    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, cube_vertices.size() * sizeof(float), cube_vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    GLuint axisVAO, axisVBO;
    glGenVertexArrays(1, &axisVAO);
    glBindVertexArray(axisVAO);
    glGenBuffers(1, &axisVBO);

    std::vector<float> axis = {-1.f,0.f,0.f, 1.f,0.f,0.f,
                               0.f,-1.f,0.f, 0.f,1.f,0.f,
                               0.f,0.f,-1.f, 0.f,0.f,1.f,};
    glBindBuffer(GL_ARRAY_BUFFER, axisVBO);
    glBufferData(GL_ARRAY_BUFFER, axis.size() * sizeof(float), axis.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);
    glLineWidth(0.5f);
    glEnable(GL_LINE_SMOOTH);




    Shader lightCubeShader("../shaders/light_cube.vert",
                           "../shaders/light_cube.frag");
    Shader surfaceShader("../shaders/surface.vert",
                         "../shaders/surface.frag");

    glfwMakeContextCurrent(settings_window);
    InitImGui(settings_window);




    // render loop
    // -----------
    while (!glfwWindowShouldClose(main_window)  && !glfwWindowShouldClose(settings_window))
    {


        glfwPollEvents();
        glfwMakeContextCurrent(main_window);
        processInput(main_window);
        glClearColor(clear_color.x, clear_color.y, clear_color.z,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO);
        surfaceShader.use();
        surfaceShader.setVec3("lightColor", light_color);
        surfaceShader.setVec3("lightPos", light_pos);
        surfaceShader.setVec3("ambientColor", surface_material.ambient);
        surfaceShader.setVec3("diffuseColor", surface_material.diffuse);
        surfaceShader.setVec3("specularColor", surface_material.specular);
        surfaceShader.setFloat("shininess", surface_material.shininess);
        surfaceShader.setVec3("gridColor", grid_color);

        surface.SetPrecision(precision);

        if (surface.isChanged()) {
            surface_vertices = surface.GetTriangles();
            glNamedBufferData(VBO, surface_vertices.size() * sizeof(float), surface_vertices.data(), GL_DYNAMIC_DRAW);
        }

        glm::mat4 projection = glm::perspective(glm::radians(fov), (float) main_width / (float) main_height, 0.1f, 100.0f);

        glm::mat4 model = glm::mat4(1.f);
        model = glm::scale(model, glm::vec3(scale));

        glm::mat4 view = glm::mat4(1.f);
        view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
        view = glm::rotate(view, glm::radians(rot_x), glm::vec3(1.f,0.f,0.f));
        view = glm::rotate(view, glm::radians(rot_y), glm::vec3(0.f,1.f,0.f));
        view = glm::rotate(view, glm::radians(rot_z), glm::vec3(0.f,0.f,1.f));

        glm::vec3 temp_cam_pos = glm::vec3(glm::vec4(camera_pos, 1.0) * view);
        surfaceShader.setVec3("viewPos", temp_cam_pos);

        surfaceShader.setMat4("model", model);
        surfaceShader.setMat4("view", view);
        surfaceShader.setMat4("projection", projection);

        surfaceShader.setBool("drawGrid", false);
        if (fill) {
            glDrawArrays(GL_TRIANGLES, 0, surface_vertices.size() / 3);
        }
        if (grid) {
            surfaceShader.setBool("drawGrid", true);
            glDrawArrays(GL_LINES, 0, surface_vertices.size() / 3);
        }

        glBindVertexArray(lightVAO);
        lightCubeShader.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, light_pos);
        model = glm::scale(model, glm::vec3(.2f));
        glm::vec3 minor_objects_color = {1.f, 1.f, 1.f};
        lightCubeShader.setVec3("minorColor", minor_objects_color);
        lightCubeShader.setMat4("model", model);
        lightCubeShader.setMat4("view", view);
        lightCubeShader.setMat4("projection", projection);
        glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size() / 3);

        minor_objects_color = imVec4toVec3(first_bezier_color);
        lightCubeShader.setVec3("minorColor", minor_objects_color);
        for (const glm::vec3& bezier_point : surface.GetFirstCurve().GetKeyPoints()) {
            model = glm::mat4(1.0f);
            model = glm::scale(model, glm::vec3(scale));
            model = glm::translate(model, bezier_point);
            model = glm::scale(model, glm::vec3(.2f));
            lightCubeShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size() / 3);
        }
        minor_objects_color = imVec4toVec3(second_bezier_color);
        lightCubeShader.setVec3("minorColor", minor_objects_color);
        for (const glm::vec3& bezier_point : surface.GetSecondCurve().GetKeyPoints()) {
            model = glm::mat4(1.0f);
            model = glm::scale(model, glm::vec3(scale));
            model = glm::translate(model, bezier_point);
            model = glm::scale(model, glm::vec3(.2f));
            lightCubeShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size() / 3);
        }

        glBindVertexArray(axisVAO);
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(10.f));
        lightCubeShader.setMat4("model", model);
        minor_objects_color = {0.8f, 0.f, 0.f};
        lightCubeShader.setVec3("minorColor", minor_objects_color);
        glDrawArrays(GL_LINES, 0, 2);
        minor_objects_color = {0.f, 0.8f, 0.f};
        lightCubeShader.setVec3("minorColor", minor_objects_color);
        glDrawArrays(GL_LINES, 2, 2);
        minor_objects_color = {0.f, 0.f, 0.8f};
        lightCubeShader.setVec3("minorColor", minor_objects_color);
        glDrawArrays(GL_LINES, 4, 2);



        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(main_window);

        glfwMakeContextCurrent(settings_window);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        static bool SchemeTab = true;
        static bool SettingsTab = false;
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;
        ImGui::NewFrame();

        ImGui::StyleColorsClassic();

        ImGui::Begin("Settings", nullptr, flags);
        ImGui::SetWindowSize(ImVec2{settings_width, settings_height});
        ImGui::SliderFloat("Scale", &scale, 0.0f, 2.0f);
        ImGui::SliderFloat("Rotate oX", &rot_x, 0.0f, 360.0f);
        ImGui::SliderFloat("Rotate oY", &rot_y, 0.0f, 360.0f);
        ImGui::SliderFloat("Rotate oZ", &rot_z, 0.0f, 360.0f);

        ImGui::SliderFloat("Light x", &light_pos.x, -10.f, 10.f);
        ImGui::SliderFloat("Light y", &light_pos.y, -10.f, 10.f);
        ImGui::SliderFloat("Light z", &light_pos.z, -10.f, 10.f);
        ImGui::ColorEdit3("Bezier 1 color", (float *) &first_bezier_color);
        ImGui::ColorEdit3("Bezier 2 color", (float *) &second_bezier_color);
        float pts[3];
        for (int i = 0; i < surface.GetFirstCurve().GetKeyPoints().size(); ++i) {
            std::string label = "Bezier 1." + std::to_string(i + 1);
            glm::vec3 prev_point = surface.GetFirstCurve().GetKeyPoints()[i];
            pts[0] = prev_point.x;
            pts[1] = prev_point.y;
            pts[2] = prev_point.z;
            if (ImGui::SliderFloat3(label.c_str(), pts, -10.f, 10.f)) {
                surface.GetFirstCurve().UpdatePoint(i, glm::vec3{pts[0], pts[1], pts[2]});
            }
        }
        for (int i = 0; i < surface.GetSecondCurve().GetKeyPoints().size(); ++i) {
            std::string label = "Bezier 2." + std::to_string(i + 1);
            glm::vec3 prev_point = surface.GetSecondCurve().GetKeyPoints()[i];
            pts[0] = prev_point.x;
            pts[1] = prev_point.y;
            pts[2] = prev_point.z;
            if (ImGui::SliderFloat3(label.c_str(), pts, -10.f, 10.f)) {
                surface.GetSecondCurve().UpdatePoint(i, glm::vec3{pts[0], pts[1], pts[2]});
            }
        }
        ImGui::SliderInt("Figure precision", &precision, 2, 100);
        ImGui::Checkbox("Fill", &fill);
        ImGui::SameLine();
        ImGui::Checkbox("Grid", &grid);
        ImGui::End();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(settings_window);
    }

    glfwTerminate();
    return 0;
}

GLFWwindow* CreateWindow(int width, int height,
                         int xpos, int ypos,
                         const char* title)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent(window);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetWindowPos(window, xpos, ypos);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!glad_initialized) {
        glad_initialized = true;
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    glViewport(0,0,width,height);
    return window;
}

void InitImGui(GLFWwindow* glfw_window) {
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("../imgui/fonts/synthesisregular.ttf", 13.f);

    ImGui_ImplGlfw_InitForOpenGL(glfw_window, true);
    ImGui_ImplOpenGL3_Init(GLSL_version);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
