//
//  errors.h
//  MicroSSH
//
//  Created by Alagris on 27/11/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#ifndef errors_h
#define errors_h

enum mshError{
    MSH_SUCCESS,
    MSH_SERV_SOCKET_OPEN_FAIL,
    MSH_SERV_SOCKET_BIND_FAIL,
    MSH_SERV_SOCKET_READ_FAIL,
    MSH_SERV_SOCKET_WRITE_FAIL,
    MSH_SERV_CONNECTION_FAIL,
    MSH_SERV_LISTEN_FAIL,
    MSH_CONN_READ_FAIL,
    MSH_CONN_WRITE_FAIL,
    MSH_CONN_CLOSE_FAIL,
    MSH_CLIENT_SOCKET_OPEN_FAIL,
    MSH_HOST_RESOLVE_FAIL,
    MSH_FILE_OPEN_FAIL,
    MSH_FILE_WRITE_FAIL,
    MSH_FILE_READ_FAIL,
    
};

#endif /* errors_h */
