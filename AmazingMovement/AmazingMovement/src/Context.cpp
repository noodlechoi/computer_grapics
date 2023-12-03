#include "Context.h"

CContext::CContext()
{

}

CContext::~CContext()
{
    if (m_program) {
        delete m_program;
    }
    /*for (auto& mesh : m_meshes) {
        delete mesh;
    }*/
    if (m_box) {
        delete m_box;
    }
}

void CContext::KeyBoard(const unsigned char& key, const int& x, const int& y)
{
    const float camera_speed = 0.05f;

    // 카메라 x축은 카메라 UP벡터와 z축 벡터의 직교를 단위 벡터로 만든 것이다.
    auto camera_right = glm::normalize(glm::cross(m_camera_up, -m_camera_front));
    auto camera_up = glm::normalize(glm::cross(-m_camera_front, camera_right));
    switch (key) {
    case 't':
        t_flag = !t_flag;
        break;
    case 'c':
        color_cnt = (color_cnt + 1) % 4;
        if (color_cnt == 0) {
            m_light_color = glm::vec3(1.0f, 1.0f, 1.0f);
        }
        else if (color_cnt == 1) {
            m_light_color = glm::vec3(1.0f, 0.1f, 0.1f);
        }
        else if (color_cnt == 2) {
            m_light_color = glm::vec3(0.1f, 1.0f, 1.0f);
        }
        else if (color_cnt == 3) {
            m_light_color = glm::vec3(0.8f, 0.8f, 0.1f);
        }
        break;
    case 'Y':
        Y_flag = !Y_flag;
        break;
    case 'y':
        y_flag = !y_flag;
        break;
    case 's':
        if (m_program) {
            delete m_program;
        }
        
        Init();
        break;
    case 'q':
        exit(0);
    default:
        break;
    }

    glutPostRedisplay();
}

void CContext::Mouse(const int& button, const int& state, const int& x, const int& y)
{
}

void CContext::Motion(const int& x, const int& y)
{
}

void CContext::Render()
{
    glm::vec3 camera_pos(0.0f, 5.0f, 6.0f);
    auto camera_trans = glm::rotate(glm::mat4(1.0f), glm::radians(m_camera_y), glm::vec3(0.0f, 1.0f, 0.0f));
    camera_pos = camera_trans * glm::vec4(camera_pos, 1.0f);

    m_camera_front = glm::rotate(glm::mat4(1.0f), glm::radians(m_camera_yaw), glm::vec3(0.0f, 1.0f, 0.0f)) * 
        glm::rotate(glm::mat4(1.0f), glm::radians(m_camera_pitch), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);

    auto projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.01f, 40.0f);

    auto view = glm::lookAt(
        camera_pos,
        camera_pos + m_camera_front,
        m_camera_up);

    // 조명 위치 계산
    glm::vec3 light_pos(0.0f, 0.0f, 0.0f);
    auto light_trans = glm::rotate(glm::mat4(1.0f), glm::radians(m_light_obj_y), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::mat4(1.0), radius);
    light_pos = light_trans * glm::vec4(light_pos, 1.0f);

    m_program->UseShader();
    
    // 모델 조명
    m_program->SetUniform("viewPos", camera_pos);
    m_program->SetUniform("lightPos", light_pos);
    m_program->SetUniform("ambientStrength", m_ambient_strength);
    m_program->SetUniform("specularStrength", m_spec_strength);
    m_program->SetUniform("specularShininess", m_spec_shininess);
    m_program->SetUniform("objectColor", m_object_color);

    if (!t_flag) {
        m_program->SetUniform("lightColor", m_light_color);
    }
    else {
        // 조명 끄기
        m_program->SetUniform("lightColor", glm::vec3(0.1f));
    }

    CRandom random;
    for (int i = 0; i < div_height; ++i) {
        for (int j = 0; j < div_width; ++j) {
            auto rand_size = glm::radians(static_cast<float>(random.get(100, 1000)) * 0.1f);
            auto model = glm::translate(glm::mat4(1.0), glm::vec3(first_box_pos.x + size_width * j, first_box_pos.y + rand_size / 2 , first_box_pos.z - size_height * i))
                * glm::scale(glm::mat4(1.0f), glm::vec3(size_width, rand_size, size_height))
                * glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_y), glm::vec3(0.0f, 1.0f, 0.0f))
                * glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_x), glm::vec3(1.0f, 0.0f, 0.0f))
                * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
 
            auto transform = projection * view * model;
            // transform, model 변환 행렬 전달
            m_program->SetUniform("transform", transform);
            m_program->SetUniform("modelTransform", model);
            m_program->SetUniform("invModelTransform", transpose(inverse(model)));
    
            m_box->Draw(m_program);
        }
    }
}

void CContext::Init()
{
	m_program = new CShader("vertex.glsl", "fragment.glsl");
	m_program->MakeShaderProgram();

    m_box = new CMesh();
    m_box->CreateBox();

    while (true) {
        std::cout << "가로 세로 입력(5 ~ 20): ";
        std::cin >> div_width >> div_height;
        if (div_width >= 5 && div_width <= 20 && div_height >= 5 && div_height <= 20) {
            break;
        }
    }
    size_width = 1.0f / div_width;
    size_height = 1.0f / div_height;
    // 첫번째 박스의 위치 = size / 2 * (cnt - 1)
    first_box_pos = glm::vec3(0.0f - ((size_width / 2) * (div_width - 1)), 0.0f, 0.0f - ((size_height / 2) * (div_height - 1)));

    is_start = true;
}

void CContext::Update()
{
}

void CContext::Time(int value)
{
    if (value == 1) {
        if (is_start) {
            first_box_pos.y -= 0.3f;
            m_obj_radian_y += 10;
            if (first_box_pos.y <= 0.0f) {
                is_start = false;
                first_box_pos.y = 0.0f;
                m_obj_radian_y = 0;
            }
        }
        if (x_flag) {
            m_obj_radian_x += 10;
        }
        if (y_flag) {
            m_camera_y += 10;
            m_camera_yaw += 10;
        }
        else if (Y_flag) {
            m_camera_y -= 10;
            m_camera_yaw -= 10;
        }
        glutPostRedisplay();
    }
}
