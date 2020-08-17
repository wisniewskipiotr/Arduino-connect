import socket 
import threading
import json
import influx_test_database as ifdb
import datetime
#import obliczenia


HEADER = 2048                          # header to receive right data
PORT = 8090                            # port where we communicate
SERVER = '192.168.0.100'                # server is on my computer

ADDR = (SERVER, PORT)                                   
FORMAT = 'utf-8'
DISCONNECT_MESSAGE = "!DISCONNECT"

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # AF_INET - IPV4, SOCK_STREAM - TCP
server.bind(ADDR)
buffer = []
db_name = 'przeplywomierz'


def obliczenia(message):
    print("zaczynam oblicznia")
    json_setup = json.loads(message)
    if json_setup["sensor_p1"] > 7:
        json_setup["ez1"] = '1'
    else: 
        json_setup["ez1"] = '0'
        
    if json_setup["sensor_p2"] > 7:
        json_setup["ez2"] = '1'
    else: 
        json_setup["ez2"] = '0'
            
    if json_setup["sensor_p3"] > 7:
        json_setup["ez3"] = '1'
    else: 
        json_setup["ez3"] = '0'

    print("w trakcie oblicznia", )
    
    print("koncze oblicznia")
    return (json_setup)



def handle_client(conn, addr):
    print(f"[NEW CONNECTION] {addr} connected.")
    try:
        #print('message1')
        #clientSocket, address = server.accept()
        #print('message2')
        #data = clientSocket.recv(HEADER)
        #print('message3')
        #message = json.load(data.decode)
        print('message') 
        message = conn.recv(HEADER).decode(FORMAT)
        print('message' + message)
        if(message):

            #print(size(message))
            #print(addr[0])
            try:
                ifdb.setup_server_json(message,addr,db_name)
                print(f"Stworzono baze danych o nazwie:{db_name}")
            except:
                #json_setup = json.loads(message) 
                json_setup = obliczenia(message)
 
                table_name = json_setup['table_name']

                #now2 = datetime.now()
                json_body = {
                        "measurement": table_name,
                        "tags": {
                            "name": table_name
                        },
                        "fields": {
                            "p1" : json_setup["sensor_p1"],
                            "p2" : json_setup['sensor_p2'],
                            "p3" : json_setup["sensor_p3"],
                            "z1" : json_setup["ez1"],
                            "z2" : json_setup["ez2"],
                            "z3" : json_setup["ez3"],
                            "p" : json_setup["pressure"],
                            "dew" : json_setup["dew_point"],
                            "current time" : datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")
                        }
                            }  
                
                print("przesyłane dane")
                print(json_body)
                
                buffer.append(json_body)
                # jak buffer zawiera 3 wiadomosci to dodaj
                
                if len(buffer) == 3:
                    ifdb.loop_server_json(buffer,addr,db_name)
                    buffer.clear()
        else: 
            print("wiadomosc jest pusta ")
    except:
        print('handle_client problem ')


def start():
    server.listen()
    print(f"[LISTENING] Server is listening on {SERVER}")
    while True:
        conn, addr = server.accept()
        thread = threading.Thread(target=handle_client, args=(conn, addr))
        thread.start()
        print(f"[ACTIVE CONNECTIONS] {threading.activeCount() - 1}")

if __name__ == '__main__':
    print("[STARTING] server is starting...")
    start()

