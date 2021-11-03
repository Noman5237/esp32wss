/**
 * @file: ws_server.h
 * @author: Noman5237
 * @date: 28/10/2021; 02:13
 */


#ifndef ESPWSS_WS_SERVER_H
#define ESPWSS_WS_SERVER_H

#define THRUST 0
#define ROLL 1
#define PITCH 2
#define YAW 3

extern int ws_server_fc_input[4];

/**
 * Start the websocket server to receive data
 */
void ws_server_start();

void ws_server_fc_input_format();

#endif  //ESPWSS_WS_SERVER_H