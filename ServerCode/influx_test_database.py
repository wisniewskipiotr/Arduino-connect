import influxdb
import json
from datetime import datetime


def setup_server_json(message,addr,now):
    
    json_setup = json.loads(message) 
    name_db = now
    dbuser = "admin2"
    dbuser_password = "admin"
    client = influxdb.InfluxDBClient('localhost',8086,dbuser,dbuser_password,name_db)
    #client.switch_user(dbuser, dbuser_password)
    json_body = [
        {
            "measurement": json_setup['table_name'],
            "tags": {
                "host": "Setup---",
                "name": json_setup['name']
            },
            "fields": {
                "work_voltage": json_setup['work voltage[V]'],
                "resistor_value": json_setup['resistor value'],
                "dew_point":json_setup['dew_point']
            }
        }        
    ] 
    
    client.create_database(now)
    
    client.switch_database(now)
    
    client.write_points(json_body)
    
    
def loop_server_json(buffer, addr,now):
    print("mam wyslac")

    client = influxdb.InfluxDBClient('localhost',8086,"admin2","admin",now,retries=0);
    print("wczytalem")
    client.switch_database(now)
    client.write_points(buffer,'ms',protocol=u'json')
    print("wyslalem")
        

    
    
if __name__ == '__main__':
    setup_server_json('{"name":"192.168.0.102","work voltage[V]":"200","resistor value":"2000","current time":"302d:302d:302d 302d.302d.304d"}','192.168.0.101' )
    loop_server_json('{"sensor_p1":"192.168.0.102","sensor_p2":"250","sensor_p3":"2000","sensor_4":"22","sensor_5":"44", "current time":"2929u4646","solenoid value":"3","module":"false"}','192.168.0.101' )
