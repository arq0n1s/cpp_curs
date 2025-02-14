#include <iostream>


class IConnection{
protected:
    static bool m_is_connected;
public:
    virtual ~IConnection() = default;
    virtual void connect()=0;
    virtual bool is_connected()=0;
};

class CelularConnection: public IConnection {
public:
    CelularConnection();

    void connect() override{
        m_is_connected = true;
    }
};

class WiFiConnection: public IConnection {
public:
    WiFiConnection();

    void connect() override{
        m_is_connected = true;
    }
};

class TCP_Connection{
    IConnection *m_tcp_connection;
public:
    TCP_Connection(IConnection *connection){
        m_tcp_connection = connection;
    }
    bool open_connection(){
        std::cout << "connection is opened" << std::endl;
        m_tcp_connection->connect();
        return m_tcp_connection->is_connected();
    }
};

class HTTP_Connection{
    TCP_Connection m_tcp;
public: 
    HTTP_Connection(IConnection *connection) : m_tcp(connection) {};
    bool do_get_request(std::string url){
        m_tcp.open_connection();
        return true;
    }
};


int main(){
    std::cout << "work" << std::endl;

    TCP_Connection tcp;
    tcp.open_connection();

    HTTP_Connection http;
    http.do_get_request("ajjirldmnsdlfjk");

}