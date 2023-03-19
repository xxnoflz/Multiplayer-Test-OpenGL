#include "udp_client.h"

Network::Udp_Client::Udp_Client(asio::io_context& io_context, Entities::PlayableCharacter* player) :
	m_resolver(io_context), m_socket(io_context), m_server_endpoint(),
	m_player(player), m_players(),
	m_send_buffer(max_size), m_receive_buffer(max_size)
{
	
}

void Network::Udp_Client::OpenClient() {
	if (m_socket.is_open())
		return;
	m_socket.open(asio::ip::udp::v4());
	start_send();
}

void Network::Udp_Client::SetIP(std::string_view new_ip) {
	m_server_endpoint = *m_resolver.resolve(asio::ip::udp::v4(), new_ip, "6969");
	m_socket.cancel();
}

void Network::Udp_Client::DisableClient() {
	if (m_socket.is_open())
		m_socket.close();
}

void Network::Udp_Client::start_send() {
	archive_data();
	m_socket.async_send_to(asio::buffer(m_send_buffer), m_server_endpoint, boost::bind(&Network::Udp_Client::handle_send, this));
}

void Network::Udp_Client::handle_send() {
	m_socket.async_receive_from(asio::buffer(m_receive_buffer), m_server_endpoint, boost::bind(&Network::Udp_Client::handle_receive, this));
}

void Network::Udp_Client::archive_data() {
	Entities::Player send_player{ Entities::BasicEntity(m_player->GetBasicEntity()), "simple_cube" };

	std::ostringstream archive_stream{};
	boost::archive::binary_oarchive archive{ archive_stream };
	archive << send_player;
	std::string archive_string{ archive_stream.str() };
	m_send_buffer = { archive_string.begin(), archive_string.end() };
}

void Network::Udp_Client::unarchive_data() {
	std::string received{ m_receive_buffer.begin(), m_receive_buffer.end() };
	if (received.front()) {
		std::istringstream archive_stream{ received };
		boost::archive::binary_iarchive archive{ archive_stream };
		archive >> m_players;
	}
}

void Network::Udp_Client::handle_receive() {
	unarchive_data();
	start_send();
}

std::vector<Entities::Player>& Network::Udp_Client::GetPlayers() {
	return m_players;
}

size_t Network::Udp_Client::GetPlayersCount() const {
	return m_players.size();
}