#include "Mesh.h"

CMesh::CMesh() : m_primitive_type{GL_TRIANGLES}
{
}

// 프래그먼트가 생성 안됨
CMesh::CMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, unsigned int primitive_type)
{
    m_vao = new CVAO();

    m_vao->Gen();

    m_vertexbuffer = new CBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices.data(), sizeof(Vertex), vertices.size());

    m_indexbuffer = new CBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices.data(), sizeof(unsigned int), indices.size());

    m_vao->SetAttrib(0, 3, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, position));
    m_vao->SetAttrib(1, 4, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, normal));
    m_vao->SetAttrib(2, 2, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, texture));
}

CMesh::~CMesh()
{
    if (m_vao) {
        delete m_vao;
    }
    if (m_vertexbuffer) {
        delete m_vertexbuffer;
    }
    if (m_indexbuffer) {
        delete m_indexbuffer;
    }
}

void CMesh::Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, unsigned int primitive_type)
{
    m_vao = new CVAO();

    m_vao->Gen();

    m_vertexbuffer = new CBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices.data(), sizeof(Vertex), vertices.size());

    m_indexbuffer = new CBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices.data() , sizeof(unsigned int), indices.size());
    
    m_vao->SetAttrib(0, 3, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, position));
    m_vao->SetAttrib(1, 4, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, normal));
    m_vao->SetAttrib(2, 2, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, texture));
}

void CMesh::InitText(std::string_view name)
{
    /*for (int i = 0; i < 6; ++i) {
        m_texs.push_back(CTexture());
        m_texs[i].CreateTexture();
    }

    m_texs[0].SetTextureImage("res/A.png");
    m_texs[1].SetTextureImage("res/B.png");
    m_texs[2].SetTextureImage("res/C.png");
    m_texs[3].SetTextureImage("res/D.png");
    m_texs[4].SetTextureImage("res/E.png");
    m_texs[5].SetTextureImage("res/F.png");*/
}

void CMesh::Draw(const CShader* program) const
{
    m_vao->Bind();
    //m_texs[0].Bind();
    glDrawElements(m_primitive_type, m_indexbuffer->GetCount(), GL_UNSIGNED_INT, 0);
}

void CMesh::CreateBox()
{
    std::vector<Vertex> vertices = {
        Vertex { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(0.0f,  0.0f, -1.0f, 0.5f), glm::vec2(0.0f, 0.0f)},
        Vertex { glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.0f,  0.0f, -1.0f, 0.5f),  glm::vec2(1.0f, 0.0f)  },
        Vertex { glm::vec3(0.5f,  0.5f, -0.5f), glm::vec4(0.0f,  0.0f, -1.0f, 0.5f),  glm::vec2(1.0f, 1.0f)  },
        Vertex { glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(0.0f,  0.0f, -1.0f, 0.5f),  glm::vec2(0.0f, 1.0f) },
                                                                                   
        Vertex { glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(0.0f,  0.0f,  1.0f, 0.5f), glm::vec2(0.0f, 0.0f)  },
        Vertex { glm::vec3(0.5f, -0.5f,  0.5f), glm::vec4(0.0f,  0.0f,  1.0f, 0.5f),   glm::vec2(1.0f, 0.0f) },
        Vertex { glm::vec3(0.5f,  0.5f,  0.5f), glm::vec4(0.0f,  0.0f,  1.0f, 0.5f),  glm::vec2(1.0f, 1.0f)  },
        Vertex { glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(0.0f,  0.0f,  1.0f, 0.5f), glm::vec2(0.0f, 1.0f)  },
                                                                                  
        Vertex { glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(-1.0f,  0.0f,  0.0f, 0.5f), glm::vec2(1.0f, 0.0f) },
        Vertex { glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(-1.0f,  0.0f,  0.0f, 0.5f), glm::vec2(1.0f, 1.0f) },
        Vertex { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(-1.0f,  0.0f,  0.0f, 0.5f), glm::vec2(0.0f, 1.0f) },
        Vertex { glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(-1.0f,  0.0f,  0.0f, 0.5f), glm::vec2(0.0f, 0.0f) },
                                                                                  
        Vertex { glm::vec3(0.5f,  0.5f,  0.5f), glm::vec4(1.0f,  0.0f,  0.0f, 0.5f), glm::vec2(1.0f, 0.0f)   },
        Vertex { glm::vec3(0.5f,  0.5f, -0.5f), glm::vec4(1.0f,  0.0f,  0.0f, 0.5f),  glm::vec2(1.0f, 1.0f)  },
        Vertex { glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(1.0f,  0.0f,  0.0f, 0.5f),  glm::vec2(0.0f, 1.0f)  },
        Vertex { glm::vec3(0.5f, -0.5f,  0.5f), glm::vec4(1.0f,  0.0f,  0.0f, 0.5f),  glm::vec2(0.0f, 0.0f)  },
                                                                                  
        Vertex { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(0.0f, -1.0f,  0.0f, 0.5f),  glm::vec2(0.0f, 1.0f) },
        Vertex { glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.0f, -1.0f,  0.0f, 0.5f),   glm::vec2(1.0f, 1.0f) },
        Vertex { glm::vec3(0.5f, -0.5f,  0.5f), glm::vec4(0.0f, -1.0f,  0.0f, 0.5f),   glm::vec2(1.0f, 0.0f) },
        Vertex { glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(0.0f, -1.0f,  0.0f, 0.5f),  glm::vec2(0.0f, 0.0f) },
                                                                                  
        Vertex { glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(0.0f,  1.0f,  0.0f, 0.5f),  glm::vec2(0.0f, 1.0f) },
        Vertex { glm::vec3(0.5f,  0.5f, -0.5f), glm::vec4(0.0f,  1.0f,  0.0f, 0.5f),   glm::vec2(1.0f, 1.0f)  },
        Vertex { glm::vec3(0.5f,  0.5f,  0.5f), glm::vec4(0.0f,  1.0f,  0.0f, 0.5f),  glm::vec2(1.0f, 0.0f)  },
        Vertex { glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(0.0f,  1.0f,  0.0f, 0.5f),  glm::vec2(0.0f, 0.0f) },
    };

    std::vector<uint32_t> indices = {
         0,  2,  1,  2,  0,  3,
         4,  5,  6,  6,  7,  4,
         8,  9, 10, 10, 11,  8,
        12, 14, 13, 14, 12, 15,
        16, 17, 18, 18, 19, 16,
        20, 22, 21, 22, 20, 23,
    };

    Init(vertices, indices, GL_TRIANGLES);
}

void CMesh::CreateSquarePy()
{
    std::vector<Vertex> vertices = {
        Vertex{glm::vec3(0.0f, 0.5f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(0.5f, 1.0f)},
        Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},

        Vertex{glm::vec3(0.0f, 0.5f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f)},
        Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},

        Vertex{glm::vec3(0.0f, 0.5f, 0.0f), glm::vec4(0.0f, 0.0f, -1.0f, 1.0f), glm::vec2(0.5f, 1.0f)},
        Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.0f, 0.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(0.0f, 0.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},

        Vertex{glm::vec3(0.0f, 0.5f, 0.0f), glm::vec4(-1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f)},
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(-1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(-1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},

        Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(0.0f, -1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(0.0f, -1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec4(0.0f, -1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.0f, -1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
    };

    std::vector<uint32_t> indices = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,
        9, 10, 11,
        12, 13, 14, 13, 15, 14
    };

    Init(vertices, indices, GL_TRIANGLES);
}
