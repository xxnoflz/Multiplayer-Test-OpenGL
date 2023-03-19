#pragma once
#include <asio.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "Vendor/Dear ImGui/imgui_stdlib.h"

#include <cstdint>
#include <string_view>
#include <thread>

#include "Utilities/resource_manager.h"
#include "Utilities/intersection_solver.h"
#include "Entities/playable_character.h"
#include "Entities/player.h"

#include "Network/udp_server.h"
#include "Network/udp_client.h"

constexpr std::string_view window_name = "Multiplayer Test";

constexpr float fov_value = 45.0f;

constexpr std::string_view vertex_shader_path = "source/Multiplayer Test/Shaders/simple_vertex_shader.glsl";
constexpr std::string_view fragment_shader_path = "source/Multiplayer Test/Shaders/simple_fragment_shader.glsl";
constexpr std::string_view model_path = "source/Multiplayer Test/Models/cube.obj";

constexpr std::string_view shader_name = "simple_shader";
constexpr std::string_view model_name = "simple_cube";

constexpr std::chrono::duration maximum_wait_time = std::chrono::milliseconds(10);

namespace Game {

	class Multiplayer_Test {
	public:
		Multiplayer_Test(const uint32_t window_width, const uint32_t window_height);

		void Run();

		Entities::PlayableCharacter& GetPlayer();
		void UpdateWindowSize(const uint32_t window_width, const uint32_t window_height);
	private:
		struct TimeHandler {
			float deltaTime;
			float currentFrame;
			float lastFrame;
		};
		enum NetworkType {
			Client,
			Server
		};

		uint32_t m_window_width;
		uint32_t m_window_height;
		GLFWwindow* m_window;
		TimeHandler m_time;

		asio::io_context m_io_context;
		Network::Udp_Server m_server;
		Network::Udp_Client m_client;
		NetworkType m_netType;
		std::string m_server_ip;
		std::jthread m_network_thread;

		Entities::PlayableCharacter m_playableCharacter;

		void Init();
		void InitOpenGL();
		void InitImGui();

		void Update();
		void ProcessIntersections();
		void UpdateTime();
		void ProcessKeyboard();
		void ProcessNetworking();

		void Render();

		void FrameStartImGui();
		void FrameEndImGui();
	};

}