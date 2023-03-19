#include "udp_server.h"

Network::Udp_Server::Udp_Server(asio::io_context& io_context, Entities::PlayableCharacter* player) :
    m_socket(io_context), m_player(player), 
    m_receive_buffer(max_size), m_send_buffer(max_size),
    m_connected(), m_current_connection()
{

}

void Network::Udp_Server::OpenServer() {
    if (m_socket.is_open())
        return;
    m_socket.open(asio::ip::udp::v4());
    m_socket.bind(asio::ip::udp::endpoint(asio::ip::udp::v4(), 6969));
    new_connection();
}

void Network::Udp_Server::DisableServer() {
    if(m_socket.is_open())
        m_socket.close();
}

void Network::Udp_Server::new_connection() {
	m_socket.async_receive_from(asio::buffer(m_receive_buffer), m_current_connection, boost::bind(&Network::Udp_Server::on_connected, this));
}

void Network::Udp_Server::on_connected() {
    unarchive_data();
    send_to();
}

void Network::Udp_Server::archive_data() {
    std::vector<Entities::Player> to_send{};
    to_send.push_back(Entities::Player(m_player->GetBasicEntity(), "simple_cube"));
    for (auto& item : m_connected)
        if (item.first != m_current_connection)
            to_send.push_back(item.second);

    std::ostringstream archive_stream{};
    boost::archive::binary_oarchive archive{ archive_stream };
    archive << to_send;
    std::string archive_string{ archive_stream.str() };
    m_send_buffer = { archive_string.begin(), archive_string.end() };
}

void Network::Udp_Server::unarchive_data() {
    std::string received{ m_receive_buffer.begin(), m_receive_buffer.end() };
    if (received.front()) {
        Entities::Player received_player;
        std::istringstream archive_stream{ received };
        boost::archive::binary_iarchive archive{ archive_stream };
        archive >> received_player;
        m_connected[m_current_connection] = received_player;
    }
}

void Network::Udp_Server::send_to() {
    archive_data();
    m_socket.async_send_to(asio::buffer(m_send_buffer), m_current_connection, boost::bind(&Network::Udp_Server::handle_send, this));
}

void Network::Udp_Server::handle_send() {
    new_connection();
}

size_t Network::Udp_Server::GetConnectedCount() const {
    return m_connected.size();
}

std::map<asio::ip::udp::endpoint, Entities::Player>& Network::Udp_Server::GetConnected() {
    return m_connected;
}