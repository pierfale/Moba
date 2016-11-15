/*
 * Packet.cpp
 *
 *  Created on: 21 avr. 2013
 *      Author: pierre
 */

#include "Packet.hpp"

namespace network {

	Packet::Packet(boost::asio::ip::tcp::socket* socket, PacketType::PacketTypeFinal type) : m_socket(socket), m_type(type) {
		m_buffer = (char*)malloc(PACKET_BUFFER_ALLOC);
		m_bufferAllocSize = PACKET_BUFFER_ALLOC;
		m_bufferCurrSize = 2*sizeof(int);
		m_readerCursor = 0;

		memset((void*)(m_buffer), 0x0, sizeof(int));
		memcpy((void*)(m_buffer+sizeof(int)), (void*)&m_type, sizeof(int));
	}

	void Packet::setSocket(boost::asio::ip::tcp::socket* socket) {
		m_socket = socket;
	}

	void Packet::send() {
		memcpy((void*)m_buffer, (void*)&m_bufferCurrSize, 4);
		m_socket->send(boost::asio::buffer(m_buffer, m_bufferCurrSize));
	}

	bool Packet::receive(){
		unsigned int length = 0;
		m_bufferCurrSize = 0;
		boost::system::error_code error;

		while(length < sizeof(int) || length < m_bufferCurrSize) {
			if(m_bufferCurrSize == 0)
				length += m_socket->read_some(boost::asio::buffer(m_buffer, sizeof(int)), error);
			else
				length += m_socket->read_some(boost::asio::buffer(m_buffer+length, m_bufferCurrSize-length), error);
			if(error == boost::asio::error::eof) {
				std::cerr << "[Network] End of file reached" << std::endl;
				return false;
			}
			else if(error == boost::asio::error::connection_aborted || error.value() == 10054) {
				std::cerr << "[Network] Connection aborted" << std::endl;
				return false;
			}
			else if(error) {
				std::cerr << "[Network] error " << error.value() << " : " << error.message() << std::endl;
			}
			if(m_bufferCurrSize == 0 && length >= sizeof(int)) {
				memcpy((void*)&m_bufferCurrSize, (void*)m_buffer, sizeof(int));
			}
		}
		int type;
		memcpy((void*)&type, (void*)(m_buffer+sizeof(int)), sizeof(int));
		m_type = static_cast<PacketType::PacketTypeFinal>(type);
		m_readerCursor = 8;

		return true;
	}

	PacketType::PacketTypeFinal Packet::getType() {
		return m_type;
	}

	void Packet::display() {
		for(unsigned int i=0; i<m_bufferCurrSize; i++) {
			printf("%x : %x\n", i, m_buffer[i]);
			fflush(0);
		}
	}

	Packet& Packet::operator<<(int i) {
		if(m_bufferCurrSize+sizeof(int) < m_bufferAllocSize) {
			m_buffer = (char*)realloc(m_buffer, m_bufferAllocSize+PACKET_BUFFER_ALLOC);
			m_bufferAllocSize += PACKET_BUFFER_ALLOC;
		}
		memcpy((void*)(m_buffer+m_bufferCurrSize), (void*)&i, sizeof(int));
		m_bufferCurrSize += sizeof(int);
	    return *this;
	}

	Packet& Packet::operator<<(float i) {
		if(m_bufferCurrSize+sizeof(float) < m_bufferAllocSize) {
			m_buffer = (char*)realloc(m_buffer, m_bufferAllocSize+PACKET_BUFFER_ALLOC);
			m_bufferAllocSize += PACKET_BUFFER_ALLOC;
		}
		memcpy((void*)(m_buffer+m_bufferCurrSize), (void*)&i, sizeof(float));
		m_bufferCurrSize += sizeof(float);
	    return *this;
	}

	Packet& Packet::operator<<(std::string s) {
		//size of string
		int size = s.length();
		if(m_bufferCurrSize+size*sizeof(char)+sizeof(int) < m_bufferAllocSize) {
			m_buffer = (char*)realloc(m_buffer, m_bufferAllocSize+PACKET_BUFFER_ALLOC);
			m_bufferAllocSize += PACKET_BUFFER_ALLOC;
		}
		memcpy((void*)(m_buffer+m_bufferCurrSize), (void*)&size, sizeof(int));
		m_bufferCurrSize += sizeof(int);
		memcpy((void*)(m_buffer+m_bufferCurrSize), (void*)s.c_str(), size*sizeof(char));
		m_bufferCurrSize += size*sizeof(char);
		return *this;
	}

	Packet& Packet::operator>>(int* i) {
		memcpy((void*)i, (void*)(m_buffer+m_readerCursor), sizeof(int));
		m_readerCursor +=  sizeof(int);
	    return *this;
	}

	Packet& Packet::operator>>(float* i) {
		memcpy((void*)i, (void*)(m_buffer+m_readerCursor), sizeof(float));
		m_readerCursor +=  sizeof(float);
	    return *this;
	}

	Packet& Packet::operator>>(std::string* s) {
		int size;
		memcpy((void*)&size, (void*)(m_buffer+m_readerCursor), sizeof(int));
		m_readerCursor += sizeof(int);
		char str[size+1];
		memcpy((void*)str, (void*)(m_buffer+m_readerCursor), size*sizeof(char));
		m_readerCursor += size*sizeof(char);
		str[size] = '\0';
		s->assign(str);
		return *this;
	}


}


