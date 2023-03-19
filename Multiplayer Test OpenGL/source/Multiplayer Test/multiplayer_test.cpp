#include "multiplayer_test.h"

Game::Multiplayer_Test::Multiplayer_Test(const uint32_t window_width, const uint32_t window_height) :
	m_window_width(window_width), m_window_height(window_height), 
	m_window(), m_time(),
	m_playableCharacter(),
	m_io_context(), m_server(m_io_context, &m_playableCharacter), m_client(m_io_context, &m_playableCharacter), m_netType(), m_server_ip(),
	m_network_thread()
{
	Init();
}

//Callbacks
void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	Game::Multiplayer_Test* game{ static_cast<Game::Multiplayer_Test*>(glfwGetWindowUserPointer(window)) };
	game->GetPlayer().ProcessMouseInput((float)xPos, (float)yPos);
}

void Game::Multiplayer_Test::ProcessKeyboard() {
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);
	if (glfwGetKey(m_window, GLFW_KEY_K) == GLFW_PRESS)
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwGetKey(m_window, GLFW_KEY_L) == GLFW_PRESS)
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		m_playableCharacter.ProcessKeyboardInput(Entities::PlayableCharacter::W, m_time.deltaTime);
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		m_playableCharacter.ProcessKeyboardInput(Entities::PlayableCharacter::S, m_time.deltaTime);
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		m_playableCharacter.ProcessKeyboardInput(Entities::PlayableCharacter::A, m_time.deltaTime);
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		m_playableCharacter.ProcessKeyboardInput(Entities::PlayableCharacter::D, m_time.deltaTime);
}

void resize_callback(GLFWwindow* window, int width, int height) {
	Game::Multiplayer_Test* game{ static_cast<Game::Multiplayer_Test*>(glfwGetWindowUserPointer(window)) };
	game->UpdateWindowSize(width, height);
}

//Getter
Entities::PlayableCharacter& Game::Multiplayer_Test::GetPlayer() {
	return m_playableCharacter;
}

//Setter
void Game::Multiplayer_Test::UpdateWindowSize(const uint32_t window_width, const uint32_t window_height) {
	m_window_width = window_width;
	m_window_height = window_height;
	Utilities::ResourceManager::GetShader(shader_name).ApplyProjectionMatrix(fov_value, (float)m_window_width / m_window_height);
	glViewport(0, 0, window_width, window_height);
}

//Initializing
void Game::Multiplayer_Test::Init() {
	InitOpenGL();
	InitImGui();

	Utilities::ResourceManager::CreateShader(vertex_shader_path, fragment_shader_path, shader_name);
	Utilities::ResourceManager::GetShader(shader_name).ApplyProjectionMatrix(fov_value, (float)m_window_width / m_window_height);

	Utilities::ResourceManager::LoadModel(model_path, model_name);
}

void Game::Multiplayer_Test::InitOpenGL() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_window_width, m_window_height, window_name.data(), nullptr, nullptr);
	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		return;
	}

	glViewport(0, 0, m_window_width, m_window_height);
	glEnable(GL_DEPTH_TEST);

	glfwSetFramebufferSizeCallback(m_window, resize_callback);
		
	glfwSetCursorPosCallback(m_window, mouse_callback);
	glfwSetWindowUserPointer(m_window, this);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::Multiplayer_Test::InitImGui() {
	ImGui::CreateContext();
	ImGuiIO& io{ ImGui::GetIO() };
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
}

//Imgui
void Game::Multiplayer_Test::FrameStartImGui() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Game::Multiplayer_Test::FrameEndImGui() {
	ImGui::Begin("Debug Menu");
	ImGui::SetWindowSize(ImVec2(500.0f, 200.0f));
	ImGui::Text("FPS: %f", ImGui::GetIO().Framerate);
	ImGui::Text("Frametime: %f", 1000.0f / ImGui::GetIO().Framerate);
	ImGui::Text("Screen: %dx%d", m_window_width, m_window_height);
	ImGui::Text("Player position: %f,%f,%f", m_playableCharacter.GetPosition().x, m_playableCharacter.GetPosition().y, m_playableCharacter.GetPosition().z);
	ImGui::Text("Player direction: %f,%f,%f", m_playableCharacter.GetDirection().x, m_playableCharacter.GetDirection().y, m_playableCharacter.GetDirection().z);
	switch (m_netType) {
	case Server:
		ImGui::Text("Player count: %d", m_server.GetConnectedCount());
		break;
	case Client:
		ImGui::Text("Player count: %d", m_client.GetPlayersCount());
		ImGui::InputText("Server IP", &m_server_ip);
		ImGui::SameLine();
		if (ImGui::Button("Connect"))
			m_client.SetIP(m_server_ip);
		break;
	}

	const char* listbox_items[] = { "Client", "Server" };
	ImGui::ListBox("Network Type", reinterpret_cast<int*>(&m_netType), listbox_items, 2, 2);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

//Updates
void Game::Multiplayer_Test::UpdateTime() {
	m_time.currentFrame = (float)glfwGetTime();
	m_time.deltaTime = m_time.currentFrame - m_time.lastFrame;
	m_time.lastFrame = m_time.currentFrame;
}

void Game::Multiplayer_Test::ProcessNetworking() {
	switch(m_netType) {
		case Server:
			m_client.DisableClient();
			m_server.OpenServer();
			break;
		case Client:
			m_server.DisableServer();
			m_client.OpenClient();
			break;
	}
	m_io_context.run_for(maximum_wait_time);
}

void Game::Multiplayer_Test::ProcessIntersections() {
	switch (m_netType) {
	case Server:
		for (auto& [ip, player] : m_server.GetConnected()) {
			player.GetColor() = glm::vec3(0.9f, 0.9f, 0.9f);
			if (Utilities::IntersectionSolver::RayObbIntersest(m_playableCharacter, player))
				player.GetColor() = glm::vec3(0.8f, 0.0f, 0.0f);
		}
		break;
	case Client:
		for (auto& player : m_client.GetPlayers()) {
			player.GetColor() = glm::vec3(0.9f, 0.9f, 0.9f);
			if(Utilities::IntersectionSolver::RayObbIntersest(m_playableCharacter, player))
				player.GetColor() = glm::vec3(0.8f, 0.0f, 0.0f);
		}
		break;
	}
}

void Game::Multiplayer_Test::Update() {
	if (!m_network_thread.joinable()) 
		m_network_thread = std::jthread(boost::bind(&Game::Multiplayer_Test::ProcessNetworking, this));
	UpdateTime();
	ProcessKeyboard();
	m_network_thread.join();
	ProcessIntersections();
}

//Render
void Game::Multiplayer_Test::Render() {
	Utilities::ResourceManager::GetShader(shader_name).Use();
	Utilities::ResourceManager::GetShader(shader_name).SetMat4("view", m_playableCharacter.GetViewMatrix());
	switch (m_netType) {
		case Server:
			for (auto element : m_server.GetConnected())
				element.second.Draw(shader_name);
			break;
		case Client:
			for (auto element : m_client.GetPlayers())
				element.Draw(shader_name);
			break;
	}
}

//Main Loop
void Game::Multiplayer_Test::Run() {
	while (!glfwWindowShouldClose(m_window)) {
		Update();

		FrameStartImGui();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		Render();
		FrameEndImGui();

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
	glfwTerminate();
}