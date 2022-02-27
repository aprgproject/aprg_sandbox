class SerialPort
{
public:
    int set_interface_attribs (int speed, int parity);
    void set_blocking (int should_block);
    void openSerial();
    void closeSerial();
    void writeSerial(unsigned char* buf, unsigned size);
    void readSerial(unsigned char* buf, unsigned size);
    int getFd();
    int getBytesRead();
private:
    int m_fd;
    int m_bytesRead;
};
