#pragma once
#include <asio.hpp>

#include <boost/bind/bind.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include <map>
#include <vector>

#include <glm/glm.hpp>

#include "../Entities/playable_character.h"
#include "../Entities/player.h"


namespace Network {

	class Udp_Server {
		const size_t max_size = 2048;
	public:
		Udp_Server(asio::io_context& io_context, Entities::PlayableCharacter* player);

		void OpenServer();
		void DisableServer();

		std::map<asio::ip::udp::endpoint, Entities::Player>& GetConnected();
		size_t GetConnectedCount() const;
	private:
		Entities::PlayableCharacter* m_player;

		asio::ip::udp::socket m_socket;

		std::vector<char> m_receive_buffer;
		std::vector<char> m_send_buffer;

		std::map<asio::ip::udp::endpoint, Entities::Player> m_connected;
		asio::ip::udp::endpoint m_current_connection;

		void on_connected();
		void new_connection();

		void archive_data();
		void unarchive_data();

		void send_to();
		void handle_send();
	};

}