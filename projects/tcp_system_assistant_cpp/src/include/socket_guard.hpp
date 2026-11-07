#pragma once
#include <unistd.h>

class SocketGuard
{
	public:
		SocketGuard(int fd) : m_fd(fd)
		{}

        SocketGuard(const SocketGuard &other) = delete;
        SocketGuard& operator=(const SocketGuard &other) = delete;

		~SocketGuard()
		{
			close(m_fd);
		}
	private:
		int m_fd;	
};

