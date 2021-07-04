#include <Gemstone.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <ImGui/imgui.h>
//#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Gemstone::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.f), m_SquarePosition(0.f)
	{
		// Object 1
		m_VertexArray.reset(Gemstone::VertexArray::Create());
		float vertices[3 * 7] = {
			-0.5f,	-0.5f,	0.f,	1.f,	0.f,	 1.f,	 1.f,
			0.5f,	-0.5f,	0.f,	0.f,	1.f,	 1.f,	 1.f,
			0.f,	0.5f,	0.f,	0.f,	0.f,	 1.f,	 1.f
		};

		std::shared_ptr<Gemstone::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Gemstone::VertexBuffer::Create(vertices, sizeof(vertices)));
		Gemstone::BufferLayout layout =
		{
			{ Gemstone::ShaderDataType::Float3, "a_Position" },
			{ Gemstone::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		std::shared_ptr<Gemstone::IndexBuffer> indexBuffer;
		uint32_t indices[3] = { 0, 1, 2 };
		indexBuffer.reset(Gemstone::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// Object 2
		m_SquareVA.reset(Gemstone::VertexArray::Create());
		float vertices2[3 * 4] = {
			-0.5f,	-0.5f,	0.f,
			0.5f,	-0.5f,	0.f,
			0.5f,	0.5f,	0.f,
			-0.5f,	0.5f,	0.f
		};

		std::shared_ptr<Gemstone::VertexBuffer> squareVB;
		squareVB.reset(Gemstone::VertexBuffer::Create(vertices2, sizeof(vertices2)));
		squareVB->SetLayout({
				{ Gemstone::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t indices2[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Gemstone::IndexBuffer> squareIB;
		squareIB.reset(Gemstone::IndexBuffer::Create(indices2, sizeof(indices2) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		// Object 1
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(v_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position + 0.5, 1.0);
				color = v_Color;
			}
		)";
		m_Shader.reset(Gemstone::Shader::Create(vertexSrc, fragmentSrc));

		// Object 2
		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(v_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(Gemstone::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

	}

	virtual void OnImGuiRender() override
	{
		/* EXAMPLE
		* ImGui::Begin("Test");
		* ImGui::Text("Hello World");
		* ImGui::End();
		*/
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnUpdate(Gemstone::Timestep ts) override
	{
		GS_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		if (Gemstone::Input::IsKeyPressed(GS_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Gemstone::Input::IsKeyPressed(GS_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Gemstone::Input::IsKeyPressed(GS_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Gemstone::Input::IsKeyPressed(GS_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Gemstone::Input::IsKeyPressed(GS_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Gemstone::Input::IsKeyPressed(GS_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Gemstone::RenderCommand::SetClearColor({ 0.12f, 0.12f, 0.12f, 1.f });
		Gemstone::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Gemstone::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::identity<glm::mat4>(), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Gemstone::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Gemstone::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.f);
				glm::mat4 transform = glm::translate(glm::identity<glm::mat4>(), pos) * scale;
				Gemstone::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		Gemstone::Renderer::Submit(m_Shader, m_VertexArray);

		Gemstone::Renderer::EndScene();
	}

	void OnEvent(Gemstone::Event& event) override
	{
		/* EXAMPLE
		* if (event.GetEventType() == Gemstone::EventType::KeyPressed)
		* {
		*	Gemstone::KeyPressedEvent& e = (Gemstone::KeyPressedEvent&)event;
		*	GS_TRACE("{0}, {1}", event, (char)e.GetKeyCode());
		* }
		* else
		*	GS_TRACE("{0}", event);
		*/

	}

private:
	std::shared_ptr<Gemstone::Shader> m_Shader;
	std::shared_ptr<Gemstone::VertexArray> m_VertexArray;

	std::shared_ptr<Gemstone::Shader> m_FlatColorShader;
	std::shared_ptr<Gemstone::VertexArray> m_SquareVA;

	Gemstone::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.f;

	float m_CameraRotation = 0.f;
	float m_CameraRotationSpeed = 90.f;

	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed = 1.f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sapphire : public Gemstone::Application
{
public:
	Sapphire()
	{
		PushLayer(new ExampleLayer());
	}

	~Sapphire()
	{

	}
};

Gemstone::Application* Gemstone::CreateApplication()
{
	return new Sapphire();
}