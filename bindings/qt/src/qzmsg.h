/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
#ifndef Q_ZMSG_H
#define Q_ZMSG_H

#include "qzebra.h"

class QT_ZEBRA_EXPORT QZmsg : public QObject
{
    Q_OBJECT
public:

    //  Copy-construct to return the proper wrapped c types
    QZmsg (zmsg_t *self, QObject *qObjParent = 0);

    //  Create a new empty message object
    explicit QZmsg (QObject *qObjParent = 0);

    //  Receive message from socket, returns zmsg_t object or NULL if the recv   
    //  was interrupted. Does a blocking recv. If you want to not block then use 
    //  the zloop class or zmsg_recv_nowait or zmq_poll to check for socket input
    //  before receiving.                                                        
    static QZmsg* recv (void *source, QObject *qObjParent = 0);

    //  Load/append an open file into new message, return the message.
    //  Returns NULL if the message could not be loaded.              
    static QZmsg* load (FILE *file, QObject *qObjParent = 0);

    //  Decodes a serialized message buffer created by zmsg_encode () and returns
    //  a new zmsg_t object. Returns NULL if the buffer was badly formatted or   
    //  there was insufficient memory to work.                                   
    static QZmsg* decode (const byte *buffer, size_t bufferSize, QObject *qObjParent = 0);

    //  Generate a signal message encoding the given status. A signal is a short
    //  message carrying a 1-byte success/failure code (by convention, 0 means  
    //  OK). Signals are encoded to be distinguishable from "normal" messages.  
    static QZmsg* newSignal (byte status, QObject *qObjParent = 0);

    //  Destroy a message object and all frames it contains
    ~QZmsg ();

    //  Send message to destination socket, and destroy the message after sending
    //  it successfully. If the message has no frames, sends nothing but destroys
    //  the message anyhow. Nullifies the caller's reference to the message (as  
    //  it is a destructor).                                                     
    int send (void *dest);

    //  Send message to destination socket as part of a multipart sequence, and 
    //  destroy the message after sending it successfully. Note that after a    
    //  zmsg_sendm, you must call zmsg_send or another method that sends a final
    //  message part. If the message has no frames, sends nothing but destroys  
    //  the message anyhow. Nullifies the caller's reference to the message (as 
    //  it is a destructor).                                                    
    int sendm (void *dest);

    //  Return size of message, i.e. number of frames (0 or more).
    size_t size ();

    //  Return total size of all frames in message.
    size_t contentSize ();

    //  Return message routing ID, if the message came from a ZMQ_SERVER socket.
    //  Else returns zero.                                                      
    quint32 routingId ();

    //  Set routing ID on message. This is used if/when the message is sent to a
    //  ZMQ_SERVER socket.                                                      
    void setRoutingId (quint32 routingId);

    //  Push frame to the front of the message, i.e. before all other frames.  
    //  Message takes ownership of frame, will destroy it when message is sent.
    //  Returns 0 on success, -1 on error. Deprecates zmsg_push, which did not 
    //  nullify the caller's frame reference.                                  
    int prepend (QZframe *frameP);

    //  Add frame to the end of the message, i.e. after all other frames.      
    //  Message takes ownership of frame, will destroy it when message is sent.
    //  Returns 0 on success. Deprecates zmsg_add, which did not nullify the   
    //  caller's frame reference.                                              
    int append (QZframe *frameP);

    //  Remove first frame from message, if any. Returns frame, or NULL.
    QZframe * pop ();

    //  Push block of memory to front of message, as a new frame.
    //  Returns 0 on success, -1 on error.                       
    int pushmem (const void *src, size_t size);

    //  Add block of memory to the end of the message, as a new frame.
    //  Returns 0 on success, -1 on error.                            
    int addmem (const void *src, size_t size);

    //  Push string as new frame to front of message.
    //  Returns 0 on success, -1 on error.           
    int pushstr (const QString &string);

    //  Push string as new frame to end of message.
    //  Returns 0 on success, -1 on error.         
    int addstr (const QString &string);

    //  Push formatted string as new frame to front of message.
    //  Returns 0 on success, -1 on error.                     
    int pushstrf (const QString &param);

    //  Push formatted string as new frame to end of message.
    //  Returns 0 on success, -1 on error.                   
    int addstrf (const QString &param);

    //  Pop frame off front of message, return as fresh string. If there were
    //  no more frames in the message, returns NULL.                         
    QString popstr ();

    //  Push encoded message as a new frame. Message takes ownership of    
    //  submessage, so the original is destroyed in this call. Returns 0 on
    //  success, -1 on error.                                              
    int addmsg (QZmsg *msgP);

    //  Remove first submessage from message, if any. Returns zmsg_t, or NULL if
    //  decoding was not succesful.                                             
    QZmsg * popmsg ();

    //  Remove specified frame from list, if present. Does not destroy frame.
    void remove (QZframe *frame);

    //  Set cursor to first frame in message. Returns frame, or NULL, if the
    //  message is empty. Use this to navigate the frames as a list.        
    QZframe * first ();

    //  Return the next frame. If there are no more frames, returns NULL. To move
    //  to the first frame call zmsg_first(). Advances the cursor.               
    QZframe * next ();

    //  Return the last frame. If there are no frames, returns NULL.
    QZframe * last ();

    //  Save message to an open file, return 0 if OK, else -1. The message is  
    //  saved as a series of frames, each with length and data. Note that the  
    //  file is NOT guaranteed to be portable between operating systems, not   
    //  versions of CZMQ. The file format is at present undocumented and liable
    //  to arbitrary change.                                                   
    int save (FILE *file);

    //  Serialize multipart message to a single buffer. Use this method to send  
    //  structured messages across transports that do not support multipart data.
    //  Allocates and returns a new buffer containing the serialized message.    
    //  To decode a serialized message buffer, use zmsg_decode ().               
    size_t encode (byte **buffer);

    //  Create copy of message, as new message object. Returns a fresh zmsg_t
    //  object. If message is null, or memory was exhausted, returns null.   
    QZmsg * dup ();

    //  Send message to zsys log sink (may be stdout, or system facility as
    //  configured by zsys_set_logstream).                                 
    void print ();

    //  Return true if the two messages have the same number of frames and each  
    //  frame in the first message is identical to the corresponding frame in the
    //  other message. As with zframe_eq, return false if either message is NULL.
    bool eq (QZmsg *other);

    //  Return signal value, 0 or greater, if message is a signal, -1 if not.
    int signal ();

    //  Probe the supplied object, and report if it looks like a zmsg_t.
    static bool is (void *self);

    //  Self test of this class.
    static void test (bool verbose);

    zmsg_t *self;
};
#endif //  Q_ZMSG_H
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
