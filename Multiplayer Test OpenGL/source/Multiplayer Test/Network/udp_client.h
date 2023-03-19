#pragma once
#include <asio.hpp>

#include <boost/bind/bind.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include <string_view>
#include <vector>

#include <glm/glm.hpp>

#include "../Entities/playable_character.h"


namespace Network {

	class Udp_Client {
		const size_t max_size = 2048;
	public:
		Udp_Client(asio::io_context& io_context, Entities::PlayableCharacter* player);

		void OpenClient();
		void SetIP(std::string_view new_ip);
		void DisableClient();

		std::vector<Entities::Player>& GetPlayers();

		size_t GetPlayersCount() const;
	private:
		Entities::PlayableCharacter* m_player;

		std::vector<char> m_receive_buffer;
		std::vector<char> m_send_buffer;

		asio::ip::udp::resolver m_resolver;
		asio::ip::udp::socket m_socket;
		asio::ip::udp::endpoint m_server_endpoint;

		std::vector<Entities::Player> m_players;

		void start_send();
		void handle_send();

		void archive_data();
		void unarchive_data();

		void handle_receive();
	};

}