#ifndef NETWORKPROTOCOLTNFS
#define NETWORKPROTOCOLTNFS

#include "networkProtocol.h"
#include "sio.h"
#include "tnfslib.h"

class networkProtocolTNFS : public networkProtocol
{
public:
    networkProtocolTNFS();
    virtual ~networkProtocolTNFS();

    virtual bool open(EdUrlParser *urlParser, cmdFrame_t *cmdFrame);
    virtual bool close();
    virtual bool read(uint8_t *rx_buf, unsigned short len);
    virtual bool write(uint8_t *tx_buf, unsigned short len);
    virtual bool status(uint8_t *status_buf);
    virtual bool special(uint8_t *sp_buf, unsigned short len, cmdFrame_t *cmdFrame);
    virtual bool del(EdUrlParser *urlParser, cmdFrame_t *cmdFrame);
    virtual bool rename(EdUrlParser *urlParser, cmdFrame_t *cmdFrame);
    virtual bool mkdir(EdUrlParser *urlParser, cmdFrame_t *cmdFrame);
    virtual bool rmdir(EdUrlParser *urlParser, cmdFrame_t *cmdFrame);

    virtual bool special_supported_00_command(unsigned char comnd);

private:
    bool block_read(uint8_t *rx_buf, unsigned short len);
    bool block_write(uint8_t *tx_buf, unsigned short len);
    unsigned char status_dir();

    tnfsMountInfo mountInfo;
    int16_t fileHandle;
    string filename;
    string directory;
    string path;
    tnfsStat fileStat;
    char entryBuf[256];
    char aux1;
    char aux2;
    size_t comma_pos;
    string rnTo;
    bool dirEOF=false;
};

#endif /* NETWORKPROTOCOLTNFS */